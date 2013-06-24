/******************************************************************************
 * Unit Test for DSMTP                                                        *
 ******************************************************************************/

#include <iostream>
#include <cstdlib>
#include "dlibs.h" // replace it by #include <dlibs/dlibs.h>

using namespace std;

int testdsmtp(  bool fileauto  = false )
{
	DSMTP mail;
	DSMTP::ERRNO code;
	DStringList receiverlist;
	DStringList transaction;
	DStringList::const_iterator it;
	DString sender, host, subject, text, receiver;

	if (  fileauto  )
	{
		host = "smtp://smtp.free.fr:25";
		host = "smtp://localhost:25";
		sender = "didier.fabert@free.fr";
		receiver = "didier30300@free.fr";
	}
	else
	{
		cout << "Enter the smtp server address : ";
		cin >> host;
		cout << "Enter the sender email address : ";
		cin >> sender;
		cout << "Enter the receiver email address : ";
		cin >> receiver;
	}
	
	receiverlist.push_back ( receiver );

	mail.setHost ( host );
	mail.setSender ( sender );
	mail.setReceiver ( receiverlist );
	mail.setEmail ( "DLibs test", "This is just a simple DLibs test, SMTP part" );
	cout << "sending" << endl;
	code = mail.send();
	if ( code == DSMTP::SUCCESS )
	{
		cout << "Email sent" << endl;
	}
	else
	{
		cout << mail.getLastError() << endl;
	}
	cout << "Transaction : " << endl;
	transaction = mail.getTransactionLog();
	for ( it = transaction.begin() ; it != transaction.end() ; it++ )
	{
		cout << *it << endl;
	}
	return 0;
}