#include <iostream>
#include <unistd.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <python3.11/Python.h>

class Main
{
public:
	int run = 1;
	const int STANDART_WINDOW_WIDTH = 640;
	const int STANDART_WINDOW_HEIGHT = 480;
	SDL_DisplayMode display_mode;
	SDL_Event event;
	SDL_Surface* window_surface = NULL;
	SDL_Window* window = NULL;

	int
	start()
	{
		if (init_systems() == 1)
			return 1;

		if (load_resources() == 1)
			return 1;

		if (mainloop() == 1)
		{
			quit();
			return 1;
		}

		if (quit() == 1)
			return 1;

		return 0;
	}

	int
	mainloop()
	{
		while (run) 
		{
			process_events();

			window_surface = SDL_GetWindowSurface(window);

			SDL_FillRect(window_surface, NULL,
					     SDL_MapRGB(window_surface->format, 255, 0, 0));

			SDL_UpdateWindowSurface(window);
			usleep(5 * 1000);
		}

		return 0;
	}

	int
	init_systems() 
	{
		if (SDL_Init(SDL_INIT_EVERYTHING) != 0) 
		{
			std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		    return 1;
		}

		if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
		{
			std::cout << "Can't init image: " << IMG_GetError() << std::endl;
			return 1;
		}

		window = SDL_CreateWindow("SDd",
	    						  SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
	    						  STANDART_WINDOW_WIDTH, STANDART_WINDOW_HEIGHT,
	    						  SDL_WINDOW_SHOWN|SDL_WINDOW_RESIZABLE);
	    
		if (window == NULL) 
		{
			std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
			return 1;
		}

		return 0;
	}

	int
	load_resources()
	{
		return 0;
	}

	int
	unload_resources()
	{
		return 0;
	}

	int
	process_events()
	{
		while (SDL_PollEvent(&event) != 0) 
		{
			if (event.type == SDL_QUIT) 
				run = 0;
		}

		return 0;
	}

	int
	quit()
	{
		if (unload_resources() == 1)
			return 1;
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 0;
	}
};

class OuterTeletypeInterface
{
	
};

class InnerTeletypeInterface
{
	
};

int
main(int argc, char ** args) 
{
	Main main_object;

	if (main_object.start() == 1)
		return 1;

	return 0;
}
