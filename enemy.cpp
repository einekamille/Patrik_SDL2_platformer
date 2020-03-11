#include "enemy.hpp"

Enemy::Enemy(void)
{
	animation_is_on = false;
	frame_counter = 0;
	frame_delay = 5;
	collision_corrector = 5;
	on_ladder = false;
	attack = false;
	dx = -0.7;
	ExAnimCount = 0;
	jumpFlag = false;
}


Enemy::~Enemy()
{
}

void Enemy::CollisionTestX(Level* Map)
{
	int i, j;
	for (i = y / Map->BlockSize; i < (y + height) / Map->BlockSize; i++)
	{
		for (j = (x + collision_corrector) / Map->BlockSize; j < (x - collision_corrector + width) / Map->BlockSize; j++)
		{
			switch (Map->LevelMap[i][j].Type)
			{
			case GROUND:
				if ((dx > 0)) x = j * Map->BlockSize - width + collision_corrector;
				if ((dx < 0)) x = j * Map->BlockSize + Map->BlockSize - collision_corrector;
				if (TestLowWall(Map) && on_ground)
				{
					dy = -8;

				}
				else if (on_ground && !TestLowWall(Map))
				{
					dx = -dx;
				}
				break;
			case BOX:
				if ((dx > 0) && Map->LevelMap[i][j].isEnable()) x = j * Map->BlockSize - width + collision_corrector;
				if ((dx < 0) && Map->LevelMap[i][j].isEnable()) x = j * Map->BlockSize + Map->BlockSize - collision_corrector;
				dx = -dx;
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



void Enemy::move(Level* map)
{
	if (!attack) x += dx;
	CollisionTestX(map);

	if(!on_ground) dy = dy + 0.5;

	y += dy;

	on_ground = false;
	on_ladder = false;

	CollisionTestY(map);
}

void Enemy::draw(SDL_Renderer* rendr, int offsetX_)
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
		current_frame = 4;
	}

	if (dx == 0 && on_ground)
	{
		current_frame = 9;
	}

	SDL_Rect clip;

	if (!attack)
	{
		clip.x = current_frame * width;
	}
	else
	{
		clip.x = (number_of_frames_move + ExAnimCount) * width;
		ExAnimCount++;
		if (ExAnimCount > 6)
		{
			ExAnimCount = 0;
			attack = false;
		}
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
}

bool Enemy::CollisionWithPlayer(Player player)
{
	if ((x + width - collision_corrector > player.x) && (y + height - collision_corrector > player.y) && (x + collision_corrector < player.x + player.width) && (y + collision_corrector < player.y + player.height))
	{
		Fight(player);
		return true;
	}
	else return false;
}

void Enemy::Fight(Player player)
{
	if (player.is_life)
	{
		if (x > player.x)
		{
			if (move_direction_right) dx = -dx;
		}
		else
		{
			if (!move_direction_right) dx = -dx;
		}
		attack = true;
	}
}

bool Enemy::TestLowWall(Level *Map)
{
	int i, j;
	if (!move_direction_right)
	{
		j = (x - Map->BlockSize / 2) / Map->BlockSize;
	}
	else
	{
		j = (x + width + Map->BlockSize / 2) / Map->BlockSize;
	}
	i = (y + height - Map->BlockSize * 2 - Map->BlockSize / 2) / Map->BlockSize;
	if (Map->LevelMap[i][j].Type == NONE) return true;
	else return false;
}

void Enemy::AI()
{

}

