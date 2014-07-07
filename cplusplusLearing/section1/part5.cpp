//Filename:part5.cpp

#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<string>

using namespace std;

int main(){
    string filename;
    int count[10]={0};
    int grade;
    ifstream fp;
    cout<<"Please enter the file name:";
    cin>>filename;
    fp.open(filename.c_str());
    while(!fp.is_open()){
        cout<<"Please enter the file name:";
        cin>>filename;
        fp.open(filename.c_str());
    }
    while(fp>>grade){
        switch(grade/10){
            case 9: 
                count[9]++;
                break;
            case 8: 
                count[8]++;
                break;
            case 7: 
                count[7]++;
                break;
            case 6: 
                count[6]++;
                break;
            case 5: 
                count[5]++;
                break;
            case 4: 
                count[4]++;
                break;
            case 3: 
                count[3]++;
                break;
            case 2: 
                count[2]++;
                break;
            case 1: 
                count[1]++;
                break;
            case 0: 
                count[0]++;
                break;
            default: cout<<"there is a error grad:"<<grade<<endl;
        }
    }
    for(int i=0;i<10;i++){
        //cout<<"i:"<<count[i]<<endl;
        string histogram(count[i],'X');
        cout<<i*10<<"-"<<i*10+9<<":"<<histogram<<endl;
    }


}
