//Filename:handout8.cpp

#include<iostream>
#include<string>
#include<map>

using namespace std;

void ListMnemonics(string str);
int list(string prix,string str,const map<char,string> keyboard);

int main(){
    while(true){
        string str;
        cout<<"enter a numerstring(0 to quit):";
        cin>>str;
        if(str=="0") break;
        ListMnemonics(str);
    }
}

void ListMnemonics(string str){
    map<char,string> keyboard;
    keyboard.insert(make_pair('0',"0"));
    keyboard.insert(make_pair('1',"1"));
    keyboard.insert(make_pair('2',"ABC"));
    keyboard.insert(make_pair('3',"DEF"));
    keyboard.insert(make_pair('4',"GHI"));
    keyboard.insert(make_pair('5',"JKL"));
    keyboard.insert(make_pair('6',"MNO"));
    keyboard.insert(make_pair('7',"PRS"));
    keyboard.insert(make_pair('8',"TUV"));
    keyboard.insert(make_pair('9',"WXY"));
    string prix;
    int count=list(prix,str,keyboard);
    cout<<"count:"<<count<<endl;

}

int list(string prix,string str,const map<char,string> keyboard){
    if(str.size()==0){
        cout<<prix<<endl;
        return 1;
    }
    int count=0;

    string pro=keyboard.find(str[0])->second;
    str=str.substr(1);
    for(unsigned int i=0;i<pro.size();i++){
        string p=prix;
        p.push_back(pro[i]);
        count+=list(p,str,keyboard);
    }

    return count;
}
