#include "rasterizer.h"

#include <math.h>
#include <stdlib.h>

int* interpolate(point p0, point p1) {
  int* values = NULL;
  if (p0.x == p1.x) {
    values = (int*)realloc(values, 1);
    *values = p0.y;
    return values;
  }

  float slope = (float)(p1.y - p0.y) / (p1.x - p0.x);
  float y = p0.x;
  values = (int*)realloc(values, sizeof(int) * (p1.x - p0.x + 1));
  int i = 0;
  for (int x = p0.x; x <= p1.x; x++) {
    values[i] = ceilf(y);
    y += slope;
    i++;
  }
  return values;
}

// Bresenham's line drawing algorithm
void draw_line(PPM* img, point p0, point p1, ppmcolor color) {
  int dx = abs(p1.x - p0.x);
  int dy = abs(p1.y - p0.y);
  int sx = p0.x < p1.x ? 1 : -1;
  int sy = p0.y < p1.y ? 1 : -1;
  int err = dx - dy;

  int e2 = err * 2;
  if (dx >= dy) {
    for (int i = 0; i <= dx; i++) {
      easyppm_set(img, p0.x, p0.y, color);

      if (e2 > -dy) {
        err -= dy;
        p0.x += sx;
      }

      if (e2 < dx) {
        err += dx;
        p0.y += sy;
      }

      e2 = err * 2;
    }
  } else {
    for (int i = 0; i <= dy; i++) {
      easyppm_set(img, p0.x, p0.y, color);

      if (e2 > -dx) {
        err -= dx;
        p0.y += sy;
      }

      if (e2 < dy) {
        err += dy;
        p0.x += sx;
      }

      e2 = err * 2;
    }
  }

  easyppm_set(img, p1.x, p1.y, color); // Draw the last point
}

void draw_triangle(PPM* img, point p0, point p1, point p2, ppmcolor color) {
  draw_line(img, p0, p1, color);
  draw_line(img, p1, p2, color);
  draw_line(img, p2, p0, color);
}