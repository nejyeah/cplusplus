//Filename:test.cpp
#include<iostream>
#include<vector>
#include<set>
#include"compare.h"

using namespace std;
bool operator<(const vector<int> &A,const vector<int> &B){
    int Atotal=0;
    int Btotal=0;
    for(unsigned int i=0;i<A.size();i++){
        Atotal+=A[i];
    }

    for(unsigned int j=0;j<B.size();j++){
        Btotal+=B[j];
    }

    if(Atotal<Btotal) return true;
    else return false;
}
int main(){
    int b=3;
    int c=4;
    Compare<int> e(b,c);
    cout<<e.max()<<"   max"<<endl;
    cout<<e.min()<<"   min"<<endl;

    set<vector<int> > a;
    vector<int> a1;
    a1.push_back(4);
    a1.push_back(5);
    a.insert(a1);
    vector<int> a2;
    a2.push_back(1);
    a2.push_back(2);
    a.insert(a2);

    vector<int> a3=*(a.begin());
    for(unsigned int j=0;j<a3.size();j++){
        cout<<a3[j]<<endl;
    }

    return 0;
}
