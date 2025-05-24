#pragma once

#include <iostream>
#include <time.h>

#include "core/Application.h"

class OceanicGame : public Application
{
public:
	void Start() override
	{
		std::cout << "Start.\n";
	}

	bool Flags() override
	{
		return false;
	}

	void OnUpdate(clock_t dt) override
	{
		std::cout << "Update.\n";
		count++;
	}

	void End() override
	{
		std::cout << "End.\n";
	}
private:
	int count = 0;
};