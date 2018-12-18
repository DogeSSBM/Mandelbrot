#include<stdbool.h>
#include<complex.h>
#include<stdint.h>
#include<math.h>
#include<SDL2/SDL.h>
#include<stdio.h>
#include"Doge_SDL.h"

const long unsigned int ITER = 1000;

#define REALMIN -2.0f
#define REALMAX 1.0f
#define IMAGMIN -1.0f
#define IMAGMAX 1.0f

#define REALLEN (REALMAX - REALMIN)
#define IMAGLEN (IMAGMAX - IMAGMIN)

// step = axis len / window len
#define REALSTEP (REALLEN / WINDX)
#define IMAGSTEP (IMAGLEN / WINDY)

// iterates c for up to 20 times as long as c remains bounded
bool isInSet(float complex c)
{
  float complex z = 0;
  for(long unsigned int x=0; x<ITER; x++){
    z = z * z + c;
    if(crealf(z)>2.0f || cimagf(z)>2.0f){
      return false;
    }
  }
  return true;
}

int main()
{
  init();
  for(uint y=0; y<WINDY && run; y++){
    for(uint x=0; x<WINDX && run; x++){
      events();
      float complex n = (REALMIN+(x*REALSTEP))+((IMAGMIN+(y*IMAGSTEP))*I);
      if(isInSet(n)){
        setColor(255, 255, 255);
      }
      else{
        setColor(0, 0, 0);
      }
      drawPixel(x, y);
    }
    printf("Y %d done...\n", y);
  }
  printf("FINISHED!\n");
  drawFrame();
  while(run){
    delay(5);
    /*for(float imag = IMAGMIN; imag < IMAGMAX; imag += IMAGSTEP){
      for(float real = REALMIN; real < REALMAX; real += REALSTEP){
        float complex num = real + imag * I;


      }
    }*/
    events();
  }
  quit();
  return 0;
}
