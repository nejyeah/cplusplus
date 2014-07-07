//Filename:part6.cpp
/**problem about cut pipes
*/

#include<iostream>
#include<vector>
#include"random.h"
#include<stdlib.h>
#include<time.h>
using namespace std;

void randomnumber(vector<int> &requests,const int number,const int length);
int CutStock(vector<int> &requests,int stockLength);
int CutStock1(vector<int> &requests,int stockLength);
int getFullStock(vector<int> &left,vector<int> requests,int stockLength);
vector<int>::iterator find(vector<int> &requests,int left);
int getmax(const vector<int> &requests);


int main(){
    const int number=10;
    const int length=10;
    int times=0;
    cout<<"0 to random,others to youself:";
    int i;
    cin>>i;
    if(i==0){
        while(times<10){
            vector<int> requests;
            srand(times);
            randomnumber(requests,number,length);
            int count=CutStock1(requests,length);
            cout<<"count:"<<count<<endl;
            times++;
        }
    }
    else{
        vector<int> requests;
        cout<<"enter the pipe(0 to quit):";
        int a;
        while(true){
            cin>>a;
            if(a==0) break;
            requests.push_back(a);
        }
        int count=CutStock1(requests,length);
        cout<<"count:"<<count<<endl;
    }
    return 0;
}

void randomnumber(vector<int> &requests,const int number,const int length){
    cout<<"numbers:";
    for(int i=0;i<number;i++){
        int n=1+rand()%(length-1);

        requests.push_back(n);
        cout<<n<<" ";
    }
    cout<<endl;

}

int CutStock1(vector<int> &requests,int stockLength){
    vector<int> left;
    int count=getFullStock(left,requests,stockLength);
    count+=CutStock(left,stockLength);
    return count;
}

int getFullStock(vector<int> &left,vector<int> requests,int stockLength){
    int count=0;
    if(requests.size()==0) return count;
    vector<int> copy=requests;
    vector<int> ways;
    int max=getmax(copy);
    ways.push_back(max);
    copy.erase(find(copy,max));
    int l=stockLength-max;
    while(l>0){
        vector<int>::iterator itr=find(copy,l);
        if(itr!=copy.end()){
            copy.erase(itr);
            max=max+l;
            ways.push_back(l);
            l=stockLength-max;
            //cout<<"max:"<<max<<"  left:"<<left<<endl;
            continue;
        }
        l--;
    }
    if(max==stockLength){
        count++;
        vector<int>::iterator itr=ways.begin();
        while(itr!=ways.end()){
            cout<<*itr<<" ";
            itr++;
        }
        cout<<":" <<max<<endl;
        count+=getFullStock(left,copy,stockLength);
    }
    else{
        max=getmax(requests);
        left.push_back(max);
        requests.erase(find(requests,max));
        count+=getFullStock(left,requests,stockLength);
    }
    return count;
}

int CutStock(vector<int> &requests,int stockLength){
    if(requests.size()==0) return 0;
    int max=getmax(requests);
    vector<int> ways;
    ways.push_back(max);
    requests.erase(find(requests,max));
    //cout<<"max:"<<max<<endl;
    int left=stockLength-max;
    while(left>0){
        vector<int>::iterator itr=find(requests,left);
        if(itr!=requests.end()){
            requests.erase(itr);
            ways.push_back(left);
            max=max+left;
            left=stockLength-max;
            //cout<<"max:"<<max<<"  left:"<<left<<endl;
            continue;
        }
        left--;
    }
    for(unsigned int i=0;i<ways.size();i++){
        cout<<ways[i]<<" ";
    }
    cout<<":"<<max<<endl;
    int a=CutStock(requests,stockLength);
    return 1+a;
}


vector<int>::iterator find(vector<int> &requests,int left){
    vector<int>::iterator itr=requests.begin();
    while(itr!=requests.end()){
        if(*itr==left) return itr;
        itr++;
    }
    return itr;
}
int getmax(const vector<int> &requests){
    int max=0;
    vector<int>::const_iterator itr=requests.begin();
    while(itr!=requests.end()){
        if(max<*itr){
            max=*itr;
        }
        itr++;
    }
    return max;
}
