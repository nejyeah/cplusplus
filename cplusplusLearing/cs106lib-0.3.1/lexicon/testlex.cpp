#include "lexicon.h"
#include <iostream>
#include "genlib.h"

int main()
{
    cout << "constructing lex..." << endl;
    Lexicon lex("lexicon.dat");
    cout << " done" << endl;
    return 0;
}
