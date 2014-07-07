//Filename:handout6.cpp
/*
 * append the second list onto the first
 */

#include<iostream>
#include<list>

using namespace std;

void appendlist(list<int> &list1,list<int> &list2);
int main(){
    list<int> list1;
    list<int> list2;
    int num;
    cout<<"enter the num in list1(0 to end):";
    while(true){
        cin>>num;
        if(num==0) break;
        list1.push_back(num);
    }
    cout<<"enter the num in list2(0 to end):";
    while(true){
        cin>>num;
        if(num==0) break;
        list2.push_back(num);
    }
    appendlist(list1,list2);
    cout<<"list1:";
    for(list<int>::iterator itr=list1.begin();itr!=list1.end();itr++){
        cout<<*itr<<",";
    }
    cout<<endl;
}

void appendlist(list<int> &list1,list<int> &list2){
    if(!list2.empty()){
        list1.push_back(list2.front());
        list2.pop_front();
        appendlist(list1,list2);
    }
}
