#include "SDL.h"
#include <time.h>
#include <iostream>
#include <SDL_image.h>
#include "game.h"
#include "board.h"
#include <chrono>
#include <ctime>
#include <SDL_ttf.h>
#include <string>
#include <algorithm>
#include <sstream>
#include <fstream>
#include "player.h"
#include <cstdio>
using namespace std::chrono;

#define width 1640
#define height 980

char str[26];
bool checkmate, whitemate, blackmate;
bool endscreen = 1;
chrono::system_clock::time_point p = chrono::system_clock::now();
time_t t = chrono::system_clock::to_time_t(p);
fstream fout;
string fileName;
stringstream buffer;
ifstream MOVE;
string file_content;
string* atfileName = &fileName;
int graczdoczasu=0;
bool menu;
double chesstime, increment, timepassed, whitetime,blacktime, secondstotaltimepassed;
int realitycheck=0 ;
int playermarker = 0;
int mx1, my1,mx2,my2,ymenu,xmenu;
int g,f,z,m,w;  // Zmienne do operacji po zmianie rozmiaru ekranu
int ssquare; //selected square
int* square = &ssquare;
int* mousex1 = &mx1;
int* mousey1 = &my1;
int* mousey2 = &my2;
int* mousex2 = &mx2;
int* atxmenu = &xmenu;
int* atymenu = &ymenu;
bool running, fullscreen,draw;
Player* currentPlayer = NULL;
SDL_Renderer* renderer;
SDL_Window* window;
SDL_Event e;

SDL_Texture* gTexture = NULL;
SDL_Texture* loadTexture(std::string path)
{
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	return newTexture;
}
void dosave() {
	
	MOVE.open("last move.txt");
		

	buffer << MOVE.rdbuf();
	file_content = buffer.str();

	MOVE.close();
	//wpisanie w trybie append do pliku z dat¹ w nazwie
	fstream fout(fileName, ios::app);
	fout << file_content;
	fout.close();
}
void highlightsquares() {
	
	SDL_Rect rect;
	int a, b;
	a = ssquare % 8;
	b = ssquare / 8;
	if (Board::getBoard()->squareAt(a, b)->occupiedBy()) {
		for (int j = 0; j < 8; j++) {
			for (int i = 0; i < 8; i++) {
					Square* target = Board::getBoard()->squareAt(i, j);
					if (bool canMove = Board::getBoard()->squareAt(a, b)->occupiedBy()->canMoveTo(*target)) {

						rect.x = z * g + (m / 8) * i ;
						rect.y = z * f + (m / 8) * j ;
						rect.w = m / 32;
						rect.h = m / 32;
						SDL_SetRenderDrawColor(renderer, 45, 255, 51, 45);
						SDL_RenderFillRect(renderer, &rect);
					}
				}
			}
		}
	}
