//Filename:handout3.cpp

#include<iostream>
#include<set>

using namespace std;

struct pairT{
    string first,second;
};

set<pairT> CartesianProduct(set<string> &one,set<string> &two);
bool operator<(const pairT &a,const pairT &b);

int main(){
    set<string> one,two;
    one.insert("A");
    one.insert("B");
    one.insert("c");
    two.insert("X");
    two.insert("Y");
    set<pairT> product=CartesianProduct(one,two);
    set<pairT>::iterator itr=product.begin();
    while(itr!=product.end()){
        cout<<(*itr).first<<","<<(*itr).second<<endl;
        itr++;
    }
    return 0;
}


set<pairT> CartesianProduct(set<string> &one,set<string> &two){
   set<pairT> product;
   for(set<string>::iterator i=one.begin();i!=one.end();i++){
        for(set<string>::iterator j=two.begin();j!=two.end();j++){
            pairT pa;
            pa.first=*i;
            pa.second=*j;
            product.insert(pa);
        }
   }
   return product;
}

bool operator<(const pairT &a,const pairT &b){
    if(a.first<b.first) return true;
    else if(a.first>b.first) return false;
    else if(a.second<b.second) return true;
    else if(a.second>b.second) return false;
    else    return false;
}
