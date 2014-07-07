/*
 * File: scanner.cpp
 * -----------------
 * Implementation for the simplified Scanner class.
 * Code taken from the CS106B/X Course Reader, page 332, Figure 9.6
 */

#include "genlib.h"
#include "scanner.h"
#include <cctype>
#include <iostream>

/*
 * The details of the representation are inaccessible to the client,
 * but consist of the following fields:
 *
 * buffer -- String passed to setInput
 * len -- Length of buffer, saved for efficiency
 * cp -- Current character position in the buffer
 * spaceOption -- Setting of the space option extension
 */

Scanner::Scanner() {
    buffer = "";
    spaceOption = PreserveSpaces;
}

Scanner::~Scanner() {
    /* Empty */
}

void Scanner::setInput(string str) {
    buffer = str;
    len = buffer.length();
    cp = 0;
}

/*
 * Implementation notes: nextToken
 * -------------------------------
 * The code for nextToken follows from the definition of a token.
 */

string Scanner::nextToken() {
    if (cp == -1) {
	Error("setInput has not been called");
    }
    if (spaceOption == IgnoreSpaces) skipSpaces();
    int start = cp;
    if (start >= len) return "";
    if (isalnum(buffer[cp])) {
	int finish = scanToEndOfIdentifier();
	return buffer.substr(start, finish - start + 1);
    }
    cp++;
    return buffer.substr(start, 1);
}

bool Scanner::hasMoreTokens() {
    if (cp == -1) {
	Error("setInput has not been called");
    }
    if (spaceOption == IgnoreSpaces) skipSpaces();
    return (cp < len);
}

void Scanner::setSpaceOption(spaceOptionT option) {
    spaceOption = option;
}

Scanner::spaceOptionT Scanner::getSpaceOption() {
    return spaceOption;
}

/* Private functions */

/*
 * Private method: skipSpaces
 * Usage: skipSpaces();
 * -------------------
 * This function advances the position of the scanner until the
 * current character is not a whitespace character.
 */

void Scanner::skipSpaces() {
    while (cp < len && isspace(buffer[cp])) {
	cp++;
    }
}

/*
 * Private method: scanToEndOfIdentifier
 * Usage: finish = scanToEndOfIdentifier();
 * ----------------------------------------
 * This function advances the position of the scanner until it
 * reaches the end of a sequence of letters or digits that make
 * up an identifier. The return value is the index of the last
 * character in the identifier; the value of the stored index
 * cp is the first character after that.
 */

int Scanner::scanToEndOfIdentifier() {
    while (cp < len && isalnum(buffer[cp])) {
	cp++;
    }
    return cp - 1;
}
