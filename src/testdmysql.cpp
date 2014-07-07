/******************************************************************************
 * Unit Test for DMySQL                                                       *
 ******************************************************************************/

#include <iostream>
#include <cstdlib>
#include "dlibs.h" // replace it by #include <dlibs/dlibs.h>

using namespace std;

int testdmysql( bool fileauto )
{
	DMySQL sql;
	DDatabaseParams params;
	DDatabaseResult result;
	DDatabaseRows::iterator ite;
	DDatabaseRow::iterator it;
	DString table;

	if ( fileauto )
	{
		params.host = "localhost";
		params.user = "root";
		params.password = "obione";
		params.base = "mysql";
	}
	else
	{
		cout << "Enter the database address : ";
		cin >> params.host;
		cout << "Enter the database name : ";
		cin >> params.base;
		cout << "Enter the database user : ";
		cin >> params.user;
		cout << "Enter the database password : ";
		cin >> params.password;
	}
	params.port = "0";

	sql.setParams ( params );

	// Open MySQL connection
	result = sql.open();
	if ( result.errnb != DMySQL::SUCCESS )
	{
		cout << "Error " << result.errnb << endl;
		cout << result.error << endl;
		return 0;
	}

	cout << "Execute MySQL Queries on base " << params.base;
	cout << " which is on host " << params.host;
	cout << " with " << params.user << "/" << params.password << " account";
	cout << ", on port " << params.port << endl;

	cout << "---------------------------------------------------------" << endl;
	
	// Execute show tables query
	result = sql.exec ( "SHOW TABLES" );
	if ( result.errnb != DMySQL::SUCCESS )
	{
		cout << "Error " << result.errnb << endl;
		cout << result.error << endl;
	}
	cout << result << endl;

	cout << "---------------------------------------------------------" << endl;

	// Execute show columns query
	result = sql.exec ( "SHOW COLUMNS FROM " + table );
	if ( result.errnb != DMySQL::SUCCESS )
	{
		cout << "Error " << result.errnb << endl;
		cout << result.error << endl;
	}
	cout << result << endl;

	// Close MySQL connection
	sql.close();
	cout << "---------------------------------------------------------" << endl;
	params.host = "nohost";
	sql.setParams ( params );

	sql.useDExceptions( true );
	try
	{
		sql.open();
		result = sql.exec ( "SHOW TABLES" );
		cout << result << endl;
		sql.close();
	}
	catch (const DException_database & e)
	{
		cout << "DException_database exception encoured" << endl;
		cout << e.what() << endl;
	}
	catch (const DException & e)
	{
		cout << "DException exception encoured" << endl;
		cout << e.what() << endl;
	}
	catch ( ... )
	{
		cout << "Another unknow exception encoured" << endl;
	}
	return 0;
}