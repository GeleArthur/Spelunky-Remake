
#include <ctime>
#include "Game.h"

void StartHeapControl();
void DumpMemoryLeaks();

#pragma comment (lib,"opengl32.lib")
#pragma comment (lib,"Glu32.lib")

int SDL_main(int argv, char** args)
{
	srand(static_cast<unsigned int>(time(nullptr)));
	
	StartHeapControl();

	Game* pGame{ new Game{ Window{ "Spelunky - van den Barselaar, Arthur - 1DAE16", 1280.f , 720.f, false } } };
	pGame->Run();
	delete pGame;

	return 0;
}


void StartHeapControl()
{
#if defined(DEBUG) | defined(_DEBUG)
	// Notify user if heap is corrupt
	HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0);

	// Report detected leaks when the program exits
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// Set a breakpoint on the specified object allocation order number
	// _CrtSetBreakAlloc( 156 );
#endif
}

// !!!!!!!! DONT THIS IS BAD AND REPORTS FALSE POSITIVES
// void DumpMemoryLeaks()
// {
// 	
// #if defined(DEBUG) | defined(_DEBUG)
// 	_CrtDumpMemoryLeaks();
// #endif
// }
