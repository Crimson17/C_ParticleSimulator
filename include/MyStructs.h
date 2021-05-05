#ifndef MYSTRUCTS_H
#define MYSTRUCTS_H

// A point in 2D space
typedef struct Point2D
{
    float x;
    float y;
} POINT2D;

// A vector in 2D space
typedef struct Vector2D
{
    float i;
    float j;
} VECTOR2D;

typedef struct Particle{
    POINT2D location;
    float velocity;
    unsigned int color;
}PARTICLE;

#endif
