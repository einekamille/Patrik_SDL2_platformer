#define _CRT_SECURE_NO_WARNINGS
#include "map.hpp"

Block::Block()
{
	this->Enable = true;
	this->Type = NONE;
}

Block::~Block()
{
}

bool Block::isEnable()
{
	return Enable;
}

void Block::Kill()
{
	Enable = false;
	Type = NONE;
}

Level::Level(void)
{
}

Level::~Level()
{
}

void Level::loadTexture(SDL_Renderer* rendr)
{
	SDL_Texture *newTexture = NULL;

	SDL_Surface *loadedSurface = IMG_Load("resources/ground.bmp");
	if (loadedSurface == NULL)
	{
		cout << "Unable to load image! SDL_image Error: " <<  IMG_GetError() << endl;
	}
	else
	{
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
		newTexture = SDL_CreateTextureFromSurface(rendr, loadedSurface);
		if (newTexture == NULL)
		{
		    cout << "Unable to create texture from! SDL_image Error: " <<  SDL_GetError() << endl;
		}
		SDL_FreeSurface(loadedSurface);
	}
	texture[BRICK] = newTexture;

	loadedSurface = IMG_Load("resources/break-brick.bmp");
	if (loadedSurface == NULL)
	{
	    cout << "Unable to load image! SDL_image Error: " <<  IMG_GetError() << endl;
	}
	else
	{
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
		newTexture = SDL_CreateTextureFromSurface(rendr, loadedSurface);
		if (newTexture == NULL)
		{
		    cout << "Unable to create texture from! SDL_image Error: " <<  SDL_GetError() << endl;

		}
		SDL_FreeSurface(loadedSurface);
	}
	texture[MINE] = newTexture;

	loadedSurface = IMG_Load("resources/leiter.bmp");
	if (loadedSurface == NULL)
	{
	    cout << "Unable to load image! SDL_image Error: " <<  IMG_GetError() << endl;
	}
	else
	{
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
		newTexture = SDL_CreateTextureFromSurface(rendr, loadedSurface);
		if (newTexture == NULL)
		{
			cout << "Unable to create texture from! SDL_image Error: " <<  SDL_GetError() << endl;
		}
		SDL_FreeSurface(loadedSurface);
	}
	texture[LEITERS] = newTexture;

	BlockSize = 32;
}

void Level::load_map(SDL_Renderer* rendr, char* PathToMap)
{
	FILE* map_File;
	int i = 0, j = 0;
	char temp_byte;
	map_File = fopen(PathToMap, "r");

	while ((temp_byte = getc(map_File)) != EOF){
		if (temp_byte == '\n'){
			i++;
			j = 0;
		}else{
			switch (temp_byte)
			{
			case '#':
				LevelMap[i][j].Type = GROUND;
				break;
			case '@':
				LevelMap[i][j].Type = BOX;
				break;
			case '$':
				LevelMap[i][j].Type = LEITER;
				break;
			default:
				LevelMap[i][j].Type = NONE;
				break;
			}
			j++;
		}
	}
	Width = j + 1;
	Height = i + 1;
	fclose(map_File);
	loadTexture(rendr);
}

void Level::draw(SDL_Renderer* rendr, int offsetX_)
{
	for (int i = 0; i < Height; i++){
		for (int j = 0; j < Width; j++){
			SDL_Rect renderQuad = {j * BlockSize - offsetX_, i * BlockSize, BlockSize, BlockSize};
			switch (LevelMap[i][j].Type)
			{
			case GROUND:
				SDL_RenderCopy(rendr, texture[BRICK], NULL, &renderQuad);
				break;
			case BOX:
				SDL_RenderCopy(rendr, texture[MINE], NULL, &renderQuad);
				break;
			case LEITER:
				SDL_RenderCopy(rendr, texture[LEITERS], NULL, &renderQuad);
				break;
			default:
				break;
			}
		}
	}
}

