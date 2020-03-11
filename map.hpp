#ifndef MAP_H
#define MAP_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

using namespace std;

//������������ ��� �������� ��������� � ����� ������� ��� �������� �����
enum TXD
{
	BRICK,
	MINE,
	LEITERS,
	ENEMY,
	TXDNUM
};

//������������ ��� �������� ��������� � ����� �������� �����
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

//����� ��� ������, �� ������� �������� �����
class Block
{
protected:
	bool Enable;		//���� ����������� ������������� �����
public:
	BlockType Type;		//��� ����� (������ �� ������������)

	Block();
	~Block();
	bool isEnable();	//������ �������� �� ���� enable
	void Kill();		//����������� ����� �� �����
};

class DestroyableBlock : public Block
{
private:

public:

};

//����� ��� ������
class Level
{
private:
	SDL_Texture* texture[TXDNUM];	//������ ������� ��� ������ ����� ������

public:
	int Width;						//����� ������
	int Height;						//������ ������
	int BlockSize;					//������ ����� � ������
	Block LevelMap[300][100];		//������ ������ (����� ������)

	Level(void);
	~Level();
	void load_map(SDL_Renderer* rendr, char *weg_zu_map_);	//�������� �����
	void loadTexture(SDL_Renderer* rendr);					//�������� ������� � ������
	void draw(SDL_Renderer* rendr, int offsetX_);			//���������
};

#endif // MAP_H
