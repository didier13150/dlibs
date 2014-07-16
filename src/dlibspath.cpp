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
 *     (___)_)   File : dlibspath.cpp                       ||--|| *          *
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
 ******************************************************************************/

#include <cstdlib>
#include <getopt.h>
#include <iostream>
#include <string>
#include <unistd.h>

#include "dlibs.h"

using namespace std;

/**
 * @brief Displays the syntax of the program command line.
 */
void show_help()
{
	cout << "Syntax: dlibspath [options]" << endl;
	cout << "Options" << endl;
	cout << "  -h, --help      Print this help" << endl;
	cout << "  -v, --version   Show version" << endl;
	cout << "  --tarname       Show package name" << endl;
	cout << "  --bugreport     Show address where bug report must be sent" << endl;
	cout << "  --prefix        Show the prefix where dlibs are installed" << endl;
	
	cout << endl;
}

/**
 * @brief Parses command line options. *
 * @param int argc: number of arguments in the command line.
 * @param char ** argv: the list of arguments in the command line.
 */
void parse_options(int argc, char *argv[])
{
	int option_index = 0;
	int opt;

    // Parse arg
	while (1)
	{
		static struct option long_options[] =
		{
			{ "help",       no_argument,       0, 'h' },
			{ "version",    no_argument,       0, 'v' },
			{ "prefix",     no_argument,       0, 0   },
			{ "tarname",    no_argument,       0, 0   },
			{ "bugreport",  no_argument,       0, 0   },
			{ 0, 0, 0, 0 }
		};

        // Get optionnal argument number
		opt = getopt_long( argc, argv, "h?v", long_options, &option_index );

        // Leave the loop when all optionnal arguments have been parsed.
		if( opt < 0 )
		{
			break;
		}

		switch( opt )
		{
			case '?':
			case 'h':
			{
				show_help();
				exit(EXIT_SUCCESS);
			}
			case 'v':
			{
				cout << DLIBS_VERSION << endl;
				exit(EXIT_SUCCESS);
			}
			case 0:
			{
				if (long_options[option_index].name == std::string("prefix") )
				{
					cout << DLIBS_PREFIX_PATH << endl;
					exit(EXIT_SUCCESS);
				}
				if (long_options[option_index].name == std::string("tarname") )
				{
					cout << DLIBS_PACKAGE_NAME << "-" << DLIBS_VERSION << endl;
					exit(EXIT_SUCCESS);
				}
				if (long_options[option_index].name == std::string("bugreport") )
				{
					cout << DLIBS_BUG_REPORT << endl;
					exit(EXIT_SUCCESS);
				}
				break;
			}
			default:
			{
				show_help();
				exit(EXIT_FAILURE);
			}
		}
	}
}

int main (int argc, char *argv[])
{
	parse_options(argc, argv);
}
