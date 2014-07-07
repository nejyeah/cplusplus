/*
 * File : graphicsclient.cpp
 * Last modified September 2011 by Colin
 * ---------------------------------------------
 * Implements the client end of the Tcp connection,
 * and provides a simple way for graphics functions to
 * exchange messages with the server.
 */

#include "graphicsclient.h"
#include "ClientSocket.h"
#include "SocketException.h"
#include "genlib.h"

GraphicsClient::GraphicsClient(string host, int port)
{
    InitClient(host, port);
}

int GraphicsClient::InitClient(string host, int port)
{
    try {
        _sock = new ClientSocket(host, port);
    }
    catch (SocketException& e) {
        Error("Client exception: " + e.description());
    }
    return 0;
}

string GraphicsClient::ExchangeMsg(string cmd)
// All commands should provoke a reply (usually "OK")
{
    string reply;

    try {
        *_sock << cmd;
        *_sock >> reply;
    }
    catch ( SocketException& e ) {
        Error("Client exception: " + e.description());
    }
    return reply;
}
