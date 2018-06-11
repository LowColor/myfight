#include <SFML/Graphics.hpp>
#include "view.h"
#include <iostream>
#include <sstream>
#include "mission.h"
#include "iostream"
#include <vector>
#include <list>
#include <string>
#include <map>
#include "entity.h"



int main()
{
	sf::RenderWindow window(sf::VideoMode(640, 480), "martial world v 0.01");
	view.reset(sf::FloatRect(0, 0, 640, 480));

	//Keyboard klava = new Keyboard();

	Level lvl;//������� ��������� ������ �������
	lvl.LoadFromFile("map.tmx");//��������� � ���� �����, ������ ������ � ������� ������� �� �� ����������.


	Image heroImage;
	heroImage.loadFromFile("img/ichigo_sprite.png");
	heroImage.createMaskFromColor(Color(0, 128, 0));//��� ����� �� ����� � ����������� �����
	
	Image back;
	back.loadFromFile("img/back.jpg");
	Texture btext;
	Sprite backSprite;
	btext.loadFromImage(back);
	backSprite.setTexture(btext);

	Image easyEnemyImage;
	easyEnemyImage.loadFromFile("img/hero.png");
	easyEnemyImage.createMaskFromColor(Color(255, 0, 0));//��� ����� �� ����� � ����������� �����


	Object player = lvl.GetObject("player");//������ ������ �� ����� �����.������ ���������� ������ � ������ ��� ������ ����
	Object easyEnemyObject = lvl.GetObject("easyEnemy");//������ ������� ����� �� ����� �����





	PlayerOne p(heroImage, "player", lvl, player.rect.left, player.rect.top, 64, 64);//�������� ���������� �������������� player �� ����� � ���������� ������ ������
	
	Clock clock;
	while (window.isOpen())
	{

		float time = clock.getElapsedTime().asMicroseconds();

		clock.restart();
		time = time / 800;

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			
		}
		p.update(time, event);

		window.setView(view);
		window.clear(Color(77, 83, 140));
		lvl.Draw(window);//������ ����� �����
		window.draw(backSprite);



		window.draw(p.sprite);
		window.display();
	}
	return 0;
}
