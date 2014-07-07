#include "testgraphics.h"
#include "genlib.h"
#include "strutils.h"
#include "simpio.h"
#include "graphics.h"
#include "extgraph.h"
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
	     << "1 : Basic graphics" << endl
	     << "2 : Extended graphics" << endl
	     << "3 : Mouse operations" << endl
	     << "4 : Pictures" << endl
	     << "5 : Erasing" << endl
	     << "6 : Info" << endl
	     << "7 : Save/Restore" << endl
	     << "10 : CoordinateSystem to inch" << endl
	     << "11 : CoordinateSystem to Cartesian" << endl
	     << "12 : CoordinateSystem to screen" << endl
	     << "0 : Exit" << endl << endl
	     << "Option> ";
	resp = GetInteger();
	switch (resp) {
	case 1 :
	    BasicGraphics();
	    break;
	case 2 :
	    MoreGraphics();
	    break;
	case 3 :
	    MouseStuff();
	    break;
	case 4 :
	    Pictures();
	    break;
	case 5 :
	    Erasing();
	    break;
	case 6 :
	    Info();
	    break;
	case 7 :
	    Saves();
	    break;
	case 10 :
	    SetCoordinateSystem("inch");
	    InitGraphics();
	    SetWindowSize(6.00, 4.00);
	    break;
	case 11 :
	    SetCoordinateSystem("cartesian");
	    InitGraphics();
	    SetWindowSize(600, 400);
	    break;
	case 12 :
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

void BasicGraphics()
{
    cout << "=== Starting basic graphics tests" << endl; 
    InitGraphics();
    string coord = GetCoordinateSystem();
    if (coord == "INCH") {
	MovePen(2.00,3.00);
	DrawLine(0.30, 0.20);
	DrawArc(0.50, 45, 90);
    }
    else if (coord == "CARTESIAN") {
	MovePen(200,300);
	DrawLine(30, 20);
	DrawArc(50, 45, 90);
    }
    else if (coord == "SCREEN") {
	MovePen(200,100);
	DrawLine(30, -20);
	DrawArc(50, 45, 90);
    }
    cout << "x: " << GetCurrentX() << " y: " << GetCurrentY() << endl;
    cout << "Window: " << GetWindowWidth() << " " << GetWindowHeight() << endl;
}

void MoreGraphics()
{
    cout << "=== Starting more graphics tests" << endl; 
    InitGraphics();
    string coord = GetCoordinateSystem();
    if (coord == "INCH") {
	MovePen(0.10, 3.80);
	DrawTextString("Default font");

	MovePen(1.20,2.20);
	EllipseSegments(0.60, 0.80);

	TextLayout(0.10, 1.00);
    }
    else if (coord == "CARTESIAN") {
	MovePen(10, 380);
	DrawTextString("Default font");

	MovePen(120,220);
	EllipseSegments(60, 80);

	TextLayout(10, 100);
    }
    else if (coord == "SCREEN") {
	MovePen(10, 20);
	DrawTextString("Default font");

	MovePen(120, 180);
	EllipseSegments(60, 80);

	TextLayout(10, 300);
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

    if (coord == "INCH") MovePen(0.20, 3.80 - height);
    else if (coord == "CARTESIAN") MovePen(20, 380 - height);
    else if (coord == "SCREEN") MovePen(20, height + 40);

    msg = "Width: " + RealToString(width) +
	"   height: " + RealToString(height);
    DrawTextString(msg);

    if (coord == "INCH") MovePen(0.50 + width, 3.80);
    else if (coord == "CARTESIAN") MovePen(50 + width, 380);
    else if (coord == "SCREEN") MovePen(50 + width, 20);

    DrawNamedPicture("Heckert_GNU.png");
    width = GetPictureWidth("Heckert_GNU.png");
    height = GetPictureHeight("Heckert_GNU.png");

    if (coord == "INCH") MovePen(GetCurrentX(), 3.80 - height);
    else if (coord == "CARTESIAN") MovePen(GetCurrentX(), 380 - height);
    else if (coord == "SCREEN") MovePen(GetCurrentX(), height + 40);

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
	SetFont("Comic Sans");
	SetPointSize(20);
	StateTest("20pt Comic", 0.60, 3.20);
	RestoreGraphicsState();
	StateTest("First restore (to default)", 0.70, 2.40);
	RestoreGraphicsState();
	StateTest("Second restore (to entry values)", 0.80, 1.80);
    }
    else if (coord == "CARTESIAN") {
	StateTest("Default state", 50, 380);
	MovePen(250, 330);
	SetFont("Comic Sans");
	SetPointSize(20);
	StateTest("20pt Comic", 60, 320);
	RestoreGraphicsState();
	StateTest("First restore (to default)", 70, 240);
	RestoreGraphicsState();
	StateTest("Second restore (to entry values)", 80, 180);
    }
    else if (coord == "SCREEN") {
	StateTest("Default state", 50, 20);
	MovePen(250, 70);
	SetFont("Comic Sans");
	SetPointSize(20);
	StateTest("20pt Comic", 60, 80);
	RestoreGraphicsState();
	StateTest("First restore (to default)", 70, 160);
	RestoreGraphicsState();
	StateTest("Second restore (to entry values)", 80, 220);
    }
}

void StateTest(string msg, double x, double y)
{
    stringstream forOutput;
    forOutput << msg << "  x: " << GetCurrentX() << "  y: " << GetCurrentY();
    MovePen(x,y);
    DrawTextString(forOutput.str());
    MovePen(x, y+GetFontHeight());
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
