#include <stdio.h>
#include <stdlib.h>

#include "easyppm.h"
#include "rasterizer.h"


int main(void) {
  PPM ppm = easyppm_create(256, 256, IMAGETYPE_PPM);
  easyppm_clear(&ppm, easyppm_rgb(64, 64, 64));
  draw_line(&ppm, 5, 5, 225, 250, easyppm_rgb(128, 16, 128));
  easyppm_write(&ppm, "image.ppm");
  puts("Finished drawing image.");
  return 0;
}
