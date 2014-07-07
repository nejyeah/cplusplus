//Filename:warmup1.cpp
/**recursion problem
 * about translate an interger into binary
 */

#include<iostream>
using namespace std;

void PrintInBinary(int number);
int main(){

    int number;
    while(true){
        cout<<"Please input an Integer(Enter zero to quit):"<<endl;
        cin>>number;
        //cout<<number<<endl;
        if(number==0) break;
        else {
            PrintInBinary(number);
            cout<<endl;
        }
    }
    return 0;
}

void PrintInBinary(int number){
    if(number==1){
        cout<<number;
    }
    else{
        int a=number/2;
        PrintInBinary(a);
        cout<<number%2;
    }
}