bool squareisselected(int g) {	
	if (g == 1) {
		realitycheck+=1; 
	}
	return realitycheck%2;
}
int slsquare(int msx, int msy,int w, int odl,int x, int z) {
	msx = (msx - odl *x) / (w / 8);
		msy =  (msy - odl*z) / (w / 8);
		msy = 8 * (msy);
	int a = msx+ msy +1;	
	return a;
}
void play() {

	int a, b, c, d, square2;
	
	square2 = slsquare(mx2, my2, m, z, g, f) - 1;
	a = ssquare % 8;
	b = ssquare / 8;
	c = square2 % 8;
	d = square2 / 8;
	ifstream kopia;
	kopia.open("Last_move_octal.txt");
	stringstream buffer;
	buffer << kopia.rdbuf();
	string copy = buffer.str();
	kopia.close();
	ofstream skopiuj("backup.txt");
	skopiuj << copy;
	skopiuj.close();
	currentPlayer = Game::getNextPlayer();
	if (currentPlayer->inCheckMate())
	{
		checkmate = 1;
	}
	if (!currentPlayer->makeMove(ssquare, (square2)))
	{
		ifstream kopia;
		kopia.open("backup.txt");
		stringstream buffer;
		buffer << kopia.rdbuf();
		string copy = buffer.str();
		kopia.close();
		ofstream skopiuj("Last_move_octal.txt");
		skopiuj << copy;
		skopiuj.close();
		currentPlayer = Game::getNextPlayer();
		cerr << "Nie mozna wykonac takiego ruchu" << endl;
	}
	else {
		playermarker++;
		if (graczdoczasu % 2 == 0) {
			whitetime -= increment;
		}
		else {
			blacktime -= increment;
		}
		graczdoczasu++;
		dosave();
	}
	currentPlayer = Game::getNextPlayer();
	if (currentPlayer->inCheckMate())
	{
		checkmate = 1;
	}
	currentPlayer = Game::getNextPlayer();
	mx1 = 0;
	my1 = 0;
	mx2 = 0;
	my2 = 0;
	

}	
bool loadMedia(std::string path)
{
	//Loading success flag
	bool success = true;

	//Load PNG texture
	gTexture = loadTexture("assets/" + path);
	if (gTexture == NULL)
	{
		printf("Failed to load texture image!\n");
		success = false;
	}

	return success;
}
void input() {
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			fstream fout("Last_move_octal.txt");
			fout << "    ";
			fout.close();
			running = false;
		}
		if (e.type == SDL_MOUSEBUTTONDOWN) {
			if (!squareisselected(0)) {
				SDL_GetMouseState(mousex1, mousey1);
				squareisselected(1);
				
				
			}
			else {
				SDL_GetMouseState(mousex2, mousey2);
				play();
				squareisselected(1);
			}
		}
			
	
	}
	const Uint8* keystates = SDL_GetKeyboardState(NULL);
	if (keystates[SDL_SCANCODE_BACKSLASH]) draw = true;
	if (keystates[SDL_SCANCODE_ESCAPE]) running = false;
	if (keystates[SDL_SCANCODE_F11])  fullscreen =!fullscreen;
}
void update(){
	if (fullscreen) SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
	if (!fullscreen) SDL_SetWindowFullscreen(window, 0);

}
void gettimer() {
	
	string c = to_string(int(chesstime-whitetime));
	string f = to_string(int(chesstime - blacktime));
	TTF_Font* Sans = TTF_OpenFont("SofiaSans-Bold.ttf", 150);
	SDL_Color White = { 130, 35, 35 };
	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, c.c_str(), White);
	SDL_Texture* Message1 = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
	SDL_Surface* surfaceMessage2 = TTF_RenderText_Solid(Sans, f.c_str(), White);
	SDL_Texture* Message2 = SDL_CreateTextureFromSurface(renderer, surfaceMessage2);
	SDL_Rect timero;
	timero.x = w-z;
	timero.y = m-100;
	timero.w = 100;
	timero.h = 100;
	SDL_Rect blacktimero;
	blacktimero.x = z-m/8;
	blacktimero.y = 0;
	blacktimero.w = 100;
	blacktimero.h = 100;
	SDL_RenderCopy(renderer, Message1, NULL, &timero);
	SDL_RenderCopy(renderer, Message2, NULL, &blacktimero);
	SDL_RenderPresent(renderer);
}
void drawcheckmate() {
	if (checkmate == 1) {
		SDL_Rect rect;
		rect.x = z * g + (m / 2)-137;
		rect.y = z * f + (m / 2)-75;
		rect.w = 274;
		rect.h = 151;
		SDL_Rect src;
		src.x = 0;
		src.y = 0;
		src.w = 274;
		src.h = 151;
		if (playermarker % 2 == 1) {
			loadMedia("Whiteendscreen.png");
		}
		else {
			loadMedia("Blackendscreen.png");
		}
		SDL_RenderCopy(renderer, gTexture, &src, &rect);
		SDL_DestroyTexture(gTexture);
	}
}
void highightlastmove(int a1, int b1) {
	SDL_Rect rect;
	ifstream MOVE1;
	string file_content1;
	MOVE1.open("Last_move_octal.txt");
	stringstream buffer1;
	buffer1 << MOVE1.rdbuf();
	file_content1 = buffer1.str();
	char a = file_content1[0];
	char b = file_content1[1];
	char c = file_content1[2];
	char d = file_content1[3];

	SDL_SetRenderDrawColor(renderer, 189, 188, 123, 100);

	if (a != NULL) {
		if (a1 == int(a - '0') && b1 == int(b - '0')) {
			rect.x = z * g + (m / 8) * int(a - '0');
			rect.y = z * f + (m / 8) * (7 - int(b - '0'));
			rect.w = m / 8;
			rect.h = m / 8;
			SDL_RenderFillRect(renderer, &rect);
		}
		else if (a1 == int(c - '0') && b1 == int(d - '0')) {
			rect.x = z * g + (m / 8) * int(c - '0');
			rect.y = z * f + (m / 8) * (7 - int(d - '0'));
			rect.w = m / 8;
			rect.h = m / 8;
			SDL_RenderFillRect(renderer, &rect);
		}
	}
}
void drawdraw() {
	SDL_Rect rect;
	rect.x = z * g + (m / 2) - 137;
	rect.y = z * f + (m / 2) - 75;
	rect.w = 274;
	rect.h = 151;
	SDL_Rect src;
	src.x = 0;
	src.y = 0;
	src.w = 274;
	src.h = 151;
	loadMedia("Drawendscreen.png");
	SDL_RenderCopy(renderer, gTexture, &src, &rect);
}
void drawboard() {
	 g = 1;
	 f = 0;
	string path;
	SDL_GetRendererOutputSize(renderer, &w, &m);
	SDL_Rect src;
	src.x = 0;
	src.y = 0;
	src.w = 800;
	src.h = 800;
	SDL_Rect rect;
	rect.x = 0;
	rect.y = 0;
	rect.w = w;
	rect.h = m;
	SDL_SetRenderDrawColor(renderer, 45, 45,51,45);
	SDL_RenderFillRect(renderer, &rect);
	if (m > w) {
		w = w + m;
		m = w - m;
		w = w - m;
		g = 0;
		f = 1;
	}
	 z = (w - m) / 2;
	int i = 0;
	int j = 0;
	

	for (j = 7; j >= 0; j--) {
		for (i = 7; i >= 0; i--) {
			rect.x = z * g + (m / 8) * i;
			rect.y = z * f + (m / 8) * j;
			rect.w = m / 8;
			rect.h = m / 8;
			if ((i + j) % 2 == 1) SDL_SetRenderDrawColor(renderer, 232, 235, 239, 1);
			if ((i + j) % 2 == 0)SDL_SetRenderDrawColor(renderer, 100, 111, 140, 25);
			if (slsquare(mx1, my1, m, z, g, f) != 0 && slsquare(mx1, my1, m, z, g, f) == (i + j * 8 + 1)) {
				if (squareisselected(0)) {
					SDL_SetRenderDrawColor(renderer, 50, 150, 50, 50);
					*square = (i + j * 8);

				}

			}
			SDL_RenderFillRect(renderer, &rect);
			highightlastmove(i, 7 - j);


			if (Board::getBoard()->squareAt(i, 7 - j)->occupied()) {
				path = Board::getBoard()->squareAt(i, 7 - j)->occupiedBy()->getName();
				path += ".png";
				loadMedia(path);
				SDL_RenderCopy(renderer, gTexture, &src, &rect);
				SDL_DestroyTexture(gTexture);
			}
			
		}
	}
	if (currentPlayer->availablePromotion()) {
		cout << "trueeee";
		rect.x = z * g - m/8;
		rect.y = m/8;
		rect.w = m / 8;
		rect.h = m / 8;
		loadMedia("BQ.png");
		SDL_RenderCopy(renderer, gTexture, &src, &rect);
				SDL_DestroyTexture(gTexture);
		rect.y = m/4;
		loadMedia("BS.png");
		SDL_RenderCopy(renderer, gTexture, &src, &rect);
		SDL_DestroyTexture(gTexture);

		rect.y = 3*m/8;
		loadMedia("BG.png");
		SDL_RenderCopy(renderer, gTexture, &src, &rect);
		SDL_DestroyTexture(gTexture);
		rect.y = 4* m / 8;
		loadMedia("BW.png");
		SDL_RenderCopy(renderer, gTexture, &src, &rect);
		SDL_DestroyTexture(gTexture);

	}
	if (draw) {
		drawdraw();
	}
	drawcheckmate();
	gettimer();
	SDL_RenderPresent(renderer);



}
void viewmenu() {
	SDL_GetRendererOutputSize(renderer, &w, &m);
	SDL_Rect src;
	src.x = 0;
	src.y = 0;
	src.w = 1680;
	src.h = 851;
	SDL_Rect rect;
	rect.x = 0;
	rect.y = 0;
	rect.w = w;
	rect.h = m;
	SDL_SetRenderDrawColor(renderer, 45, 45, 51, 45);
	SDL_RenderFillRect(renderer, &rect);
	loadMedia("MainMenu.png");
	SDL_RenderCopy(renderer, gTexture, &src, &rect);
	SDL_DestroyTexture(gTexture);
	SDL_RenderPresent(renderer);


}
void Timeselect(double czas,int inc) {
	chesstime = czas*60;
	increment = inc;
	menu = 0;
};
void menuinput() {
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			menu = false;
			running = false;
		}
		if (e.type == SDL_MOUSEBUTTONDOWN) {
			SDL_GetMouseState(&xmenu, &ymenu);
			if (xmenu < w / 3) {
				if (ymenu > m / 11.5 && ymenu < m / 4.5) {
				
					Timeselect(1, 0);
				}
				else if (ymenu > m / 2.85 && ymenu < m / 2.02) {
					Timeselect(3, 0);
				}
				else if (ymenu > m / 1.6 && ymenu < m / 1.316) {
					Timeselect(10, 0);
				}

			}
			else if (xmenu > (w / 3) &&  xmenu<(2*w/3) ) {
				if (ymenu > m / 11.5 && ymenu < m / 4.5) {
					Timeselect(1, 1);
				}
				else if (ymenu > m / 2.85 && ymenu < m / 2.02) {
					Timeselect(3, 2);
				}
				else if (ymenu > m / 1.6 && ymenu < m / 1.316) {
					Timeselect(15, 10);
				}
			}
				else if (xmenu> (2*w/3)) {
					if (ymenu > m / 11.5 && ymenu < m / 4.5) {
						Timeselect(2, 1);
					}
					else if (ymenu > m / 2.85 && ymenu < m / 2.02) {
						Timeselect(5, 0);
					}
					else if (ymenu > m / 1.6 && ymenu < m / 1.316) {
						Timeselect(30, 0);
					}
				}
			}
		
				
		}

	const Uint8* keystates = SDL_GetKeyboardState(NULL);
	if (keystates[SDL_SCANCODE_ESCAPE]) running = false;
	if (keystates[SDL_SCANCODE_F11])  fullscreen = !fullscreen;
	}
