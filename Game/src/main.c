#include "hdr/init.h"

const SDL_Color WHITE = { 255,255,255 };

int main(int argc, char* args[])
{
	leCore CORE = { 0 };

	open_sdl_shit();
	coreInit(&CORE);

	main_loop(&CORE);

	close_sdl_shit();

	return 0;
}
