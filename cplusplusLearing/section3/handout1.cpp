//Filename:handout1.cpp
/**defined a struct 
 * store in a set
 * write a comparision
 */

#include<iostream>
#include<string>
#include<set>
#include"strutils.h"

using namespace std;

struct entryT{
    string firstName;
    string lastName;
    string phoneNumber;
};

//int CompareEntry(entryT one,entryT two);
//set<entryT> addresses(CompareEntry);
bool operator<(const entryT &a,const entryT &b);
bool operator<(const string &a,const string &b);
void teststruct();
void teststring();

int main(){

    teststruct();
    teststring();
    return 0;
}

void teststring(){
    set<string> wf;
    string tg="hello";
    string ld="Hello";
    string dj="hello";
    cout<<(tg<ld)<<endl;
    cout<<(ld<tg)<<endl;
    cout<<(tg<dj)<<endl;
    cout<<(tg==dj)<<endl;
    wf.insert(tg);
    wf.insert(ld);
    wf.insert(dj);
    cout<<wf.size()<<endl;
    cout<<"count tg:"<<wf.count(tg)<<endl;
    cout<<"count ld:"<<wf.count(ld)<<endl;
    cout<<"count dj:"<<wf.count(dj)<<endl;
    set<string>::iterator itr=wf.begin();
    while(itr!=wf.end()){
        cout<<*itr<<endl;
        itr++;
    }
}


bool operator<(const string &a,const string &b){
    /*
    string la=ConvertToLowerCase(a);
    string lb=ConvertToLowerCase(b);
    if(la<lb) return true;
    else return false;
    */
    for(unsigned int i=0;i<(a.size()<b.size()?a.size():b.size());i++){
        char la,lb;
        if(a[i]>='A'&&a[i]<='Z') la=a[i]+32;
        else la=a[i];
        if(b[i]>='A'&&b[i]<='Z') lb=b[i]+32;
        else lb=b[i];
        if(la<lb) return true;
    }
    return false;
}

void teststruct(){
    entryT wf;
    wf.firstName="w";
    wf.lastName="f";
    wf.phoneNumber="1333";
    entryT tg;
    tg.firstName="w";
    tg.lastName="f";
    tg.phoneNumber="13";
    entryT ld;
    ld.firstName="w";
    ld.lastName="l";
    ld.phoneNumber="1";
    set<entryT> book;
    book.insert(wf);
    book.insert(tg);
    book.insert(ld);
    cout<<book.size()<<endl;
    cout<<book.count(wf)<<endl;
    cout<<book.count(tg)<<endl;
    cout<<book.count(ld)<<endl;
    
    set<entryT>::iterator itr=book.begin();
    while(itr!=book.end()){
        cout<<(*itr).phoneNumber<<endl;
        itr++;
    }

}
/*
int CompareEntry(entryT one,entryT two){
    if(one.lastName<two.lastName) return -1;
    else if(one.lastName>two.lastName) return 1;
    else if(one.firstName<two.firstName) return -1;
    else if(one.firstName>two.firstName) return 1;
    else return 0;
}
*/

bool operator<(const entryT &a,const entryT &b){
    if(a.firstName<b.firstName) return true;
    
    else if(a.firstName==b.firstName){
        if(a.lastName<b.lastName) return true;
        else return false;
    }
    else return false;
}

