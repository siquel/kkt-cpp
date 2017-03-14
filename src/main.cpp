#include <bx/platform.h>
#include <bx/bx.h>
#include <bgfx/platform.h>
#include <bgfx/bgfx.h>

#if BX_PLATFORM_EMSCRIPTEN
#	include <emscripten.h>
#endif 

#include <SDL2/SDL.h>
BX_PRAGMA_DIAGNOSTIC_PUSH()
BX_PRAGMA_DIAGNOSTIC_IGNORED_CLANG("-Wextern-c-compat")
#include <SDL2/SDL_syswm.h>
BX_PRAGMA_DIAGNOSTIC_POP()

inline bool sdlSetWindow(SDL_Window* _window)
{
	SDL_SysWMinfo wmi;
	SDL_VERSION(&wmi.version);
	if (!SDL_GetWindowWMInfo(_window, &wmi) )
	{
		return false;
	}

	bgfx::PlatformData pd;
#if BX_PLATFORM_LINUX
	pd.ndt          = wmi.info.x11.display;
	pd.nwh          = (void*)(uintptr_t)wmi.info.x11.window;
#elif BX_PLATFORM_WINDOWS
	pd.ndt          = NULL;
	pd.nwh          = wmi.info.win.window;
#endif
	pd.context      = NULL;
	pd.backBuffer   = NULL;
	pd.backBufferDS = NULL;
	bgfx::setPlatformData(pd);

	return true;
}

void render()
{
    bgfx::touch(0);
	bgfx::dbgTextClear();
    bgfx::frame();
#if BX_PLATFORM_EMSCRIPTEN
    emscripten_cancel_main_loop();
#endif
}

int main()
{
	SDL_Init(SDL_INIT_EVENTS);

	SDL_Window* window = NULL;
	int width = 640;
	int height = 480;
    window = SDL_CreateWindow("asmjs", 
    				SDL_WINDOWPOS_UNDEFINED,
    				SDL_WINDOWPOS_UNDEFINED,
    				width,
    				height,
    				SDL_WINDOW_SHOWN);

    sdlSetWindow(window);

#if !BX_PLATFORM_EMSCRIPTEN
    bgfx::renderFrame();
#endif

    bgfx::init();
    bgfx::reset(width, height, BGFX_RESET_NONE);

    bgfx::setDebug(BGFX_DEBUG_TEXT);

    bgfx::setViewClear(0,
    	BGFX_CLEAR_COLOR|BGFX_CLEAR_DEPTH,
    	0x303030ff,
    	1.f,
    	0
    );
	bgfx::setViewRect(0, 0, 0, uint16_t(width), uint16_t(height));

#if BX_PLATFORM_EMSCRIPTEN
    emscripten_set_main_loop(render, -1, 1);
#else
    render();
#endif
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}