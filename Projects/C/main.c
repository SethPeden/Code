#include <stdio.h>
#include "Vector.h"

int main(void) {
	
	Vector v = createVector(0.5, 1.0);
	
	printf("%s\n", v.info(v));
	
}