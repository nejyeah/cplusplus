/*
 * File: testgraphics.cpp
 * Last modified September 2011, by Colin
 * ------------------------------------------------------------
 * A series of tests for the open-source version of the CS106B libraries,
 * especially the client-server graphics
 */

#include "testgraphics.h"
#include "genlib.h"
#include "strutils.h"
#include "simpio.h"
#include "graphics.h"
#include "extgraph.h"
#include "random.h"
#include "sound.h"
#include "maze.h"
#include "gboggle.h"
#include <iostream>
#include <cstdlib>
#include <sstream>


int main() {
    int resp;
    // SetCoordinateSystem("screen");
    InitGraphics();
    cout << GetCoordinateSystem() << endl;
    SetWindowSize(6.00, 4.00);
    while (true) {
	cout << endl
	     << "Coord system is now: " << GetCoordinateSystem() << endl << endl
	     << "1 : Assorted graphics" << endl
	     << "2 : Mouse operations" << endl
	     << "3 : Pictures" << endl
	     << "4 : Erasing" << endl
	     << "5 : Info" << endl
	     << "6 : Save/Restore" << endl
	     << "7 : Dummy maze" << endl
	     << "8 : Dummy Boggle" << endl
	     << "20 : CoordinateSystem to inch" << endl
	     << "21 : CoordinateSystem to Cartesian" << endl
	     << "22 : CoordinateSystem to screen" << endl
	     << "0 : Exit" << endl << endl
	     << "Option> ";
	resp = GetInteger();
	switch (resp) {
	case 1 :
	    MiscGraphics();
	    break;
	case 2 :
	    MouseStuff();
	    break;
	case 3 :
	    Pictures();
	    break;
	case 4 :
	    Erasing();
	    break;
	case 5 :
	    Info();
	    break;
	case 6 :
	    Saves();
	    break;
	case 7 :
	    DrawMaze();
	    break;
	case 8 :
	    DrawBoggle();
	    break;
	case 20 :
	    SetCoordinateSystem("inch");
	    InitGraphics();
	    SetWindowSize(6.00, 4.00);
	    break;
	case 21 :
	    SetCoordinateSystem("cartesian");
	    InitGraphics();
	    SetWindowSize(600, 400);
	    break;
	case 22 :
	    SetCoordinateSystem("screen");
	    InitGraphics();
	    SetWindowSize(600, 400);
	    break;
	case 0 :
	    return(0);
	default :
	    cout << "Invalid response!" << endl;
	}
    }
    return(0);
}


void MiscGraphics()
{
    cout << "=== Starting more graphics tests" << endl; 
    InitGraphics();
    string coord = GetCoordinateSystem();
    if (coord == "INCH") {
	MovePen(0.10, 3.80);
	DrawTextString("Default font");

	MovePen(1.20,2.20);
	EllipseSegments(0.60, 0.80);

	TextLayout(0.10, 0.70);
    }
    else if (coord == "CARTESIAN") {
	MovePen(10, 380);
	DrawTextString("Default font");

	MovePen(120,220);
	EllipseSegments(60, 80);

	TextLayout(10, 70);
    }
    else if (coord == "SCREEN") {
	MovePen(10, 20);
	DrawTextString("Default font");

	MovePen(120, 180);
	EllipseSegments(60, 80);

	TextLayout(10, 330);
    }
    Fills();

    CustomColors();
}

void Fills()
{
    SetPenColor("Cyan");
    string coord = GetCoordinateSystem();
    if (coord == "INCH") {
	FillGradient(3.20);

	SetPenColor("Blue");
	StartFilledRegion(0.5);
	MovePen(5.00, 2.50);
	DrawEllipticalArc(0.50,0.40,0,270);
	EndFilledRegion();

	SetPenColor("Yellow");
	StartFilledRegion(); // default density=1
	MovePen(5.00,1.50);
	DrawRect(-0.80,0.50);
	EndFilledRegion();
    }
    else if (coord == "CARTESIAN") {
	FillGradient(320);

	SetPenColor("Blue");
	StartFilledRegion(0.5);
	MovePen(500, 250);
	DrawEllipticalArc(50,40,0,270);
	EndFilledRegion();

	SetPenColor("Yellow");
	StartFilledRegion(); // default density=1
	MovePen(500,150);
	DrawRect(-80,50);
	EndFilledRegion();
    }
    else if (coord == "SCREEN") {
	FillGradient(80);

	SetPenColor("Blue");
	StartFilledRegion(0.5);
	MovePen(500, 150);
	DrawEllipticalArc(50,40,0,270);
	EndFilledRegion();

	SetPenColor("Yellow");
	StartFilledRegion(); // default density=1
	MovePen(500,250);
	DrawRect(-80,-50);
	EndFilledRegion();
    }
}

