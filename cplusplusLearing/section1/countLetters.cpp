//Filename:countLetters.cpp

#include<iostream>
#include<string>
#include<fstream>
#include<cctype>
#include<stdlib.h>
using namespace std;

void CountLetters(string filename);

int main(){
    string filename="letters.txt";
    string f="hello\n\0";
    cout<<(int)f[5]<<endl;
    cout<<(int)f[6]<<endl;
    cout<<(int)f[7]<<endl;
    cout<<(int)f[8]<<endl;
    CountLetters(filename);
    return 0;
}

void CountLetters(string filename){
    ifstream fp(filename.c_str());
    if(fp.is_open()){
        char a;
        //int test='a';
        //cout<<"a:"<<test<<endl;
        int num[26]={0};
        while(fp>>a){
            if(a>='a'&&a<='z'||a>='A'&&a<='Z'){
                a=tolower(a);
                num[a-97]++;
            }
        }
        char b='a';
        for(int i=0;i<26;i++){
            
            cout<<b<<": "<<num[i]<<endl;
            b=b+1;
        }
    }
    else{
        cout<<"can not open the file "<<filename<<endl;
    }
}
