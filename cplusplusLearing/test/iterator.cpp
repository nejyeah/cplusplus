//Filename:testIterator.cpp

#include<iostream>
#include<vector>
#include<map>

using namespace std;

int main(){
    vector<int> testvector;
    for(int i=0;i<1;i++){
        testvector.push_back(i);
    }
    vector<int>::iterator itr=testvector.begin();
   testvector.erase(testvector.begin()); 
    return 0;
}