void MouseStuff()
{
    InitGraphics();
    cout << "click and drag the mouse" << endl;
    WaitForMouseDown();
    while (true) {
	if (!MouseButtonIsDown()) break;
	cout << "X: " << GetMouseX() << " Y: " << GetMouseY() << endl;
    }
    cout << "Mouse released at " "X: "
	 << GetMouseX() << " Y: " << GetMouseY() << endl;
    cout << "click and drag the mouse again" << endl;
    WaitForMouseDown();
    MovePen(GetMouseX(),GetMouseY());
    WaitForMouseUp();
    DrawRect(GetMouseX()-GetCurrentX(),GetMouseY()-GetCurrentY());
}

void Pictures()
{
    InitGraphics();
    double width, height;
    string msg;
    string coord = GetCoordinateSystem();
    
    if (coord == "INCH") MovePen(0.20, 3.80);
    else if (coord == "CARTESIAN") MovePen(20, 380);
    else if (coord == "SCREEN") MovePen(20, 20);

    DrawNamedPicture("Stanford_University_seal.png");
    width = GetPictureWidth("Stanford_University_seal.png");
    height = GetPictureHeight("Stanford_University_seal.png");

    if (coord == "INCH") MovePen(0.20, 3.50 - height);
    else if (coord == "CARTESIAN") MovePen(20, 350 - height);
    else if (coord == "SCREEN") MovePen(20, height + 70);

    msg = "Width: " + RealToString(width) +
	"   height: " + RealToString(height);
    DrawTextString(msg);

    if (coord == "INCH") MovePen(0.50 + width, 3.80);
    else if (coord == "CARTESIAN") MovePen(50 + width, 380);
    else if (coord == "SCREEN") MovePen(50 + width, 20);

    DrawNamedPicture("Heckert_GNU.png");
    width = GetPictureWidth("Heckert_GNU.png");
    height = GetPictureHeight("Heckert_GNU.png");

    if (coord == "INCH") MovePen(GetCurrentX(), 3.50 - height);
    else if (coord == "CARTESIAN") MovePen(GetCurrentX(), 350 - height);
    else if (coord == "SCREEN") MovePen(GetCurrentX(), height + 70);

    msg = "Width: " + RealToString(width) +
	"   height: " + RealToString(height);
    DrawTextString(msg);
}

void Erasing()
{
    InitGraphics();
    string coord = GetCoordinateSystem();
    double x, y;
    if (coord == "INCH") {
	x=0.50; y=3.50;
	MovePen(x,y);
	DrawRect(0.60,-0.30);
	for (int i=0; i<50; i++) {
	    Pause(0.1);
	    SetEraseMode(true);
	    DrawRect(0.60,-0.30);
	    SetEraseMode(false);
	    x += 0.05; y -= 0.05;
	    MovePen(x,y);
	    DrawRect(0.60,-0.30);
	}
    
	x = 4.00; y = 3.50;
	SetPenColor("Blue");
	SetPointSize(20);
	MovePen(x,y);
	DrawTextString("Drifting...");
	for (int i=0; i<50; i++) {
	    Pause(0.1);
	    SetEraseMode(true);
	    MovePen(x,y);
	    DrawTextString("Drifting...");
	    SetEraseMode(false);
	    x -= 0.05; y -= 0.05;
	    MovePen(x,y);
	    DrawTextString("Drifting...");
	}
    }
    else if (coord == "CARTESIAN") {
	x=50; y=350;
	MovePen(x,y);
	DrawRect(60,-30);
	for (int i=0; i<50; i++) {
	    Pause(0.1);
	    SetEraseMode(true);
	    DrawRect(60,-30);
	    SetEraseMode(false);
	    x += 5; y -= 5;
	    MovePen(x,y);
	    DrawRect(60,-30);
	}
    
	x = 400; y = 350;
	SetPenColor("Blue");
	SetPointSize(20);
	MovePen(x,y);
	DrawTextString("Drifting...");
	for (int i=0; i<50; i++) {
	    Pause(0.1);
	    SetEraseMode(true);
	    MovePen(x,y);
	    DrawTextString("Drifting...");
	    SetEraseMode(false);
	    x -= 5; y -= 5;
	    MovePen(x,y);
	    DrawTextString("Drifting...");
	}
    }
    else if (coord == "SCREEN") {
	x=50; y=50;
	MovePen(x,y);
	DrawRect(60,30);
	for (int i=0; i<50; i++) {
	    Pause(0.1);
	    SetEraseMode(true);
	    DrawRect(60,30);
	    SetEraseMode(false);
	    x += 5; y += 5;
	    MovePen(x,y);
	    DrawRect(60,30);
	}
    
	x = 400; y = 50;
	SetPenColor("Blue");
	SetPointSize(20);
	MovePen(x,y);
	DrawTextString("Drifting...");
	for (int i=0; i<50; i++) {
	    Pause(0.1);
	    SetEraseMode(true);
	    MovePen(x,y);
	    DrawTextString("Drifting...");
	    SetEraseMode(false);
	    x -= 5; y += 5;
	    MovePen(x,y);
	    DrawTextString("Drifting...");
	}
    }
}

