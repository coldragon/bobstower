#include <SDL2/SDL.h>
#include <string.h>
#include "hdr/struct.h"
#include "hdr/map.h"
#include "hdr/event.h"

int messageBox(char* title, char* message)
{
	const SDL_MessageBoxButtonData buttons[] =
	{
		{SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT,0,"No" },
		{SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT,1,"Yes"},
	};

	const SDL_MessageBoxColorScheme colorScheme =
	{
		{
			/* [SDL_MESSAGEBOX_COLOR_BACKGROUND] */
			{ 255,   0,   0 },
			/* [SDL_MESSAGEBOX_COLOR_TEXT] */
			{ 0, 255,   0 },
			/* [SDL_MESSAGEBOX_COLOR_BUTTON_BORDER] */
			{ 255, 255,   0 },
			/* [SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND] */
			{ 0,   0, 255 },
			/* [SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED] */
			{ 255,   0, 255 }
		}
	};

	const SDL_MessageBoxData messageboxdata = {
		SDL_MESSAGEBOX_INFORMATION, /* .flags */
		NULL, /* .window */
		title, /* .title */
		message, /* .message */
		SDL_arraysize(buttons), /* .numbuttons */
		buttons, /* .buttons */
		&colorScheme /* .colorScheme */
	};
	int buttonid;
	if (SDL_ShowMessageBox(&messageboxdata, &buttonid) < 0)
	{
		SDL_Log("error displaying message box");
		return 1;
	}
	if (buttonid == -1)
	{
		return -1;
	}
	else
	{
		if (buttons[buttonid].text == "Yes")
			return 1;
		if (buttons[buttonid].text == "No")
			return 0;
		return -1;
	}

}

void inputReturn(leInput *INPUT)
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			INPUT->quit = 1;
			break;
		case SDL_KEYDOWN:
			INPUT->key[event.key.keysym.scancode] = 1;
			break;
		case SDL_KEYUP:
			INPUT->key[event.key.keysym.scancode] = 0;
			break;
		case SDL_MOUSEWHEEL:
			if (event.wheel.y > 0)
				INPUT->wheelup = 1;
			if (event.wheel.y < 0)
				INPUT->wheeldown = 1;
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				INPUT->leftclic = 1;
				INPUT->leftclic_position_x = event.motion.x;
				INPUT->leftclic_position_y = event.motion.y;
			}
			if (event.button.button == SDL_BUTTON_RIGHT)
			{
				INPUT->rightclic = 1;
				INPUT->rightclic_position_x = event.motion.x;
				INPUT->rightclic_position_y = event.motion.y;
			}
			break;
		case SDL_MOUSEBUTTONUP:
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				INPUT->leftclic = 0;
			}
			if (event.button.button == SDL_BUTTON_RIGHT)
			{
				INPUT->rightclic = 0;
			}
			break;
		case SDL_MOUSEMOTION:
			INPUT->mousex = event.motion.x;
			INPUT->mousey = event.motion.y;
			break;
		case SDL_DROPFILE:
			INPUT->filedrop = event.drop.file;
			break;
		case SDL_WINDOWEVENT:
			switch (event.window.event)
			{
			case SDL_WINDOWEVENT_FOCUS_GAINED:
				INPUT->focus = 1;
				break;
			case SDL_WINDOWEVENT_FOCUS_LOST:
				INPUT->focus = 0;
				break;
			default:
				break;
			}
		default:
			break;
		}
		if (event.wheel.y == 0)
		{
			INPUT->wheelup = 0;
			INPUT->wheeldown = 0;
		}
	}
}

void inputInit(leInput *INPUT)
{
	int temp = INPUT->focus;
	memset(INPUT, 0, sizeof(leInput));
	INPUT->focus = temp;
}

