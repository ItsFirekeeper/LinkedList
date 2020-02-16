#include "globals.h"
#include "indexList.h"
#include <iomanip>
#include <iostream>
#include <cstring>
using namespace std;
const int STRMAX = 26;

indexList::indexList(){

    head.next = &tail;
    tail.prev = &head;
}

indexList::~indexList(){

    indexPtr temp = NULL, temp2 = head.next;

    while (temp2 != &tail){
	temp =temp2;
	temp2 = temp->next;
	delete temp;
    }
    head.next = &tail;
    tail.prev = &head;
}

void indexList::update(const WORD aWord, int max_count, bool &success){

    indexPtr here = NULL, next, prev, newNode;
    bool found = false;
    int amount;
    success = false;
    search(aWord, here, found);

    if (found){
	amount = getCount(aWord);
	if (amount < max_count){
	    here->count++;
	    success = true;
	}
	else {
	    prev = here->prev;
	    next = here->next;
	    prev->next = next;
	    next->prev = prev;
	    delete here;
	}
    }
    else {
	here = head.next;
	if (size() == 0){
	    prev = &head;
	    next = &tail;
	    cout << size() << endl;
	}

	else if (size() == 1){

	    if (strncmp(here->word, aWord, STRMAX) > 0){
		prev = &head;
		next = here;
	    }
	    else {
		prev = here;
		next = &tail;
	    }
	    cout << size() << endl;
	}

	else{
	    getSpot(aWord, next);
	    prev = next->prev;
	}
	newNode = new indexNode;
	newNode->count = 1;
	strncpy(newNode->word, aWord, STRMAX);
	newNode->prev = prev;
	newNode->next = next;
	prev->next= newNode;
	next->prev = newNode;
	success = true;
    }
    return;
}

void indexList::write(ostream &os){
    int amount = 0;
    indexPtr temp = head.next;
    if (head.next == &tail){
	    os << "Index List is empty" << endl;
    }
    else {
	while (temp != &tail && amount < size()){
	    amount++;
	    os <<  left << setw(5) << amount << left << setw(STRMAX)
	       << temp->word << temp->count << endl;
	    temp = temp->next;
	}
    }
    return;
}
// the following three functions are provided for testing purposes only
void indexList::getWord(int position, WORD aWord, bool &found) const{

    indexPtr temp = head.next;

    int count;

    if (position <= size()){
	for (count = 1; temp != &tail && count < position; count++){
	    temp = temp->next;
	}
	strncpy(aWord, temp->word, STRMAX);
	found = true;
    }

    else {
	found = false;
    }
    return;
}
int indexList::getCount(const WORD aWord) const{

    int count = 0;
    indexPtr temp = head.next;
    while (temp != &tail && count != 0){
	if (strncmp(temp->word, aWord, STRMAX) == 0){
	    count = temp->count;
	}
	else {
	    temp = head.next;
	}
    }
    return count;
}

int indexList::size() const{

    indexPtr temp;
    int amount = 0;

    if (head.next != &tail){
	temp = head.next;
	amount++;
	while(temp != &tail){
	    temp = temp->next;
	    amount++;
	}
    }
    return amount;
}

void indexList::search(const WORD aWord, indexPtr &here, bool &found) const{

    here = head.next;
    found = false;
	if (here != &tail){

	    if (aWord[0] >= 'a' && aWord[0] <= 'm'){
		while (here != &tail && !found) {
		    if (strncmp(aWord, here->word, STRMAX) == 0){
			found = true;
		    }
		    else {
			here = here->next;
		    }
		}
	    }
	    else if (aWord[0] >= 'n' && aWord[0] <= 'z'){
		here = tail.prev;
	    }
	    while (here != &head && !found){
		if (strncmp(aWord, here->word, STRMAX) == 0){
		    found = true;
		}
		else {
		    here = here->prev;
		}
	    }
	}
	if (!found){



	}
	return;
}

void indexList::getSpot(const WORD aWord, indexPtr &spot){
    indexPtr back = head.next;
    indexPtr front = back->next;
    bool found = false;

    while (!found && front != &tail){
	if ((strncmp(front->word, aWord, STRMAX)) < 0 && back->prev == &head){
	    found = true;
	    spot = front;
	}
	else if ((strncmp(front->word, aWord, STRMAX)) > 0 && front->next == &tail){
	    found = true;
	    spot = front;
	}
	else if ((strncmp(front->word, aWord, STRMAX)) > 0
	    && (strncmp(back->word, aWord, STRMAX) < 0)){
	found = true;
	spot = front;
	}
	else {
	    back = front;
	    front = front->next;
	}
    }
    return;
}
/*
 *
 *     search     takes a word
 *                the index list is search for this word and if it is found,
 *                the boolean, found, parameter is set to true and the pointer,
 *                here, is set to point to the node containing the word;
 *                otherwise if the word is not found, the found parameter is
 *                set to false and here is set to point to the node with the
 *                word that would follow the word being searched for,
 *                i.e. the word’s alphabetic successor.
 *
 *                Details:
 *                Since the list can be traversed in either direction, this
 *                function will start searching from the head node for words
 *                that start with the letters ‘a’ through ‘m’; the search will
 *                start from the tail node for words starting with the letters
 *                'n' through 'z'.
 *
 */

