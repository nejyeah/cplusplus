#ifndef GRAPHICSCLIENT_H
#define GRAPHICSCLIENT_H

#include <string>
#include <iostream>
#include "ClientSocket.h"
#include "SocketException.h"

using namespace std;

class GraphicsClient
{
public:
    GraphicsClient(string host, int port);
    string ExchangeMsg(string cmd);

private:
    int InitClient(string host, int port);

    ClientSocket *_sock;
};

#endif // GRAPHICSCLIENT_H