void windowInterraction(leInput *INPUT, leState *STATE, SDL_Window *window, leMap *MAP)
{
	// WINDOW MOVE
	if (INPUT->rightclic && !STATE->fullscreen)
	{
		int x_mouse_screen; int y_mouse_screen;
		SDL_GetGlobalMouseState(&x_mouse_screen, &y_mouse_screen);
		SDL_SetWindowPosition(window, x_mouse_screen - INPUT->rightclic_position_x, y_mouse_screen - INPUT->rightclic_position_y);
	}

	// FULLSCREEN
	if (INPUT->leftclic && INPUT->leftclic_position_x > WWIN - 64 && INPUT->leftclic && INPUT->leftclic_position_x < WWIN - 32 && INPUT->leftclic_position_y < 32)
	{
		if (!STATE->fullscreen)
		{
			SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
			STATE->fullscreen = 1;
			inputInit(INPUT);
		}
		else
		{
			SDL_SetWindowFullscreen(window, 0);
			STATE->fullscreen = 0;
			inputInit(INPUT);
		}
	}

	// MINIMISE
	if (INPUT->leftclic && INPUT->leftclic_position_x > WWIN - 96 && INPUT->leftclic_position_x < WWIN - 64 && INPUT->leftclic_position_y < 32)
	{
		SDL_MinimizeWindow(window);
		inputInit(INPUT);
	}

	// QUIT

	if (INPUT->key[SDL_SCANCODE_ESCAPE] || (INPUT->leftclic && INPUT->leftclic_position_x > WWIN - 32 && INPUT->leftclic_position_y < 32))
	{
		if (messageBox("Quit", "Do you want to quit the editor, unsaved work will be lost ?") == 1)
			INPUT->quit = 1;
	}

	// Filedrop

	if (INPUT->filedrop != NULL)
	{
		if (messageBox("Quit", "Do you want to load map you dragged ? Any unsaved work will be lost") == 1)
			map_load(MAP, INPUT->filedrop);
	}
	INPUT->filedrop = NULL;
}

void tileEditInterraction(leInput *INPUT, leState *STATE, leMap *MAP)
{
	if (INPUT->leftclic && INPUT->leftclic_position_y >32)
	{
		int x = 0, y = 0; caseReturn(INPUT, &x, &y);
		if (STATE->actualLayer == 0) // Tile
		{
			MAP->tile[y][x] = STATE->actualTile;
		}
		if (STATE->actualLayer == 1) // Tile 2
		{
			MAP->tile2[y][x] = STATE->actualTile;
		}
		if (STATE->actualLayer == 2) // Obj
		{
			MAP->obj[y][x] = STATE->actualTile;
		}
		if (STATE->actualLayer == 3) // Col
		{
			MAP->col[y][x] = STATE->actualTile;
		}
		if (STATE->actualLayer == 4) // Spawn
		{
			MAP->sy=INPUT->mousey; MAP->sx = INPUT->mousex;
		}
		if (STATE->actualLayer == 5) // Exit
		{
			MAP->ey = y; MAP->ex = x;
		}
		inputInit(INPUT);
	}
	if (INPUT->wheelup)
	{
		STATE->actualTile++;
		INPUT->wheelup=0;
	}
	if (INPUT->wheeldown)
	{
		STATE->actualTile--;
		INPUT->wheeldown = 0;
	}
	if (STATE->actualTile < 0)
		STATE->actualTile == 0;
}

