/* pathfinder.cpp
 * ---------------
 * A starter file with some starting constants and handy utility routines.
 */

#include "genlib.h"
#include "extgraph.h"
#include <iostream>
#include <cmath>
#include <set>
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib>
/* Constants
 * --------
 * A few program-wide constants concerning the graphical display.
 */
const double CircleRadius =.05;     	// the radius of a node
const int LabelFontSize = 9;          // for node name labels


/* Type: coordT
 * ------------
 * Just a simple struct to handle a pair of x,y coordinate values.
 */
struct coordT {
    double x, y;
};

/* Type: laborT
 * ------------
 * Just a simple struct to stand for the labor information about a point.
 */
struct laborT {
    string name;
    double distance;
};

/* Type: infoT
 * ------------
 * Just a simple struct to stand for all information about a point..
 */
struct infoT {
    coordT location;
    set<laborT> labor;
};

/* Type: arcT
 * ------------
 * Just a simple struct to stand for arc.
 */
struct arcT {
    string start,end;
    double distance;
};

/* Function: DrawFilledCircleWithLabel
 * Usage:  DrawFilledCircleWithLabel(center, "Green", "You are here");
 * -------------------------------------------------------------------
 * Uses facilities from extgraph to draw a circle filled with
 * color specified. The circle is centered at the given coord has the
 * specified radius.  A label is drawn to the right of the circle.
 * You can leave off the last argument if no label is desired.
 */
void DrawFilledCircleWithLabel(coordT center, string color, string label = "")
{
    MovePen(center.x + CircleRadius, center.y);
    SetPenColor(color);
    StartFilledRegion(1.0);
    DrawArc(CircleRadius, 0, 360);
    EndFilledRegion();
    if (!label.empty()) {
        MovePen(center.x + CircleRadius, center.y);
        SetFont("Helvetica");
        SetPointSize(LabelFontSize);
        DrawTextString(label);
    }
}

/* Function: DrawLineBetween
 * Usage:  DrawLineBetween(coord1, coord2, "Black");
 * -------------------------------------------------
 * Uses facilities from extgraph to draw a line of the
 * specified color between the two given coordinates.
 */
void DrawLineBetween(coordT start, coordT end, string color)
{
    SetPenColor(color);
    MovePen(start.x, start.y);
    DrawLine(end.x - start.x, end.y - start.y);
}


/* Function: GetMouseClick
 * Usage:  loc = GetMouseClick();
 * ------------------------------
 * Waits for the user to click somewhere on the graphics window
 * and returns the coordinate of where the click took place.
 */
coordT GetMouseClick()
{
    coordT where;
    WaitForMouseDown();
    WaitForMouseUp();
    where.x = GetMouseX();
    where.y = GetMouseY();
    return where;
}

/* Function: WithinDistance
 * Usage:  if (WithinDistance(click, pt))...
 * -----------------------------------------
 * Returns true if the Cartesian distance between the two coordinates
 * is <= the specified distance, false otherwise. If not specified,
 * the distance is assumed to be size of the node diameter on screen.
 */
bool WithinDistance(coordT pt1, coordT pt2, double maxDistance = CircleRadius*2)
{
    double dx = pt2.x - pt1.x;
    double dy = pt2.y - pt1.y;
    double distance = sqrt(dx*dx + dy*dy);
    return (distance <= maxDistance);
}

/*Function:operator<
 * Operator overloading
 * --------------------------------------------
 * coordT is a self-defined struct,
 * when it stored in container set,
 * it has to be sorted by operator<.
 */
bool operator<(const coordT &A,const coordT &B){
    if(A.x<B.x) return true;
    else if(A.x==B.x&&A.y<B.y) return true;
    else return false;
}

bool operator<(const laborT &A,const laborT &B){
    if(A.distance<B.distance) return true;
    else if(A.distance>B.distance) return false;
    else if(A.name<B.name) return true;
    else return false;
}

bool operator<(const arcT &A,const arcT &B){
    if(A.distance<B.distance) return true;
    else if(A.distance>B.distance) return false;
    else if(A.start<B.start) return true;
    else if(A.start>B.start) return false;
    else if(A.end<B.end) return true;
    else return false;
}

bool operator==(const coordT &A,const coordT &B){
    if(A.x==B.x&&A.y==B.y) return true;
    else return false;
}

bool operator<(const vector<laborT> &A,const vector<laborT> &B){
    double Atotal=0;
    double Btotal=0;
    for(unsigned int i=0;i<A.size();i++){
        Atotal+=A[i].distance;
    }   

    for(unsigned int j=0;j<B.size();j++){
        Btotal+=B[j].distance;
    }   

    if(Atotal<Btotal) return true;
    else return false;
}

