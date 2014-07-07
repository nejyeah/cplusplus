#include "extgraph.h"
#include "simpio.h"
#include "strutils.h"
#include "genlib.h"
#include "graphicsclient.h"
#include <string>
#include <sstream>
#include <ctime>

extern GraphicsClient *TcpClient;
extern string CoordSystem;
string NoSpaces(string str);
void ClientPause(double sec);
string GetPictureDirectory();

void DrawEllipticalArc(double rx, double ry,
                       double start, double sweep)
{
    if (TcpClient == NULL) Error("Graphics not initialized");
    stringstream cmd;
    cmd << "DRAWELLIPTICALARC " << rx << " " << ry << " "
	<< start << " " << sweep;
    string resp = TcpClient->ExchangeMsg(cmd.str());
    if (resp != "OK") Error(cmd.str() + ": " + resp);
}

void StartFilledRegion(double density /*= 1.0*/)
{
    if (TcpClient == NULL) Error("Graphics not initialized");
    stringstream cmd;
    cmd << "STARTFILLEDREGION " << density;
    string resp = TcpClient->ExchangeMsg(cmd.str());
    if (resp != "OK") Error(cmd.str() + ": " + resp);
}

void EndFilledRegion()
{
    if (TcpClient == NULL) Error("Graphics not initialized");
    stringstream cmd;
    cmd << "ENDFILLEDREGION ";
    string resp = TcpClient->ExchangeMsg(cmd.str());
    if (resp != "OK") Error(cmd.str() + ": " + resp);
}

void DrawTextString(string text)
{
    if (TcpClient == NULL) Error("Graphics not initialized");
    stringstream cmd;
    cmd << "DRAWTEXTSTRING " << text;
    string resp = TcpClient->ExchangeMsg(cmd.str());
    if (resp != "OK") Error(cmd.str() + ": " + resp);
}

double TextStringWidth(string text)
{
    if (TcpClient == NULL) Error("Graphics not initialized");
    stringstream cmd;
    cmd << "TEXTSTRINGWIDTH " << text;
    string resp = TcpClient->ExchangeMsg(cmd.str());
    double val;
    try { val = StringToReal(resp); }
    catch (ErrorException e) { Error("TextStringWidth: " + resp); }
    return val;
}

void SetFont(string font)
{
    if (TcpClient == NULL) Error("Graphics not initialized");
    stringstream cmd;
    cmd << "SETFONT " << font;
    string resp = TcpClient->ExchangeMsg(cmd.str());
    if (resp != "OK") Error(cmd.str() + ": " + resp);
}

string GetFont()
{
    if (TcpClient == NULL) Error("Graphics not initialized");
    string resp = TcpClient->ExchangeMsg("GETFONT");
    return resp;
}

void SetPointSize(int size)
{
    if (TcpClient == NULL) Error("Graphics not initialized");
    stringstream cmd;
    cmd << "SETPOINTSIZE " << size;
    string resp = TcpClient->ExchangeMsg(cmd.str());
    if (resp != "OK") Error(cmd.str() + ": " + resp);
}

int GetPointSize()
{
    if (TcpClient == NULL) Error("Graphics not initialized");
    string resp = TcpClient->ExchangeMsg("GETPOINTSIZE");
    int val;
    try { val = StringToInteger(resp); }
    catch (ErrorException e) { Error("GetPointSize: " + resp); }
    return val;
}

void SetStyle(int style)
{
    if (TcpClient == NULL) Error("Graphics not initialized");
    stringstream cmd;
    cmd << "SETSTYLE " << style;
    string resp = TcpClient->ExchangeMsg(cmd.str());
    if (resp != "OK") Error(cmd.str() + ": " + resp);
}

int GetStyle()
{
    if (TcpClient == NULL) Error("Graphics not initialized");
    string resp = TcpClient->ExchangeMsg("GETSTYLE");
    double val;
    try { val = StringToReal(resp); }
    catch (ErrorException e) { Error("GetCurrentX: " + resp); }
    return val;
}

double GetFontAscent()
{
    if (TcpClient == NULL) Error("Graphics not initialized");
    string resp = TcpClient->ExchangeMsg("GETFONTASCENT");
    double val;
    try { val = StringToReal(resp); }
    catch (ErrorException e) { Error("GetFontAscent: " + resp); }
    return val;
}

double GetFontDescent()
{
    if (TcpClient == NULL) Error("Graphics not initialized");
    string resp = TcpClient->ExchangeMsg("GETFONTDESCENT");
    double val;
    try { val = StringToReal(resp); }
    catch (ErrorException e) { Error("GetFontDescent: " + resp); }
    return val;
}

double GetFontHeight()
{
    if (TcpClient == NULL) Error("Graphics not initialized");
    string resp = TcpClient->ExchangeMsg("GETFONTHEIGHT");
    double val;
    try { val = StringToReal(resp); }
    catch (ErrorException e) { Error("GetCurrentX: " + resp); }
    return val;
}

