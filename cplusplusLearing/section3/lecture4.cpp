//Filename:lecture4.cpp
//
/**recursion problem 
 * about solve puzzles
 * still not plot it
 * just using grid.h
 */

#include<iostream>
#include"grid.h"
#include"random.h"
using namespace std;

void SolveSudoku(Grid<int> &puzzle);
void initpuzzle(Grid<int> &puzzle,const int initnumber);
int main(){
    const int initnumber=40;
    Grid<int> puzzle(9,9);
    initpuzzle(puzzle);
    SolveSudoku
}

void initpuzzle(Grid<int> &puzzle,const int initnumber){
    for(int i=0;i<puzzle.numRows();i++){
        for(int j=0;j<puzzle.numCols();j++){
            puzzle.setAt(i,j,0);
        }
    }
    int number=initnumber;
    while(number!=0){
        
    }
}

void SolveSudoku(Grid<int> &puzzle){
    
}
