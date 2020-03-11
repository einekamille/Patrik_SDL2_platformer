#ifndef CHARACTER_H
#define CHARACTER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "map.hpp"

using namespace std;

class Character
{
protected:
	SDL_Texture*    sprite;	        //��������� �� ������-����
	int     number_of_frames_total;	//���������� ������ � ������-����� (�����)
	int     number_of_frames_move;	//���������� ������ � ������-�����, ����������� � �������� �������� �� x
	bool    move_direction_right;	//���� ����������� �������� ��� �������������� �������� � �����
	int     current_frame;		    //������� ���� ��������
	int     frame_counter;			//���������� ��� ������� ������
	int     frame_delay;			//����������, ��������������� �������� ������� ����� ������� (�� ����, ���������� �� �������� ��������)
	bool    animation_is_on;		//���� ���������� ��������
	int     collision_corrector;	//����������� ���������� ��� ������������� �������� ������ � ��������� �� ����� (���� ���� ����, ��� ��������)

public:
	bool    is_life;
	float   x;				//���������� ������ �� x
	float   y;				//���������� ������ �� y
	float   dx;				//����������� �������� �� ��� x
	float   dy;				//����������� �������� �� ��� y
	int     width;			//������ �������� ������
	int     height;			//������ �������� ������
	bool    on_ladder;		//���� ���������� �� "��������"
	bool    on_ground;		//���� ���������� �� "������" �����������
	bool    verticalMove;


    Character();
    ~Character();

    /*�������� ������-����� ������.
	rendr - ������� ������ SDL2
	path_to_bmp_file_ - ���� � �����
	x_ � y_ - ����������,
	number_of_frames_total_ - ���������� ������
	number_of_frames_move_ - ���������� ������ �������� �������� �� x (������ ���� ������� � ������-�����)*/
	void load(SDL_Renderer* rendr, char *path_to_bmp_file_, float x_, float y_,
           int number_of_frames_total_, int number_of_frames_move_);
	void collision(bool dir_, Level* karte_);		//�������� � ��������� �����
	void move(Level* karte_);						//��������
	void draw(SDL_Renderer* rendr, int offsetX_);	//���������
	void CollisionTestX(Level* Map);				//���� �������� � ��������� ����� �� x
	void CollisionTestY(Level* Map);				//���� �������� � ��������� ����� �� y
	void death();
};

#endif // CHARACTER_H
