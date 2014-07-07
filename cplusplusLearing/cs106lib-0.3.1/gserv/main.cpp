/*
 * File: main.cpp
 * Last modified August 2011 by Colin
 * -----------------------------------
 * main() just parses the command line then starts the event loop.
 * All serious processing is done in the gWin and GraphicsHandler
 * objects, plus GraphicsArea to handle mouse stuff.
 */

#include <QtGui/QApplication>
#include "gwin.h"

using namespace std;

int main(int argc, char *argv[])
{
    const int DEFAULTPORT = 30004;
    const QString DEFAULTHOST = "localhost";

    int i = 1;
    int port = DEFAULTPORT;
    QString host = DEFAULTHOST;
    bool showTextArea = false;
    bool ok;
    QString arg;

    while (i < argc) {
        arg = argv[i];

        if (arg == "-p") { // non-default port setting
            ++i;
            QString newPort = argv[i];
            port = newPort.toInt(&ok);
            if (!ok) {
                port = DEFAULTPORT; //invalid setting on command line
                qDebug() << "Invalid argument to -p option: must be an integer port number <32k" << endl;
            }
//            qDebug() << "Starting on port " << port << endl;
        }

        if (arg == "-h") { // non-default host setting (should be an IP address)
            ++i;
            host = argv[i];
//            qDebug() << "Starting on host " << host << endl;
        }

        if (arg == "-d" || arg == "--debug") {
            showTextArea = true;
//            qDebug() << "starting in debug mode" << endl;
        }
        ++i;
    }

    QApplication a(argc, argv);
    gWin w(port, host, showTextArea);
    w.show();

    return a.exec();
}
