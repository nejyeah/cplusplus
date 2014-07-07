//Filename:part5.cpp
/**solve a puzzle row 
 */
#include<iostream>
#include<vector>
#include<set>
#include"random.h"

using namespace std;

bool Solvable(int start,vector<int> &squares);
bool solve(int start,vector<int> &squares,set<int> &include);
bool Solvable1(int start,vector<int> &squares);

int main(){
    while(true){
        vector<int> squares;
        cout<<"Enter the row number(one 0 to quit):"<<endl;
        int num;
        while(true){
            cin>>num;
            squares.push_back(num);
            if(num==0) break;
        }
        if(squares.size()==1) break;
        //bool result=Solvable(0,squares);
        bool result=Solvable1(0,squares);
        cout<<"can solve? "<<result<<endl;
    }
}

bool Solvable1(int start,vector<int> &squares){
    set<int> include;
    include.insert(start);
    return solve(start,squares,include);
}

bool solve(int start,vector<int> &squares,set<int> &include){
    if(start==squares.size()-1) return true;
    int nextstart;
    nextstart=start+squares[start];
    if(nextstart<squares.size()&&include.count(nextstart)==0){
        include.insert(nextstart);
        if(solve(nextstart,squares,include)) return true;
    }
    nextstart=start-squares[start];
    if(nextstart>0&&include.count(nextstart)==0){
        include.insert(nextstart);
        if(solve(nextstart,squares,include)) return true;
    }
    return false;
}

bool Solvable(int start,vector<int> &squares){
    if(start==squares.size()-1) return true;
    if(squares[start]<=start&&squares[start]+start<squares.size()){
        switch(RandomInteger(0,2)){
            case 0:

                if(Solvable(start-squares[start],squares)) return true;
                else{
                    if(Solvable(start+squares[start],squares)) return true;
                }
                break;
            case 1:
                if(Solvable(start+squares[start],squares)) return true;
                else{
                    if(Solvable(start-squares[start],squares)) return true;
                }
                break;
        }
    }
    else if(squares[start]<=start){
        if(Solvable(start-squares[start],squares)) return true;
    }
    else if(squares[start]+start<squares.size()){
        if(Solvable(start+squares[start],squares)) return true;
    }
    return false;
}
