#include <string>
#include <iostream>
using namespace std;

#include "extgraph.h"
#include "graphics.h"
#include "random.h"


void SetPoint(double &x,double &y);
void LinkPoint(double,double,double,double);
void RandomPoint(double &,double &,double,double,double,double,double,double);

const double radius=0.01;

void main(){
    InitGraphics();
    cout<<"hello";
    double Ax,Ay;
    SetPoint(Ax,Ay);

    cout<<Ax<<"HHHH"<<Ay;
    double Bx,By;
    SetPoint(Bx,By);


    double Cx,Cy;
    SetPoint(Cx,Cy);

    LinkPoint(Ax,Ay,Bx,By);
    LinkPoint(Bx,By,Cx,Cy);
    LinkPoint(Cx,Cy,Ax,Ay);

    double movingPointX,movingPointY;
    RandomPoint(movingPointX,movingPointY,Ax,Ay,Bx,By,Cx,Cy);
    MovePen(movingPointX,movingPointY);
    cout<< movingPointX<<" "<< movingPointY;
    
    MovePen(1,1);
    cout<<GetCurrentX()<<"--"<<GetCurrentY();
    DrawArc(radius,0.0,360.0); 

    double aimPointX,aimPointY;
    bool flag=true;
    while(flag){
        RandomPoint(aimPointX,aimPointY,Ax,Ay,Bx,By,Cx,Cy);
        movingPointX=(movingPointX+aimPointX)/2;
        movingPointY=(movingPointY+aimPointY)/2;
        MovePen(movingPointX,movingPointY);
        DrawArc(radius,0,360);
        UpdateDisplay();
        if(MouseButtonIsDown()){
            flag=false;
        }
    }

}

void SetPoint(double & x,double & y){
    WaitForMouseDown();
    x= GetMouseX();
    y= GetMouseY();
    WaitForMouseUp();
}

void LinkPoint(double x1,double y1, double x2,double y2){
    MovePen(x1,y1);
    DrawLine(x2-x1,y2-y1);
}

void RandomPoint(double & x,double & y,double x1,double y1,double x2,double y2,double x3,double y3){
    switch(RandomInteger(1,4)){
        case 1:
            x=x1;
            y=y1;
            break;
        case 2:
            x=x2;
            y=y2;
            break;
        case 3:
            x=x3;
            y=y3;
            break;
    }
}
