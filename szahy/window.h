#pragma once
#include <string>
#include <SDL.h>
class Window {
	Window(const std::string& title, int width, int height);
	
private:
	bool init();
private:
	std::string _title;
	int _width = 800;
	int _height =  600;

	bool _closed = false;
	SDL_Window * _window = nullptr; 
};