/* File: boggle.cpp
 * ----------------
 * Your name here!
 */

#include "genlib.h"
#include "simpio.h"
#include <iostream>
#include <string>
#include <set>
#include <map>
#include <vector>
#include "extgraph.h"
#include "gboggle.h"
#include "random.h"
#include "lexicon.h"
#include "strutils.h"
#include "sound.h"

struct pointT{
    int row,col;
};

string StandardCubes[16]  = 
{"AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS", "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
    "DISTTY", "EEGHNW", "EEINSU", "EHRTVW", "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"};

string BigBoggleCubes[25]  = 
{"AAAFRS", "AAEEEE", "AAFIRS", "ADENNN", "AEEEEM", "AEEGMU", "AEGMNN", "AFIRSY", 
    "BJKQXZ", "CCNSTW", "CEIILT", "CEILPT", "CEIPST", "DDLNOR", "DDHNOT", "DHHLOR", 
    "DHLNOR", "EIIITT", "EMOTTT", "ENSSSU", "FIPRSY", "GORRVW", "HIPRRY", "NOOTUW", "OOOTTU"};

void GiveInstructions()
{
    cout << endl << "The boggle board is a grid onto which I will randomly distribute " 
        << "cubes. These 6-sided cubes have letters rather than numbers on the faces, " 
        << "creating a grid of letters on which you try to form words. You go first, " 
        << "entering all the words you can find that are formed by tracing adjoining " 
        << "letters. Two letters adjoin if they are next to each other horizontally, " 
        << "vertically, or diagonally. A letter can only be used once in the word. Words "
        << "must be at least 4 letters long and can only be counted once. You score points "
        << "based on word length: a 4-letter word is worth 1 point, 5-letters earn 2 "
        << "points, and so on. After your puny brain is exhausted, I, the super computer, "
        << "will find all the remaining words and double or triple your paltry score." << endl;

    cout << "\nHit return when you're ready...";
    GetLine();
}

static void Welcome()
{
    cout << "Welcome!  You're about to play an intense game of mind-numbing Boggle. " 
        << "The good news is that you might improve your vocabulary a bit.  The "
        << "bad news is that you're probably going to lose miserably to this little "
        << "dictionary-toting hunk of silicon.  If only YOU had a gig of RAM..." << endl << endl;
}

/*
 * random to chose the face-up letters from the StandardCubes[16] above
 */
void randomShuffleCubeLocation(const int rowlength,const int collength,string letters,const int flag){

    for(int row=0;row<rowlength;row++){
        for(int col=0;col<collength;col++){
            int index=RandomInteger(0,letters.size());
            char a =letters[index];
            letters.erase(letters.begin()+index);
            LabelCube(row,col,a);
        }
    }
}

void randomChoseFaceupLetters(const int rowlength,const int collength,const int flag){
    string letters;
    for(int row=0;row<rowlength;row++){
        for(int col=0;col<collength;col++){
            string lettercube;
            if(flag==0) lettercube=StandardCubes[row*collength+col];
            else lettercube=BigBoggleCubes[row*collength+col];
            int index=RandomInteger(0,lettercube.size());
            letters.push_back(lettercube[index]);
        }
    }
    randomShuffleCubeLocation(rowlength,collength,letters,flag);

}


void InitLetters(const int rowlength,const int collength,const int flag){
    cout<<"initializing the cubes ........"<<endl;
    cout<<"........................................"<<endl;

    //random to creat the cube
    randomChoseFaceupLetters(rowlength,collength,flag);

    /*
    //creat the cube exactly the same as the sample 
    //easy to test 
    string s="EECAALEPHNBOQTTY";
    for(int row=0;row<rowlength;row++){
        for(int col=0;col<collength;col++){
            char a =s[row*collength+col];
            LabelCube(row,col,a);
        }
    }*/

    cout<<"the cubes is initialized!"<<endl;
}

/*
 * struct pointT store in set should  
 */
bool operator<(const pointT &A,const pointT &B){
    if(A.row<B.row) return true;
    else if(A.row==B.row&&A.col<B.col) return true;
    else return false;
}

pointT operator+(const pointT &A,const pointT &B){
    pointT c;
    c.row=A.row+B.row;
    c.col=A.col+B.col;
    return c;
}

