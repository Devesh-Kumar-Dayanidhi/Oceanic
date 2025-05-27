#include "OceanicGame.h"

#include <iostream>
#include <time.h>
#include <SDL3/SDL.h>
#include <glm/glm.hpp>

#include "core/Application.h"
#include "core/Utils.h"

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
	SDL_SetWindowFullscreen(window, true);

	renderer = SDL_CreateRenderer(window, NULL);
	if (!renderer)
	{
		SDL_Log("SDL_CreateRenderer error: %s", SDL_GetError());
		exit(3);
	}

	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, m_ViewportWidth, m_ViewportHeight);
	if (!texture)
	{
		SDL_Log("SDL_CreateTexture error: %s", SDL_GetError());
		exit(4);
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

	for (int i = 0; i < m_ViewportWidth * m_ViewportHeight; i++)
	{
		glm::vec4 v = glm::vec4(1.0f);
		uint32_t color = Utils::Vec4ToRGBA(v);
		m_ImageData[i] = color;
	}
	m_ImageData[0] = Utils::Vec4ToRGBA(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));

	void* texturePixels;
	int pitch;
	SDL_LockTexture(texture, nullptr, &texturePixels, &pitch);
	memcpy(texturePixels, m_ImageData, sizeof(uint32_t) * m_ViewportWidth * m_ViewportHeight);
	SDL_UnlockTexture(texture);

	SDL_RenderClear(renderer);
	SDL_RenderTexture(renderer, texture, nullptr, nullptr);
	SDL_RenderPresent(renderer);

	SDL_Delay(17);
	count += 17;
}

void OceanicGame::End()
{
	delete[] m_ImageData;
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	exit(0);
}

Application* FetchApplication()
{
	return new OceanicGame("Oceanic", 320, 300);
}