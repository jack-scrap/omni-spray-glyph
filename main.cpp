#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>

#include "disp.h"
#include "prog.h"
#include "util.h"
#include "col.h"
#include "layout.h"
#include "glyph.h"

bool scr(std::string path, SDL_Window* win, SDL_Renderer* rend) {
	SDL_Surface* surfSave = NULL;
	SDL_Surface* surfInfo = SDL_GetWindowSurface(win);
	if (!surfInfo) {
		std::cerr << "Failed to create info surface from window in save(string), SDL_GetError() - " << SDL_GetError() << std::endl;
	} else {
		unsigned char* pix[surfInfo->w * surfInfo->h * surfInfo->format->BytesPerPixel];
		if (!pix) {
			std::cerr << "Unable to allocate memory for screenshot pixel data buffer!" << std::endl;

			return false;
		} else {
			if (SDL_RenderReadPixels(rend, &surfInfo->clip_rect, surfInfo->format->format, pix, surfInfo->w * surfInfo->format->BytesPerPixel) != 0) {
				std::cerr << "Failed to read pixel data from SDL_Renderer object. SDL_GetError() - " << SDL_GetError() << std::endl;

				return false;
			} else {
				surfSave = SDL_CreateRGBSurfaceFrom(pix, surfInfo->w, surfInfo->h, surfInfo->format->BitsPerPixel, surfInfo->w * surfInfo->format->BytesPerPixel, surfInfo->format->Rmask, surfInfo->format->Gmask, surfInfo->format->Bmask, surfInfo->format->Amask);

				if (!surfSave) {
					std::cerr << "Couldn't create SDL_Surface from renderer pixel data. SDL_GetError() - " << SDL_GetError() << std::endl;

					return false;
				}

				SDL_SaveBMP(surfSave, path.c_str());
				SDL_FreeSurface(surfSave);
				surfSave = NULL;
			}
		}

		SDL_FreeSurface(surfInfo);
		surfInfo = NULL;
	}

	return true;
}

int main(int argc, char* argv[]) {
	Disp disp("Glyph texture generator", 100, 100);

	if (argc != 2) {
		std::cout << "Error: Wrong number of arguments" << std::endl;

		return 1;
	}

	if (strlen(argv[1]) > 1) {
		std::cout << "Error: Length of argument longer than one" << std::endl;

		return 1;
	}

	char c = argv[1][0];

	Glyph glyph(c, 1);

	// Draw
	disp.clear(col[true].r / 255.0, col[true].g / 255.0, col[true].b / 255.0, 1);

	glyph.draw();

	disp.update();

	std::string path = std::string("o/") + std::string(1, c) + ".bmp";

	if (!scr(path.c_str(), disp.win, disp.rend)) {
		std::cout << "Error: Couldn't save renderbuffer" << std::endl;
	}
}
