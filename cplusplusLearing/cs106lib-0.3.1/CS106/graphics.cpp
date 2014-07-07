/*
 * File : graphics.cpp
 * Last modified September 2011 by Colin
 * -----------------------------------------
 * Implements the (few) functions in graphics.h
 * Responsible for establishing a Tcp connection with the server,
 * needed before any of the other graphics or extgraph functions will work
 */


#include "graphics.h"
#include "private/graphics.h"
#include "simpio.h"
#include "strutils.h"
#include "genlib.h"
#include "graphicsclient.h"

void SetPort(int port)
/* Sets a global variable, defined in private/graphics.h,
 * in case the student wants to override the default (30004).
 * Call this BEFORE calling InitGraphics() for the first time.
 */
{
    TcpPort = port;
}

void InitGraphics()
{
    if (TcpClient == NULL) {
	// Make initial connection
	try {
	    TcpClient = new GraphicsClient("localhost", TcpPort);
	}
	catch (ErrorException e) {
	    StartServer();
	    return;
	}
    }
    string resp = TcpClient->ExchangeMsg("TESTCONNECTION");
    if (resp == "OK") {
	resp = TcpClient->ExchangeMsg("INITGRAPHICS");
	if (resp != "OK") Error("InitGraphics error: " + resp);
	resp = TcpClient->ExchangeMsg("SETCOORDINATESYSTEM " + CoordSystem);
    }
    else {
	Error("Server connection error on initialization:\n" + resp);
    }
}

void StartServer()
{
/*
 * Placeholder until we can do something better!  
 * Ideally we would start the server automatically,
 * but it is not immediately obvious how to implment this in
 * a way that would work across various *nix and Windows systems.
 */
    cout << "Error: please start the server" << endl;
}

void MovePen(double x, double y)
{
    if (TcpClient == NULL) Error("Graphics not initialized");
    stringstream cmd;
    cmd << "MOVEPEN " << x << " " << y;
    string resp = TcpClient->ExchangeMsg(cmd.str());
    if (resp != "OK") Error(cmd.str() + ": " + resp);
}

void DrawLine(double dx, double dy)
{
    if (TcpClient == NULL) Error("Graphics not initialized");
    stringstream cmd;
    cmd << "DRAWLINE " << dx << " " << dy;
    string resp = TcpClient->ExchangeMsg(cmd.str());
    if (resp != "OK") Error(cmd.str() + ": " + resp);
}

void DrawArc(double r, double start, double sweep)
{
    if (TcpClient == NULL) Error("Graphics not initialized");
    stringstream cmd;
    cmd << "DRAWARC " << r << " " << start << " " << sweep;
    string resp = TcpClient->ExchangeMsg(cmd.str());
    if (resp != "OK") Error(cmd.str() + ": " + resp);
}

double GetWindowWidth()
{
    if (TcpClient == NULL) Error("Graphics not initialized");
    string resp = TcpClient->ExchangeMsg("GETWINDOWWIDTH");
    double val;
    try { val = StringToReal(resp); }
    catch (ErrorException e) { Error("GetWindowWidth: " + resp); }
    return val;
}

double GetWindowHeight()
{
    if (TcpClient == NULL) Error("Graphics not initialized");
    string resp = TcpClient->ExchangeMsg("GETWINDOWHEIGHT");
    double val;
    try { val = StringToReal(resp); }
    catch (ErrorException e) { Error("GetWindowHeight: " + resp); }
    return val;
}

double GetCurrentX()
{
    if (TcpClient == NULL) Error("Graphics not initialized");
    string resp = TcpClient->ExchangeMsg("GETCURRENTX");
    double val;
    try { val = StringToReal(resp); }
    catch (ErrorException e) { Error("GetCurrentX: " + resp); }
    return val;
}

double GetCurrentY()
{
    if (TcpClient == NULL) Error("Graphics not initialized");
    string resp = TcpClient->ExchangeMsg("GETCURRENTY");
    double val;
    try { val = StringToReal(resp); }
    catch (ErrorException e) { Error("GetCurrentY: " + resp); }
    return val;
}
