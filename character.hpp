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
	SDL_Texture*    sprite;	        //указатель на спрайт-лист
	int     number_of_frames_total;	//количество кадров в спрайт-листе (всего)
	int     number_of_frames_move;	//количество кадров в спрайт-листе, относящихся к анимации движения по x
	bool    move_direction_right;	//флаг направления движения для зеркалирования текстуры в кадре
	int     current_frame;		    //текущий кадр анимации
	int     frame_counter;			//переменная для счтчика кадров
	int     frame_delay;			//переменная, устанавливающая интервал времени между кадрами (по сути, отвечающая за скорость анимации)
	bool    animation_is_on;		//флаг активности анимации
	int     collision_corrector;	//техническая переменная для корректировки коллизии игрока с объектами на карте (если кадр шире, чем текстура)

public:
	bool    is_life;
	float   x;				//координата игрока по x
	float   y;				//координата игрока по y
	float   dx;				//модификатор движения по оси x
	float   dy;				//модификатор движения по оси y
	int     width;			//ширина текстуры игрока
	int     height;			//высота текстуры игрока
	bool    on_ladder;		//флаг нахождения на "лестнице"
	bool    on_ground;		//флаг нахождения на "твёрдой" поверхности
	bool    verticalMove;


    Character();
    ~Character();

    /*загрузка спрайт-листа игрока.
	rendr - текущий рендер SDL2
	path_to_bmp_file_ - путь к файлу
	x_ и y_ - координаты,
	number_of_frames_total_ - количество кадров
	number_of_frames_move_ - количество кадров анимации движения по x (должны идти первыми в спрайт-листе)*/
	void load(SDL_Renderer* rendr, char *path_to_bmp_file_, float x_, float y_,
           int number_of_frames_total_, int number_of_frames_move_);
	void collision(bool dir_, Level* karte_);		//коллизия с объектами карты
	void move(Level* karte_);						//движение
	void draw(SDL_Renderer* rendr, int offsetX_);	//отрисовка
	void CollisionTestX(Level* Map);				//тест коллизии с объектами карты по x
	void CollisionTestY(Level* Map);				//тест коллизии с объектами карты по y
	void death();
};

#endif // CHARACTER_H
