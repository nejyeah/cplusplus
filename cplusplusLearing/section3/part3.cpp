//Filename:part3.cpp

/**count the number of critical vote
 * the votes blocks is store in a vector
 */

#include<iostream>
#include<vector>
#include<stdlib.h>

using namespace std;

int CountCriticalVotes(vector<int> &blocks,int blockIndex);
int sum(const vector<int> nums);
int count(vector<int> &Alice,vector<int> &Bob,float low,float high);

int main(){
    vector<int> blocks;
    while(true){
        int a;
        cout<<"Enter the votes(0 to end):"<<endl;
        cin>>a;
        if(a==0) break;
        blocks.push_back(a);
    }

    for(unsigned int i=0;i<blocks.size();i++){
        int num=CountCriticalVotes(blocks,i);
        cout<<"votesize:"<<blocks[i]<<"    count:"<<num<<endl;
    }
}


int CountCriticalVotes(vector<int> &blocks,int blockIndex){
    vector<int> Alice;
    int vote=blocks[blockIndex];
    vector<int> remain=blocks;
    remain.erase(remain.begin()+blockIndex);
    int all=sum(remain);
    float high=(all+vote)/2.0;
    float low=(all-vote)/2.0; 
    return count(Alice,remain,low,high);

}

int count(vector<int> &Alice,vector<int> &Bob,float low,float high){
    int num=0;
    if(sum(Alice)>low&&sum(Alice)<high) num++;
    if(!Bob.empty()){
        vector<int>::iterator itr;
    
        for(itr=Bob.begin();itr!=Bob.end();itr++){
            vector<int> alice=Alice;
            vector<int> bob(itr+1,Bob.end());
            alice.push_back(*itr);
            num+=count(alice,bob,low,high);
        }
    
    }
    return num;
}

int sum(const vector<int> nums){
    int sum=0;
    for(unsigned int i=0;i<nums.size();i++){
        sum+=nums[i];
    }
    return sum;
}
