//Filename:testSort.cpp
#include<iostream>
#include<vector>
#include"algorithms.h"

using namespace std;

int main(){
    vector<int> nums;
    int num;
    cout<<"enter the nums (0 to end):";
    while(true){
        cin>>num;
        if(num==0) break;
        nums.push_back(num);
    }
    insertionSort(nums);
    for(unsigned int i=0;i<nums.size();i++){
        cout<<nums[i]<<",";
    }
    cout<<endl;
    return 0;
}
