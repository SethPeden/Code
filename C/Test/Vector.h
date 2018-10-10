typedef struct {

        float x, y, z;

} Vector;

Vector *createVector(float x, float y, float z);

void destroyVector(Vector *);

void print(Vector *);

Vector *add(Vector *mutating, Vector *added);

Vector *multiply(Vector *vator, float scalar);

Vector *subtract(Vector *mutating, Vector *subtracted);

Vector *divide(Vector *vector, float scalar);

float dotProduct(Vector *v1, Vector *v2);

Vector *crossProduct(Vector *mutating, Vector *crossed);

float magnitudeSquared(Vector *vector);

float magnitude(Vector *vector);
