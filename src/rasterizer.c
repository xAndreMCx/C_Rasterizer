#include "rasterizer.h"

#include <math.h>
#include <stdlib.h>

int* interpolate(int x0, int y0, int x1, int y1) {
  int* values = NULL;
  if (x0 == x1) {
    values = (int*)realloc(values, 1);
    *values = y0;
    return values;
  }

  float slope = (float)(y1 - y0) / (x1 - x0);
  float y = y0;
  values = (int*)realloc(values, sizeof(int) * (x1 - x0 + 1));
  int i = 0;
  for (int x = x0; x <= x1; x++) {
    values[i] = ceilf(y);
    y += slope;
    i++;
  }
  return values;
}

// Bresenham's line drawing algorithm
void draw_line(PPM* img, int x1, int y1, int x2, int y2, ppmcolor color) {
  int dx = abs(x2 - x1);
  int dy = abs(y2 - y1);
  int sx = x1 < x2 ? 1 : -1;
  int sy = y1 < y2 ? 1 : -1;
  int err = dx - dy;

  int e2 = err * 2;
  if (dx >= dy) {
    for (int i = 0; i <= dx; i++) {
      easyppm_set(img, x1, y1, color);

      if (e2 > -dy) {
        err -= dy;
        x1 += sx;
      }

      if (e2 < dx) {
        err += dx;
        y1 += sy;
      }

      e2 = err * 2;
    }
  } else {
    for (int i = 0; i <= dy; i++) {
      easyppm_set(img, x1, y1, color);

      if (e2 > -dx) {
        err -= dx;
        y1 += sy;
      }

      if (e2 < dy) {
        err += dy;
        x1 += sx;
      }

      e2 = err * 2;
    }
  }

  easyppm_set(img, x2, y2, color); // Draw the last point
}