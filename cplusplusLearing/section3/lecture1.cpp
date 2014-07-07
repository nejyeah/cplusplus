//Filename:lecture1.cpp
/**recursion problem 
 * re-arrangements of letters
 */
#include<iostream>
#include<string>

using namespace std;

void RecPermute(string soFar,string rest);
int main(){
    while(true){
        string rest;
        string soFar="";
        cout<<"enter a string(q to quit):"<<endl;
        cin>>rest;
        if(rest=="q") break;
        cout<<"----------"<<endl;
        RecPermute(soFar,rest);
    }
    return 0;
}

void RecPermute(string soFar,string rest){
   if(rest.empty()){
        cout<<soFar<<endl;
   }
   else{
        for(int i=0;i<rest.size();i++){
            string remaining=rest.substr(0,i)+rest.substr(i+1);
            RecPermute(soFar+rest[i],remaining);
        }
   }
}
