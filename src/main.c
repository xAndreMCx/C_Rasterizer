#include <stdio.h>
#include <stdlib.h>

#include "easyppm.h"
#include "rasterizer.h"

int main(void) {

  // ppmcolor cl_purple = easyppm_rgb(150, 111, 214); 
  ppmcolor cl_green = easyppm_rgb(120, 220, 120);
  ppmcolor cl_blue = easyppm_rgb(167, 199, 231); 
  ppmcolor cl_red = easyppm_rgb(255, 57, 46); 
  // ppmcolor cl_yellow = easyppm_rgb(255, 250, 160);
  ppmcolor cl_pure_green = easyppm_rgb(0, 255, 0);
  ppmcolor cl_black = easyppm_black_white(1);
  ppmcolor cl_white = easyppm_black_white(0);


  PPM ppm = easyppm_create(CANVAS_WIDTH, CANVAS_HEIGHT, IMAGETYPE_PPM);
  easyppm_clear(&ppm, easyppm_rgb(64, 64, 64));

  point p1 = {20, -250, 1};
  point p2 = {200, -50, 0};
  point p3 = {-200, 250, 0.5};

  draw_triangle_fill(&ppm, p1, p2, p3, cl_pure_green);
  draw_triangle_wireframe(&ppm, p1, p2, p3, cl_black);

  easyppm_write(&ppm, "./image.ppm");
  puts("Finished drawing image.");

  // -------------------------------------------------------------- //

  PPM threeD = easyppm_create(CANVAS_WIDTH, CANVAS_HEIGHT, IMAGETYPE_PPM);
  vertex Af = {-3, 1, 1};
  vertex Bf = {-1, 1, 1};
  vertex Cf = {-1, -1, 1};
  vertex Df = {-3, -1, 1};

  vertex Ab = {-3, 1, 2};
  vertex Bb = {-1, 1, 2};
  vertex Cb = {-1, -1, 2};
  vertex Db = {-3, -1, 2};

  draw_line(&threeD, project_vertex(Af), project_vertex(Bf), cl_blue);
  draw_line(&threeD, project_vertex(Bf), project_vertex(Cf), cl_blue);
  draw_line(&threeD, project_vertex(Cf), project_vertex(Df), cl_blue);
  draw_line(&threeD, project_vertex(Df), project_vertex(Af), cl_blue);

  draw_line(&threeD, project_vertex(Ab), project_vertex(Bb), cl_red);
  draw_line(&threeD, project_vertex(Bb), project_vertex(Cb), cl_red);
  draw_line(&threeD, project_vertex(Cb), project_vertex(Db), cl_red);
  draw_line(&threeD, project_vertex(Db), project_vertex(Ab), cl_red);

  draw_line(&threeD, project_vertex(Af), project_vertex(Ab), cl_green);
  draw_line(&threeD, project_vertex(Bf), project_vertex(Bb), cl_green);
  draw_line(&threeD, project_vertex(Cf), project_vertex(Cb), cl_green);
  draw_line(&threeD, project_vertex(Df), project_vertex(Db), cl_green);

  easyppm_write(&threeD, "./3D.ppm");
  printf("Finished drawing 3D image.\n");

  return 0;
}

