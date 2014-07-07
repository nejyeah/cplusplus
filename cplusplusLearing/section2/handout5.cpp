//Filename:handout5.cpp

#include<iostream>
#include"grid.h"
#include"random.h"
using namespace std;

Grid<int> MakeGridOfCounts(Grid<bool> &bombLocations);
int main(){
    Grid<bool> g(10,10);
    for(int row=0;row<g.numRows();row++){
        for(int col=0;col<g.numCols();col++){
            int i=RandomInteger(0,4);
            if(i<3) g.setAt(row,col,false);
            else g.setAt(row,col,true);
            cout<<g.getAt(row,col)<<" ";
        }
        cout<<endl;
    }
    Grid<int> result=MakeGridOfCounts(g);

    return 0;
}

Grid<int> MakeGridOfCounts(Grid<bool> &bombLocations){
    Grid<int> number(bombLocations.numRows(),bombLocations.numCols());
    for(int row=0;row<number.numRows();row++){
        for(int col=0;col<number.numCols();col++){
            int count=0;
            for(int i=0;i<4;i++){
                switch(i){
                    case 0:
                        if(bombLocations.inBounds(row-1,col)){
                            bool f=bombLocations.getAt(row-1,col);
                            if(f) count++;
                        }
                        break;
                    case 1:
                        if(bombLocations.inBounds(row+1,col)){
                            bool f=bombLocations.getAt(row+1,col);
                            if(f) count++;
                        }
                        break;
                    case 2:
                        if(bombLocations.inBounds(row,col-1)){
                            bool f=bombLocations.getAt(row,col-1);
                            if(f) count++;
                        }
                        break;
                    default:
                        if(bombLocations.inBounds(row,col+1)){
                            bool f=bombLocations.getAt(row,col+1);
                            if(f) count++;
                        }
                        break;
                }
            }
            number.setAt(row,col,count);
            cout<<count<<" ";
            
        }
        cout<<endl;
    }
    return number;
}
