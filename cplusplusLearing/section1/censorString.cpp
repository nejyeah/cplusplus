//Filename:censorString.cpp

#include<iostream>
#include<string>
using namespace std;

string CensorString1(string text,string remove);
void CensorString2(string &text,string remove);

int main(){
    string text;
    string remove;
    string output;
    cout<<"please input two string:"<<endl;
    cin>>text>>remove;
    //output=CensorString1(text,remove);
    CensorString2(text,remove);
    //cout<<"the output:"<<output<<endl;
    cout<<"the text:"<<text<<endl;
    return 0;
}

string CensorString1(string text,string remove){
    string output;
    cout<<"method1"<<endl;
    for(int i=0;i<text.size();i++){
        if(remove.find(text[i])==string::npos){
            output.push_back(text[i]);
        }
    }
    return output;
}

void CensorString2(string &text,string remove){
    string::iterator iter1;
    cout<<"method2"<<endl;
    for(iter1=text.begin();iter1!=text.end();iter1++){
        if(remove.find(*iter1)!=string::npos){
            text.erase(iter1);
            iter1--;
        }
    }
}
