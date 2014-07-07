//Filename:warmup2.cpp
/**
 * recursion problem 
 * about find out certain targetsun in a vector number
 */

#include<iostream>
#include<vector>

using namespace std;
bool CanMakeSum(vector<int> &nums,int targetSum);
int sum(const vector<int> nums);
bool CanMakeSum1(vector<int> &soFar,vector<int> &remain,int targetSum,int &count);

int main(){
    vector<int> nums;
    vector<int> soFar;
    int targetSum;
    int count=0;
    cout<<"Enter a serise of integers(0 to end):"<<endl;
    while(true){
        int a;
        cin>>a;
        if(a==0) break;
        nums.push_back(a);
    }
    cout<<"Enter a targetSum:"<<endl;
    cin>>targetSum;
    //bool flag=CanMakeSum(nums,targetSum);
    bool flag=CanMakeSum1(soFar,nums,targetSum,count);
    cout<<"count:"<<count<<endl;
    //cout<<"can make sum? "<<flag<<endl;
}

bool CanMakeSum1(vector<int> &soFar,vector<int> &remain,int targetSum,int &count){
    if(sum(soFar)==targetSum){
        for(unsigned int i=0;i<soFar.size();i++){
            cout<<soFar[i]<<" ";
        }
        cout<<endl;
        count++;
        return true;
    }
    else if(sum(soFar)>targetSum) return false;
    else{
        vector<int>::iterator itr;
        for(itr=remain.begin();itr!=remain.end();itr++){
            vector<int> sofar=soFar;
            vector<int> rema(itr+1,remain.end());
            sofar.push_back(*itr);
            //if(CanMakeSum1(sofar,rema,targetSum)) return true;
            CanMakeSum1(sofar,rema,targetSum,count);
        }
    }
    return false;
}

bool CanMakeSum(vector<int> &nums,int targetSum){
    if(sum(nums)==targetSum){
        for(unsigned int i=0;i<nums.size();i++){
            cout<<nums[i]<<" ";
        }
        cout<<endl;
        return true; 
    }
    else{
        for(unsigned int i=0;i<nums.size();i++){
            vector<int> num=nums;
            num.erase(num.begin()+i);
            if(CanMakeSum(num,targetSum)) return true;
            //CanMakeSum(num,targetSum);
        }
    }
    return false;
}

int sum(const vector<int> nums){
    int sum=0;
    for(unsigned int i=0;i<nums.size();i++){
        sum+=nums[i];
    }
    return sum;
}
