#pragma once
#include<stdbool.h>
#include<SDL2/SDL.h>
#include<stdint.h>
#include<stdio.h>

// window size macros
#define WINDX 1792
#define WINDY 1008
#define WINDXMID (WINDX / 2)
#define WINDYMID (WINDY / 2)

typedef unsigned int uint;
typedef uint8_t u8;

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Event event;

bool run = true;

void events()
{
	while(SDL_PollEvent(&event)){
		if (event.type == SDL_QUIT){
			run = false;
			printf("Quitting now!\n");
		}
	}
}

void delay(uint ms)
{
	SDL_Delay(ms);
}

void setColor(u8 r, u8 g, u8 b)
{
	SDL_SetRenderDrawColor(renderer, r, g, b, 255);
}

void drawPixel(uint x, uint y)
{
	SDL_RenderDrawPoint(renderer, x, y);
}

void drawLine(uint x1, uint y1, uint x2, uint y2)
{
	SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}

void drawRect(uint x, uint y, uint xlen, uint ylen)
{
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.w = xlen;
	rect.h = ylen;
	SDL_RenderDrawRect(renderer, &rect);
}

void fillRect(uint x, uint y, uint xlen, uint ylen)
{
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.w = xlen;
	rect.h = ylen;
	SDL_RenderFillRect(renderer, &rect);
}

void drawFrame()
{
	SDL_RenderPresent(renderer);
}

void init()
{
	if(SDL_Init(SDL_INIT_VIDEO)<0){
		printf("SDL borked! Error: %s\n", SDL_GetError());
		// Destroy renderer
		SDL_DestroyRenderer(renderer);
		// Destroy window
		SDL_DestroyWindow( window );
		// Quit SDL subsystems
		SDL_Quit();
	}
	else{
		//Create window
		SDL_CreateWindowAndRenderer(WINDX, WINDY, 0,
			&window, &renderer);
		setColor(0, 0, 0);
		drawRect(0, 0, WINDX, WINDY);
		drawFrame();
	}
}

void quit()
{
	// Destroy renderer
	SDL_DestroyRenderer(renderer);
	// Destroy window
	SDL_DestroyWindow(window);
	// Quit SDL subsystems
	SDL_Quit();
}
