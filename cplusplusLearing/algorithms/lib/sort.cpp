//Filename:sort.cpp
#include"algorithms.h"

void insertionSort(vector<int> &nums){
    int length=nums.size();
    for(int j=1;j<length;j++){
        int key=nums[j];
        int i=j-1;
        while(i>=0&&nums[i]>key){
            nums[i+1]=nums[i];
            i--;
        }
        nums[i+1]=key;
    }
}
