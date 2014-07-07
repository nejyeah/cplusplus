//Filename:test.cpp

#include<iostream>
#include<string>
#include<fstream>
#include<stdlib.h>
using namespace std;

int main(){
    string a="hello";
    string filename;
    ifstream fp;
    cout<<a.back()<<endl;
    cout<<"enter a filename:";
    cin>>filename;
    fp.open(filename.c_str());
    if(fp.is_open()){
        cout<<"opened"<<endl;
    }
    cout<<filename<<endl;
}
