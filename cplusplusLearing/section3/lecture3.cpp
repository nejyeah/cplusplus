//Filename:lecture3.cpp
/**recursion problem
 * about 8 queens
 * and some test about graphis
 * to plot the resluts
 */

#include<iostream>
//#include"graphics.h"
//#include"extgraph.h"
#include"grid.h"

using namespace std;
bool Solve(Grid<bool> &board,int col,int &count);
bool IsSafe(Grid<bool> board,int row,int col);
bool RowIsClear(Grid<bool> board,int row,int col);
bool LowerDiagIsClear(Grid<bool> board,int row,int col);
bool UpperDiagIsClear(Grid<bool> board,int row,int col);

int main(){
    //InitGraphics();
    int count=0;
    Grid<bool> board(8,8);
    for(int i=0;i<board.numRows();i++){
        for(int j=0;j<board.numCols();j++){
            board.setAt(i,j,false);
        }
    }
    Solve(board,0,count);
    cout<<"count:"<<count<<endl;
    return 0;
}

bool Solve(Grid<bool> &board,int col,int &count){
    if(col>=board.numCols()){
        for(int i=0;i<board.numRows();i++){
            for(int j=0;j<board.numCols();j++){
                cout<<board.getAt(i,j)<<" ";
            }
            cout<<endl;
        }
        cout<<".............."<<endl;
        count++;
        return true;
    }

    for(int rowToTry=0;rowToTry<board.numRows();rowToTry++){
        if(IsSafe(board,rowToTry,col)){
            board.setAt(rowToTry,col,true);
            //if(Solve(board,col+1,count)) return true;
            Solve(board,col+1,count);
            board.setAt(rowToTry,col,false);
        }
    }
    return false;
}

bool IsSafe(Grid<bool> board,int row,int col){
    return (LowerDiagIsClear(board,row,col)&&RowIsClear(board,row,col)&&UpperDiagIsClear(board,row,col));
}

bool RowIsClear(Grid<bool> board,int row,int col){
    for(int j=0;j<col;j++){
        if(board.getAt(row,j)) return false;
    }
    return true;
}

bool LowerDiagIsClear(Grid<bool> board,int row,int col){
    for(int i=row-1,j=col-1;i>=0&&j>=0;i--,j--){
        if(board.getAt(i,j)) return false;
    }
    return true;
}

bool UpperDiagIsClear(Grid<bool> board,int row,int col){
    for(int i=row+1,j=col-1;i<board.numRows()&&j>=0;i++,j--){
        if(board.getAt(i,j)) return false;
    }
    return true;
}
