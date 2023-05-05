#include "easyppm.h"

void draw_line(PPM* img, int x1, int y1, int x2, int y2, ppmcolor color);
int* interpolate(int x0, int y0, int x1, int y1);