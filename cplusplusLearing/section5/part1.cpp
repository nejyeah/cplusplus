//Filename:part1.cpp

#include<iostream>
#include<vector>
#include<string>
#include"vector.h"
#include"random.h"

using namespace std;
struct PointT{
    int x,y;
};

template<typename T>
int OperatorCmp(T,T);

template<typename T>
void Sort(Vector<T> &v,int (cmpfn)(T,T)=OperatorCmp);
int operatorcmp(PointT a,PointT b);


int main(){
    int length;
    int num;
    Vector<int> v;
    cout<<"enter the length of random vector:";
    cin>>length;
    while(length>0){
        num=RandomInteger(1,10);
        v.add(num);
        length--;
        cout<<num<<" ";
    }
    cout<<endl;

    Sort(v);
    cout<<"shell sort:";
    for(int i=0;i<v.size();i++){
        cout<<v[i]<<" ";
    }
    cout<<endl;

    Vector<PointT> v1;
    PointT a,b;
    a.x=1;
    a.y=2;
    b.x=2;
    b.y=1;
    v1.add(a);
    v1.add(b);
    Sort(v1,operatorcmp);

    return 0;
}
int operator=()
int operatorcmp(PointT a,PointT b){
    if(a.x<b.x) return 1;
    if(a.x>b.x) return -1;
    else return 0;

}

template<typename T>
void Sort(Vector<T> &v,int (cmpFn)(T,T)=OperatorCmp){
        int n=v.size();    
        int d,i,j,temp;
        for(d=n/2;d>=1;d=d/2)
        {
            for(i=d;i<n;i++)
            {
                temp=v[i];
                for(j=i-d;(j>=0)&&(v[j]>temp);j=j-d)
                {
                    v[j+d]=v[j];
                }
                v[j+d]=temp;
            }
        }
}

template <typename T>
int OperatorCmp(T one,T two){
    if(one==two) return 0;
    if(one<two) return -1;
    return 1;
}

