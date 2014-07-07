/******************************************************************************
 * Unit Test for DLog class                                                   *
 ******************************************************************************/

#include <iostream>
#include <cstdlib>

#include "dlibs.h" // replace it by #include <dlibs/dlibs.h>

using namespace std;

int testdlog ( bool fileauto )
{
    DString message1, message2;
    DLogger * log = DLogger::getInstance();
    DLogParams params;

#ifdef DLIBS_HAVE_MYSQL
    DString dbtype = "dmysql";
#elif DLIBS_HAVE_PGSQL
    DString dbtype = "dpgsql";
#else
    DString dbtype = "dsqlite";
#endif

    if ( !fileauto )
    {
        cout << "Log file to write : ";
        cin >> params.specific["filename"];
    }

    else
    {
        params.specific["filename"] = "/tmp/testdlog.log";
    }


    if ( !log->addUserVar ( "%SYSTEM_ID" ) )
    {
        std::cout << "Cannot insert this user defined variable" << std::endl;
    }

    log->setupUserVar ( "%SYSTEM_ID", "MYSELF" );

    message1 = "debug log text which must be printed only on stdout";
    message2 = "info log text which must be printed on stdout, database, "
               "socket, syslog(/var/log/messages) and file";


    if ( dbtype == "dmysql" )
    {
        // specific to dmysql
        params.specific["dbtype"] = "dmysql";
        params.specific["dbuser"] = "dlibs";
        params.specific["dbpassword"] = "dlibspw";
        params.specific["dbhost"] = "localhost";
        params.specific["dbbase"] = "dlibs";
    }

    else if ( dbtype == "dsqlite" )
    {
        // specific to dsqlite
        params.specific["dbtype"] = "dsqlite";
        params.specific["dbbase"] = "/tmp/testdlog.db";
        params.specific["dbcreate"] = "CREATE TABLE applog (date, level, message);";
    }

    // params for file log engine
    params.mode = DLogShared::OPENCLOSE; // can be DLogShared::PERSISTANT;

    params.minlevel = DLogShared::INFO;

    params.optionnal["dateformat"] = "%Y-%m-%d %H-%M-%S";

    params.optionnal["pattern"] = "%SYSTEM_ID %DATE - %TYPE - %MESSAGE";

    // create file log engine
    DLogEngine * filelog = log->addLogEngine ( DLogEngine::FILE, params );

    // params for stdout log engine
    params.minlevel = DLogShared::DEBUG;

    // create stdout log engine
    log->addLogEngine ( DLogEngine::STDOUT, params );

    // params for database log engine
    params.minlevel = DLogShared::INFO;

    params.optionnal["dateformat"] = DString::getFormat ( DString::ISO_DATETIME_T );

    params.optionnal["pattern"] = "INSERT INTO applog(date, level, message) VALUES(\"%DATE\", \"%TYPE\", \"%MESSAGE\");";

    // create database log engine
    DLogEngine * dblog = log->addLogEngine ( DLogEngine::DATABASE, params );

    // params for socket log engine
    params.mode = DLogShared::PERSISTANT;

    params.optionnal["dateformat"] = "%Y-%m-%d %H-%M-%S";

    params.optionnal["pattern"] = "%DATE - %TYPE - %MESSAGE";

    params.specific["sockhost"] = "localhost:12345";

    // create socket log engine
    log->addLogEngine ( DLogEngine::SOCKET, params );

    // params for syslog log engine
    params.specific["appname"] = "testdlog";

    // create syslog log engine
    log->addLogEngine ( DLogEngine::SYSLOG, params );

    // unintialized engine ( test for unintialized engine pointer )
    DLogEngine * uninitializedlog;

    for ( int i = 0 ; i < 5 ; ++i )
    {
        // Remove file log engine
        if ( i == 3 )
        {
            log->removeLogEngine ( filelog );
            // gcc complains about var which may be used unitialized
            // it's just a test with an unitialized pointer to be sure this
            // class is safe.
            log->removeLogEngine ( uninitializedlog );
        }

        // Remove file database engine

        if ( i == 4 )
        {
            log->removeLogEngine ( dblog );
        }

        log->insertMessage ( message1, DLogShared::DEBUG );

        log->insertMessage ( message2, DLogShared::INFO );
        sleep ( 1 );
    }

    log->close();

    cout << "End of log writing process" << endl;
    cout << "#########################################################" << endl;
    cout << "Following is to be sure that the log process make a good job." << endl;

    DFactory<DDatabase> factory;
    DDatabaseParams dbparams;
    ifstream file;
    DString buffer;

    cout << "Read log file : " << params.specific["filename"] << endl;
    file.open ( params.specific["filename"].c_str() );

    while ( getline ( file, buffer ) )
    {
        cout << buffer << endl;
    }

    cout << "End of log file" << endl;

    cout << "Read log database" << endl;
    DDatabaseResult results;
#if WITH_EXCEPTIONS
    DFactory<DDatabase>::Register ( "dsqlite", new DSQLite ( true ) );
#else
	DFactory<DDatabase>::Register ( "dsqlite", new DSQLite () );
#endif
#ifdef DLIBS_HAVE_MYSQL
#if WITH_EXCEPTIONS
    DFactory<DDatabase>::Register ( "dmysql", new DMySQL ( true ) );
#else
    DFactory<DDatabase>::Register ( "dmysql", new DMySQL () );
#endif
#endif
#ifdef DLIBS_HAVE_PGSQL
#if WITH_EXCEPTIONS
    DFactory<DDatabase>::Register ( "dpgsql", new DPgSQL ( true ) );
#else
    DFactory<DDatabase>::Register ( "dpgsql", new DPgSQL () );
#endif
#endif
    DDatabase * db = factory.create ( dbtype );
    dbparams.base = params.specific["dbbase"];
    dbparams.user = params.specific["dbuser"];
    dbparams.password = params.specific["dbpassword"];
    dbparams.host = params.specific["dbhost"];
    std::cout << dbparams << std::endl;

    try
    {
        db->setParams ( dbparams );
        db->open();
        results = db->exec ( "SELECT * FROM applog;" );
        std::cout << results << std::endl;
        db->close();
    }

    catch ( const DException_database & e )
    {
        cout << "DException_database exception encoured" << endl;
        cout << e.what() << endl;
        cout << "base was " << dbparams.base << endl;
    }

    catch ( const DException & e )
    {
        cout << "DException exception encoured" << endl;
        cout << e.what() << endl;
    }

    catch ( ... )
    {
        cout << "Another unknow exception encoured" << endl;
    }

    delete db;

    return 0;
}
