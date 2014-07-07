//Filename:part1.cpp

#include<iostream>
#include<vector>
#include<string>
#include"vector.h"
#include"mysterysort.h"

using namespace std;

template<typename T>
int compare(const T &v1,const T &v2);

int main(){
    int a=1;
    int b=2;
    Vector<int> v;
    v.add(3);
    v.add(2);
    v.add(1);
    
    MysterySort1(v);
    
    string c="a";
    string d="b";
    cout<<compare(a,b)<<endl;
    cout<<compare(c,d)<<endl;
   return 0;
}

template<typename T>
int compare(const T &v1,const T &v2){
    if(v1<v2) return -1;
    if(v2<v1) return 1;
    return 0;
}
