#include <stdio.h>

#include "easyppm.h"

int main(void) {
  PPM ppm = easyppm_create(256, 256, IMAGETYPE_PPM);
  easyppm_clear(&ppm, easyppm_rgb(255, 0, 0));
  easyppm_write(&ppm, "image.ppm");
  puts("Hello World!");
  return 0;
}