#include <iostream>
#include <string>
#include <unistd.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <python3.11/Python.h>

#include "menu_interface.cpp"
#include "outer_teletype_interface.cpp"
#include "inner_teletype_interface.cpp"

class Main
{
public:
	int run = 1;
	const int STANDART_WINDOW_WIDTH = 640;
	const int STANDART_WINDOW_HEIGHT = 480;
	int window_width = STANDART_WINDOW_WIDTH;
	int window_height = STANDART_WINDOW_HEIGHT;

	SDL_Surface* window_surface = NULL;
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	SDL_DisplayMode display_mode;
	SDL_Event event_handler;

	MenuInterface menu_interface();
	OuterTeletypeInterface outer_teletype_interface();
	InnerTeletypeInterface inner_teletype_interface();

	int
	start()
	{
		if (init_systems() == 1)
			return 1;

		if (load_resources() == 1)
		{
			quit();
			return 1;
		}

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

			SDL_RenderClear(renderer);

			SDL_RenderPresent(renderer);
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

		renderer = SDL_CreateRenderer(window, -1, 
									  SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

		if (renderer == NULL)
		{
			std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
			return 1;
		}

		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);

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
		while (SDL_PollEvent(&event_handler) != 0) 
		{
			if (event_handler.type == SDL_QUIT) 
				run = 0;

			if (event_handler.type == SDL_WINDOWEVENT)
			{
				if (event_handler.window.event == SDL_WINDOWEVENT_RESIZED)
				{
					window_width = event_handler.window.data1;
					window_height = event_handler.window.data2;
				}
			}
		}

		return 0;
	}

	int
	quit()
	{
		int success = 0;
		
		if (unload_resources() == 1)
			success = 1;

		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		
		return success;
	}
};

int
main(int argc, char ** args) 
{
	Main main_object;

	if (main_object.start() == 1)
		return 1;

	return 0;
}
