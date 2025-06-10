#pragma once

#include <iostream>
#include <string>
#include <time.h>
#include <SDL3/SDL.h>
#include <glm/glm.hpp>

#include "core/Application.h"

class OceanicGame : public Application
{
public:
	OceanicGame() :
		m_ViewportWidth(0), m_ViewportHeight(0), m_ImageData(nullptr), m_WindowTitle(""), m_Quit(false), window(nullptr), renderer(nullptr), texture(nullptr), m_Time(0) {}
	OceanicGame(const std::string& title, uint32_t width, uint32_t height) :
		m_ViewportWidth(width), m_ViewportHeight(height), m_WindowTitle(title), m_Quit(false), window(nullptr), renderer(nullptr), texture(nullptr), m_Time(0)
	{
		m_ImageData = new uint32_t[width * height];
	}
public:
	void Start() override;
	bool Flags() override;
	void OnUpdate(clock_t dt) override;
	void End() override;
private:
	uint32_t m_ViewportWidth, m_ViewportHeight;
	uint32_t* m_ImageData;
	std::string m_WindowTitle;
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Texture* texture;
	bool m_Quit;
	clock_t m_Time;
	glm::vec2 cameraPosition = glm::vec2(3, 3);
	glm::vec2 cameraDirection = glm::normalize(glm::vec2(1, 0));
	glm::vec2 velocity = glm::vec2(0.0f);
	glm::vec2 acceleration = glm::vec2(0.0f);
};