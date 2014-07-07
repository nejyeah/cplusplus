//Filename:handout2.cpp
//

#include<iostream>
#include<queue>
#include<stack>

using namespace std;

void ReverseQueue(queue<int> &q);

int main(){
    queue<int> q;
    int i;
    for(i=0;i<10;i++){
        q.push(i);
        cout<<i<<",";
    }
    cout<<endl;
    cout<<"reverse"<<endl;
    ReverseQueue(q);
    while(!q.empty()){
        cout<<q.front()<<",";
        q.pop();
    }
    cout<<endl;
    return 0;
}

void ReverseQueue(queue<int> &q){
    stack<int> b;
    int a;
    while(!q.empty()){
        a=q.front();
        b.push(a);
        q.pop();
    }

    while(!b.empty()){
        a=b.top();
        q.push(a);
        b.pop();
    }
}
