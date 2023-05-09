#include <stdio.h>
#include <stdlib.h>

#include "easyppm.h"
#include "rasterizer.h"


int main(void) {
  PPM ppm = easyppm_create(256, 256, IMAGETYPE_PPM);
  easyppm_clear(&ppm, easyppm_rgb(64, 64, 64));
  point p0 = {5, 5};
  point p1 = {125, 250};
  point p2 = {242, 100};
  // draw_line(&ppm, p0, p1, easyppm_rgb(128, 16, 128));
  draw_triangle(&ppm, p0, p1, p2, easyppm_rgb(128, 16, 128));
  easyppm_write(&ppm, "image.ppm");
  puts("Finished drawing image.");
  return 0;
}
