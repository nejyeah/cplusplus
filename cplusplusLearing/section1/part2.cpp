//Filename:votetest.cpp

#include<iostream>
#include"simpio.h"
#include"random.h"

using namespace std;

bool testElection(const int vn,const double ps,const double er);
int main(){
    const int times=500;
    int votersnumber;
    double percentageSpread;
    double errorRate;
    int count=0;
    bool flag;
    cout<<"Enter number of voters:";
        votersnumber=GetInteger();
    cout<<"Enter percentage spread between candidates:";
        percentageSpread=GetReal();
    cout<<"Enter voting error percentage:";
        errorRate=GetReal();
    for(int i=0;i<times;i++){
        flag=testElection(votersnumber,percentageSpread,errorRate);
        if(flag){
            count++; 
        }
    }
    cout<<"Chance of an invalid election result after "<<times<<" trials = "<<(double)count/times*100<<"%"<<endl;
    return 0;
}

bool testElection(const int vn,const double ps,const double er){
    int A=vn*((1-ps)/2+ps);
    //cout<<"A:"<<A<<endl;
    int Acount=0;
    int Bcount=0;
    for(int i=0;i<vn;i++){
        if(i<A){
            if(RandomChance(er)){
                Bcount++;
            }
            else{
                Acount++;
            }
        }
        else{
            if(RandomChance(er)){
                Acount++;
            }
            else{
                Bcount++;
            }

        }
    }
    //cout<<"B:"<<Bcount<<"  A:"<<Acount<<endl;
    if(Bcount>=Acount) return true;
    else    return false;
}
