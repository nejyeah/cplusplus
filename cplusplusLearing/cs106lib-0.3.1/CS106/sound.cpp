/*
 * File: sound.cpp
 * Last modified Sept 2011, by Colin
 * --------------------------------------------------------------
 * Implements simple WAV file handling via the graphics server
 */

#include "sound.h"
#include "graphics.h"
#include "graphicsclient.h"
#include <sstream>

extern GraphicsClient *TcpClient;

string GetSoundDirectory()
{
    //TODO - find a portable way to set the path
    // getcwd() is POSIX compliant but won't work on Windows
    char the_path[256];
    getcwd(the_path, 255);
    string soundDir = the_path;
    soundDir += "/Sounds/";
    return soundDir;
}

bool TestSound()
{
    if (TcpClient == NULL) Error("Graphics not initialized");
    string resp = TcpClient->ExchangeMsg("TESTSOUND");
    if (resp == "OK") return true;
    else return false;;
}

void PlayNamedSound(string name)
/* We need to send an absolute file path, as the server has no idea
 * of the client's current directory.
 */
{
    if (TcpClient == NULL) Error("Graphics not initialized");
    string soundDir = GetSoundDirectory();
    stringstream cmd;
    cmd << "PLAYNAMEDSOUND " << soundDir << name;
    string resp = TcpClient->ExchangeMsg(cmd.str());
    if (resp != "OK") Error(cmd.str() + ": " + resp);
}


void SetSoundOn(bool on)
{
    if (TcpClient == NULL) Error("Graphics not initialized");
    string msg = "SETSOUNDON ";
    if (on) msg += "Y";
    else msg += "N";
    string resp = TcpClient->ExchangeMsg(msg);
    if (resp != "OK") Error(msg + ": " + resp);
}