double GetMouseX()
{
    if (TcpClient == NULL) Error("Graphics not initialized");
    string resp = TcpClient->ExchangeMsg("GETMOUSEX");
    double val;
    try { val = StringToReal(resp); }
    catch (ErrorException e) { Error("GetMouseX: " + resp); }
    return val;
}

double GetMouseY()
{
    if (TcpClient == NULL) Error("Graphics not initialized");
    string resp = TcpClient->ExchangeMsg("GETMOUSEY");
    double val;
    try { val = StringToReal(resp); }
    catch (ErrorException e) { Error("GetMouseY: " + resp); }
    return val;
}

bool MouseButtonIsDown()
{
    if (TcpClient == NULL) Error("Graphics not initialized");
    string resp = TcpClient->ExchangeMsg("MOUSEBUTTONISDOWN");
    if (resp == "TRUE") return true;
    if (resp == "FALSE") return false;

    // else problems 
    Error("MouseButtonIsDown: " + resp);
}

void WaitForMouseDown()
{
    if (TcpClient == NULL) Error("Graphics not initialized");
    while (true) {
	if (MouseButtonIsDown()) return;
    }
}

void WaitForMouseUp()
{
    if (TcpClient == NULL) Error("Graphics not initialized");
    while (true) {
	if (!MouseButtonIsDown()) return;
    }
}

void SetPenColor(string color)
{
    if (TcpClient == NULL) Error("Graphics not initialized");
    stringstream cmd;
    cmd << "SETPENCOLOR " << NoSpaces(color);
    string resp = TcpClient->ExchangeMsg(cmd.str());
    if (resp != "OK") Error(cmd.str() + ": " + resp);
}

void SetPenColorRGB(double red, double green, double blue)
{
    if (TcpClient == NULL) Error("Graphics not initialized");
    stringstream cmd;
    cmd << "SETPENCOLORRGB " << red << " " << green << " " << blue;
    string resp = TcpClient->ExchangeMsg(cmd.str());
    if (resp != "OK") Error(cmd.str() + ": " + resp);
}

string NoSpaces(string str)
{
    size_t found;
    while ((found = str.find(' ')) != string::npos) {
	str.erase(found,1);
    }
    return str;
}

string GetPenColor()
{
    if (TcpClient == NULL) Error("Graphics not initialized");
    string resp = TcpClient->ExchangeMsg("GETPENCOLOR");
    return resp;
}

void DefineColor(string name,
                 double red, double green, double blue)
{
    if (TcpClient == NULL) Error("Graphics not initialized");
    stringstream cmd;
    cmd << "DEFINECOLOR " << NoSpaces(name) << " "
	<< red << " " << green << " " << blue;
    string resp = TcpClient->ExchangeMsg(cmd.str());
    if (resp != "OK") Error(cmd.str() + ": " + resp);
}

void DrawNamedPicture(string name)
/* We need to send an absolute file path, as the server has no idea
 * of the client's current directory.
 * Only the filename (no path) is stored with the width & height,
 * so GetPictureWidth/Height only need to send the filename.
 */
{
    if (TcpClient == NULL) Error("Graphics not initialized");
    string picDir = GetPictureDirectory();
    stringstream cmd;
    cmd << "DRAWNAMEDPICTURE " << picDir << name;
    string resp = TcpClient->ExchangeMsg(cmd.str());
    if (resp != "OK") Error(cmd.str() + ": " + resp);
}

string GetPictureDirectory()
{
    //TODO - find a portable way to set the path
    // getcwd() is POSIX compliant but won't work on Windows
    char the_path[256];
    getcwd(the_path, 255);
    string picDir = the_path;
    picDir += "/Pictures/";
    return picDir;
}

double GetPictureWidth(string name)
{
    if (TcpClient == NULL) Error("Graphics not initialized");
    stringstream cmd;
    cmd << "GETPICTUREWIDTH " << name;
    string resp = TcpClient->ExchangeMsg(cmd.str());
    double val;
    try { val = StringToReal(resp); }
    catch (ErrorException e) { Error("GetPictureWidth: " + resp); }
    return val;
}

double GetPictureHeight(string name)
{
    if (TcpClient == NULL) Error("Graphics not initialized");
    stringstream cmd;
    cmd << "GETPICTUREHEIGHT " << name;
    string resp = TcpClient->ExchangeMsg(cmd.str());
    double val;
    try { val = StringToReal(resp); }
    catch (ErrorException e) { Error("GetPictureHeight: " + resp); }
    return val;
}

void SetCoordinateSystem(string system)
{
    // Just store the value in a global variable for now
    // InitGraphics() will send it to the server later
    CoordSystem = system;
    
    // if (TcpClient == NULL) Error("Graphics not initialized");
    // stringstream cmd;
    // cmd << "SETCOORDINATESYSTEM " << system;
    // string resp = TcpClient->ExchangeMsg(cmd.str());
    // if (resp != "OK") Error(cmd.str() + ": " + resp);
}

string GetCoordinateSystem()
{
    if (TcpClient == NULL) Error("Graphics not initialized");
    string resp = TcpClient->ExchangeMsg("GETCOORDINATESYSTEM");
    return resp;
}

