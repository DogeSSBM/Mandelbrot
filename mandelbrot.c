#include<stdbool.h>
#include<complex.h>
#include<stdint.h>
#include<math.h>
#include<SDL2/SDL.h>
#include<stdio.h>
#include"Doge_SDL.h"

const long unsigned int ITER = 2000;

#define REALMIN -2.0f
#define REALMAX 1.0f
#define IMAGMIN -1.0f
#define IMAGMAX 1.0f

#define REALLEN (REALMAX - REALMIN)
#define IMAGLEN (IMAGMAX - IMAGMIN)

// step = axis len / window len
#define REALSTEP (REALLEN / WINDX)
#define IMAGSTEP (IMAGLEN / WINDY)

// returns the number of iterations completed while c remained bounded
// uses absolute distance from origin for bailout. (better accuracy, slower)
long unsigned int iterate(float complex c)
{
  float dist = 0.0f;
  float complex z = 0.0f;
  for(long unsigned int x=0; x<ITER; x++){
    z = z * z + c;
    dist = pow(crealf(z), 2.0f) + pow(cimagf(z), 2.0f);
    if(dist > 4.0f){
      return x;
    }
  }
  return ITER;
}

void idle()
{
  while(run){
    delay(5);
    events();
  }
}

int main()
{
  init();

  for(uint y=0; y<WINDY && run; y++){
    for(uint x=0; x<WINDX && run; x++){
      events();
      float complex n = (REALMIN+(x*REALSTEP))+((IMAGMIN+(y*IMAGSTEP))*I);
      u8 val = ITER - iterate(n);
      setColor(val, val, val);
      drawPixel(x, y);
    }
    printf("Y %d done...\n", y);
  }

  printf("FINISHED!\n");
  drawFrame();
  idle();

  quit();
  return 0;
}
