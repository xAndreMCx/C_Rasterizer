#include <stdio.h>

#include "easyppm.h"

void draw_line(PPM* img, int x1, int y1, int x2, int y2, ppmcolor color);

int main(void) {
  PPM ppm = easyppm_create(256, 256, IMAGETYPE_PPM);
  easyppm_clear(&ppm, easyppm_rgb(64, 64, 64));
  draw_line(&ppm, 10, 10, 100, 50, easyppm_rgb(128, 16, 128));
  easyppm_write(&ppm, "image.ppm");
  puts("Hello World!");
  return 0;
}

void draw_line(PPM* img, int x1, int y1, int x2, int y2, ppmcolor color) {
  float a = (y2 - y1) / (x2 - x1);
  int b = (int)(y1 - (a * x1));

  for (int i = x1; i <= x2; i++) {
    int y = (int)((a * i) + b);
    easyppm_set(img, i, y, color);
  }
}