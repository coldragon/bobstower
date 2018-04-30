#include <stdio.h>
#include "hdr/texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "hdr/stb_image.h"

Texture* TextureCreate(SDL_Renderer* renderer, const char* spriteName, int r, int g, int b, int a)
{
	SDL_Surface * surf = NULL;

	int req_format = STBI_rgb_alpha;
	int width, height, orig_format;
	unsigned char* data = stbi_load(spriteName, &width, &height, &orig_format, req_format);
	if (data == NULL) {
		SDL_Log("ERROR : Can't load image : %s", stbi_failure_reason());
		surf = NULL;
	}
	else {
		int depth, pitch;
		Uint32 pixel_format;
		if (req_format == STBI_rgb) {
			depth = 24;
			pitch = 3 * width;
			pixel_format = SDL_PIXELFORMAT_RGB24;
		}
		else {
			depth = 32;
			pitch = 4 * width;
			pixel_format = SDL_PIXELFORMAT_RGBA32;
		}

		surf = SDL_CreateRGBSurfaceWithFormatFrom((void*)data, width, height,
			depth, pitch, pixel_format);
	}

	if (surf == NULL)
	{
		printf("Erreur (Fonction TextureCreate) : impossible de charger l'image \"%s\".\n", spriteName);
		exit(-1);
	}

	if (r >= 0 && g >= 0 && b >= 0)
	{
		SDL_SetColorKey(surf, SDL_TRUE, SDL_MapRGB(surf->format, r, g, b));
		if (a < 255 && a >= 0)
			SDL_SetSurfaceAlphaMod(surf, a);
	}

	Texture * tex = (Texture*)malloc(sizeof(Texture));

	if (tex != NULL)
	{
		tex->handle = SDL_CreateTextureFromSurface(renderer, surf);
		if (tex->handle == NULL)
			printf("Erreur (fonction TextureCreate): impossible de créer la texture à partir de la surface (%s)\n", SDL_GetError());
		tex->w = surf->w;
		tex->h = surf->h;
	}
	SDL_FreeSurface(surf);
	return tex;
}

void TextureFree(Texture* tex)
{
	SDL_DestroyTexture(tex->handle);
	free(tex);
}

Texture* TextureCopy(SDL_Renderer* renderer, Texture* tex)
{
	Texture* texDst;
	texDst = (Texture*)malloc(sizeof(Texture));
	texDst->w = tex->w;
	texDst->h = tex->h;

	texDst->handle = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, texDst->w, texDst->h);

	SDL_SetTextureBlendMode(texDst->handle, SDL_BLENDMODE_BLEND);
	SDL_SetRenderTarget(renderer, texDst->handle);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, tex->handle, NULL, NULL);
	SDL_SetRenderTarget(renderer, NULL);

	return texDst;
}

int TextureRender(SDL_Renderer* renderer, Texture* tex, int x, int y, SDL_Rect* clip)
{
	SDL_Rect destBuf = { x, y, tex->w, tex->h };
	if (clip != NULL)
	{
		destBuf.w = clip->w;
		destBuf.h = clip->h;
	}
	return SDL_RenderCopy(renderer, tex->handle, clip, &destBuf);
}
// Created by Scorbutics