void layerInterraction(leInput *INPUT, leState *STATE)
{
	// SHOW LAYER
	// layer1
	if (INPUT->leftclic && INPUT->leftclic_position_x > 0 && INPUT->leftclic_position_x < 16 && INPUT->leftclic_position_y < 16)
	{
		if (!STATE->tile)
		{
			STATE->tile = 1;
			inputInit(INPUT);
		}
		else
		{
			STATE->tile = 0;
			inputInit(INPUT);
		}

	}
	// layer2
	if (INPUT->leftclic && INPUT->leftclic_position_x > 0 && INPUT->leftclic_position_x < 16 && INPUT->leftclic_position_y < 32 && INPUT->leftclic_position_y > 16)
	{
		if (!STATE->tile2)
		{
			STATE->tile2 = 1;
			inputInit(INPUT);
		}
		else
		{
			STATE->tile2 = 0;
			inputInit(INPUT);
		}

	}
	// obj
	if (INPUT->leftclic && INPUT->leftclic_position_x > 104 && INPUT->leftclic_position_x < 120 && INPUT->leftclic_position_y < 16)
	{
		if (!STATE->obj)
		{
			STATE->obj = 1;
			inputInit(INPUT);
		}
		else
		{
			STATE->obj = 0;
			inputInit(INPUT);
		}

	}
	// col
	if (INPUT->leftclic && INPUT->leftclic_position_x > 104 && INPUT->leftclic_position_x < 120 && INPUT->leftclic_position_y < 32 && INPUT->leftclic_position_y > 16)
	{
		if (!STATE->col)
		{
			STATE->col = 1;
			inputInit(INPUT);
		}
		else
		{
			STATE->col = 0;
			inputInit(INPUT);
		}

	}
	//  spawn
	if (INPUT->leftclic && INPUT->leftclic_position_x > 208 && INPUT->leftclic_position_x < 240 && INPUT->leftclic_position_y < 16)
	{
		if (!STATE->sp)
		{
			STATE->sp = 1;
			inputInit(INPUT);
		}
		else
		{
			STATE->sp = 0;
			inputInit(INPUT);
		}

	}
	// exit
	if (INPUT->leftclic && INPUT->leftclic_position_x > 208 && INPUT->leftclic_position_x < 240 && INPUT->leftclic_position_y < 32 && INPUT->leftclic_position_y > 16)
	{
		if (!STATE->ex)
		{
			STATE->ex = 1;
			inputInit(INPUT);
		}
		else
		{
			STATE->ex = 0;
			inputInit(INPUT);
		}

	}

	// SELECT LAYER
	// Layer 1
	if (INPUT->leftclic && INPUT->leftclic_position_x > 16 && INPUT->leftclic_position_x < 96 && INPUT->leftclic_position_y < 16)
	{
		STATE->actualLayer = 0; STATE->actualTile = 1;
	}
	// Layer 2
	if (INPUT->leftclic && INPUT->leftclic_position_x > 16 && INPUT->leftclic_position_x < 96 && INPUT->leftclic_position_y < 32 && INPUT->leftclic_position_y > 16)
	{
		STATE->actualLayer = 1; STATE->actualTile = 1;
	}
	// Obj
	if (INPUT->leftclic && INPUT->leftclic_position_x > 120 && INPUT->leftclic_position_x < 200 && INPUT->leftclic_position_y < 16)
	{
		STATE->actualLayer = 2; STATE->actualTile = 1;
	}
	// Col
	if (INPUT->leftclic && INPUT->leftclic_position_x > 120 && INPUT->leftclic_position_x < 200 && INPUT->leftclic_position_y < 32 && INPUT->leftclic_position_y > 16)
	{
		STATE->actualLayer = 3; STATE->actualTile = 1;
	}
	// Spawn
	if (INPUT->leftclic && INPUT->leftclic_position_x > 224 && INPUT->leftclic_position_x < 304 && INPUT->leftclic_position_y < 16)
	{
		STATE->actualLayer = 4; 
	}
	// Exit
	if (INPUT->leftclic && INPUT->leftclic_position_x > 224 && INPUT->leftclic_position_x < 304 && INPUT->leftclic_position_y < 32 && INPUT->leftclic_position_y > 16)
	{
		STATE->actualLayer = 5;
	}
}

void menuInterraction(leInput *INPUT, leState *STATE, leMap *MAP, SDL_Window *window)
{
	// SAVE
	if (INPUT->leftclic && INPUT->leftclic_position_x > WWIN - 182 && INPUT->leftclic_position_x < WWIN - 104 && INPUT->leftclic_position_y < 32)
	{
		char path[300];
		int usepath = 0;
		//#if defined(_WIN32) || defined(_WIN64)
		//	usepath = SaveFile(path);
		//#endif
		map_save(MAP, path, usepath);
		inputInit(INPUT);
	}

	// LOAD
	if (INPUT->leftclic && INPUT->leftclic_position_x > WWIN - 260 && INPUT->leftclic_position_x < WWIN - 182 && INPUT->leftclic_position_y < 32)
	{
			char path[300] = "load_map/map.txt";

			//#if defined(_WIN32) || defined(_WIN64)

			//char path2[300];

			//if (LoadFile(path2))
				//strcpy(path, path2);

			//#endif
			if (messageBox("Open", "Are you sure you want to load a new map ?") == 1)
				map_load(MAP, path);
		inputInit(INPUT);
	}

	// Reset
	if (INPUT->leftclic && INPUT->leftclic_position_x > WWIN - 300 && INPUT->leftclic_position_x < WWIN - 268 && INPUT->leftclic_position_y < 32)
	{
		if (messageBox("Reset", "Do you want to reset the map ?") == 1)
		{
			map_init(MAP);
		}
		inputInit(INPUT);
	}
}

void caseReturn(leInput *INPUT, int *x, int *y)
{
	*x = INPUT->mousex / TCASE;
	*y = INPUT->mousey / TCASE;
}

void LOGICAL(leCore *CORE)
{
	inputReturn(CORE->INPUT);
	tileEditInterraction(CORE->INPUT, &CORE->STATE, CORE->MAP);
	windowInterraction(CORE->INPUT, &CORE->STATE, CORE->WINDOW, CORE->MAP);
	layerInterraction(CORE->INPUT, &CORE->STATE);
	menuInterraction(CORE->INPUT, &CORE->STATE, CORE->MAP, CORE->WINDOW);
}