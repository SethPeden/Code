#include <stdio.h>
#include <stdlib.h>

typedef struct Node {

	void *data;
	struct Node *next;
	struct Node *previous;

} Node;

typedef struct LinkedList {

	Node *head;
	Node *tail;

} LinkedList;

typedef struct BigInteger {
	
	LinkedList *bytes;
	unsigned long size;

} BigInteger;

BigInteger *createBigInteger(char bytes[], unsigned long size) {

	BigInteger *integer = malloc(sizeof(BigInteger));
	integer->size = size;
	integer->bytes = malloc(sizeof(LinkedList));
	(integer->bytes)->head = NULL;
	(integer->bytes)->tail = NULL;

	unsigned long i = 0;

	while (i++ < integer->size) {

		Node *node = malloc(sizeof(Node));
		node->data = malloc(sizeof(char));
		*((int *) node->data) = *bytes++;
		
		if ((integer->bytes)->head) {

			// Not the first byte added
			node->previous = (integer->bytes)->tail;
			(node->previous)->next = node;

		} else {

			// First byte added
			node->previous = NULL;
			(integer->bytes)->head = node;

		}

		node->next = NULL;
		(integer->bytes)->tail = node;

	}

	return integer;

}

BigInteger *createBigIntegerFromInt(int val) {

	char bytes[4];

	for (int i = 0; i < 4; i++)
		bytes[3 - i] = (val >> (char) ((8 * i)) & 0xff);

	return createBigInteger(bytes, sizeof bytes / sizeof *bytes);

}

void print(BigInteger *integer) {

	Node *elem = (integer->bytes)->head;

	unsigned long i = 0;

	while (i++ < integer->size) {

		if (!((*(char *) elem->data) & 0xf0))
			printf("0");

		printf("%x", *((char *) elem->data) & 0xff);
		elem = elem->next;

	}

	printf("\n");

}

// TODO: Enable addition, subtraction, multiplication, and division

int main(void) {

	BigInteger *integer = createBigIntegerFromInt(0xffffffff);

	print(integer);

}