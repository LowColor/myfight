#include <sstream>
#include <list>
#include "level.h"
#include "skills.h"

















////////////////////////////////////����� �����-��������//////////////////////////
class Entity {
public:
	std::vector<Object> obj;//������ �������� �����
	float dx, dy, x, y, speed,moveTimer;
	int w,h,health;
	bool life, isMove, onGround;
	Texture texture;
	Sprite sprite;
	String name;
	Entity(Image &image, String Name, float X, float Y, int W, int H){
		x = X; y = Y; w = W; h = H; name = Name; moveTimer = 0;
		speed = 0; health = 100; dx = 0; dy = 0;
		life = true; onGround = false; isMove = false;
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		sprite.setOrigin(w / 2, h / 2);
	}


	FloatRect getRect(){//�-��� ��������� ��������������. ��� �����,������� (���,�����).
		return FloatRect(x, y, w, h);//��� �-��� ����� ��� �������� ������������ 
	}
};
////////////////////////////////////////////////////����� ������////////////////////////
class PlayerOne :public Entity {
public:

	enum { left, right, up, down, jump, stay } state;
	int playerScore;
	float CurrentFrame;//variable for anima
	int c = 0;
	

	PlayerOne(Image &image, String Name, Level &lev, float X, float Y, int W, int H) :Entity(image, Name, X, Y, W, H ){
		   playerScore = 0; state = stay; obj = lev.GetAllObjects();//��������������.�������� ��� ������� ��� �������������� ��������� � ������
		   CurrentFrame=0;
		   if (Name == "player"){
			   sprite.setTextureRect(IntRect(-5,0, w, h));//x,y - ���������� �� ����� ��� �������(������������� 0-0, 33-0, 65-0 � ��..
		   }
	   }

	void voice() const{
			   std::cout<<"I'm Player!!"<<std::endl;
    }
	//animation of player
	void AnimaPlayer(float time){
		
		switch (state)
		   {
		   case right: CurrentFrame += 0.015*time;
			   sprite.setScale(2, 2);
			   if (CurrentFrame >= 8) CurrentFrame -= 8;
			   switch ((int(CurrentFrame))) {
			   case 0:sprite.setTextureRect(IntRect(0, 65, 64, 64)); break;
			   case 1:sprite.setTextureRect(IntRect(75, 65, 64, 64)); break;
			   case 2:sprite.setTextureRect(IntRect(150, 65, 64, 64)); break;
			   case 3:sprite.setTextureRect(IntRect(227, 65, 64, 64)); break;
			   case 4:sprite.setTextureRect(IntRect(304, 65, 64, 64)); break;
			   case 5:sprite.setTextureRect(IntRect(383, 65, 64, 64)); break;
			   case 6:sprite.setTextureRect(IntRect(461, 65, 64, 64)); break;
			   case 7:sprite.setTextureRect(IntRect(536, 65, 64, 64)); break;
			   }
			   break;
		   case left:CurrentFrame += 0.005*time;
			   sprite.setScale(-2, 2);
			   if (CurrentFrame >= 8) CurrentFrame -= 8;
			   switch ((int(CurrentFrame))) {
			   case 0:sprite.setTextureRect(IntRect(0, 65, 64, 64));  break;
			   case 1:sprite.setTextureRect(IntRect(75, 65, 64, 64));  break;
			   case 2:sprite.setTextureRect(IntRect(150, 65, 64, 64)); break;
			   case 3:sprite.setTextureRect(IntRect(227, 65, 64, 64)); break;
			   case 4:sprite.setTextureRect(IntRect(304, 65, 64, 64)); break;
			   case 5:sprite.setTextureRect(IntRect(383, 65, 64, 64)); break;
			   case 6:sprite.setTextureRect(IntRect(461, 65, 64, 64)); break;
			   case 7:sprite.setTextureRect(IntRect(536, 65, 64, 64)); break;
			   }
			   break;
		   case up: CurrentFrame += 0.005*time;
			   if (CurrentFrame >= 8) CurrentFrame -= 8;
			   switch ((int(CurrentFrame))) {

			   }
			   break;
		   case down: CurrentFrame += 0.005*time;
			   if (CurrentFrame >= 8) CurrentFrame -= 8;
			   switch ((int(CurrentFrame))) {
			
			   }
			   break;
		   case jump: CurrentFrame += 0.05*time;
			   if (CurrentFrame >= 8) CurrentFrame -= 8;
			   switch ((int(CurrentFrame))) {break;
			   case 0:sprite.setTextureRect(IntRect(7, 151, 64, 64)); sprite.setPosition(sprite.getPosition().x, sprite.getPosition().y + 10);  break;
			   case 1:sprite.setTextureRect(IntRect(75, 151, 64, 64));  break;
			   case 2:sprite.setTextureRect(IntRect(136, 151, 64, 64)); break;
			   //case 3:sprite.setTextureRect(IntRect(196, 151, 64, 64)); break;
			   //case 4:sprite.setTextureRect(IntRect(264, 151, 64, 64)); break;
			   //case 5:sprite.setTextureRect(IntRect(333, 151, 64, 64)); break;
			   //case 6:sprite.setTextureRect(IntRect(405, 151, 64, 64));  break;
			   }
			   break;

		   case stay:sprite.setScale(2, 2); sprite.setTextureRect(IntRect(0, 0, 64, 64)); break;
		}
		}

