//Filename:set.cpp
/**test weather test is ordered or not
 */

#include<iostream>
#include<set>

using namespace std;

int main(){
    set<int> test;
    while(true){
        int n;
        cin>>n;
        test.insert(n);
        if(n==0) break;
    }
    set<int>::iterator itr=test.begin();
    while(itr!=test.end()){
        cout<<*itr<<endl;
        itr++;
    }
    return 0;
}

