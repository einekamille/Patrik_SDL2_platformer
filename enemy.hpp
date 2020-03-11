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

	bool    attack;			        //���� ����� �� ������
	int     ExAnimCount;		    //�������������� ������� ��� ��������
	bool    jumpFlag;

public:

	Enemy(void);									//�����������
	~Enemy();										//����������

	void move(Level* karte_);						//��������
	void draw(SDL_Renderer* rendr, int offsetX_);	//���������
	void CollisionTestX(Level* Map);				//���� �������� � ��������� ����� �� x
	bool CollisionWithPlayer(Player player);
	void Fight(Player player);
	bool TestLowWall(Level *Map);
	void AI();
};

#endif // ENEMY_H