/*Function: DrawLabeledPointAndLine
 * Usage DrawLabeledPointAndLine("Stanford.txt");
 * ------------------------------------------------
 * read maps information from "Stanford.txt",
 * draw labeled points in the map,
 * draw Line between the points.
 */
void readMapData(map<string,infoT> &point,set<arcT> &arc,string mapsFileName){
    ifstream fp(mapsFileName.c_str());
    string tem;
    while(fp>>tem){
        if(tem=="NODES") break;
    }
    while(true){
        string pointname;
        string x,y;
        infoT info;
        fp>>pointname;
        if(pointname=="ARCS") break;
        fp>>x>>y;
        cout<<pointname<<" "<<x<<" "<<y<<endl;
        info.location.x=atof(x.c_str());
        info.location.y=atof(y.c_str());
        point.insert(pair<string,infoT>(pointname,info));
    }
    cout<<"--------------------------------------------"<<endl;
    while(true){
        string start,end;
        string length;
        double len;
        fp>>start;
        if(start=="") break;
        fp>>end>>length;
        len=atof(length.c_str());
        cout<<start<<" "<<end<<" "<<len<<endl;
        //store labor info
        laborT s,e;
        s.name=end;
        s.distance=len;
        e.name=start;
        e.distance=len;
        point.find(start)->second.labor.insert(s);
        point.find(end)->second.labor.insert(e);
        //store arc
        arcT temArc;
        temArc.start=start;
        temArc.end=end;
        temArc.distance=len;
        arc.insert(temArc);
    }
}

void DrawLabeledPointAndLine(const map<string,infoT> &point,const set<arcT> &arc){

    map<string,infoT>::const_iterator itrP=point.begin();
    while(itrP!=point.end()){
        DrawFilledCircleWithLabel(itrP->second.location, "green", itrP->first);
        itrP++;
    }

    set<arcT>::const_iterator itrA=arc.begin();
    while(itrA!=arc.end()){
        //read arc
        string start=(*itrA).start;
        string end=(*itrA).end;
        //draw
        DrawLineBetween(point.find(start)->second.location, point.find(end)->second.location,"green");
        itrA++;
    }
}

void drawLine(const vector<laborT> &path,const map<string,infoT> &point,const string sp){
    vector<laborT>::const_iterator itr=path.begin();
    cout<<"drawing the path"<<endl;
    while((itr+1)!=path.end()){
        cout<<(*itr).name<<"-----"<<(*(itr+1)).name<<endl;
        DrawLineBetween(point.find((*itr).name)->second.location,point.find((*(itr+1)).name)->second.location,"red");
        itr++;
    }
}

void draw(const map<string,infoT> &point,const set<arcT> arc,set<string> include,set<vector<laborT> > path,const string sp,const string ep){
    laborT begin;
    begin.name=sp;
    begin.distance=0;
    vector<laborT> begin1;
    begin1.push_back(begin);
    path.insert(begin1);

    while(!path.empty()){
        string top=(*path.begin()).back().name;
        if(top==ep){
            cout<<"get the path"<<endl;
            drawLine(*path.begin(),point,sp);
            break;
        }
        cout<<"start:"<<top<<endl;
        set<laborT> laborhood=point.find(top)->second.labor;
        set<laborT>::iterator itr=laborhood.begin();
        while(itr!=laborhood.end()){
            if(include.count((*itr).name)==0){
                cout<<"neigberhood:"<<(*itr).name<<endl;
                vector<laborT> first=*path.begin();
                first.push_back(*itr);
                path.insert(first);
                include.insert((*itr).name);
            }
            itr++;
        }
        path.erase(path.begin());
        cout<<path.empty()<<endl;
    }

}


void DrawOptionalPath(const map<string,infoT> &point,const set<arcT> &arc){
    cout<<"select the start point and end point use the mouse in the map."<<endl;
    cout<<"you will get the optimal path"<<endl;
    coordT startP,endP;
    string sp,ep;
    //get the start and end
    while(true){
        cout<<"please click the start point....."<<endl;
        startP=GetMouseClick();
        map<string,infoT>::const_iterator itr=point.begin();
        while(itr!=point.end()){
            if(WithinDistance(startP,itr->second.location)) break;
            itr++;
        }
        if(itr==point.end()){
            cout<<"wrong click,there is no point in the click place"<<endl;
        }
        else{
            cout<<"the start point is "<<itr->first<<endl;
            sp=itr->first;
            break;
        }
    }
    while(true){
        cout<<"please click the end point....."<<endl;
        endP=GetMouseClick();
        map<string,infoT>::const_iterator itr=point.begin();
        while(itr!=point.end()){
            if(WithinDistance(endP,itr->second.location)) break;
            itr++;
        }
        if(itr==point.end()){
            cout<<"wrong click,there is no point in the click place"<<endl;
        }
        else{
            cout<<"the end point is "<<itr->first<<endl;
            ep=itr->first;
            break;
        }
    }

    //draw the optional path
    set<string> include;
    set< vector<laborT> > path;
    include.insert(sp);
    cout<<"start drawing optional path..."<<endl;
    draw(point,arc,include,path,sp,ep);

}