void SetEraseMode(bool mode)
{
    if (TcpClient == NULL) Error("Graphics not initialized");
    stringstream cmd;
    cmd << "SETERASEMODE ";
    if (mode) cmd << "TRUE";
    else cmd << "FALSE";
    string resp = TcpClient->ExchangeMsg(cmd.str());
    if (resp != "OK") Error(cmd.str() + ": " + resp);
}

bool GetEraseMode()
{
    if (TcpClient == NULL) Error("Graphics not initialized");
    string resp = TcpClient->ExchangeMsg("GETERASEMODE");
    if (resp == "TRUE") return true;
    if (resp == "FALSE") return false;

    // else problems 
    Error("GetEraseMode: " + resp);
}

void SetWindowTitle(string title)
{
    if (TcpClient == NULL) Error("Graphics not initialized");
    stringstream cmd;
    cmd << "SETWINDOWTITLE " << title;
    string resp = TcpClient->ExchangeMsg(cmd.str());
    if (resp != "OK") Error(cmd.str() + ": " + resp);
}

string GetWindowTitle()
{
    if (TcpClient == NULL) Error("Graphics not initialized");
    string resp = TcpClient->ExchangeMsg("GETWINDOWTITLE");
    return resp;
}

void UpdateDisplay()
{
    if (TcpClient == NULL) Error("Graphics not initialized");
    stringstream cmd;
    cmd << "UPDATEDISPLAY ";
    string resp = TcpClient->ExchangeMsg(cmd.str());
    if (resp != "OK") Error(cmd.str() + ": " + resp);
}

void Pause(double seconds)
{
    if (TcpClient == NULL) Error("Graphics not initialized");
    stringstream cmd;
    int msec = seconds * 1000;
    cmd << "PAUSE " << msec;
    string resp = TcpClient->ExchangeMsg(cmd.str());
    // return value is milliseconds elapsed
}

void ExitGraphics()
{
    if (TcpClient == NULL) Error("Graphics not initialized");
    stringstream cmd;
    cmd << "EXITGRAPHICS ";
    string resp = TcpClient->ExchangeMsg(cmd.str());
    if (resp != "OK") Error(cmd.str() + ": " + resp);
}

void SaveGraphicsState()
{
    if (TcpClient == NULL) Error("Graphics not initialized");
    stringstream cmd;
    cmd << "SAVEGRAPHICSSTATE ";
    string resp = TcpClient->ExchangeMsg(cmd.str());
    if (resp != "OK") Error(cmd.str() + ": " + resp);
}

void RestoreGraphicsState()
{
    if (TcpClient == NULL) Error("Graphics not initialized");
    stringstream cmd;
    cmd << "RESTOREGRAPHICSSTATE ";
    string resp = TcpClient->ExchangeMsg(cmd.str());
    if (resp != "OK") Error(cmd.str() + ": " + resp);
}

double GetFullScreenWidth()
{
    if (TcpClient == NULL)
	Error("Sorry, in this version you need to run InitGraphics BEFORE GetFullScreenWidth/Height");
    string resp = TcpClient->ExchangeMsg("GETFULLSCREENWIDTH");
    double val;
    try { val = StringToReal(resp); }
    catch (ErrorException e) { Error("GetFulScreenWidth: " + resp); }
    return val;
}

double GetFullScreenHeight()
{
    if (TcpClient == NULL)
	Error("Sorry, in this version you need to run InitGraphics BEFORE GetFullScreenWidth/Height");
    string resp = TcpClient->ExchangeMsg("GETFULLSCREENHEIGHT");
    double val;
    try { val = StringToReal(resp); }
    catch (ErrorException e) { Error("GetFullScreenHeight: " + resp); }
    return val;
}

void SetWindowSize(double width, double height)
// This has the side effect of erasing the screen
{
    if (TcpClient == NULL) Error("Graphics not initialized");
    stringstream cmd;
    cmd << "SETWINDOWSIZE " << width << " " << height;
    string resp = TcpClient->ExchangeMsg(cmd.str());
    if (resp != "OK") Error(cmd.str() + ": " + resp);
}

void ClientPause(double sec)
// Note the contrast with Pause() - which tells the server to pause
// ClientPause() is local, blocking communication with the server
// May not be needed in the release version, but useful during debugging
{
    time_t start = time(NULL);
    while (difftime(time(NULL), start) < sec) {
	/* do nothing */
    } 
}

double GetXResolution()
{
    if (TcpClient == NULL) Error("Graphics not initialized");
    string resp = TcpClient->ExchangeMsg("GETXRESOLUTION");
    double val;
    try { val = StringToReal(resp); }
    catch (ErrorException e) { Error("GetXResolution: " + resp); }
    return val;
}

double GetYResolution()
{
    if (TcpClient == NULL) Error("Graphics not initialized");
    string resp = TcpClient->ExchangeMsg("GETYRESOLUTION");
    double val;
    try { val = StringToReal(resp); }
    catch (ErrorException e) { Error("GetYResolution: " + resp); }
    return val;
}
