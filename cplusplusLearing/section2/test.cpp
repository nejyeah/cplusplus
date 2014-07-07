#include <iostream>

using namespace std;
int main(){

    int i=1;
    while(true){
        while(i<5){
            if(i<5){
                if(i<4){
                    if(i<3){
                        cout<<"break"<<endl;
                        break;
                    }
                }
            }
        }
        cout<<i<<"out"<<endl;
        i++;
        if(i==4) break; 

    }
    return 0;
}