void DrawMinimalSpanningTree(const map<string,infoT> &point,const set<arcT> &arc){
    set<string> include;
    cout<<"start drawing the SpanningTree......"<<endl;
    include.insert(point.begin()->first);
    while(true){
        set<string>::iterator itr=include.begin();
        double min=100000;
        string start,end;
        while(itr!=include.end()){
            cout<<"start point:"<<*itr<<endl;
            set<laborT>::iterator itr_labor=point.find(*itr)->second.labor.begin();
            while(itr_labor!=point.find(*itr)->second.labor.end()){
                string target=(*itr_labor).name;
                cout<<"     labor:"<<target<<endl;
                if(include.count(target)==0){
                    double distance=(*itr_labor).distance;
                    if(distance<min){
                        min=distance;
                        start=*itr;
                        end=target;
                        cout<<"short line:"<<start<<":"<<end<<endl;
                    }
                }
                itr_labor++;
            }
            itr++;
        }
        if(min==100000) break;
        include.insert(end);
        cout<<"include.insert:"<<end<<endl;
        cout<<"Draw line:"<<start<<"-----------------"<<end<<endl;
        DrawLineBetween(point.find(start)->second.location, point.find(end)->second.location,"red");
    }
}

int main()
{
    InitGraphics();
    SetWindowTitle("CS106 Pathfinder");
    cout << "This masterful piece of work is a graph extravaganza!" << endl
        << "The main attractions include a lovely visual presentation of the graph" << endl
        << "along with an implementation of Dijkstra's shortest path algorithm and" << endl
        << "the computation of a minimal spanning tree.  Enjoy!" << endl;
    //double w=GetPictureWidth("Stanford.jpg");
    //double h=GetPictureHeight("Stanford.jpg");
    //cout<<w<<":"<<h<<endl;
    //cout<<GetWindowWidth()<<":"<<GetWindowHeight()<<endl;

    //define the map data source
    const string Stanford="Stanford.txt";
    const string Small="Small.txt";
    const string USA="USA.txt";
    const string PicStanford="stanford.jpg";
    const string PicUSA="USA.bmp";

    //define the map data struct
    map<string,infoT> point;
    set<arcT> arc;

    while(true){
        cout<<"0) Stanford.txt   1) Small.txt  2) USA.txt\n";
        cout<<"Please select the map data source(0,1 or 2):\n";
        int flag;
        cin>>flag;
        if(flag==0){
            //:wq
            //SetWindowSize(7,5);
            //double w=GetPictureWidth("stanford2.png");
            //double h=GetPictureHeight("stanford2.png");
            //cout<<w<<":"<<h<<endl;
            //SetWindowSize(w,h);
            DrawNamedPicture("stanford2.png");
            readMapData(point,arc,Stanford); 
            break;
        }
        //double w=GetPictureWidth("USA.bmp");
        //double h=GetPictureHeight("USA.bmp");
        //cout<<w<<":"<<h<<endl;
        SetWindowSize(6.3,4);
        if(flag==1){
            DrawNamedPicture("USA.bmp");
            readMapData(point,arc,Small);
            break;
        }
        else if(flag==2){
            DrawNamedPicture("USA.bmp");
            readMapData(point,arc,USA);
            break;
        }
        else{
            cout<<"Wrong number!"<<endl;
        }

    }
    //draw map
    DrawLabeledPointAndLine(point,arc);

    map<string,infoT>::iterator it=point.begin();
    while(it!=point.end()){
        cout<<it->first<<":"<<endl;
        set<laborT> la=it->second.labor;
        set<laborT>::iterator i=la.begin();
        while(i!=la.end()){
            cout<<"     "<<(*i).name<<":"<<(*i).distance<<endl;
            i++;
        }
        it++;
    }

    while(true){
        cout<<"What do you want?"<<endl;
        cout<<"0) draw the optional path between the slected points"<<endl;
        cout<<"1) draw the minimal spanning tree"<<endl;
        cout<<"Please select(0 or 1):";
        int flag;
        cin>>flag;
        if(flag==0){
            //draw the optional path
            DrawOptionalPath(point,arc);
            break;
        }
        else if(flag==1){
            //draw the minimal spanning tree
            DrawMinimalSpanningTree(point,arc);
            break;
        }
        else{
            cout<<"wrong number!"<<endl;
        }
    }
    return (0);
}
