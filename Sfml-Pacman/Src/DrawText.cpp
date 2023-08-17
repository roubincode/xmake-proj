#include <cmath>
#include <SFML/Graphics.hpp>

#include "include/DrawText.hpp"
#include "include/Global.hpp"

void draw_text(bool i_center, bool i_top, bool i_left, const std::string& i_text, sf::RenderWindow& i_window)
{
	short character_x;
	short character_y;
	unsigned char character_width;

	sf::Sprite character_sprite;

	sf::Texture font_texture;
	font_texture.loadFromFile("Resources/Images/Font.png");

	//There are 96 characters in the font texture.
	character_width = font_texture.getSize().x / 96;

	character_sprite.setTexture(font_texture);

	if (1 == i_center)
	{
		//I spent HOURS trying to make this work.
		//If you know any better way of doing this, please tell me.
		character_x = static_cast<short>(round(0.5f * (CELL_SIZE * MAP_WIDTH - character_width * i_text.substr(0, i_text.find_first_of('\n')).size())));
		character_y = static_cast<short>(round(0.5f * (CELL_SIZE * MAP_HEIGHT - FONT_HEIGHT * (1 + std::count(i_text.begin(), i_text.end(), '\n')))));
	}
	else
	{
		if (1 == i_top)
		{
			character_y = 0;
		}
		else
		{
			character_y = CELL_SIZE * MAP_HEIGHT - FONT_HEIGHT * (std::count(i_text.begin(), i_text.end(), '\n'));
		}

		if (1 == i_left)
		{
			character_x = 0;
		}
		else
		{
			character_x = CELL_SIZE * MAP_WIDTH - character_width * i_text.substr(0, i_text.find_first_of('\n')).size();
		}
		
		//character_x = 0;
	}
	
	for (std::string::const_iterator a = i_text.begin(); a != i_text.end(); a++)
	{
		if ('\n' == *a)
		{
			if (1 == i_center)
			{
				//I still don't understand what I wrote here.
				character_x = static_cast<short>(round(0.5f * (CELL_SIZE * MAP_WIDTH - character_width * i_text.substr(1 + a - i_text.begin(), i_text.find_first_of('\n', 1 + a - i_text.begin()) - (1 + a - i_text.begin())).size())));
			}
			else
			{
				character_x = 0;
			}
			character_y += FONT_HEIGHT;
			continue;
		}

		character_sprite.setPosition(character_x, character_y);
		//The font texture begins with a space character, which is the 32nd character.
		character_sprite.setTextureRect(sf::IntRect(character_width * (*a - 32), 0, character_width, FONT_HEIGHT));

		character_x += character_width;

		i_window.draw(character_sprite);
	}
}