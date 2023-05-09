#include "easyppm.h"

typedef struct {
  int x;
  int y;
} point;

void draw_line(PPM* img, point p0, point p1, ppmcolor color);
int* interpolate(point p0, point p1);
void draw_triangle(PPM* img, point p0, point p1, point p2, ppmcolor color);