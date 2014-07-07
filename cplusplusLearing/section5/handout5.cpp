//Filename:handout5.cpp

#include<iostream>
#include<vector>
#include<time.h>
#include"random.h"

using namespace std;

int generalAlgorithm(vector<int> &v,int &start,int &end);
int divideConquer(int low,int upper,vector<int> &v,int &start,int &end);
int lesstime(vector<int> &v);

int main(){
    cout<<"enter the length of vector:";
    int len=0;
    cin>>len;
    vector<int> v;
    /*
     *Random to generize the vector
     */
    Randomize();
    cout<<"integers as follows:"<<endl;
    while(len!=0){
        int a=RandomInteger(1,10);
        bool flag=RandomChance(0.33);
        if(flag) a=(-1)*a;
        //cout<<a<<" ";
        v.push_back(a);
        len--;
    }
    cout<<endl;
    
    /*
    cout<<"enter the nums in vector(0 to end):";
    int a;
    vector<int> v;
    while(true){
        cin>>a;
        if(a==0) break;
        v.push_back(a);
    }
    */
    int start=0;
    int end=0;
    int max=0;
    
    cout<<"the generalAlgorithm,O(N^2)"<<endl;
    time_t time1=time(NULL);
    max=generalAlgorithm(v,start,end);
    time_t time2=time(NULL);
    cout<<"the max :"<<max<<endl;
    cout<<"subvectors: startindex "<<start<<"  endindex "<<end<<endl;;
    /*
    for(int i=start;i<=end;i++){
        cout<<v[i]<<" ";
    }
    
    cout<<endl;
    */
    cout<<"time:"<<time2-time1<<endl;
    cout<<endl;

    cout<<"divide and conquer,O(NlogN)"<<endl;
    time_t time3=time(NULL);
    max=divideConquer(0,v.size()-1,v,start,end);
    time_t time4=time(NULL);
    cout<<"the max :"<<max<<endl;
    cout<<"subvectors: startindex "<<start<<"  endindex "<<end<<endl;;
    /*
    for(int i=start;i<=end;i++){
        cout<<v[i]<<" ";
    }
    cout<<endl;
    */
    cout<<"time:"<<time4-time3<<endl;
    cout<<endl;

    cout<<"less time ,O(N)"<<endl;
    time_t time5=time(NULL);
    max=lesstime(v);
    time_t time6=time(NULL);
    cout<<"the max:"<<max<<endl;
    cout<<"time:"<<time6-time5<<endl;
    cout<<endl;

}

int generalAlgorithm(vector<int> &v,int &start,int &end){
    int max=0;
    for(unsigned int i=0;i<v.size();i++){
        int sum=0;
        for(unsigned int j=i;j<v.size();j++){
            sum+=v[j];
            if(sum>max){
                max=sum;
                start=i;
                end=j;
            }
        }
    }
    return max;
}

int divideConquer(int low,int upper,vector<int> &v,int &start,int &end){
    //0 element
    if(low>upper) return 0;
    //1 element
    if(low==upper){
        if(v[low]>0){
            start=low;
            end=low;
            return v[low];
        }
        return 0;
    }
    int middle=(low+upper)/2;
    int SumLeft=0;
    int MaxToLeft=0;
    int MaxCrossLeftIndex=middle+1;
    for(int i=middle;i>=low;i--){
        SumLeft+=v[i];
        if(MaxToLeft<SumLeft){
            MaxToLeft=SumLeft;
            MaxCrossLeftIndex=i;
        }
    }
    int SumRight=0;
    int MaxToRight=0;
    int MaxCrossRightIndex=middle;
    for(int i=middle+1;i<=upper;i++){
        SumRight+=v[i];
        if(MaxToRight<SumRight){
            MaxToRight=SumRight;
            MaxCrossRightIndex=i;
        }
    }
    int MaxCrossing=MaxToLeft+MaxToRight;
    
    int leftsideLowIndex=0;
    int leftsideUpperIndex=0;
    int MaxInLeftHalf = divideConquer(low,middle,v,leftsideLowIndex,leftsideUpperIndex);

    
    int RightsideLowIndex=0;
    int RightsideUpperIndex=0;
    int MaxInRightHalf = divideConquer(middle+1,upper,v,RightsideLowIndex,RightsideUpperIndex);

    if(MaxInLeftHalf>MaxInRightHalf){
        if(MaxInLeftHalf>MaxCrossing){
            start=leftsideLowIndex;
            end=leftsideUpperIndex;
            return MaxInLeftHalf;
        }
        else{
            start=MaxCrossLeftIndex;
            end=MaxCrossRightIndex;
            return MaxCrossing;
        }
    }
    else{
        if(MaxInRightHalf>MaxCrossing){
            start=RightsideLowIndex;
            end=RightsideUpperIndex;
            return MaxInRightHalf;
        }
        else{
            start=MaxCrossLeftIndex;
            end=MaxCrossRightIndex;
            return MaxCrossing;
        }
        
    }
}

int lesstime(vector<int> &v){
    int max=0;
    int leftmax=0;
    for(unsigned int i=0;i<v.size();i++){
        if(v[i]<0){
            leftmax+=v[i];
        }
        else{
            if(leftmax<0) leftmax=v[i];
            else leftmax+=v[i];
        }
        if(max<leftmax) max=leftmax;

    }
    return max;
}
