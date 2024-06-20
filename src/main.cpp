
#include <ctime>
#include "Game.h"

#ifdef __EMSCRIPTEN__
#include <emscripten/html5.h>
#endif

// #pragma comment (lib,"opengl32.lib")
// #pragma comment (lib,"Glu32.lib")

void StartHeapControl();

int SDL_main(int argv, char** args)
{
	srand(static_cast<unsigned int>(time(nullptr)));
	
	StartHeapControl();

	Game game{ Game{ Window{ "Spelunky - van den Barselaar, Arthur - 1DAE16", 1280.f , 720.f, false } } };
	game.Run();

	#ifdef __EMSCRIPTEN__
		emscripten_set_main_loop_arg(
			[](void *userData) {
				Game& app = *reinterpret_cast<Game*>(userData);
				app.MainLoop();
			},
			(void*)&game,
			0, true
		);
	#else
		while (game.IsRunning()) { game.MainLoop(); }
	#endif

	return 0;
}

int main(){
	return SDL_main(0, nullptr);
}


void StartHeapControl()
{
#if defined(DEBUG)
	// Notify user if heap is corrupt
	HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0);

	// Report detected leaks when the program exits
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// Set a breakpoint on the specified object allocation order number
	// _CrtSetBreakAlloc( 156 );
#endif
}

