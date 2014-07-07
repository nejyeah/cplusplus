//Filename:part1.cpp
/*The function is to read a file of character,based on Markov 
 *seed,read character-by-character and observe what follows the
 *characters.According to frequency information to generate random 
 *text
 *
 * use fp.get() will not mis the space or enter
 */

#include<iostream>
#include<fstream>
#include<string>
#include<map>
#include<vector>
#include"strutils.h"
#include"random.h"
#include"simpio.h"
using namespace std;

string produceText(const map<string,vector<char> > &Marcovchain,const unsigned int textLength);

int main(){
    const unsigned int textLength=2000;
    string filename;
    ifstream fp;
    while(true){
        cout<<"please input the filename:"<<endl;
        cin>>filename;
        fp.open(filename.c_str());
        if(fp.is_open()){
            break;
        }
        else{
            cout<<"invaild filename!"<<endl;
        }
    }
    cout<<"please input the Marcov seed:"<<endl;
    unsigned int seed=GetInteger();

    char ch;
    map<string ,vector<char> > Marcovchain;
    string key;
    vector<char> follow;
    while((ch=fp.get())!=EOF){

        if(key.size()==seed){
            //whether the key is already in the map
            
            map<string, vector<char> >::iterator it = Marcovchain.find(key);
            if(it!=Marcovchain.end()){
                it->second.push_back(ch);
            }
            else{
                follow.push_back(ch);
                Marcovchain.insert(make_pair(key,follow));
            }

            key.erase(key.begin());
            key.push_back(ch);
            follow.clear();
        }
        else{
            key.push_back(ch);
        }

    }
    string text;
    text=produceText(Marcovchain,textLength);
    cout<<"produce text:"<<endl;
    cout<<text<<endl;
    return 0;
}

string produceText(const map<string,vector<char> > &Marcovchain,const unsigned int textLength){
    unsigned int init=0;
    string init_character="";

    //find out the key which appear most,and store it in init_character
    map<string,vector<char> >::const_iterator it=Marcovchain.begin();
    while(it!=Marcovchain.end()){
        if(init<it->second.size()){
            init=it->second.size();
            init_character=it->first;
        }
        it++;
    }
    
    string text=init_character;
    //base on the marcovchain to produce text
    //stop only if the characters is not in the map,or text come to is limited length 
    while(true){
        map<string, vector<char> >::const_iterator iter = Marcovchain.find(init_character);
        if(iter==Marcovchain.end()){
            break;
        }
        else{
            int length=iter->second.size();
            //cout<<"length:"<<length<<endl;
            int index=RandomInteger(0,length);
            //cout<<"index:"<<index<<endl;
            char a=iter->second[index];
            text.push_back(a);
            init_character.erase(init_character.begin());
            init_character.push_back(a);
        }
        if(text.size()==textLength){
            break;
        }
    }
    return text;

}
