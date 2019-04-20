#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "Vector.h"

float magnitude(Vector v) {
	return sqrt(v.x * v.x + v.y * v.y);
}

float angle(Vector v) {
	return atan2(v.y, v.x);
}

Vector unit(Vector v) {
	Vector w = {v.x / magnitude(v), v.y / magnitude(v)};
	return w;
}

char* toString(Vector v) {
	char buf[128];
	snprintf(buf, sizeof buf, "[%f, %f]", v.x, v.y);
	char* p = buf;
	return p;
}

char* info(Vector v) {
	char buf[4096] = "{";
	char inter[100];
	strcat(buf, v.toString(v));
	strcat(buf, ", magnitude=");
	snprintf(inter, sizeof inter, "%f", v.magnitude(v));
	strcat(buf, inter);
	strcat(buf, ", angle=");
	snprintf(inter, sizeof inter, "%f", v.angle(v));
	strcat(buf, inter);
	strcat(buf, ", unit=");
	strcat(buf, v.toString(v.unit(v)));
	strcat(buf, "}");
	char* p = buf;
	return p;
}

Vector createVector(float x, float y) {
	Vector v = {x, y, magnitude, angle, unit, toString, info};
	return v;
}