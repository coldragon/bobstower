#include "hdr/init.h"

int main(int argc, char* args[])
{
	leCore CORE = { 0 };

	open_sdl_shit();

	coreInit(&CORE);
	mainLoop(&CORE);
	coreFree(&CORE);

	close_sdl_shit();

	return 0;
}
