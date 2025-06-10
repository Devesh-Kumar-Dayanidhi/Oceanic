#include "OceanicGame.h"

#include <iostream>
#include <time.h>
#include <SDL3/SDL.h>
#include <glm/glm.hpp>

#include "core/Application.h"
#include "core/Utils.h"

#define RED_WALL 1
#define GREEN_WALL 2
#define BLUE_WALL 3

static void VerticalLine(float xStartF, float yStartF, float yEndF, float lineWidthF, const glm::vec4& color, uint32_t* data, uint32_t vw, uint32_t vh)
{
	int xStart = std::max(0, static_cast<int>(xStartF));
	int xEnd = std::min(static_cast<int>(xStartF + lineWidthF), static_cast<int>(vw));

	int yStart = std::max(0, static_cast<int>(yStartF));
	int yEnd = std::min(static_cast<int>(yEndF), static_cast<int>(vh));

	uint32_t rgba = Utils::Vec4ToRGBA(color);

	for (int x = xStart; x < xEnd; ++x)
	{
		for (int y = yStart; y < yEnd; ++y)
		{
			uint32_t index = x + y * vw;
			data[index] = rgba;
		}
	}
}

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

	if (!SDL_SetWindowFullscreen(window, true))
	{
		SDL_Log("SDL_SetWindowFullscreen error: %s", SDL_GetError());
		exit(3);
	}

	if (!SDL_HideCursor())
	{
		SDL_Log("SDL_HideCursor error: %s", SDL_GetError());
		exit(4);
	}

	renderer = SDL_CreateRenderer(window, NULL);
	if (!renderer)
	{
		SDL_Log("SDL_CreateRenderer error: %s", SDL_GetError());
		exit(5);
	}

	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, m_ViewportWidth, m_ViewportHeight);
	if (!texture)
	{
		SDL_Log("SDL_CreateTexture error: %s", SDL_GetError());
		exit(6);
	}
}

bool OceanicGame::Flags()
{
	return m_Quit;
}

