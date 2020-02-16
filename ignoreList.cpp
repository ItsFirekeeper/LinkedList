#include "ignoreList.h"
#include <iomanip>
#include <iostream>
#include <cstring>
using namespace std;

const int STRMAX = 26;

ignoreList::ignoreList(){

    maxSize = 25;
    fillLevel = 0;
    ignoreWords = new ignoreNode[maxSize];
}

ignoreList::~ignoreList(){
    delete []ignoreWords;
}

void ignoreList::load(istream &in){

    WORD aWord;
    in >> aWord;

    while(!in.eof()){
	insert(aWord, false);
	fillLevel++;
	in >> aWord;
    }
    fillLevel--;
    return;
}

bool ignoreList::contains(const WORD aWord){
    bool found = false;

    for (int i = 0; i < fillLevel && !found; i++){

	if (strncmp(ignoreWords[i].aWord, aWord, STRMAX) == 0){
	    found = true;
	}
    }
    return found;
}

void ignoreList::insert(const WORD aWord, bool fromWhere){

    if (fromWhere){
	fillLevel++;
    }
    if (fillLevel == maxSize){
	resize();
    }
    strncpy(ignoreWords[fillLevel].aWord, aWord, STRMAX);
    ignoreWords[fillLevel].fromText = fromWhere;
    return;
}

void ignoreList::resize(){

    maxSize += 10;
    ignoreNode *temp = new ignoreNode[maxSize];

    for (int i = 0; i < fillLevel; i++)
    {
	strncpy(temp[i].aWord, ignoreWords[i].aWord, STRMAX);
	temp[i].fromText = ignoreWords[i].fromText;
    }

    delete []ignoreWords;
    ignoreWords = temp;
    return;

}

void ignoreList::write(ostream &os){
    int amountFromList = 0;
    int newIgnore = 0;

    while ((size()!= 0) && !ignoreWords[fillLevel].fromText){
	amountFromList++;
    }
    os << amountFromList << " words from ignore file." << endl;

    if (size()!= 0 && ignoreWords[fillLevel].fromText){
	os << "New ignore words from book" << endl;
	newIgnore++;
	while (newIgnore <= fillLevel){
	    os << left << setw(5) << newIgnore+1 << ignoreWords[newIgnore].aWord << endl;
	    newIgnore++;
	}
    }
    else
	os << "No new ignore words from book file." << endl;

    return;
}
void ignoreList::getWord(int position, WORD aWord, bool &fromWhere, bool &found){

    if (position <= fillLevel){
	strncpy(aWord, ignoreWords[position-1].aWord, STRMAX);
	fromWhere = ignoreWords[position-1].fromText;
	found = true;
    }
    else {
	found = false;
    }
    return;
}
int ignoreList::size(){

    return fillLevel;
}

