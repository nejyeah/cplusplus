//Filename:part2.cpp

/*This is a demo about maze
*/

#include<iostream>
#include"maze.h"
#include<set>
//#include"set.h"
#include"random.h"
#include<queue>
#include<stack>
#include"extgraph.h"
#include"graphics.h"
extern"C"{
#include<time.h>
}
//#include"stack.h"
//#include"queue.h"

using namespace std;

void creatMaze(Maze &maze,const unsigned int y_row,const unsigned int x_col);
bool operator<(const pointT& a,const pointT& b);
bool operator==(const pointT& a,const pointT& b);
bool operator!=(const pointT& a,const pointT& b);
void workoutMaze(Maze &maze,const pointT entry,const pointT exit);
void breadthFirstSearch(Maze &maze,const pointT entry,const pointT exit);
void deepthFirstIteratorSearch(Maze &maze,const pointT entry,const pointT exit);
void deepthFirstStackSearch(Maze &maze,const pointT entry,const pointT exit);
bool search(Maze &maze,set<pointT> &includePoint,pointT current,pointT exit);

int main(){
    const unsigned int y_row=40;
    const unsigned int x_col=40;
    const unsigned int y_entry=0;
    const unsigned int x_entry=0;
    const unsigned int y_exit=y_row-1;
    const unsigned int x_exit=x_col-1;
    //define the entry and exit of maze
    pointT entry,exit;
    entry.row=y_entry;
    entry.col=x_entry;
    exit.row=y_exit;
    exit.col=x_exit;

    InitGraphics();
    SetWindowTitle("maze");
    SetWindowSize(GetFullScreenWidth(),GetFullScreenHeight());

    Maze maze(y_row,x_col,true);
    time_t time0=time(NULL);
    maze.draw();
    time_t time1=time(NULL);
    cout<<"drawtime:"<<time1-time0<<endl;
    creatMaze(maze,y_row,x_col);
    time_t time2=time(NULL);
    cout<<"creatMaze:"<<time2-time1<<endl;
    workoutMaze(maze,entry,exit);
    time_t time3=time(NULL);
    cout<<"workout maze:"<<time3-time2<<endl;
    //time(10,74,6) size 40*40  deepthStacksearch
    //time(10,73,6) size 40*40  breathSearch
    return 0;
}

void creatMaze(Maze &maze,const unsigned int y_row,const unsigned int x_col){
    pointT start;
    pointT next;
    set<pointT> includePointT;
    start.row=RandomInteger(0,y_row);
    start.col=RandomInteger(0,x_col);
    next.row=start.row;
    next.col=start.col;
    includePointT.insert(start);
    while(includePointT.size()!=y_row*x_col){
        //cout<<"start:"<<start.row<<","<<start.col<<endl;
        int index=0;
        bool flag=false;

        while(!flag){
            next.row=start.row;
            next.col=start.col;
            index=RandomInteger(0,4);
            switch(index){
                case 0:
                    next.col--;
                    break;
                case 1:
                    next.row--;
                    break;
                case 2:
                    next.col++;
                    break;
                default:
                    next.row++;
            }
            flag=maze.pointInBounds(next);
        }

        int i=includePointT.count(next);
        if(i==0){
            maze.setWall(start,next,false);
            includePointT.insert(next);
        }

        start.row=next.row;
        start.col=next.col;

    }

}

bool search(Maze &maze,set<pointT> &includePoint,pointT current,pointT exit){
    pointT around;
    includePoint.insert(current);
    int i=0;
    while(i<4){
        around=current;
        switch(i){
            case 0:
                around.col--;
                break;
            case 1:
                around.row--;
                break;
            case 2:
                around.col++;
                break;
            default:
                around.row++;
        }
        //判断该点合法
        if(maze.pointInBounds(around)&&!maze.isWall(current,around)&&includePoint.count(around)==0){
            if(around==exit){
                cout<<"get it"<<endl;
                maze.drawMark(around,"Red");

                return true;
            }
            else{
                bool flag=search(maze,includePoint,around,exit);
                if(flag){
                    maze.drawMark(around,"Red");
                    return true;
                }
            }
        }
        i++;
    }
    return false;
}

