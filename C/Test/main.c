#include <stdio.h>
#include "Vector.h"

int main(void) {
  
	Vector *v1 = createVector(1.5, 2.2, -1.3);
	Vector *v2 = createVector(0.3, -5.7, 0.0);

	print(add(v1, v2));
	print(subtract(v1, v2));
	print(multiply(v1, -2));
	print(divide(v1, -0.25));
	printf("%f\n", dotProduct(v1, v2));
	print(crossProduct(v1, v2));
	printf("%f\n", magnitude(v1));

}
