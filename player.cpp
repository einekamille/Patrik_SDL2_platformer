#include "player.hpp"

Player::Player(void)
{
	animation_is_on = false;
	frame_counter = 0;
	frame_delay = 5;
	collision_corrector = 5;
	on_ladder = false;
	is_life = true;
}

Player::~Player()
{
}