void deepthFirstIteratorSearch(Maze &maze,pointT current,pointT exit){
    set<pointT> includePoint;
    includePoint.insert(current);
    bool flag=search(maze,includePoint,current,exit);
    if(flag) maze.drawMark(current,"Red");
}

void deepthFirstStackSearch(Maze &maze,pointT current,pointT exit){
    set<pointT> block;
    stack<pointT> pathStack;
    pathStack.push(current);
    while(true){
        pointT currentP=pathStack.top();
        block.insert(currentP);
        pointT around;
        bool flag=false;
        int i=0;
        while(i<4){
            around=currentP;
            switch(i){
                case 0:
                    around.col--;
                    break;
                case 1:
                    around.row--;
                    break;
                case 2:
                    around.col++;
                    break;
                default:
                    around.row++;
            }
            //判断该点合法
            if(maze.pointInBounds(around)&&!maze.isWall(currentP,around)&&block.count(around)==0){
                flag=true;
                break;
            }
            i++;
        }
        //有可走的子节点
        if(flag){
            if(around==exit){
                maze.drawMark(around,"Red");
                break;
            }
            else{
                pathStack.push(around);
            }
        }
        else{
            pathStack.pop();
        }
    }
    while(!pathStack.empty()){
        maze.drawMark(pathStack.top(),"Red");
        pathStack.pop();
    }
}

void workoutMaze(Maze &maze,const pointT entry,const pointT exit){
    breadthFirstSearch(maze,entry,exit);
    //deepthFirstIteratorSearch(maze,entry,exit);
    //deepthFirstStackSearch(maze,entry,exit);
}

void breadthFirstSearch(Maze &maze,const pointT entry,const pointT exit){

    pointT current=entry;
    pointT around;
    //int i=search(maze,current,current,exit);

    queue< stack<pointT> > pathQueue;
    stack<pointT> currentStack;
    set<pointT> includePointT;

    currentStack.push(current);
    pathQueue.push(currentStack);

    while(true){

        //获取当前队列的最先进去的一个栈，栈顶的点作为当前点
        currentStack=pathQueue.front();
        current=currentStack.top();

        //将当前点插入set，保证不走重复路
        includePointT.insert(current);

        //获取当前点附近可走的点
        int i=0;
        bool flag=false;
        while(i<4){
            around=current;
            switch(i){
                case 0:
                    around.col--;
                    break;
                case 1:
                    around.row--;
                    break;
                case 2:
                    around.col++;
                    break;
                default:
                    around.row++;
            }
            i++;
            //判断该点是否合法
            if(maze.pointInBounds(around)){
                //int index=includePointT.count(around);
                if(!maze.isWall(current,around)&&includePointT.count(around)==0){
                    //判断是否是出口
                    if(around==exit){
                        cout<<"get it"<<endl;    

                        maze.drawMark(around,"Red");
                        flag=true;
                        break;
                    }
                    else{
                        stack<pointT> tem = currentStack;
                        tem.push(around);
                        pathQueue.push(tem);
                    }
                }
            }

        }
        //如果找到出口退出循环
        if(flag){
            //mark the path
            while(!currentStack.empty()){
                pointT top=currentStack.top();
                maze.drawMark(top,"Red");
                currentStack.pop();
            }
            break;
        }
        else{
            pathQueue.pop();    
        }

    }

}



bool operator<(const pointT& a,const pointT& b){
    if(a.row<b.row){
        return false;
    }

    else if(a.row==b.row){
        if(a.col<=b.col){
            return false;
        }
        else{
            return true;
        }
    }

    else{
        return true;
    }
}

bool operator==(const pointT& a,const pointT& b){
    if(a.row==b.row&&a.col==b.col) return true;
    else return false;
}

bool operator!=(const pointT& a,const pointT& b){
    if(a.row==b.row&&a.col==b.col) return false;
    else return true;
}
