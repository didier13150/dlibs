/******************************************************************************
 * Unit Test for DPgSQL class                                                 *
 ******************************************************************************/

#include <iostream>
#include <cstdlib>

#include "dlibs.h" // replace it by #include <dlibs/dlibs.h>

using namespace std;

int testdpgsql( bool fileauto )
{
	DPgSQL sql;
	DDatabaseParams params;
	DDatabaseResult result;
	DDatabaseRows::iterator ite;
	DDatabaseRow::iterator it;
	DString table;

	if ( fileauto )
	{
		params.base="test";
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
		params.port = "0";
	}

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