//Filename:perfectnumber.cpp

#include<iostream>

using namespace std;

int main(){
    for(int k=2;k<=10000;k++){
        int total=0;
        for(int i=2;i<=k/i;i++){
            int a=k%i;
            int b=k/i;
            if(a==0){
                total+=i+b;
            }
        }
        if(k==total+1) cout<<k<<endl;
    }
}
