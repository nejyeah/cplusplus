//Filename:handout1.cpp
/*
 * paint the 
 */
#include<iostream>
#include<vector>
#include<iomanip>
#include"grid.h"
#include"graphics.h"
#include"extgraph.h"

enum pixelStateT { White,Black };
struct pointT {
    int row,col;
};

void FillRegion(pointT pt,Grid<pixelStateT> &screen);
void paint_house(Grid<pixelStateT> &screen);
void Draw_house_arc(const Grid<pixelStateT> &screen);

int main(){
    InitGraphics();
    Grid<pixelStateT> screen(40,40);
    paint_house(screen);
    Draw_house_arc(screen);
    pointT a;
    FillRegion(a,screen);

    return 0;
}

void paint_house(Grid<pixelStateT> &screen){
    for(int row=0;row<screen.numRows();row++){
        for(int col=0;col<screen.numCols();col++){
            screen.setAt(row,col,White);
        }

    }

    for(int row=2;row<10;row++){
        screen.setAt(row,2,Black);
        screen.setAt(row,9,Black);
    }
    for(int col=2;col<10;col++){
        screen.setAt(2,col,Black);
        screen.setAt(9,col,Black);
    }

    for(int row=2;row<10;row++){
        screen.setAt(row,30,Black);
        screen.setAt(row,38,Black);
    }
    for(int col=30;col<38;col++){
        screen.setAt(2,col,Black);
        screen.setAt(9,col,Black);
    }

    for(int row=17;row<24;row++){
        screen.setAt(row,17,Black);
        screen.setAt(row,23,Black);
    }
    for(int col=17;col<24;col++){
        screen.setAt(17,col,Black);
        screen.setAt(23,col,Black);
    }
}

void Draw_house_arc(const Grid<pixelStateT> &screen){
    
}

void FillRegion(pointT pt,Grid<pixelStateT> &screen){
    int row=pt.row;
    int col=pt.col;
    pointT p=pt;
    if(!screen.inBounds(p.row,p.col)) return ;
    if(screen.getAt(row,col)==White){
        screen.setAt(row,col,Black);
        p.row=pt.row+1;
        p.col=pt.col;
        FillRegion(p,screen);
        p.row=pt.row-1;
        p.col=pt.col;
        FillRegion(p,screen);
        p.row=pt.row;
        p.col=pt.col+1;
        FillRegion(p,screen);
        p.row=pt.row;
        p.col=pt.col-1;
        FillRegion(p,screen);

    }
}
