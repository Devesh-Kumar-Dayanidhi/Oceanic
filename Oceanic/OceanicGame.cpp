#include "OceanicGame.h"

#include <iostream>
#include <time.h>
#include <SDL3/SDL.h>

#include "core/Application.h"

void OceanicGame::Start()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0)
	{
		SDL_Log("SDL_Init error: %s", SDL_GetError());
		exit(1);
	}

	window = SDL_CreateWindow(m_WindowTitle.c_str(), m_ViewportWidth, m_ViewportHeight, 0);
	if (!window)
	{
		SDL_Log("SDL_CreateWindow error: %s", SDL_GetError());
		exit(2);
	}

	renderer = SDL_CreateRenderer(window, NULL);
	if (!window)
	{
		SDL_Log("SDL_CreateRenderer error: %s", SDL_GetError());
		exit(3);
	}
}

bool OceanicGame::Flags()
{
	return m_Quit;
}

void OceanicGame::OnUpdate(clock_t dt)
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_EVENT_QUIT:
			m_Quit = true;
			break;
		case SDL_EVENT_KEY_DOWN:
			switch (event.key.key)
			{
			case SDLK_Q:
				R += 5;
				break;
			case SDLK_A:
				R -= 5;
				break;
			case SDLK_W:
				G += 5;
				break;
			case SDLK_S:
				G -= 5;
				break;
			case SDLK_E:
				B += 5;
				break;
			case SDLK_D:
				B -= 5;
				break;
			case SDLK_ESCAPE:
				m_Quit = true;
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
	}

	R = SDL_clamp(R, 0, 255);
	G = SDL_clamp(G, 0, 255);
	B = SDL_clamp(B, 0, 255);
	SDL_SetRenderDrawColor(renderer, R, G, B, 0xff);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
	SDL_Delay(10);
}

void OceanicGame::End()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	exit(0);
}

Application* FetchApplication()
{
	return new OceanicGame("Oceanic", 600, 480);
}