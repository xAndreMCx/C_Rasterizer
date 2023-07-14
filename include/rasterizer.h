#pragma once

#include "easyppm.h"

#define CANVAS_WIDTH 512
#define CANVAS_HEIGHT 512
#define VIEWPORT_WIDTH 20
#define VIEWPORT_HEIGHT 20
#define VIEWPORT_DISTANCE 2

typedef struct {
  int x;
  int y;
  float h;
} point;

typedef struct {
  int x;
  int y;
  int z;
} vertex;

int convert_x(int x);
int convert_y(int y);
void swap_points(point** p0, point** p1);
int* interpolate(int x1, int y1, int x2, int y2);
float* interpolatef(float x1, float y1, float x2, float y2);
void draw_line(PPM* img, point p0, point p1, ppmcolor color);
void draw_triangle_wireframe(PPM* img, point p0, point p1, point p2, ppmcolor color);
void draw_triangle_fill(PPM* img, point p0, point p1, point p2, ppmcolor color);
point viewport_to_canvas(point p);
point project_vertex(vertex v);