void Info()
{
    InitGraphics();
    double x, y;
    string coord = GetCoordinateSystem();
    if (coord == "INCH")  x=0.50, y=3.70;
    else if (coord == "CARTESIAN") x=50, y=370;
    else if (coord == "SCREEN") x=50, y=30;
    MovePen(x,y);

    if (coord == "INCH" || coord == "CARTESIAN") {
	DrawTextString("Title: " + GetWindowTitle());

	y -= GetFontHeight();
	MovePen(x,y);
	DrawTextString("FullScreen w: " + IntegerToString(GetFullScreenWidth())
		       + "  h: " + IntegerToString(GetFullScreenHeight()));
	y -= GetFontHeight();
	MovePen(x,y);
	DrawTextString("Coord system: " + GetCoordinateSystem());

	y -= GetFontHeight();
	MovePen(x,y);
	DrawTextString("Font: " + GetFontDescription());
    }
    else if (coord == "SCREEN") {
	DrawTextString("Title: " + GetWindowTitle());

	y += GetFontHeight();
	MovePen(x,y);
	DrawTextString("FullScreen w: " + IntegerToString(GetFullScreenWidth())
		       + "  h: " + IntegerToString(GetFullScreenHeight()));
	y += GetFontHeight();
	MovePen(x,y);
	DrawTextString("Coord system: " + GetCoordinateSystem());

	y += GetFontHeight();
	MovePen(x,y);
	DrawTextString("Font: " + GetFontDescription());
    }
}

string GetFontDescription()
{
    stringstream fontDescription;
    fontDescription << GetFont() << " " << GetPointSize() << " pt ";
    int style = GetStyle();
    if (style & 0x01) fontDescription << "Bold ";
    if (style & 0x02) fontDescription << "Italic ";
    fontDescription << GetPenColor();
    return fontDescription.str();
}

void Saves()
{
    SaveGraphicsState(); // state at entry
    InitGraphics();
    SaveGraphicsState(); // default state at initialization
    string coord = GetCoordinateSystem();
    if (coord == "INCH") {
	StateTest("Default state", 0.50, 3.80);
	MovePen(2.50, 3.30);
	SetFont("Times");
	SetPointSize(20);
	StateTest("20pt Times", 0.60, 3.20);
	RestoreGraphicsState();
	StateTest("First restore (to default)", 0.70, 2.40);
	RestoreGraphicsState();
	StateTest("Second restore (to entry values)", 0.80, 1.80);
    }
    else if (coord == "CARTESIAN") {
	StateTest("Default state", 50, 380);
	MovePen(250, 330);
	SetFont("Times");
	SetPointSize(20);
	StateTest("20pt Times", 60, 320);
	RestoreGraphicsState();
	StateTest("First restore (to default)", 70, 240);
	RestoreGraphicsState();
	StateTest("Second restore (to entry values)", 80, 180);
    }
    else if (coord == "SCREEN") {
	StateTest("Default state", 50, 20);
	MovePen(250, 70);
	SetFont("Times");
	SetPointSize(20);
	StateTest("20pt Times", 60, 80);
	RestoreGraphicsState();
	StateTest("First restore (to default)", 70, 160);
	RestoreGraphicsState();
	StateTest("Second restore (to entry values)", 80, 220);
    }
}

void DrawMaze()
{
    SetCoordinateSystem("inch");
    Maze m(6, 10, true);
    InitGraphics();
    Randomize();
    m.draw();
    string path = "ENEENEEENNEENE";
    pointT curr, next;
    curr.row = 0;
    curr.col = 0;
    for (size_t i = 0; i<path.size(); i++) {
	m.drawMark(curr, "blue");
	char dir = path[i];
	if (dir == 'N') {
	    next.row = curr.row + 1;
	    next.col = curr.col;
	}
	else if (dir == 'E') {
	    next.row = curr.row;
	    next.col = curr.col + 1;
	}
	m.setWall(curr, next, false);
	curr.row = next.row;
	curr.col = next.col;
    }
    m.drawMark(curr, "blue");
}

