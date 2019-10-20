#include <iostream>
#include <stdlib.h>
#include <stdio.h>

#include "list.h"

using namespace std;

list stock;

int main () {
	stock.create();
	stock.open_file();
	stock.read_file();
	stock.clear();
	return EXIT_SUCCESS;
}

void list::create() {
	head = NULL;
	nodecount = 0;
}

void list::open_file () {
	tracker = fopen("input.txt", "r+");
	if(!tracker){
		cerr << "Error: Unable to read file" << endl;
		exit(EXIT_FAILURE);
	}
}

void list::read_file () {
	int k;
	fseek(tracker, 0, SEEK_SET);
	while (!feof(tracker)) {
		fscanf(tracker, " %d", &k);
		if(k == 0) {
			current_stock();
		} else if (k > 0) {
			add_stock(k);
		} else {
			sell(-k);
		}
	}
	fclose(tracker);
}

void list::add_stock(int size){	
	if(head){
		node *traverse, *tail;
		tail = NULL;
		traverse = head;
		while(traverse){
			if (traverse->size == size) {
				traverse->quant++;
				return;
			} else if (traverse->size > size) {
				node *newnode = new node;
				newnode->size = size;
				newnode->quant = 1;
				if(tail) {
					tail->next = newnode;
				} else {
					head = newnode;
				}
				newnode->next = traverse;
				nodecount++;
				return;
			}
			tail = traverse;
			traverse = traverse->next;
		}
		node *newnode = new node;
		newnode->size = size;
		newnode->quant = 1;
		newnode->next = NULL;
		tail->next = newnode;
		nodecount++;
	} else {
		node* newnode = new node;
		newnode->size = size;
		newnode->quant = 1;
		newnode->next = NULL;
		head = newnode;
		nodecount++;
	}
}

void list::current_stock(){
	if(head){
		node *traverse;
		traverse = head;
		while(traverse) {
			cout << traverse->size << ":" << traverse->quant << endl;
			traverse = traverse->next;
		}
	}
}

void list::sell(int size){
	if(head){
		node *traverse, *tail;
		traverse = head;
		tail = NULL;
		while(traverse) {
			if(traverse->size == size){
				if (traverse->quant == 1) {
					if (tail) {
						tail->next = traverse->next;
						delete traverse;
						return;
					} else {
						head = traverse->next;
						delete traverse;
						return;
					}
				} else {
					traverse->quant -= 1;
					return;
				}
			}
			tail = traverse;
			traverse = traverse->next;
		}
	}
	cout << "NO_STOCK" << endl;
}

void list::clear(){
	node *tmpptr;
	while (head){
		tmpptr = head;
		head = head->next;
		delete tmpptr;
	}
	nodecount = 0;
}
