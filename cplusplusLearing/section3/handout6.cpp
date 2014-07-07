//Filename:handout6.cpp

#include<iostream>

using namespace std;

int GCD(int x,int y);

int main(){
    int x,y;
    while(true){
        cout<<"enter the x and y(0 to quit):";
        cin>>x;
        if(x==0) break;
        cin>>y;
        if(y==0) break;
        cout<<"the greatest common divisor:"<<GCD(x,y)<<endl;
    }
    return 0;
}

int GCD(int x,int y){
   if(y==0) return x;
   else{
        return GCD(y,x%y);
   }
}
