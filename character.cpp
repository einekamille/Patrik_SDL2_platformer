#include "character.hpp"

Character::Character(void)
{
	animation_is_on = false;
	frame_counter = 0;
	frame_delay = 5;
	collision_corrector = 5;
	on_ladder = false;
	is_life = true;
}

Character::~Character()
{
}

void Character::load(SDL_Renderer* rendr, char *PathToImage, float x_, float y_, int number_of_frames_total_, int number_of_frames_move_)
{
	dy = 0;
	move_direction_right = true;
	on_ground = false;

	SDL_Texture *newTexture = NULL;
	SDL_Surface *loadedSurface = IMG_Load(PathToImage);
	if (loadedSurface == NULL)
	{
	    cout << "Unable to load image " << PathToImage << " SDL_image Error: " <<  IMG_GetError() << endl;
	}
	else
	{
		width = loadedSurface->w / number_of_frames_total_;
		height = loadedSurface->h;
		printf("Surface is created!\n");
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
		newTexture = SDL_CreateTextureFromSurface(rendr, loadedSurface);
		if (newTexture == NULL)
		{
		    cout << "Unable to create texture from" << PathToImage << " SDL_image Error: " <<  SDL_GetError() << endl;
		}
		SDL_FreeSurface(loadedSurface);
	}
	sprite = newTexture;
	x = x_;
	y = y_;
	number_of_frames_total = number_of_frames_total_;
	current_frame = 0;
	number_of_frames_move = number_of_frames_move_;
}

void Character::CollisionTestX(Level* Map)
{
	int i, j;
	for (i = y / Map->BlockSize; i < (y + height) / Map->BlockSize; i++){
		for (j = (x + collision_corrector) / Map->BlockSize; j < (x - collision_corrector + width) / Map->BlockSize; j++){
			switch (Map->LevelMap[i][j].Type)
			{
			case GROUND:
				if ((dx > 0)) x = j * Map->BlockSize - width + collision_corrector;
				if ((dx < 0)) x = j * Map->BlockSize + Map->BlockSize - collision_corrector;
				break;
			case BOX:
				if ((dx > 0) && Map->LevelMap[i][j].isEnable()) x = j * Map->BlockSize - width + collision_corrector;
				if ((dx < 0) && Map->LevelMap[i][j].isEnable()) x = j * Map->BlockSize + Map->BlockSize - collision_corrector;
				break;
			case LEITER:
				on_ladder = true;
				break;
			default:
				break;
			}
		}
	}
}

void Character::CollisionTestY(Level* Map)
{
	int i, j;
	for (i = y / Map->BlockSize; i < (y + height) / Map->BlockSize; i++){
		for (j = (x + collision_corrector) / Map->BlockSize; j < (x - collision_corrector + width) / Map->BlockSize; j++){

			on_ladder = false;
			switch (Map->LevelMap[i][j].Type)
			{
			case GROUND:
				if ((dy > 0)){
					y = i * Map->BlockSize - height;
					dy = 0;
					on_ground = true;
				}
				if ((dy < 0)){
					y = i * Map->BlockSize + Map->BlockSize;
					dy = 0;
				}
				break;
			case BOX:
				if ((dy > 0) && Map->LevelMap[i][j].isEnable()){
					y = i * Map->BlockSize - height;
					dy = 0;
					on_ground = true;
				}
				if ((dy < 0) && Map->LevelMap[i][j].isEnable()){
					Map->LevelMap[i][j].Kill();
					y = i * Map->BlockSize + Map->BlockSize;
					dy = 0;
				}
				break;
			case LEITER:
				on_ladder = true;
				break;
			default:
				on_ground = false;
				break;
			}
		}
	}
}

void Character::move(Level* karte_)
{
	if (is_life)
	{
		x += dx;
		CollisionTestX(karte_);
	}
	if (verticalMove)
	{
		y += dy;
		dy = 0;
	}
	else
	{
		if (!on_ground) dy = dy + 0.5;
		y += dy;
		on_ladder = false;
	}
	CollisionTestY(karte_);
}

void Character::draw(SDL_Renderer* rendr, int offsetX_)
{
	if (dx > 0)
	{
		move_direction_right = true;
		animation_is_on = true;
	}
	else if (dx < 0)
	{
		move_direction_right = false;
		animation_is_on = true;
	}
	else
	{
		animation_is_on = false;
	}
	if (++frame_counter >= frame_delay && animation_is_on && on_ground)
	{
		if (++current_frame > number_of_frames_move - 1)
		{
			current_frame = 0;
		}
		frame_counter = 0;
	}

	if (!on_ground && dy < 0)
	{
		current_frame = 8;
	}

	if (dx == 0 && on_ground)
	{
		current_frame = 9;
	}

	SDL_Rect clip;

	if (is_life)
	{
		clip.x = current_frame * width;
	}
	else
	{
		clip.x = 10 * width;
	}
	clip.y = 0;
	clip.w = width;
	clip.h = height;

	SDL_Rect renderQuad = {(int)(x - offsetX_), (int)y, width, height};
		renderQuad.w = clip.w;
		renderQuad.h = clip.h;

	if (move_direction_right)
	{
		SDL_RenderCopyEx(rendr, sprite, &clip, &renderQuad, 0, 0, SDL_FLIP_NONE);
	}
	else
	{
		SDL_RenderCopyEx(rendr, sprite, &clip, &renderQuad, 0, 0, SDL_FLIP_HORIZONTAL);
	}
	dx = 0;
}

void Character::death()
{
	//TODO: is_life = false;
	cout << "Pain!" << endl;
}


