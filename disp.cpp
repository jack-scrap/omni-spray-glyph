#include "disp.h"

Disp::Disp(const char* title, int wd, int ht) {
	SDL_Init(SDL_INIT_VIDEO);

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	SDL_CreateWindowAndRenderer(wd, ht, 0, &win, &rend);

	ctx = SDL_GL_CreateContext(win);

	GLenum status = glewInit();
	if (status != GLEW_OK) {
		std::cerr << "GLEW failed to initialize" << std::endl;
	}

	glEnable(GL_DEPTH_TEST);

	open = true;
}

void Disp::clear(float r, float g, float b, float a) {
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Disp::update() {
	SDL_GL_SwapWindow(win);
}

Disp::~Disp() {
	SDL_GL_DeleteContext(ctx);

	SDL_DestroyWindow(win);

	SDL_Quit();
}
