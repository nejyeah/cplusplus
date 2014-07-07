//Filename:part1.cpp
/**
 * cout ways of mixture of one and two steps through numStairs
 */

#include<iostream>

using namespace std;

int CountWays(int numStairs);

int main(){
    int numStairs;
    while(true){
        cout<<"Enter the numStairs(0 to quit):"<<endl;
        cin>>numStairs;
        if(numStairs==0) break;
        int ways=CountWays(numStairs);
        cout<<"ways:"<<ways<<endl;
        cout<<".............."<<endl;
    }
}

int CountWays(int numStairs){
    if(numStairs==0) return 1;
    else if(numStairs<0) return 0;
    else{
        return CountWays(numStairs-1)+CountWays(numStairs-2);
    }
}
