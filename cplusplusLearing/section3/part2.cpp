//Filename:part2.cpp
/**divide the rectangle 
*/

#include<iostream>
#include"graphics.h"
#include"extgraph.h"

using namespace std;

void DrawRuler(double x,double y,double w,double h); 
int main(){
    double w,h;
    double x,y;
    InitGraphics();
    while(true){
        cout<<"Enter the w and h(0 to quit):";
        cin>>w>>h;
        if(w==0||h==0) break;
        SetWindowSize(w,h);
        x=0;
        y=w;
        DrawRuler(x,y,w,h);
    }
    return 0;
}

void DrawRuler(double x,double y,double w,double h){
    if(h>0.05){ 
        MovePen((x+y)/2,0);
        DrawLine(0,h);
        DrawRuler(x,(x+y)/2,w,h/2);
        DrawRuler((x+y)/2,y,w,h/2);
    }
}

