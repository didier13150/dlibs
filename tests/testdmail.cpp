/******************************************************************************
 *      ____              ____    _       _   _                               *
 *     /# /_\_           |  _ \  (_)   __| | (_)   ___   _ __                 *
 *    |  |/o\o\          | | | | | |  / _` | | |  / _ \ | '__|                *
 *    |  \\_/_/          | |_| | | | | (_| | | | |  __/ | |                   *
 *   / |_   |            |____/  |_|  \__,_| |_|  \___| |_|                   *
 *  |  ||\_ ~|                                                                *
 *  |  ||| \/                                                                 *
 *  |  |||       Project : DLibs : usefull tools for C++ programming          *
 *  \//  |                                                                    *
 *   ||  |       Developper : Didier FABERT <didier.fabert@gmail.com>         *
 *   ||_  \      Date : 2009, April                                           *
 *   \_|  o|                                             ,__,                 *
 *    \___/      Copyright (C) 2009 by didier fabert     (oo)____             *
 *     ||||__                                            (__)    )\           *
 *     (___)_)   File : testdmail.cpp                       ||--|| *          *
 *                                                                            *
 *   This program is free software; you can redistribute it and/or modify     *
 *   it under the terms of the GNU General Public License as published by     *
 *   the Free Software Foundation; either version 3 of the License, or        *
 *   (at your option) any later version.                                      *
 *                                                                            *
 *   This program is distributed in the hope that it will be useful,          *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of           *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the            *
 *   GNU General Public License for more details.                             *
 *                                                                            *
 *   You should have received a copy of the GNU General Public License        *
 *   along with this program; if not, write to the                            *
 *   Free Software Foundation, Inc.,                                          *
 *   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.             *
 *                                                                            *
 *   Unit Test for DMail                                                      *
 *                                                                            *
 ******************************************************************************/

#include <cstdlib>
#include <iostream>
#include <fstream>
#include "testdmail.h"
#include "dmail.h"
#include "test.h"

static const char * mail1 = 
"Return-Path: root@smtp.example.com\n"
"Received: from smtp.example.com (LHLO smtp.example.com) (195.216.193.6) by\n"
" smtp.example.com with LMTP; Mon, 24 Aug 2015 17:45:28 +0200 (CEST)\n"
"Received: from localhost (localhost.localdomain [127.0.0.1])\n"
"	by smtp.example.com (Postfix) with ESMTP id 749987E0B73\n"
"	for <me@example.com>; Mon, 24 Aug 2015 17:45:28 +0200 (CEST)\n"
"X-Virus-Scanned: amavisd-new at example.com\n"
"X-Spam-Flag: NO\n"
"X-Spam-Score: -7.506\n"
"X-Spam-Level:\n"
"X-Spam-Status: No, score=-7.506 tagged_above=-10 required=6.6\n"
"	tests=[AM.WBL=-10, BAYES_50=0.8, DKIM_ADSP_NXDOMAIN=0.9,\n"
"	NO_DNS_FOR_FROM=0.001, RDNS_NONE=0.793] autolearn=no\n"
"Received: from smtp.example.com ([127.0.0.1])\n"
"	by localhost (smtp.example.com [127.0.0.1]) (amavisd-new, port 10024)\n"
"	Return-Path: root@smtp.example.com\n"
"Received: from smtp.example.com (LHLO smtp.example.com) (195.216.193.6) by\n"
" smtp.example.com with LMTP; Mon, 24 Aug 2015 17:45:28 +0200 (CEST)\n"
"Received: from localhost (localhost.localdomain [127.0.0.1])\n"
"	by smtp.example.com (Postfix) with ESMTP id 749987E0B73\n"
"	for <me@example.com>; Mon, 24 Aug 2015 17:45:28 +0200 (CEST)\n"
"X-Virus-Scanned: amavisd-new at example.com\n"
"X-Spam-Flag: NO\n"
"X-Spam-Score: -7.506\n"
"X-Spam-Level:\n"
"X-Spam-Status: No, score=-7.506 tagged_above=-10 required=6.6\n"
"	tests=[AM.WBL=-10, BAYES_50=0.8, DKIM_ADSP_NXDOMAIN=0.9,\n"
"	NO_DNS_FOR_FROM=0.001, RDNS_NONE=0.793] autolearn=no\n"
"Received: from smtp.example.com ([127.0.0.1])\n"
"	by localhost (smtp.example.com [127.0.0.1]) (amavisd-new, port 10024)\n"
"	with ESMTP id 1ofOHyovyb64 for <me@example.com>;\n"
"	Mon, 24 Aug 2015 17:45:23 +0200 (CEST)\n"
"Received: from smtp.example.com (unknown [46.218.176.171])\n"
"	by smtp.example.com (Postfix) with ESMTPS id 8BE397E0AA4\n"
"	for <me@example.com>; Mon, 24 Aug 2015 17:45:23 +0200 (CEST)\n"
"Received: from localhost.localdomain (localhost [127.0.0.1])\n"
"	by smtp.example.com (8.15.2/8.14.8) with SMTP id t7OFjJcd016987\n"
"	for root@localhost; Mon, 24 Aug 2015 17:45:21 +0200\n"
"Message-Id: <201508241545.t7OFjJcd016987@smtp.example.com>\n"
"Subject: DLibs test\n"
"From: root@smtp.example.com\n"
"To: root@smtp.example.com\n"
"Date: Mon, 24 Aug 2015 17:45:22 +0200\n"
"MIME-Version: 1.0\n"
"Content-Type: text/plain; charset=utf-8\n"
"Content-Transfer-Encoding: quoted-printable\n"
"\n"
"This is just a simple DLibs test, SMTP partwith ESMTP id 1ofOHyovyb64 for <me@example.com>;\n"
"	Mon, 24 Aug 2015 17:45:23 +0200 (CEST)\n"
"Received: from smtp.example.com (unknown [46.218.176.171])\n"
"	by smtp.example.com (Postfix) with ESMTPS id 8BE397E0AA4\n"
"	for <me@example.com>; Mon, 24 Aug 2015 17:45:23 +0200 (CEST)\n"
"Received: from localhost.localdomain (localhost [127.0.0.1])\n"
"	by smtp.example.com (8.15.2/8.14.8) with SMTP id t7OFjJcd016987\n"
"	for root@localhost; Mon, 24 Aug 2015 17:45:21 +0200\n"
"Message-Id: <201508241545.t7OFjJcd016987@smtp.example.com>\n"
"Subject: DLibs test\n"
"From: root@smtp.example.com\n"
"To: root@smtp.example.com\n"
"Date: Mon, 24 Aug 2015 17:45:22 +0200\n"
"MIME-Version: 1.0\n"
"Content-Type: text/plain; charset=utf-8\n"
"Content-Transfer-Encoding: quoted-printable\n"
"\n"
"This is just a simple DLibs test, SMTP part\n";

