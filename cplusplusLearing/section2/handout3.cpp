//Filename:handout3.cpp
/**can detect some error
 */

#include<iostream>
#include<string>
#include<stack>
#include"scanner.h"

using namespace std;
//use scanner.h
bool IsCorrectlyNested(string htmlStr);
//no use scanner.h
bool IsCorrectlyNested1(string htmlStr);

int main(){

    string html="<html><b><i>CS106 rules!</i></b></html>";
    //bool flag=IsCorrectlyNested1(html);
    bool flag=IsCorrectlyNested(html);
    cout<<"Is correct:"<<flag<<endl;
    return 0;
}

bool IsCorrectlyNested(string htmlStr){
    stack<string> sta;
    Scanner scanner;
    scanner.setInput(htmlStr);
    scanner.setSpaceOption(Scanner::IgnoreSpaces);
    string tem;
    int flag=0;
    while(scanner.hasMoreTokens()){
        string token = scanner.nextToken();
        //cout<<"token:"<<token<<endl;
        //cout<<"tem:"<<tem<<endl;
        if(flag==0){
            if(token=="<"){
                flag=1;
                tem+=token;
                //cout<<"tem:"<<tem<<endl;

            }
            else if(token==">") return false;
        }
        else if(flag==1){
            if(token=="<") return false;
            else if(token==">"){
                tem+=token;
                //cout<<"tem:"<<tem<<endl;
                if(!sta.empty()){
                    string deltoken=tem;
                    deltoken.erase(deltoken.begin()+1);
                    //cout<<"deltoken:"<<deltoken<<endl;
                    if(deltoken==sta.top()) sta.pop();
                    else sta.push(tem);
                }
                else sta.push(tem);
                tem.clear();
                flag=0;
            }
            else{
                tem+=token;
                //cout<<"tem:"<<tem<<endl;
            }
        }
    }
    if(sta.empty()) return true;
    else return false;
}

bool IsCorrectlyNested1(string htmlStr){
    stack<string> sta;
    string::iterator itr=htmlStr.begin();
    int flag=0;
    string tem;
    while(itr!=htmlStr.end()){
        if(flag==0){
            if(*itr=='<'){
                flag=1;
                tem.push_back(*itr); 
            }
            if(*itr=='>') return false;
        }
        else if(flag==1){
            if(*itr=='>'){
                tem.push_back(*itr);
                if(!sta.empty()){
                    string deltem=tem;
                    deltem.erase(deltem.begin()+1);
                    if(deltem==sta.top()) sta.pop();
                    else sta.push(tem);
                }
                else{
                    sta.push(tem);
                }
                tem.clear();
                flag=0;
            }
            else if(*itr=='<') return false;
            else{
                tem.push_back(*itr);
            }
        }
        itr++;
    }
    if(sta.empty()) return true;
    else return false;
}
