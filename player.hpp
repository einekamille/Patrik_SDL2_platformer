#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "map.hpp"
#include "character.hpp"

using namespace std;

class Player: public Character
{
private:

public:
	Player(void);									//конструктор
	~Player();										//деструктор
};

#endif // PLAYER_H
