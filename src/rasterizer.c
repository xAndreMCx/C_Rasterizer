#include "rasterizer.h"

#include <math.h>
#include <stdlib.h>
#include <string.h>

int convert_x(int x) {
  return x + (CANVAS_WIDTH / 2);
}

int convert_y(int y) {
  return y + (CANVAS_HEIGHT / 2);
}

void swap_points(point** p0, point** p1) {
  point* temp = *p0;
  *p0 = *p1;
  *p1 = temp;
}

int* interpolate(int x1, int y1, int x2, int y2) {
  // Determine the number of interpolated points based on the difference between x values
  int numPoints = abs(x2 - x1) + 1;

  int* values = malloc(numPoints * sizeof(int));

  float slope = (float)(y2 - y1) / (x2 - x1);
  for (int i = 0; i < numPoints; i++) {
    values[i] = y1 + ceilf(i * slope);
  }

  return values;
}

float* interpolatef(float x1, float y1, float x2, float y2) {
    // Determine the number of interpolated points based on the difference between x values
    int numPoints = (int)(fabs(x2 - x1)) + 1;

    float* values = malloc(numPoints * sizeof(float));

    float slope = (y2 - y1) / (x2 - x1);

    for (int i = 0; i < numPoints; i++) {
        values[i] = y1 + (i * slope);
    }

    return values;
}


// Bresenham's line drawing algorithm
void draw_line(PPM* img, point p0, point p1, ppmcolor color) {
  int dx = abs(p1.x - p0.x);
  int dy = abs(p1.y - p0.y);
  int sx = (p0.x < p1.x) ? 1 : -1;
  int sy = (p0.y < p1.y) ? 1 : -1;
  int err = dx - dy;

  while (1) {
    easyppm_set(img, convert_x(p0.x), convert_y(p0.y), color);

    if (p0.x == p1.x && p0.y == p1.y) {
      break;
    }

    int e2 = 2 * err;

    if (e2 > -dy) {
      err -= dy;
      p0.x += sx;
    }

    if (e2 < dx) {
      err += dx;
      p0.y += sy;
    }
  }
}

void draw_triangle_wireframe(PPM* img, point p0, point p1, point p2, ppmcolor color) {
  draw_line(img, p0, p1, color);
  draw_line(img, p1, p2, color);
  draw_line(img, p2, p0, color);
}

void draw_triangle_fill(PPM* img, point p0, point p1, point p2, ppmcolor color) {
  // make sure p2 is the highest point and p0 is the lowest point
  // y0 <= y1 <= y2
  if (p0.y > p1.y) {
    swap_points(&p0, &p1);
  }
  if (p0.y > p2.y) {
    swap_points(&p0, &p2);
  }
  if (p1.y > p2.y) {
    swap_points(&p1, &p2);
  }

  // the total sizes of each array
  int size_0_1 = abs(p0.y - p1.y) + 1;
  int size_1_2 = abs(p1.y - p2.y) + 1;
  int size_0_2 = abs(p0.y - p2.y) + 1;

  // shorter side
  int* x_0_1 = interpolate(p0.y, p0.x, p1.y, p1.x);
  float* h_0_1 = interpolatef(p0.y, p0.h, p1.y, p1.h); 
  // shorter side
  int* x_1_2 = interpolate(p1.y, p1.x, p2.y, p2.x);
  float* h_1_2 = interpolatef(p1.y, p1.h, p2.y, p2.h);
  // concat side
  int* x_0_1_2 = (int*)malloc( sizeof(int) * size_0_2);
  memcpy(x_0_1_2, x_0_1, sizeof(int) * (size_0_1 - 1));
  memcpy(x_0_1_2 + (size_0_1 - 1), x_1_2, sizeof(int) * size_1_2);

  float* h_0_1_2 = (float*)malloc( sizeof(float) * size_0_2);
  memcpy(h_0_1_2, h_0_1, sizeof(float) * (size_0_1 - 1));
  memcpy(h_0_1_2 + (size_0_1 -1), h_1_2, sizeof(float) * size_1_2);
  
  free(x_0_1);
  free(x_1_2);

  free(h_0_1);
  free(h_1_2);

  // longer side
  int* x_0_2 = interpolate(p0.y, p0.x, p2.y, p2.x);
  float* h_0_2 = interpolatef(p0.y, p0.h, p2.y, p2.h);

  int* x_left;
  float* h_left;
  int* x_right;
  float* h_right;
  int mid = size_0_2 / 2;
  if (x_0_2[mid] < x_0_1_2[mid]) {
    x_left = x_0_2;
    h_left = h_0_2;

    x_right = x_0_1_2;
    h_right = h_0_1_2;
  }
  else {  
    x_left = x_0_1_2;
    h_left = h_0_1_2;

    x_right = x_0_2;
    h_right = h_0_2;
  }

  for (int y = p0.y; y <= p2.y; y++) {
    float* h_values = interpolatef(x_left[y - p0.y], h_left[y - p0.y], x_right[y - p0.y], h_right[y - p0.y]);
    for (int x = x_left[y - p0.y]; x < x_right[y-p0.y]; x++) {
      float h_value = h_values[x - x_left[y - p0.y]];
      ppmcolor shaded_color = easyppm_rgb(color.r * h_value, color.g * h_value, color.b * h_value);
      easyppm_set(img, convert_x(x), convert_y(y), shaded_color);
    }
    free(h_values);
  }

  free(x_left);
  free(x_right);  

  free(h_left);
  free(h_right);
}

point viewport_to_canvas(point p) {
  point result;
  result.x = ceilf((float)p.x * CANVAS_WIDTH / VIEWPORT_WIDTH); // + CANVAS_WIDTH / 2;
  result.y = ceilf((float)p.y * CANVAS_HEIGHT / VIEWPORT_HEIGHT); // + CANVAS_HEIGHT / 2;
  result.h = 1;
  return result;
}

point project_vertex(vertex v) {
  point result;
  result.x = ceilf((float)(v.x * VIEWPORT_DISTANCE) / v.z);
  result.y = ceilf((float)v.y * VIEWPORT_DISTANCE / v.z);
  result.h = 1;
  return viewport_to_canvas(result);
}