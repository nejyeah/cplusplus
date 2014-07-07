//Filename:fileStruct.cpp
#include<iostream>
#include<fstream>
#include"stdlib.h"

using namespace std;

struct classStruct{
    int min;
    int max;
    double average;
};
void getlessonstruct(classStruct &lesson,const string filename);

int main(){
    classStruct lesson;
    string filename="grad.txt";
    getlessonstruct(lesson,filename);
    cout<<"min:"<<lesson.min<<endl;
    cout<<"max:"<<lesson.max<<endl;
    cout<<"average:"<<lesson.average<<endl;
    return 0;
}

void getlessonstruct(classStruct &lesson,const string filename){
    ifstream fp(filename.c_str());
    int n=0;
    int temp=0;
    lesson.min=100;
    lesson.max=0;
    int total=0;
    if(fp.is_open()){
        //string grad;
        int grad;
        while(fp>>grad){
            //int a=atoi(grad.c_str());
            //cout<<a<<endl;
            //total+=a;
            cout<<grad<<endl;
            total+=grad;
            n++;
            if(lesson.min>grad) lesson.min=grad;
            if(lesson.max<grad) lesson.max=grad;
        }
        lesson.average=(double)total/n;
    }
    else{
        cout<<"can not open the file!"<<endl;
    }
}