static const char * mail2 = 
"Return-Path: toto@example.com\n"
"Received: from smtp.example.com (LHLO smtp.example.com) (192.168.0.69) by\n"
" smtp.example.com with LMTP; Tue, 26 May 2015 13:13:13 +0200 (CEST)\n"
"Received: from localhost (localhost.localdomain [127.0.0.1])\n"
"	by smtp.example.com (Postfix) with ESMTP id CFF517E00C4\n"
"	for <noreply@example.com>; Tue, 26 May 2015 13:13:13 +0200 (CEST)\n"
"X-Virus-Scanned: amavisd-new at example.com\n"
"X-Spam-Flag: NO\n"
"X-Spam-Score: 1.0\n"
"X-Spam-Level: ***\n"
"X-Spam-Status: NO, score=1.0 tagged_above=-10 required=6.6\n"
"	tests=[BAYES_50=0.8, DEAR_SOMETHING=1.973, DNS_FROM_AHBL_RHSBL=2.699,\n"
"	HTML_FONT_LOW_CONTRAST=0.001, HTML_MESSAGE=0.001,\n"
"	MIME_BASE64_TEXT=1.741, RCVD_IN_BRBL_LASTEXT=1.449, RCVD_IN_PBL=3.335,\n"
"	RCVD_IN_SORBS_DUL=0.001, RCVD_IN_XBL=0.375, RDNS_NONE=0.793]\n"
"	autolearn=no\n"
"Received: from smtp.example.com ([127.0.0.1])\n"
"	by localhost (smtp.example.com [127.0.0.1]) (amavisd-new, port 10024)\n"
"	with ESMTP id aPirvKaebWHp for <noreply@example.com>;\n"
"	Tue, 26 May 2015 13:13:09 +0200 (CEST)\n"
"Received: from [192.168.0.69] (unknown [192.168.0.69])\n"
"	by smtp.example.com (Postfix) with ESMTP id 480EA7E00A2\n"
"	for <noreply@example.com>; Tue, 26 May 2015 13:13:08 +0200 (CEST)\n"
"MIME-Version: 1.0\n"
"From: <toto@example.com>\n"
"To: noreply@example.com\n"
"Date: Tue, 26 May 2015 18:13:05 +0700\n"
"Subject: Test (ref: 001) from example.com\n"
"Content-Type: multipart/mixed;\n"
"	boundary=\"--boundary_652_df201e59-c0ab-40cd-a16f-94d02c05ead0\"\n"
"Message-ID: <ae321c14-ff48-49ce-8272-8d7bcff81947@example.com>\n"
"\n"
"----boundary_652_df201e59-c0ab-40cd-a16f-94d02c05ead0\n"
"Content-Type: multipart/alternative;\n"
"	boundary=\"--boundary_651_39f42539-b48b-435f-a4c5-202a52933fdb\"\n"
"\n"
"----boundary_651_39f42539-b48b-435f-a4c5-202a52933fdb\n"
"MIME-Version: 1.0\n"
"Content-Type: text/plain; charset=\"us-ascii\"\n"
"Content-Transfer-Encoding: 7bits\n"
"\n"
"Hello world !\n"
"\n"
"----boundary_651_39f42539-b48b-435f-a4c5-202a52933fdb\n"
"MIME-Version: 1.0\n"
"Content-Type: text/html; charset=\"us-ascii\"\n"
"Content-Transfer-Encoding: 7bits\n"
"\n"
"<html><body>Hello world !</body></html>\n"
"\n"
"----boundary_651_39f42539-b48b-435f-a4c5-202a52933fdb--\n"
"\n"
"----boundary_652_df201e59-c0ab-40cd-a16f-94d02c05ead0\n"
"Content-Type: multipart/mixed;\n"
"	boundary=\"--boundary_653_7327e01c-6c7b-419e-aa3d-283d0c0828a2\"\n"
"\n"
"----boundary_653_7327e01c-6c7b-419e-aa3d-283d0c0828a2\n"
"Content-Type: application/msword; name=\"file.txt\"\n"
"Content-Transfer-Encoding: base64\n"
"Content-Disposition: attachment\n"
"\n"
"SGVsbG8gd29ybGQgIQo=\n"
"\n"
"----boundary_653_7327e01c-6c7b-419e-aa3d-283d0c0828a2\n"
"Content-Type: application/msword; name=\"file2.txt\"\n"
"Content-Transfer-Encoding: base64\n"
"Content-Disposition: attachment\n"
"\n"
"SGVsbG8gWW91IGJhc2U2NCBmaWxlLnR4dCAhCg==\n"
"\n"
"----boundary_653_7327e01c-6c7b-419e-aa3d-283d0c0828a2\n"
"\n"
"----boundary_653_7327e01c-6c7b-419e-aa3d-283d0c0828a2--\n"
"\n"
"------boundary_652_df201e59-c0ab-40cd-a16f-94d02c05ead0--\n";

