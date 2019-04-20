#include <stdio.h>

typedef struct Node_t {
	
	int data;
	struct N_t *next;

} Node;

typedef struct LinkedListL_t {
	
	Node *head;
	Node *tail;

} LinkedList;

void insertHead(Node *node, LinkedList *linkedList) {

	if (linkedList->head == NULL) {

		// Empty Case
		linkedList->head = node;
		linkedList->tail = node;

	} else {

		// Node-Empty Case
		node->next = linkedList->head;
		linkedList->head = node;

	}

}

void insertTail(Node *node, LinkedList *linkedList) {

	if (linkedList->tail == NULL) {

		// Empty Case
		linkedList->head = node;
		linkedList->tail = node;

	} else {

		// Node-Empty Case
		linkedList->tail.next = node;
		linkedList->tail = node;

	}

}

int main(void) {

	LinkedList *myList = (LinkedList *) malloc(sizeof(LinkedList));
	myList->head = NULL;
	myList->tail = NULL;

	Node *node1 = (Node *) malloc(sizeof(Node));
	node1->data = 5;
	node1->next = NULL;

	Node *node2 = (Node *) malloc(sizeof(Node));

}