/* File: testlib.h
 * Last modified: September 2011 by Colin
 *------------------------------------
 * This program aims to test the various functions in the 
 * Graphics and Extgraph libraries
 */

#ifndef _testlib_h
#define _testlib_h

#include "genlib.h"

void MiscGraphics();
void Fills();
void MouseStuff();
void Pictures();
void Erasing();
void Info();
void Saves();
void DrawMaze();
void DrawBoggle();
void DrawFill(double width, double height, double density);
void FillGradient(double y);
void EllipseSegments(double w, double h);
void TextLayout(double x, double y);
void CustomColors();
void DrawRect(double w, double h);
string GetFontDescription();
void StateTest(string msg, double x, double y);

#endif
