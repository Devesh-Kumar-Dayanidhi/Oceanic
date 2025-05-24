#include <time.h>

#include "Application.h"

extern Application* FetchApplication();

int main()
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