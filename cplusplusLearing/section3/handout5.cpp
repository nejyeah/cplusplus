//Filename:handout5.cpp
//
#include<iostream>
#include<string>

using namespace std;
string ReverseString(string str);
string ReverseStringIte(string str);

int main(){
    string str;
    while(true){
        cout<<"enter a string(q to quit):";
        cin>>str;
        if(str=="q") break;
        cout<<"recursive:"<<ReverseString(str)<<endl;
        cout<<"iterator:"<<ReverseStringIte(str)<<endl;
    }
    return 0;
}

string ReverseString(string str){
    if(str.size()==1) return str;
    else{
        return ReverseString(str.substr(1))+str[0];
    }
}

string ReverseStringIte(string str){
    string result="";
    for(int i=str.size()-1;i>=0;i--){
        result+=str[i];
    }
    return result;
}
