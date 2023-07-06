#include "easyppm.h"

typedef struct {
  int x;
  int y;
  float h;
} point;

void swap_points(point** p0, point** p1);
int* interpolate(int x1, int y1, int x2, int y2);
float* interpolatef(float x1, float y1, float x2, float y2);
void draw_line(PPM* img, point p0, point p1, ppmcolor color);
void draw_triangle_wireframe(PPM* img, point p0, point p1, point p2, ppmcolor color);
void draw_triangle_fill(PPM* img, point p0, point p1, point p2, ppmcolor color);