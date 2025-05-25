#include <time.h>
#include <SDL3/SDL.h>

#include "Application.h"

extern Application* FetchApplication();

int main(int argc, const char** argv)
{
	Application* application = FetchApplication();
	clock_t start = 0, end = 0;

	application->Start();
	while (!application->Flags())
	{
		start = clock();
		application->OnUpdate(end - start);
		end = clock();
	}

	application->End();
}