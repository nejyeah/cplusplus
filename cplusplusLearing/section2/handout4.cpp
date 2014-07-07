//Filename:handout4.cpp
/**use fp>>char will mis the space
 */

#include<iostream>
#include<fstream>
#include<map>

using namespace std;

char MostFrequentCharacter(ifstream &fp,int &numOccurrences);
int main(){
    ifstream fp("part1.txt");
    int times;
    if(fp.is_open()){
    char b=MostFrequentCharacter(fp,times);
    cout<<"most frequent character:"<<b<<","<<times<<endl;
    }
    else{
        cout<<"can not open the file."<<endl;
    }
}

char MostFrequentCharacter(ifstream &fp,int &numOccurrences){
   map<char ,int> charmap;
   char c;
   while(fp>>c){
       //cout<<c<<endl;
        map<char,int>::iterator itr;
        itr=charmap.find(c);
        if(itr!=charmap.end()){
            itr->second++;
        }
        else{
            charmap.insert(make_pair(c,1));
        }
   }

   map<char,int>::iterator it=charmap.begin();
   char c_max;
   int max;
   while(it!=charmap.end()){
       cout<<it->first<<":"<<it->second<<endl;
        if(it->second>max){
            max=it->second;
            c_max=it->first;
        }
        it++;
   }
   numOccurrences=max;
   return c_max;
}
