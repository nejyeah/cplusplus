/* File : private/graphics.h
 * Last modified September 2011 by Colin
 * -------------------------------------
 * adds a few extensions to the Stanford graphics.h,
 * needed by the open-source client/server implementation
 */

#ifndef _PRIVGRAPHICS_H
#define _PRIVGRAPHICS_H

#include <iostream>
#include <string>
#include <sstream>
#include "../graphicsclient.h"

using namespace std;

void StartServer();
void SetPort(int port);

/* Some ugly global variables follow (sorry!)
 * These are things that need to be stored BEFORE creating the GraphicsClient object.
 * It's hard to see how else to handle them in a client/server context
 * without breaking the Stanford API.
 */
GraphicsClient *TcpClient = NULL;
int TcpPort = 30004;  // a fairly random number, that nobody else seems to be using
string CoordSystem = "inch";

#endif // _PRIVGRAPHICS_H
