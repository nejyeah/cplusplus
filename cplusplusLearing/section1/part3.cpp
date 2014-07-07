//Filename:part3.cpp 
//about graphics

#include<iostream>
#include"graphics.h"
#include"extgraph.h"
#include"random.h"
using namespace std;

int main(){
    InitGraphics();
    WaitForMouseDown();
    double xA;
    double yA;

    double xB;
    double yB;
    double xC;
    double yC;
    const double r=0.01;
    bool flag=true;
    WaitForMouseDown();
    xA=GetMouseX();
    yA=GetMouseY();
    WaitForMouseUp();
    WaitForMouseDown();
    xB=GetMouseX();
    yB=GetMouseY();
    WaitForMouseUp();
    WaitForMouseDown();
    xC=GetMouseX();
    yC=GetMouseY();
    WaitForMouseUp();
    cout<<"Width:"<<GetWindowWidth()<<endl;
    cout<<"Height:"<<GetWindowHeight()<<endl;

    //StartFilledRegion(0.6);
    MovePen(xA,yA);
    DrawLine(xC-xA,yC-yA);
    DrawLine(xB-xC,yB-yC);
    DrawLine(xA-xB,yA-yB);
    while(flag){ 
        int i=RandomInteger(1,4);
        //cout<<i<<endl;
        if(i==1){
            MovePen((GetCurrentX()+xA)/2,(GetCurrentY()+yA)/2);
            MovePen(GetCurrentX()+r,GetCurrentY());
            //DrawLine((xA-GetCurrentX())/2,(yA-GetCurrentY())/2);
            DrawArc(r,0,360);
            MovePen(GetCurrentX()-r,GetCurrentY());
        }
        else if(i==2){
            MovePen((GetCurrentX()+xB)/2,(GetCurrentY()+yB)/2);
            MovePen(GetCurrentX()+r,GetCurrentY());
            //DrawLine((xB-GetCurrentX())/2,(yB-GetCurrentY())/2);
            DrawArc(r,0,360);
            MovePen(GetCurrentX()-r,GetCurrentY());

        }
        else{
            MovePen((GetCurrentX()+xC)/2,(GetCurrentY()+yC)/2);
            MovePen(GetCurrentX()+r,GetCurrentY());
            //DrawLine((xC-GetCurrentX())/2,(yC-GetCurrentY())/2);
            DrawArc(r,0,360);
            MovePen(GetCurrentX()-r,GetCurrentY());

        }
        if(MouseButtonIsDown()){
            flag=false;
        }
    }

    return 0;
}