void TestDMail::constructor_test()
{
	DMail mail;
	DMailPartList partlist;
	
	//std::cout << std::endl;
	mail.setMail( mail1 );
	partlist = mail.getMailPartList();
	mail.setMail( mail2 );
	partlist = mail.getMailPartList();
	/*for( DMailPartList::iterator it = partlist.begin() ; it != partlist.end() ; ++it ) {
		std::cout << "Type: \"" << it->getType() << "\", ";
		std::cout << "Charset: \"" << it->getCharset() << "\", ";
		std::cout << "Encoding: \"" << it->getTransfertEncoding() << "\"";
		std::cout << std::endl;
	}*/
}

void TestDMail::clear_test()
{
	DMail mail;
	DMailPartList partlist;
	//DMailPart part;
	std::cout << std::endl;
	mail.setMail( mail2 );
	mail.setMail( mail2 );
	TEST_ASSERT_MSG( mail.getHeader( "subject" ) == "Test (ref: 001) from example.com", "Headers are not cleared between two mail" )
}

void TestDMail::mail_subject_test()
{
	DString str = "=?utf-8?B?UkU6IENvb3Jkb25uw6llcyBkdSBjb25zdWx0YW50IGRlIHZvdHJlIE9mZnJl?= =?utf-8?B?IDogRlI2OSBDT05EUklFVSAtIEZSNjkgU0FJTlQtR0VPUkdFUy1ERS1SRU5F?= =?utf-8?Q?INS_-_TEST?=";
	std::cout << std::endl;
	TEST_ASSERT_MSG( DMail::decodeSubject( str ) == "RE: Coordonnées du consultant de votre Offre : FR69 CONDRIEU - FR69 SAINT-GEORGES-DE-RENEINS_-_TEST", "Bad UTF-8 Base64 decode process" )	
	
	str = "=?iso-8859-1?Q?Automatische_Antwort:_Vos_statistiques_de_d=E9poses_quotid?= =?iso-8859-1?Q?iennes.?=";
	TEST_ASSERT_MSG( DMail::decodeSubject( str ) == "Automatische_Antwort:_Vos_statistiques_de_déposes_quotidiennes.", "Bad ISO-8859 Quoted Printable decode process" )
	
	str = "=?UTF-8?Q?RE:_Coordonn=C3=A9es_du_consultant_de?= =?UTF-8?Q?_votre_Offre_:_FR28_CHATEAUDUN_-?= =?UTF-8?Q?_PL60_POZNAN_-_TEST?=";
	TEST_ASSERT_MSG( DMail::decodeSubject( str ) == "RE:_Coordonnées_du_consultant_de_votre_Offre_:_FR28_CHATEAUDUN_-_PL60_POZNAN_-_TEST", "Bad UTF-8 Quoted Printable decode process" )
}

void TestDMail::boundary_test()
{
	DString boundary = DMail::getRandomBoundary();
	TEST_ASSERT_MSG( boundary.match( "----=_Part_-[0-9]{9}_[0-9]{9}.[0-9]{10,18}" ), "Wrong random boundary" )
}

int main()
{
	TestDMail ets;
#ifdef TEST_HTML
	std::ofstream file;
	Test::HtmlOutput html;

	file.open( "dmail.html" );
	ets.run( html );
	html.generate( file, true, "DMail" );
	file.close();
#endif

#ifdef TEST_STDOUT
	Test::TextOutput output( Test::TextOutput::Verbose, std::cout );

	return ets.run( output ) ? EXIT_SUCCESS : EXIT_FAILURE;
#endif
	return EXIT_SUCCESS;
}