void dopiotr() {
	chrono::system_clock::time_point p = chrono::system_clock::now();
	time_t t = chrono::system_clock::to_time_t(p);
	char str[26];

	ctime_s(str, sizeof str, &t);
	//nazwa zaczyna siê od zdefiniowania folderu
	fileName;
	fileName = "saved_games/";
	fileName += str;
	if (!fileName.empty() && fileName[fileName.length() - 1] == '\n') {
		fileName.erase(fileName.length() - 1);
	}
	//zamiana spacji i dwukropków na podkreslenie i srednik
	replace(fileName.begin(), fileName.end(), ' ', '_');
	replace(fileName.begin(), fileName.end(), ':', ';');
	//dopisanie formatu .txt
	fileName += ".txt";

}
int endinput() {
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) endscreen = false;
		if (e.type == SDL_MOUSEBUTTONDOWN) {

			SDL_GetMouseState(mousex1, mousey1);
			if (mx1<z * g + (m / 2) && mx1>z * g + (m / 2) -100 && my1>z * f + (m / 2) && my1<z * f + (m / 2) + 115){
				cout << "tutaj";
				return 1;



		}
		if (mx1> z * g + (m / 2) && mx1< z * g + (m / 2) +100 && my1>z * f + (m / 2) && my1<z * f + (m / 2) + 115) {
			endscreen = 0;
			return 2;
			
		
		}


	}
	const Uint8* keystates = SDL_GetKeyboardState(NULL);
	if (keystates[SDL_SCANCODE_ESCAPE]) running = false;
	if (keystates[SDL_SCANCODE_F11])  fullscreen = !fullscreen;
}
}
void promotioninput() {
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_MOUSEBUTTONDOWN) {

			SDL_GetMouseState(atxmenu, atymenu);
			if (xmenu < z * g && xmenu > z * g - m / 8) {
				cout << endl << ymenu << endl;
				cout << m / 8;
				if (ymenu > m / 8 && ymenu < m / 4) {
					cout << endl << "tak" << endl;
					currentPlayer->promotePawn('Q');
				}
				else if (ymenu > m / 4 && ymenu < 3 * m / 8) {
					cout << endl << "tak" << endl;
					currentPlayer->promotePawn('S');
				}
				else if (ymenu > 3 * m / 8 && ymenu < m / 2) {
					cout << endl << "tak" << endl;

					currentPlayer->promotePawn('G');
				}
				else if (ymenu > m / 2 && ymenu < 5 * m / 8) {
					cout << endl << "tak" << endl;

					currentPlayer->promotePawn('W');
				}
			}
		}


	}
}


