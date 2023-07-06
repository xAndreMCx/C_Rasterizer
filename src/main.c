#include <stdio.h>
#include <stdlib.h>

#include "easyppm.h"
#include "rasterizer.h"

#define WIDTH 512
#define HEIGHT 512

int main(void) {
  PPM ppm = easyppm_create(WIDTH, HEIGHT, IMAGETYPE_PPM);
  easyppm_clear(&ppm, easyppm_rgb(64, 64, 64));

  // Define the points for drawing lines
  point p1 = {276, 6, 0};
  point p2 = {456, 206, 0.5};
  point p3 = {56, 506, 1};

  // ppmcolor cl_purple = easyppm_rgb(150, 111, 214); 
  // ppmcolor cl_green = easyppm_rgb(120, 220, 120);
  ppmcolor cl_blue = easyppm_rgb(167, 199, 231); 
  ppmcolor cl_yellow = easyppm_rgb(255, 250, 160);

  draw_triangle_fill(&ppm, p1, p2, p3, cl_blue);
  draw_triangle_wireframe(&ppm, p1, p2, p3, cl_yellow);

  easyppm_write(&ppm, "./image.ppm");
  puts("Finished drawing image.");
  return 0;
}

