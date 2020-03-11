#ifndef MAP_H
#define MAP_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

using namespace std;

//перечисление для удобного обращения к типам текстур для объектов карты
enum TXD
{
	BRICK,
	MINE,
	LEITERS,
	ENEMY,
	TXDNUM
};

//перечисление для удобного обращения к типам объектов карты
enum BlockType
{
	GROUND,
	GRASS,
	SWAMP,
	BOX,
	LEITER,
	NONE,
	BLOCKNUM
};

//класс для блоков, из которых строится карта
class Block
{
protected:
	bool Enable;		//флаг продолжения существования блока
public:
	BlockType Type;		//тип блока (берётся из перечисления)

	Block();
	~Block();
	bool isEnable();	//просто проверка на флаг enable
	void Kill();		//уничтожение блока на карте
};

class DestroyableBlock : public Block
{
private:

public:

};

//класс для уровня
class Level
{
private:
	SDL_Texture* texture[TXDNUM];	//массив текстур для разных типов блоков

public:
	int Width;						//длина уровня
	int Height;						//высота уровня
	int BlockSize;					//размер блока в точках
	Block LevelMap[300][100];		//массив блоков (карта уровня)

	Level(void);
	~Level();
	void load_map(SDL_Renderer* rendr, char *weg_zu_map_);	//загрузка карты
	void loadTexture(SDL_Renderer* rendr);					//загрузка текстур в массив
	void draw(SDL_Renderer* rendr, int offsetX_);			//отрисовка
};

#endif // MAP_H
