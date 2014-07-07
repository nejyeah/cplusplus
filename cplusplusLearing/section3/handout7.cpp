//Filename:handout7.cpp

#include<iostream>
#include<vector>

using namespace std;

bool IsMeasurable(int target,vector<int> &weights);
int measure(int targetV,vector<int> weights);

int main(){
    while(true){
        vector<int> weights;
        int a;
        cout<<"enter the weights(0 to end):"<<endl;
        while(true){
            cin>>a;
            if(a==0) break;
            weights.push_back(a);
        }
        if(weights.size()==0) break;
        cout<<"enter the target:";
        cin>>a;
        bool flag=IsMeasurable(a,weights);
        cout<<"Is measurable? "<<flag<<endl;
    }
}

bool IsMeasurable(int target,vector<int> &weights){
    int count=measure(target,weights);
    cout<<"ways to weight:"<<count<<endl;
    if(count>0) return true;
    else return false;
}

int measure(int targetV,vector<int> weights){
    if(weights.size()==0){
        if(targetV==0) return 1;
        else return 0;
    }
    int first=weights[0];
    int count=0;
    weights.erase(weights.begin());
    count+=measure(targetV+first,weights);
    count+=measure(targetV-first,weights);
    count+=measure(targetV,weights);
    return count;
}



