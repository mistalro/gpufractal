/* Copyright (C) 2015 Dr. Michael Robb

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General License
   as published by the Free Software Foundation; either
   version 3 of the License, or (at your option) any later version.

   The program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Public License for more details.

   You should have received a copy of the GNU Public License 
   along with the GNU C Library; if not, write to the Free
   Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
   02111-1307 USA.  */

#include "fractals.h"

// --------------------------------------------------------------------------
// Basic options
// --------------------------------------------------------------------------

static const char *help_text =
"Options are:\n"
"\t-v             - Enable verbose mode\n"
"\t-f<filename>   - Read parameters file\n"
"\t-r<replayfile> - Set replay file\n"
"\t-s             - Enable server mode (will listen for events)\n"
"\t-c             - Enable client mode\n"
"\t-n<nodefile>   - Read list of remote display servers\n"
"\t-p<portno>     - Set network port (for listening server)\n"
"\t-t<dimensions> - Set texture dimensions in width and height eg. -t1024x1024\n"
"\t-w<diemnsions> - Set window dimensions in width and height eg. -w1024x1024\n"
"\t-z<imagefile>  - Set transfer texture for colouring\n"
"\t-b             - Borderless window\n"
"\t-i             - Enable CPU mode\n"
"\t-u             - Enable fullscreen mode\n"
"\t-x<location>   - Position window at screen location eg. -x512x512\n"
"\t-m             - Dump message packets\n"
"\t-R             - Set rotation angle delta\n"
"\t-T             - Set translation delta\n"
"\t-Z             - Set zoom delta\n"
"\t-W             - Set zoom wheel delta\n"
"";

// --------------------------------------------------------------------------
// Display help
// --------------------------------------------------------------------------

void CSystemParameters::DisplayHelp(int argc, const char *argv[])
{
cout << "Usage: " << argv[0] << " " << help_text;
exit(0);
}

// --------------------------------------------------------------------------
// Process command line arguments
// --------------------------------------------------------------------------

void CSystemParameters::ProcessArguments( int argc, const char *argv[])
{
for (int idx = 1; idx < argc; idx++)
        {
        if (argv[idx][0] == '-')
                {
                switch( argv[idx][1] )
                        {
                        case '-':
                                DisplayHelp(argc, argv);
                                break;

                        case 'v':
                                m_echomode = true;
                                g_verbose = true;
                                break;

                        case 'm':
                                m_messagedump = true;
                                break;

                        case 'f':
				{
                                bool result = m_loadparameters.ReadFile( argv[idx]+2 );

				if (false == result)
					{
					cout << "Error: Could not load parameter files (" << argv[idx]+2 << ")" << endl;
					exit(0);
					}
				}
                                break;

                        case 'r':
				{
                                m_replaymode = true;
                                m_replayfile = argv[idx]+2;

				bool result = m_savelist.ReadFile( m_replayfile);

				if (false == result)
					{
					cout << "Error: Could not load save list file (" << m_replayfile << ")" << endl;
					exit(0);
					}
				}
                                break;

                        case 's':
                                m_servermode = true;
                                break;

                        case 'n':
				{
                                m_nodelistfile = argv[idx]+2;
                                bool result = m_nodelist.ReadFile( m_nodelistfile);
	
				if (false == result )			
					{
					cout << "Error: Could not load configuration file (" << m_nodelistfile << ")" << endl;
					exit(0);
					}
				}
                                break;

                        case 'c':
                                m_clientmode = true;
                                break;

                        case 'p':
                                m_server.m_port = atoi(argv[idx]+2);
                                break;

                        case 't':
                                sscanf( argv[idx]+2, "%dx%d", &m_texwidth,
                                                                &m_texheight);
                                break;

                        case 'u':
                                m_fullscreenmode = true;
                                break;

                        case 'w':
                                sscanf( argv[idx]+2, "%dx%d", &m_winwidth,
                                                                &m_winheight);
                                break;


                        case 'z':
                                m_textransfer = argv[idx]+2;
                                break;

                        case 'b':
                                m_borderless = true;
                                break;

                        case 'x':
                                sscanf( argv[idx]+2, "%dx%d", &m_winposx, &m_winposy);
                                break;

			case 'R':
				sscanf( argv[idx]+2, "%f", &m_angledelta);
				break;

			case 'T':
				sscanf( argv[idx]+2, "%f", &m_transdelta);
				break;

			case 'Z':
				sscanf( argv[idx]+2, "%f", &m_zoomdelta);
				break;

			case 'W':
				sscanf( argv[idx]+2, "%f", &m_zoomwheeldelta);
				break;

                        default:
                                break;
                        }
                }
        }
}
