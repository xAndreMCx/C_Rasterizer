#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "easyppm.h"

void draw_line(PPM* img, int x1, int y1, int x2, int y2, ppmcolor color);
void swap(int* x, int* y);
int* interpolate(int x0, int y0, int x1, int y1);

int main(void) {
  PPM ppm = easyppm_create(256, 256, IMAGETYPE_PPM);
  easyppm_clear(&ppm, easyppm_rgb(64, 64, 64));
  draw_line(&ppm, 5, 5, 225, 250, easyppm_rgb(128, 16, 128));
  easyppm_write(&ppm, "image.ppm");
  puts("Hello World!");
  return 0;
}

void swap(int* x, int* y) {
  int* temp = x;
  x = y;
  y = temp;
}

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

#define VERSION_4

#ifdef VERSION_1
void draw_line(PPM* img, int x1, int y1, int x2, int y2, ppmcolor color) {
  float a = (y2 - y1) / (x2 - x1);
  int b = (int)(y1 - (a * x1));

  for (int i = x1; i <= x2; i++) {
    int y = (int)((a * i) + b);
    easyppm_set(img, i, y, color);
  }
}
#endif

#ifdef VERSION_2
void draw_line(PPM* img, int x1, int y1, int x2, int y2, ppmcolor color) {
  float dx = x2 - x1;
  float dy = y2 - y1;

  if (fabsf(dx) > fabsf(dy)) {
    // The line is closer to horizontal
    if (y2 > y1) {
      swap(&y2, &y1);
    }

    float a = dy / dx;

    int y = y1;

    for (int x = x1; x <= x2; x++) {
      easyppm_set(img, x, y, color);
      y += floorf(a);
    }
  } else {
    // The line is closer to vertica
    if (y2 < y1) {
      swap(&y2, &y1);
    }

    float a = dy / dx;

    int x = x1;

    for (int y = y1; y <= y2; y++) {
      easyppm_set(img, x, y, color);
      x += floorf(a);
    }
  }
}
#endif

#ifdef VERSION_3
void draw_line(PPM* img, int x1, int y1, int x2, int y2, ppmcolor color) {
  float dx = x2 - x1;
  float dy = y2 - y1;

  if (fabsf(dx) > fabsf(dy)) {
    // The line is closer to horizontal
    if (x1 > x2) {
      swap(&x2, &x1);
      swap(&y2, &y1);
    }
    int* y_values = interpolate(x1, y1, x2, y2);

    for (int x = x1; x <= x2; x++) {
      easyppm_set(img, x, y_values[x - x1], color);
    }

    free(y_values);
  } else {
    // The line is closer to vertical
    if (y1 > y2) {
      swap(&x2, &x1);
      swap(&y2, &y1);
    }
    int* x_values = interpolate(y1, x1, y2, x2);

    for (int y = y1; y <= y2; y++) {
      easyppm_set(img, x_values[y - y1], y, color);
    }

    free(x_values);
  }
}

#endif

#ifdef VERSION_4
// Bresenham's line drawing algorithm
void draw_line(PPM* img, int x1, int y1, int x2, int y2, ppmcolor color) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = x1 < x2 ? 1 : -1;
    int sy = y1 < y2 ? 1 : -1;
    int err = dx - dy;

    int x = x1;
    int y = y1;
    int e2 = err * 2;
    if (dx >= dy) {

        for (int i = 0; i <= dx; i++) {
            set_pixel(img, x, y, color);

            if (e2 > -dy) {
                err -= dy;
                x += sx;
            }

            if (e2 < dx) {
                err += dx;
                y += sy;
            }

            e2 = err * 2;
        }
    } else {

        for (int i = 0; i <= dy; i++) {
            set_pixel(img, x, y, color);

            if (e2 > -dx) {
                err -= dx;
                y += sy;
            }

            if (e2 < dy) {
                err += dy;
                x += sx;
            }

            e2 = err * 2;
        }
    }

    set_pixel(img, x2, y2, color); // Draw the last point
}


#endif