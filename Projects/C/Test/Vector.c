#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "Vector.h"

Vector *createVector(float x, float y, float z) {

	Vector *vector = (Vector *) malloc(sizeof(Vector));
	vector->x = x;
	vector->y = y;
	vector->z = z;
	return vector;

}

void destroyVector(Vector *vector) {

	free(vector);

}

void print(Vector *vector) {

	printf("(%f, %f, %f)\n", vector->x, vector->y, vector->z);

}

Vector *add(Vector *mutating, Vector *added) {

	mutating->x += added->x;
	mutating->y += added->y;
	mutating->z += added->z;
	return mutating;

}

Vector *multiply(Vector *vector, float scalar) {

	vector->x *= scalar;
	vector->y *= scalar;
	vector->z *= scalar;
	return vector; 

}

Vector *subtract(Vector *mutating, Vector *subtracted) {

	Vector temp = *subtracted;
	return add(mutating, multiply(&temp, -1.0));

}

Vector *divide(Vector *vector, float scalar) {

	return multiply(vector, 1.0 / scalar);

}

float dotProduct(Vector *v1, Vector *v2) {

	return v1->x * v2->x + v1->y * v2->y + v1->z * v2->z;

}



Vector *crossProduct(Vector *mutating, Vector *crossed) {

	Vector temp;
	temp.x = mutating->y * crossed->z - mutating->z * crossed->y;
	temp.y = mutating->z * crossed->x - mutating->x * crossed->z;
	temp.z = mutating->x * crossed->y - mutating->y * crossed->x;
	*mutating = temp;
	return mutating;

}

float magnitudeSquared(Vector *vector) {

	return vector->x * vector->x + vector->y * vector->y + vector->z * vector->z;

}

float magnitude(Vector *vector) {

	return sqrt(magnitudeSquared(vector));

}
