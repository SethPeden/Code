#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int c = 1000000; // 1,000,000

typedef struct Element {
	
	struct Element *previous;
	int value;
	struct Element *next;

} Element;

Element *list = NULL;

void setup(int c) {

	srand((unsigned int) time(NULL));

	for (int i = 0; i < c; i++) {

		Element *elem = malloc(sizeof(Element));
		elem->value = rand() % 100;
		elem->previous = list;
		if (list != NULL) list->next = elem;
		list = elem;

	}

	while (list->previous) list = list->previous;

}

int main(void) {

	void setup(int);

	int time = clock();

	setup(c);

	int sum = 0;

	while (list) {

		sum += list->value;
		list = list->next;

	}

	printf("Time elasped for Linked List: %f ms.\n", (double) 1000 * (clock() - time) / CLOCKS_PER_SEC);
	printf("Linked List Sum = %d.\n", sum);

	time = clock();

	Element *array[c]; 

	for (int i = 0; i < c; i++) {

		array[i] = malloc(sizeof(Element));
		array[i]->value = rand() % 100;

	}

	sum = 0;

	for (int i = 0; i < c; i++) {

		sum += array[i]->value;

	}

	printf("Time elasped for Array: %f ms.\n", (double) 1000 * (clock() - time) / CLOCKS_PER_SEC);
	printf("Array Sum = %d.\n", sum);

	return 0;

}