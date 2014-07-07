//Filename:part4.cpp

/**problem about detect the prefix of a word
 */

#include<iostream>
#include<string>
#include<vector>
#include<string>
#include<map>
#include"lexicon.h"
#include"strutils.h"

using namespace std;

void ListCompletions(string digitSequence,Lexicon &lex);
int ListWords(const map<char,string> &keypads,string prex,string digitSequence,string alber,Lexicon &lex);

int main(){
    //cout<<sizeof(int)<<endl;
    while(true){
        string digis="";
        cout<<"Enter a digitSequence('q' to quit):";
        cin>>digis;
        if(digis=="q") break;
        else{
            digis=ConvertToLowerCase(digis);
            bool flag=false;
            for(unsigned int i=0;i<digis.size();i++){
                if(digis[i]<'2'||digis[i]>'9'){
                    cout<<"wrong number:"<<digis[i]<<endl;
                    flag=true;
                }
            }
            if(flag) continue;
            //cout<<"digis:"<<digis<<endl;
            Lexicon lex("lexicon.dat");
            //string prex="palisade";
            //cout<<"?:"<<lex.containsPrefix(prex)<<endl;
            //cout<<"?:"<<lex.containsWord(prex)<<endl;
            //cout<<lex.size()<<endl;
            ListCompletions(digis,lex);
        }
    }
    return 0;
}

void ListCompletions(string digitSequence,Lexicon &lex){
    map<char,string> keypads;
    keypads.insert(make_pair('2',"abc"));
    keypads.insert(make_pair('3',"def"));
    keypads.insert(make_pair('4',"ghi"));
    keypads.insert(make_pair('5',"jkl"));
    keypads.insert(make_pair('6',"mno"));
    keypads.insert(make_pair('7',"pqrs"));
    keypads.insert(make_pair('8',"tuv"));
    keypads.insert(make_pair('9',"wxyz"));
    string alber="abcdefghijklmnopqrstuvwxyz";
    string prex;
    int count=ListWords(keypads,prex,digitSequence,alber,lex);
    cout<<"totalnumber:"<<count<<endl;
}

int ListWords(const map<char,string> &keypads,string prex,string digitSequence,string alber,Lexicon &lex){
    int count=0;
    if(digitSequence.empty()&&lex.containsPrefix(prex)){
        if(lex.containsWord(prex)){
            count++;
            cout<<prex<<endl;
        }
        for(unsigned int i=0;i<alber.size();i++){
            string p=prex;
            p.push_back(alber[i]);
            count+=ListWords(keypads,p,digitSequence,alber,lex);
        }
        return count;
    }
    if(!digitSequence.empty()&&lex.containsPrefix(prex)){

        string nextchar=(keypads.find(digitSequence[0]))->second;
        digitSequence.erase(digitSequence.begin());
        for(unsigned int i=0;i<nextchar.size();i++){
            string p=prex;
            p.push_back(nextchar[i]);
            count+=ListWords(keypads,p,digitSequence,alber,lex);
        }
    }
    return count;
}
