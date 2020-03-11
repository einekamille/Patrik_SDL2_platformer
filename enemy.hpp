#ifndef ENEMY_H
#define ENEMY_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "map.hpp"
#include "player.hpp"
#include "character.hpp"

using namespace std;

class Enemy : public Character
{
private:

	bool    attack;			        //флаг атаки на игрока
	int     ExAnimCount;		    //дополнительный счётчик для анимаций
	bool    jumpFlag;

public:

	Enemy(void);									//конструктор
	~Enemy();										//деструктор

	void move(Level* karte_);						//движение
	void draw(SDL_Renderer* rendr, int offsetX_);	//отрисовка
	void CollisionTestX(Level* Map);				//тест коллизии с объектами карты по x
	bool CollisionWithPlayer(Player player);
	void Fight(Player player);
	bool TestLowWall(Level *Map);
	void AI();
};

#endif // ENEMY_H