void DrawBoggle()
{
    SetCoordinateSystem("inch");
    InitGraphics();
    DrawBoard(5,5);
    for (int i=0; i<25; i++) {
	LabelCube(i/5, i%5, 'A'+i);
    }
   bool soundOk = TestSound();
    if (soundOk) {
	SetSoundOn(true);
	PlayNamedSound("puzzlin.wav");
    }
    else cout << "Warning: sounds will not work on this system" << endl;
    
    string hum[] = {"This","isn't","real,","you","need","to","do","the","assignment"};
    for (size_t i=0; i<9; i++) RecordWordForPlayer(hum[i], Human);
    if (soundOk) PlayNamedSound("foolprf.wav");
    string comp[] = {"Is","sound","on?"};
    for (size_t i=0; i<3; i++) RecordWordForPlayer(comp[i], Computer);
    if (soundOk) PlayNamedSound("game.wav");
}

void StateTest(string msg, double x, double y)
{
    string coord = GetCoordinateSystem();
    stringstream forOutput;
    forOutput << msg << "  x: " << GetCurrentX() << "  y: " << GetCurrentY();
    MovePen(x,y);
    DrawTextString(forOutput.str());
	if (coord == "SCREEN") MovePen(x, y + GetFontHeight());
	else MovePen(x, y - GetFontHeight());
    DrawTextString("Font: " + GetFontDescription());
}

void EllipseSegments(double w, double h)
{
    SetPenColor("Red");
    DrawEllipticalArc(w,h,45,90);
    SetPenColor("Green");
    DrawEllipticalArc(w,h,135,90);
    SetPenColor("Blue");
    DrawEllipticalArc(w,h,225,90);
    SetPenColor("Magenta");
    DrawEllipticalArc(w,h,315,90);
}

void TextLayout(double x, double y)
{
    MovePen(x,y);
    SetFont("Times New Roman");
    SetPointSize(18);
    SetStyle(3);
    string testString = "Times New Roman 18pt bold italic";
    DrawTextString(testString);
    double testStringWidth = TextStringWidth(testString);
    double testStringHeight = GetFontHeight();
    MovePen(x+testStringWidth, y);
    SetPenColor("Dark Gray");
    SetStyle(0);
    DrawTextString("continued");
    string coord = GetCoordinateSystem();
    if (coord == "INCH" || coord == "CARTESIAN")
	MovePen(x, y-testStringHeight);
    else if (coord == "SCREEN")
	MovePen(x, y+testStringHeight);
    DrawTextString("Next line");
}

void DrawFill(double width, double height, double density)
{
    string coord = GetCoordinateSystem();
    if (coord == "INCH" || coord == "CARTESIAN") {
       StartFilledRegion(density);
       DrawLine(0,-height);
       DrawEllipticalArc(width/2, height/2, 180, 180);
       DrawLine(0,height);
       DrawEllipticalArc(width/2, height/2, 0, 180);
       EndFilledRegion();
    }
    else if (coord == "SCREEN") {
       StartFilledRegion(density);
       DrawLine(0,height);
       DrawEllipticalArc(width/2, height/2, 180, 180);
       DrawLine(0,-height);
       DrawEllipticalArc(width/2, height/2, 0, 180);
       EndFilledRegion();
   }
}

void FillGradient(double y)
{
    string coord = GetCoordinateSystem();
    double x, size;
    double dens = 0;
    if (coord == "INCH") {
	x = 0.2;
	size = 0.30;
    }
    else {
	x = 20;
	size = 30;
    }
    
    for (int i=0; i<=10; i++) {
	MovePen(x, y);
	DrawFill(size, size, dens);
	x += size;
	dens += 0.1;
    }
}

void CustomColors()
{
    string coord = GetCoordinateSystem();
    if (coord == "INCH") MovePen(2.00, 2.00);
    else MovePen(200,200);

    DefineColor("Test Color", 0.25, 0.4, 0.7);
    SetPenColor("Test Color");
    DrawTextString(GetPenColor());
    SetPenColorRGB(0.1, 0.7, 0.4);

    if (coord == "INCH") MovePen(2.00, 1.70);
    else if (coord == "CARTESIAN") MovePen(200, 170);
    else if (coord == "SCREEN") MovePen(200, 230);
    DrawTextString(GetPenColor());
}

void DrawRect(double w, double h)
{
    DrawLine(w,0);
    DrawLine(0,h);
    DrawLine(-w,0);
    DrawLine(0,-h);
}