int main(int z, char*argv[]) {
	
	if (SDL_Init(SDL_INIT_EVERYTHING < 0)) std::cout << "failed at sdl init" << std::endl;
	if (SDL_CreateWindowAndRenderer(width, height, 0, &window, &renderer) < 0) std::cout << "Failed at SDL_CreateWindowAndRenderer" << std::endl;
	SDL_SetWindowTitle(window, "fajne szahy");
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");
start:
	TTF_Init();
	Game::initialize();
		currentPlayer = Game::getNextPlayer();
	currentPlayer = Game::getNextPlayer();

	draw = 0;
	checkmate = 0;
	menu = 1;
	running = 1;
	fullscreen = 0;
	playermarker = 0;
	timepassed = 0;
	whitetime = 0;
	blacktime = 0;
	dopiotr();

	while (menu) {
		viewmenu();
		update();
		menuinput();
		SDL_WaitEvent;
	}
	drawboard();
	while (running) {
		std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
		if (!(currentPlayer->availablePromotion())) {
			input();
		}
		else {
			drawboard();
			SDL_WaitEvent;
			promotioninput();
		}
		drawboard();
		if (draw) {
			goto endscr;
		}
		update();
		SDL_RenderClear(renderer);
		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		timepassed = duration_cast<std::chrono::milliseconds>(end - begin).count();
	
		
		if (playermarker % 2 == 0) {
			whitetime += timepassed / 1000;
		}
		else {
			blacktime += timepassed / 1000;
		}
		
		if (whitetime > chesstime || blacktime > chesstime || checkmate == 1) {
			
			checkmate = 1;
			goto endscr;
		}
	}
	
	return 0;
endscr:
	fstream fout("Last_move_octal.txt");
	fout << "    ";
	fout.close();
	while (endscreen) {
		drawboard();
		SDL_WaitEvent;
		if (endinput() == 1) {
			
			goto start;
		}
		else if (endinput() == 2) {
			goto here;
		}
	}
	here:
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}