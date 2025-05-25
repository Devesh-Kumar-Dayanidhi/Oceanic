#pragma once

#include <iostream>
#include <string>
#include <time.h>
#include <SDL3/SDL.h>

#include "core/Application.h"

class OceanicGame : public Application
{
public:
	OceanicGame() :
		m_ViewportWidth(0), m_ViewportHeight(0), m_Quit(false), window(nullptr), renderer(nullptr) {}
	OceanicGame(const std::string& title, uint32_t width, uint32_t height) :
		m_WindowTitle(title), m_ViewportWidth(width), m_ViewportHeight(height), m_Quit(false), window(nullptr), renderer(nullptr) {}
public:
	void Start() override;
	bool Flags() override;
	void OnUpdate(clock_t dt) override;
	void End() override;
private:
	uint32_t m_ViewportWidth, m_ViewportHeight;
	std::string m_WindowTitle;
	bool m_Quit;
	SDL_Window* window;
	SDL_Renderer* renderer;
};