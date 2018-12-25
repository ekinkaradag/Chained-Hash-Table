#include"linkedlist.h"

linkedlist::linkedlist() {
	first = NULL;
	last = NULL;
	count = 0;
}

int linkedlist::length()const {
	return count;
}

bool linkedlist::isEmptyList()const {
	return count == 0;
}

void linkedlist::insertNew(string value) {

	node *valuenode = new node;

	valuenode->data = value;
	valuenode->wordCount = 1;
	valuenode->link = NULL;

	valuenode->link = first;
	first = valuenode;

	if (last == NULL)
	{
		last = valuenode;
	}
	count++;
}

linkedlist::~linkedlist() {

	node* temp = first;

	while (temp != NULL)
	{
		first = first->link;
		delete temp;
		temp = first;
	}
	last = NULL;
	count = 0;
}

bool linkedlist::search(string value)const {

	bool found = false;

	node *temp = first;

	while (temp != NULL)
	{
		if (temp->data == value)
		{
			found = true;
			temp->wordCount++;
			break;
		}
		temp = temp->link;

	}
	return found;
}

void linkedlist::mostUsedInList(unsigned long *topCount, string *topWord) {
	unsigned long currentHigh = 0;
	node *temp = first;

	while (temp != NULL) { //search in the current list
		if (temp->wordCount > currentHigh) {
			currentHigh = temp->wordCount;
			*topWord = temp->data;
			*topCount = temp->wordCount;
		}
		temp = temp->link;
	}

	delete temp;
}