#include <bx/bx.h>
#include <bgfx/bgfx.h>

#if BX_PLATFORM_EMSCRIPTEN
#	include <emscripten.h>
#endif 

#include <SDL2/SDL.h>

int main()
{
	SDL_Init(SDL_INIT_VIDEO);

	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_CreateWindowAndRenderer(600, 400, 0, &window, &renderer);
	int result = 0;
	SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);  SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
	return 0;
}