//recursiv to get all the words
bool recursionGetWords(string &word,pointT start,set<pointT> & include,map<string,set<pointT> > &allwords,Lexicon &lex,vector<pointT> &aroundPointT){
    if(!isInBounds(start.row,start.col)) return false;
    if(include.count(start)==1) return false;
    include.insert(start);
    char a=getLabelCube(start.row,start.col);
    word.push_back(a);
    if(!lex.containsPrefix(word)) return false;
    if(lex.containsWord(word)){
        if(allwords.count(word)==0&&word.size()>=4){
            allwords.insert(make_pair(word,include));
        }
    }
    pointT next;
    for(unsigned int i=0;i<aroundPointT.size();i++){
        next=start+aroundPointT[i];
        string nword=word;
        set<pointT> ninclude=include;
        recursionGetWords(nword,next,ninclude,allwords,lex,aroundPointT);
    }
    return true;
}

/*
 * easy through '+' to get the 8 point around
 */
void initializeAroundPoint(vector<pointT> &aroundPointT){
    pointT arPoint;
    arPoint.row=-1;
    arPoint.col=-1;
    aroundPointT.push_back(arPoint);

    arPoint.row=-1;
    arPoint.col=0;
    aroundPointT.push_back(arPoint);
    arPoint.row=-1;
    arPoint.col=1;
    aroundPointT.push_back(arPoint);
    arPoint.row=0;
    arPoint.col=-1;
    aroundPointT.push_back(arPoint);
    arPoint.row=1;
    arPoint.col=-1;
    aroundPointT.push_back(arPoint);
    arPoint.row=1;
    arPoint.col=0;
    aroundPointT.push_back(arPoint);
    arPoint.row=1;
    arPoint.col=1;
    aroundPointT.push_back(arPoint);
    arPoint.row=0;
    arPoint.col=1;
    aroundPointT.push_back(arPoint);
}

//first find out all the words and it's cubes ,stored in a map<string,set<point> >
void getAllWordsInCubes(map<string,set<pointT> > &allwords,const int rowlength,const int collength){
    Lexicon lex("lexicon.dat");
    cout<<"lexicon.dat  nums:"<<lex.size()<<endl;
    vector<pointT> aroundPointT;
    initializeAroundPoint(aroundPointT);
    for(int row=0;row<rowlength;row++){
        for(int col=0;col<collength;col++){
            pointT start;
            start.row=row;
            start.col=col;
            set<pointT> include;
            string word;
            recursionGetWords(word,start,include,allwords,lex,aroundPointT);

        }

    }
}

void humanPlay(map<string,set<pointT> > &allwords){

    cout<<"enter the words('q' to end):";
    string a;
    set<pointT> path;
    while(true){
        cin>>a;
        if(a=="q") break;
        if(a.size()<4){
            cout<<"the length is not less than 4"<<endl;
            continue;
        }
        a=ConvertToUpperCase(a);
        if(allwords.find(a)==allwords.end()){
            cout<<"wrong words! go on........."<<endl;

        }
        else{
            for(set<pointT>::iterator itr=path.begin();itr!=path.end();itr++){
                HighlightCube((*itr).row,(*itr).col,false);
            }

            RecordWordForPlayer(a,Human);
            path=allwords[a];
            allwords.erase(a);
            for(set<pointT>::iterator itr=path.begin();itr!=path.end();itr++){
                HighlightCube((*itr).row,(*itr).col,true);
            }
        }
    }
}

void computerPlay(map<string,set<pointT> > &allwords){
    set<pointT> path;
    for(map<string,set<pointT> >::iterator itr=allwords.begin();itr!=allwords.end();itr++){
        for(set<pointT>::iterator itr1=path.begin();itr1!=path.end();itr1++){
            HighlightCube((*itr1).row,(*itr1).col,false);
        }
        RecordWordForPlayer(itr->first,Computer);
        path=itr->second;
        for(set<pointT>::iterator itr2=path.begin();itr2!=path.end();itr2++){
            HighlightCube((*itr2).row,(*itr2).col,true);
        }
    }
}

int main()
{
    Welcome();
    cout<<"standard(4*4) or bigboogle(5*5),0 to standard:"<<endl;
    int flag=0;
    cin>>flag;
    int rowlength=4;
    int collength=4;
    
    if(flag==0){
        InitGraphics();
        SetWindowSize(9, 5);
    }
    else{
        rowlength=5;
        collength=5;
        InitGraphics();
        SetWindowSize(10, 6);
        
    }
    DrawBoard(rowlength,collength);
    Randomize();
    InitLetters(rowlength,collength,flag);//set the face-up letters 
    GiveInstructions();
    map<string,set<pointT> > allwords;
    getAllWordsInCubes(allwords,rowlength,collength);//first get all the possible words in the cubes
    //cout<<"nums:"<<allwords.size()<<endl;
    cout<<"would you like to turn on the sound (y or n):";
    char a;
    cin>>a;
    if(a=='y'){
        SetSoundOn(true);
        PlayNamedSound("denied.wav");
    }
    humanPlay(allwords);
    computerPlay(allwords);
    return 0;
}