	void control(Event e){
	
		   if (Keyboard::isKeyPressed){
			   if (e.KeyReleased && e.key.code == sf::Keyboard::Space)
			   {
				   std::cout << "released space" << c++<< std::endl;
			   }
			   if (Keyboard::isKeyPressed(Keyboard::Left)) {
				   state = left; 
				   speed = 0.5;
				   AnimaPlayer(5);
			   }
			   if (Keyboard::isKeyPressed(Keyboard::Right)) {
				   state = right; 
				   speed = 0.5;
				   AnimaPlayer(5);
			   }

			   if ((Keyboard::isKeyPressed(Keyboard::Up))) {
				   state = up; 
				   speed=-0.1;
				   AnimaPlayer(5);
			   }

			   if (Keyboard::isKeyPressed(Keyboard::Down)) {
				   state = down; 
				   speed = -0.1;
				   AnimaPlayer(5);
			   }
			   if (Keyboard::isKeyPressed(Keyboard::Space) && (onGround)) {
				   std::cout << "jump!!" << c++<<std::endl;
				   state = jump; 
				   dy = -0.6;  
				   AnimaPlayer(5);

			   }
		   }
		   else {
			   state = stay;
		   }
		  
	   } 

	void checkCollisionWithMap(float Dx, float Dy)
	   {

		for (int i = 0; i<obj.size(); i++)//���������� �� ��������
			if (getRect().intersects(obj[i].rect))//��������� ����������� ������ � ��������
			{
				if (obj[i].name == "wall")//���� ��������� �����������
				{
					if (Dy>0) { y = obj[i].rect.top - h;  dy = 0; onGround = true; }
					if (Dy<0) { y = obj[i].rect.top + obj[i].rect.height;   dy = 0; }
					if (Dx>0) { x = obj[i].rect.left - w; }
					if (Dx<0) { x = obj[i].rect.left + obj[i].rect.width; }
				}
			}
	   }
	    
	void update(float time, Event e)
	   {
	       
		control(e);//������� ���������� ����������
		switch (state)//��� �������� ��������� �������� � ����������� �� ���������
		{
		case right: dx = speed; break;//��������� ���� ������
		case left: dx = -speed; break;//��������� ���� �����
		case up: break;//����� ��������� �������� ������ (�������� �� ��������)
		case down: dx = 0; break;//����� ��������� �� ����� ������ ��������� (�������� �� ��������)
		case stay: dy = 0; onGround = true; break;//� ����� ����
		case jump: dy = -speed; 
			//std::cout << "on Ground is: " << onGround << std::endl;
			//std::cout << "dy = " << y << std::endl;
			break;
		}
		x += dx * time;
		checkCollisionWithMap(dx, 0);//������������ ������������ �� �
		y += dy * time;
		checkCollisionWithMap(0, dy);//������������ ������������ �� Y
		sprite.setPosition(x + w / 2, y + h / 2); //������ ������� ������� � ����� ��� ������
		if (health <= 0) { life = false; }
		if (!isMove) { speed = 0; }
		if (!onGround) { dy = dy + 0.0015*time; }//������� � ����� ������ ����������� � �����
		dy = dy + 0.0015*time;//������ ���������� � �����
		if (life) { setPlayerCoordinateForView(x, y); }
	   } 

	void attack() {
		Attack a;
		a.activate();
	}
};///����� ������

