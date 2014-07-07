//Filename:part4.cpp

#include<iostream>
#include<string>
#include"strutils.h"
using namespace std;
int main(){
    const string table[]={"AEIOUHWY","BFPV","CGJKQSXZ","DT","MN","L","R"};
    //const string stop="RETURN";
    string name;
    bool flag=true;
    while(flag){
        string code;
        cout<<"Enter surname (RETURN to quit):";

        cin>>name;
        name=ConvertToUpperCase(name);
        if(name==""){
            flag=false;
        }
        else{
            code.push_back(name[0]);
            for(int i=1;i<name.size();i++){
                for(int j=1;j<7;j++){
                    if(table[j].find(name[i])!=string::npos)
                        if((code.back()-'0')!=j){
                            code+=RealToString(j);
                        }
                }

            }
            if(code.size()>4){
                code=code.substr(0,4);
            }
            while(code.size()<4){
                code+="0";
            }
            cout<<"Soundex code for "<<name<<" is "<<code<<endl;
        }
    }
    return 0;
}


