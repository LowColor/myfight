#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace sf;

class Skills
{
public:
	virtual ~Skills() {}
	Sprite sprite;
protected:
	virtual void activate() = 0;

	Sprite getHeroSprite() {
		
	}

	void move(double x, double y) {
		sprite.setPosition(x,y);
	}

	void playSound(Sound sound, double volume) {
		// Здесь код...
	}

	void setSprite(Image& img, int count) {
		// Здесь код...
	}
};


class Attack : public Skills {
public:
	 void activate() {
		move(100,100);
	}
};
/*
if (Keyboard::isKeyPressed(Keyboard::Numpad5))
{

	IsAttacking = 1;

	if ((AttackFrame<4) && (IsAttacking == 1))
	{
		AttackFrame += 0.005*time / 500;

		if (AttackFrame<4)
		{
			switch (lastside)
			{
			case 1:warrior_player_sprite.setTextureRect(IntRect(216, 360 + 72 * int(AttackFrame), -72, 72)); break;
			case 2:warrior_player_sprite.setTextureRect(IntRect(144, 360 + 72 * int(AttackFrame), 72, 72)); break;
			case 3:warrior_player_sprite.setTextureRect(IntRect(0, 360 + 72 * int(AttackFrame), 72, 72)); break;
			case 4:warrior_player_sprite.setTextureRect(IntRect(288, 360 + 72 * int(AttackFrame), 72, 72)); break;
			case 5:warrior_player_sprite.setTextureRect(IntRect(144, 360 + 72 * int(AttackFrame), -72, 72)); break;
			case 6:warrior_player_sprite.setTextureRect(IntRect(72, 360 + 72 * int(AttackFrame), 72, 72)); break;
			case 7:warrior_player_sprite.setTextureRect(IntRect(288, 360 + 72 * int(AttackFrame), -72, 72)); break;
			case 8:warrior_player_sprite.setTextureRect(IntRect(216, 360 + 72 * int(AttackFrame), 72, 72)); break;
			}
		}
		else
		{
			switch (lastside)
			{
			case 1:warrior_player_sprite.setTextureRect(IntRect(216, 0, -72, 72)); break;
			case 2:warrior_player_sprite.setTextureRect(IntRect(144, 0, 72, 72)); break;
			case 3:warrior_player_sprite.setTextureRect(IntRect(0, 0, 72, 72)); break;
			case 4:warrior_player_sprite.setTextureRect(IntRect(288, 0, 72, 72)); break;
			case 5:warrior_player_sprite.setTextureRect(IntRect(144, 0, -72, 72)); break;
			case 6:warrior_player_sprite.setTextureRect(IntRect(72, 0, 72, 72)); break;
			case 7:warrior_player_sprite.setTextureRect(IntRect(288, 0, -72, 72)); break;
			case 8:warrior_player_sprite.setTextureRect(IntRect(216, 0, 72, 72)); break;
			}

			AttackFrame = 0;

		}
	}
}

if (!Keyboard::isKeyPressed(Keyboard::Numpad5))
{
	if (IsAttacking == 1)
	{
		if ((AttackFrame<4) && (IsAttacking == 1))
		{
			AttackFrame += 0.005*time / 500;

			if (AttackFrame<4)
			{
				switch (lastside)
				{
				case 1:warrior_player_sprite.setTextureRect(IntRect(216, 360 + 72 * int(AttackFrame), -72, 72)); break;
				case 2:warrior_player_sprite.setTextureRect(IntRect(144, 360 + 72 * int(AttackFrame), 72, 72)); break;
				case 3:warrior_player_sprite.setTextureRect(IntRect(0, 360 + 72 * int(AttackFrame), 72, 72)); break;
				case 4:warrior_player_sprite.setTextureRect(IntRect(288, 360 + 72 * int(AttackFrame), 72, 72)); break;
				case 5:warrior_player_sprite.setTextureRect(IntRect(144, 360 + 72 * int(AttackFrame), -72, 72)); break;
				case 6:warrior_player_sprite.setTextureRect(IntRect(72, 360 + 72 * int(AttackFrame), 72, 72)); break;
				case 7:warrior_player_sprite.setTextureRect(IntRect(288, 360 + 72 * int(AttackFrame), -72, 72)); break;
				case 8:warrior_player_sprite.setTextureRect(IntRect(216, 360 + 72 * int(AttackFrame), 72, 72)); break;
				}
			}
			else
			{
				switch (lastside)
				{
				case 1:warrior_player_sprite.setTextureRect(IntRect(216, 0, -72, 72)); break;
				case 2:warrior_player_sprite.setTextureRect(IntRect(144, 0, 72, 72)); break;
				case 3:warrior_player_sprite.setTextureRect(IntRect(0, 0, 72, 72)); break;
				case 4:warrior_player_sprite.setTextureRect(IntRect(288, 0, 72, 72)); break;
				case 5:warrior_player_sprite.setTextureRect(IntRect(144, 0, -72, 72)); break;
				case 6:warrior_player_sprite.setTextureRect(IntRect(72, 0, 72, 72)); break;
				case 7:warrior_player_sprite.setTextureRect(IntRect(288, 0, -72, 72)); break;
				case 8:warrior_player_sprite.setTextureRect(IntRect(216, 0, 72, 72)); break;
				}
				AttackFrame = 0;
				IsAttacking = 0;
			}
		}
	}
}*/

for (it = entities.begin(); it != entities.end(); it++)//проходимся по эл-там списка
{
	if ((*it)->getRect().intersects(p.getRect()))//если прямоугольник спрайта объекта пересекается с игроком
	{
		if ((*it)->name == "attack") {
			if ((*it)->dx>0)//если атака вправо
			{
				(*it)->x = p.x - (*it)->w; //отталкиваем 
				(*it)->dx = 0;//останавливаем
				(*it)->life -= 10;
			}
			if ((*it)->dx < 0)//если атака влево
			{
				(*it)->x = p.x + p.w; //отталкиваем вправо
				(*it)->dx = 0;//останавливаем
				(*it)->life -= 10;
			}
		}
	}
}