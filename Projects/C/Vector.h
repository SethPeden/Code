#ifndef VECTOR_H_   /* Include guard */
#define VECTOR_H_ 

typedef struct Vector {
	
	float x;
	float y;
	
	float (*magnitude) (struct Vector v);
	float (*angle) (struct Vector v);
	struct Vector (*unit) (struct Vector v);
	char* (*toString) (struct Vector v);
	char* (*info) (struct Vector v);
	
} Vector;

Vector createVector(float x, float y);

#endif 