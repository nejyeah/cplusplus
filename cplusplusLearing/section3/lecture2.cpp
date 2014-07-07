//Filename:lecture2.cpp
/**recursion problem
 * get all substring of a string
 */

#include<iostream>
#include<string>

using namespace std;

void RecSubsets(string soFar,string rest);

int main(){
    while(true){
        string soFar="";
        string rest;
        cout<<"please input a string(q to quit):";
        cin>>rest;
        if(rest=="q") break;
        cout<<"-----"<<endl;
        RecSubsets(soFar,rest);

    }
    return 0;
}

void RecSubsets(string soFar,string rest){
    if(rest.empty()){
        cout<<soFar<<endl;
    }
    else{
        RecSubsets(soFar+rest[0],rest.substr(1));
        RecSubsets(soFar,rest.substr(1));
    }
}