void OceanicGame::OnUpdate(clock_t dt)
{
	float moveSpeed = 0.2f;
	float rotationSpeed = 2.0f;

	uint32_t map[8][8] = {
		{1, 2, 3, 1, 2, 3, 1, 2},
		{2, 0, 0, 0, 0, 0, 0, 3},
		{3, 0, 1, 1, 3, 3, 0, 2},
		{1, 0, 0, 0, 0, 0, 0, 1},
		{2, 0, 0, 0, 2, 0, 0, 3},
		{3, 0, 0, 0, 0, 0, 0, 2},
		{1, 0, 0, 0, 0, 0, 0, 1},
		{2, 3, 1, 2, 3, 1, 2, 3},
	};
	int mapWidth = 8, mapHeight = 8;

	cameraDirection = glm::normalize(cameraDirection);

	for (int i = 0; i < m_ViewportWidth * m_ViewportHeight; i++)
	{
		glm::vec4 v = glm::vec4(0.4f);
		uint32_t color = Utils::Vec4ToRGBA(v);
		m_ImageData[i] = color;
	}

	float fov = 90.0f;
	float angleStep = fov / static_cast<float>(m_ViewportWidth);
	float cameraAngle = atan2(cameraDirection.y, cameraDirection.x);

	for (int x = 0; x < m_ViewportWidth; ++x)
	{
		float angle = cameraAngle + Utils_DegToRad((x - m_ViewportWidth / 2.0f) * angleStep);

		glm::vec2 rayDirection = glm::vec2(cosf(angle), sinf(angle));
		glm::vec2 rayOrigin = cameraPosition;

		float t = 0.0f;
		const float maxT = 100.0f;
		const float step = 0.1f;

		glm::vec4 finalColor = glm::vec4(0.4f);

		while (t < maxT)
		{
			glm::vec2 point = rayOrigin + rayDirection * t;

			uint32_t mapX = static_cast<uint32_t>(point.x);
			uint32_t mapY = static_cast<uint32_t>(point.y);
			if (mapX >= mapWidth || mapY >= mapHeight)
				break;

			if (map[mapY][mapX] > 0)
			{
				switch (map[mapY][mapX])
				{
				case BLUE_WALL:
					finalColor = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
					break;
				case GREEN_WALL:
					finalColor = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
					break;
				case RED_WALL:
					finalColor = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
					break;
				default:
					finalColor = glm::vec4(0.4f);
					break;
				}
				
				break;
			}

			t += step;
		}

		float correctedDistance = t * cos(angle - cameraAngle);
		float tileHeight = 2.0f;
		float wallHeight = (correctedDistance > 0.001f) ? (m_ViewportHeight * tileHeight) / correctedDistance : m_ViewportHeight;

		if (wallHeight >= m_ViewportHeight)
			wallHeight = m_ViewportHeight - 1;

		float yStart = (m_ViewportHeight - wallHeight) / 2.0f;
		float yEnd = yStart + wallHeight;

		VerticalLine(x, yStart, yEnd, 1.0f, finalColor, m_ImageData, m_ViewportWidth, m_ViewportHeight);
	}


	void* texturePixels;
	int pitch;
	SDL_LockTexture(texture, nullptr, &texturePixels, &pitch);
	memcpy(texturePixels, m_ImageData, sizeof(uint32_t) * m_ViewportWidth * m_ViewportHeight);
	SDL_UnlockTexture(texture);

	SDL_RenderClear(renderer);
	SDL_RenderTexture(renderer, texture, nullptr, nullptr);
	SDL_RenderPresent(renderer);

	SDL_Event event;
	float deltaTime = 0.17f;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_EVENT_QUIT:
			m_Quit = true;
			break;

		case SDL_EVENT_KEY_DOWN:
			if (event.key.key == SDLK_ESCAPE)
				m_Quit = true;
			break;

		default:
			break;
		}
	}

	glm::vec2 acceleration(0.0f);

	glm::vec2 forward = glm::normalize(cameraDirection);
	glm::vec2 right(-forward.y, forward.x);

	const Uint8* keystate = (const Uint8*)SDL_GetKeyboardState(NULL);
	if (keystate[SDL_SCANCODE_W]) acceleration += forward * moveSpeed;
	if (keystate[SDL_SCANCODE_S]) acceleration -= forward * moveSpeed;
	if (keystate[SDL_SCANCODE_D]) acceleration += right * moveSpeed;
	if (keystate[SDL_SCANCODE_A]) acceleration -= right * moveSpeed;
	if (keystate[SDL_SCANCODE_RIGHT])
	{
		float angle = Utils_DegToRad(rotationSpeed);
		float cs = cos(angle), sn = sin(angle);
		cameraDirection = glm::normalize(glm::vec2(
			cameraDirection.x * cs - cameraDirection.y * sn,
			cameraDirection.x * sn + cameraDirection.y * cs
		));
	}
	if (keystate[SDL_SCANCODE_LEFT])
	{
		float angle = Utils_DegToRad(-rotationSpeed);
		float cs = cos(angle), sn = sin(angle);
		cameraDirection = glm::normalize(glm::vec2(
			cameraDirection.x * cs - cameraDirection.y * sn,
			cameraDirection.x * sn + cameraDirection.y * cs
		));
	}

	glm::vec2 oldCameraPosition = cameraPosition;

	const float maxSpeed = 3.0f;

	velocity += acceleration * deltaTime;
	velocity *= 0.95f;
	if (glm::length(velocity) > maxSpeed)
		velocity = glm::normalize(velocity) * maxSpeed;

	cameraPosition += velocity * deltaTime;

	uint32_t mapX = static_cast<uint32_t>(cameraPosition.x);
	uint32_t mapY = static_cast<uint32_t>(cameraPosition.y);
	if (mapY < mapHeight && mapX < mapWidth && map[mapY][mapX] > 0)
	{
		cameraPosition = oldCameraPosition;
		velocity = glm::vec2(0.0f);
	}

	SDL_Delay(17);
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