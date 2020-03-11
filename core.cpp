#include "core.hpp"
#include "map.hpp"
#include "player.hpp"
#include "enemy.hpp"

#define SCREEN_WIDTH 500
#define SCREEN_HEIGHT  500

const int NUMBER_OF_ENEMIES = 5;

Level map;
Player Hero;
Enemy enemy[NUMBER_OF_ENEMIES];

Mix_Music *gMusic = NULL;

eCore::eCore(void)
{
	this->quitGame = false;
	this->iFPS = 0;
	this->iNumOfFPS = 0;
	this->FPSTime = 0;
	this->offsetX = 0;
	keyRight = keyLeft = keyUp = false;

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
	window = SDL_CreateWindow("Patrik!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == NULL)
	{
		quitGame = true;
	}

	rendr = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	mainEvent = new SDL_Event();

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
	    cout << "SDL_mixer could not initialize! SDL_mixer Error: " <<  Mix_GetError() << endl;
		quitGame = true;
	}
	gMusic = Mix_LoadMUS("resources/kebab.ogg");
	if (gMusic == NULL)
	{
	    cout << "Failed to load beat music! SDL_mixer Error: " <<  Mix_GetError() << endl;
		quitGame = true;
	}
	Mix_PlayMusic(gMusic, -1);
}

eCore::~eCore(void)
{
	delete mainEvent;
	SDL_DestroyRenderer(rendr);
	SDL_DestroyWindow(window);
}

void eCore::mainLoop()
{
	char RESOURCE_MAP_PATH[] = "resources/map.txt";
	char RESOURCE_PLAYER_PATH[] = "resources/player.bmp";
	char RESOURCE_ENEMY_PATH[] = "resources/knight.bmp";

	FPSTime = SDL_GetTicks();

	map.load_map(rendr, RESOURCE_MAP_PATH);
	Hero.load(rendr, RESOURCE_PLAYER_PATH, 50, 400, 11, 8);
	for (int i = 0; i < NUMBER_OF_ENEMIES; i++)
	{
		enemy[i].load(rendr, RESOURCE_ENEMY_PATH, 200 * (i + 1), 400, 11, 4);
	}
	while (!quitGame && mainEvent->type != SDL_QUIT)
	{
		frameTime = SDL_GetTicks();
		SDL_PollEvent(mainEvent);
		SDL_RenderClear(rendr);

		if ((Hero.x > SCREEN_WIDTH / 2) && (Hero.x + Hero.width < map.Width * 32 - SCREEN_WIDTH / 2))
		{
			offsetX = Hero.x - SCREEN_WIDTH / 2;
		}
		Input();
		Update();
		Draw();

		SDL_RenderPresent(rendr);

		if (SDL_GetTicks() - frameTime < MIN_FRAME_TIME)
		{
			SDL_Delay(MIN_FRAME_TIME - (SDL_GetTicks() - frameTime));
		}
	}
}

void eCore::Update()
{
	Hero.move(&map);
	for (int i = 0; i < NUMBER_OF_ENEMIES; i++)
	{
		enemy[i].move(&map);
		if (enemy[i].CollisionWithPlayer(Hero))
		{
			Hero.death();
		}
	}
}

void eCore::Draw()
{
	map.draw(rendr, offsetX);
	Hero.draw(rendr, offsetX);
	for (int i = 0; i < NUMBER_OF_ENEMIES; i++)
	{
		enemy[i].draw(rendr, offsetX);
	}

}

void eCore::Input()
{
	if (mainEvent->type == SDL_KEYDOWN)
	{
		switch (mainEvent->key.keysym.sym)
		{
		case SDLK_RIGHT:
			//
			keyRight = true;
			break;
		case SDLK_LEFT:
			//
			keyLeft = true;
			break;
		case SDLK_UP:
			//
			keyUp = true;
			break;
		case SDLK_DOWN:
			//
			keyDown = true;
			break;
		}
	}
	else if (mainEvent->type == SDL_KEYUP)
	{
		switch (mainEvent->key.keysym.sym)
		{
		case SDLK_RIGHT:
			//
			keyRight = false;
			break;
		case SDLK_LEFT:
			//
			keyLeft = false;
			break;
		case SDLK_UP:
			//
			keyUp = false;
			//if (Hero.on_ladder) Hero.dy = 0;
			break;
		case SDLK_DOWN:
			//
			keyDown = false;
			break;
		}
	}

	if (Hero.is_life)
	{
		if (keyRight)
		{
			Hero.dx = 2;
			Hero.verticalMove = false;
		}
		if (keyLeft)
		{
			Hero.dx = -2;
			Hero.verticalMove = false;
		}
		if (keyUp)
		{
			if (Hero.on_ground && !Hero.on_ladder)
			{
				Hero.dy = -11;
				Hero.verticalMove = false;
			}
			if (!Hero.on_ladder)
			{
				Hero.verticalMove = false;
			}
			else if (Hero.on_ladder)
			{
				Hero.verticalMove = true;
				//Hero.dy = -1.5;
			}
			if (Hero.verticalMove)
			{
				Hero.dy = -1.5;
			}
		}
		if (keyDown)
		{
			if (Hero.verticalMove)
			{
				Hero.dy = 1.5;
			}
		}
	}
}
