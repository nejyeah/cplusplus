//handout4.cpp

#include<iostream>
using namespace std;

int Cannonball(int height);

int main(){
    int height;
    while(true){
        cout<<"enter the height(0 to quit):";
        cin>>height;
        if(height==0) break;
        int count=Cannonball(height);
        cout<<"count:"<<count<<endl;
    }
}

int Cannonball(int height){
   if(height==1) return 1; 
   else return height*height+Cannonball(height-1);
}
