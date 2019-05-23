#include "Drawing.h"

SDL_Window* window;
SDL_Renderer* renderer;

void
InitDrawSystem()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}
	else
	{
		window = SDL_CreateWindow("odynm", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		}
		else
		{
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
			if (renderer == NULL)
			{
				printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
			}
			else
			{
				SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderPresent(renderer);
			}
		}
	}
}

void
StopAndWait()
{
	SDL_Event event;
	bool quit = false;

	while (!quit)
	{
		while (SDL_PollEvent(&event) != 0)
		{
			if (event.type == SDL_QUIT)
			{
				quit = true;
			}
		}
	}
}

//Not exactly a point, not exactly efficient. "Good enough".
void
DrawPoint(int x, int y, Colors color)
{
	SDL_Color sdlColor = GetColor(color);

	SDL_SetRenderDrawColor(renderer, sdlColor.r, sdlColor.g, sdlColor.b, sdlColor.a);

	SDL_RenderDrawPoint(renderer, x, y);
	SDL_RenderDrawPoint(renderer, x - 1, y);
	SDL_RenderDrawPoint(renderer, x, y - 1);
	SDL_RenderDrawPoint(renderer, x + 1, y);
	SDL_RenderDrawPoint(renderer, x, y + 1);

	SDL_RenderPresent(renderer);
}

void 
DrawLine(int x1, int y1, int x2, int y2, Colors color)
{
	SDL_Color sdlColor = GetColor(color);

	SDL_SetRenderDrawColor(renderer, sdlColor.r, sdlColor.g, sdlColor.b, sdlColor.a);

	SDL_RenderDrawLine(renderer, x1, y1, x2, y2);

	SDL_RenderPresent(renderer);
}

static SDL_Color GetColor(Colors color)
{
	SDL_Color result = {};
	result.a = 0xFF;

	switch (color)
	{
	case BLUE:
		result.b = 0xFF;
		break;
	case RED:
		result.r = 0xFF;
		break;
	case GREEN:
		result.g = 0xFF;
		break;
	case WHITE:
		result.r = 0xFF;
		result.g = 0xFF;
		result.b = 0xFF;
		break;
	}

	return result;
}
