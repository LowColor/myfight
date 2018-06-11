#include <SFML/Graphics.hpp>

sf::View view;
using namespace sf;



void setPlayerCoordinateForView(float x, float y) { 
	float tempX = x; float tempY = y;

	if (x < 200) tempX = 201;//левый край
	if (x > 1247) tempX = 1366;//правый край
	if (y < 100) tempY = 390;//верхнюю сторону
	if (y > 100) tempY = 700;//нижнюю стороню.для новой карты

	view.setCenter(tempX+200, tempY); 
}



std::ostringstream time;   
time << Clock.getTime();	
text.setString(time.str());
text.setPosition(view.getCenter().x + 165, view.getCenter().y - 200);
window.draw(text);

















#include "Object1.h"


Object1::Object1(void) { data(); }
Object1::~Object1(void) { }

void Object1::data(void)
{
	round.data();
	text1.setOffset(sf::Vector2f(0, -50));
	//Object1* target = NULL; // Цель не выделена
	//CHAR = new character();
	status = 0;
	vecSpeed = sf::Vector2f(0, 0);
	shadow.loadFromFile("shadow.png");
	shadow.setScale(1, 0.5);

	lineHP.loadFromFile("test/hp.png");
	lineHP.setScale(100, 1);
	lineHP.setOriginNum(4);

	lineMP.loadFromFile("test/mp.png");
	lineMP.setScale(100, 1);
	lineMP.setOriginNum(4);

	nickname.setOffset(-50, -60);
}
////////////////////////////////////
////////////////////////////////////
bool Object1::loadFromFile(std::string filename)
{
	if (!image.loadFromFile(filename))
	{
		cout << "Object1::loadFromFile(" << filename << ") == false" << endl;
		return false;
	}

	return true;
}
void Object1::draw(sf::RenderWindow* window)
{
	shadow.draw(window);
	image.draw(window);
	lineHP.draw(window);
	lineMP.draw(window);
	text1.draw(window);
	lineAttack.draw(window);
	nickname.draw(window);
}
void Object1::setPosition(float x, float y)
{
	shadow.setPosition(x, y + 32);
	image.setPosition(x, y);
	lineHP.setPosition(x - 50, y - 35);
	lineMP.setPosition(x - 50, y - 30);
	lineAttack.setPosition(x - 50, y - 40);
	nickname.setPosition(x, y);
}
sf::Vector2f Object1::getPosition()
{
	return image.getPosition();
}
void Object1::move(float dx, float dy)
{
	image.move(dx, dy);
	shadow.move(dx, dy);
	lineHP.move(dx, dy);
	lineMP.move(dx, dy);
	lineAttack.move(dx, dy);
	nickname.move(dx, dy);
}
void Object1::move2(float speed, float angle)
{
	image.move2(speed, angle);
	shadow.move2(speed, angle);
	lineHP.move2(speed, angle);
	lineMP.move2(speed, angle);
	lineAttack.line1.move2(speed, angle);
	lineAttack.line2.move2(speed, angle);
}

// 0 - ничего
// 1 - двигаемся
// 2 - наступил на центр клетки, надо проверить след. клетку в Game
void Object1::behavior(float time)
{
	lineAttack.wave(time);
	//cout << "status=" <<status<<endl;
	switch (status)
	{
	case 1:
		behavior_movement(time);
		break;
	case 2:
		behavior_follow_target(time);
		break;
	case 3:
		behavior_attack(time);
		break;
	}
	update_hp(false, 2 * time);
	update_mp(false, 1 * time);
	text1.behavior(time);
}
void Object1::behavior_movement(float time)
{
	// Если дистанция до точки назначения больше перемещения
	if (round.distanceCur > 100 * time)
		//if(round.distanceCur > CHAR->getValue(2)*time)
	{
		move(vecSpeed.x*time, vecSpeed.y*time);
		round.update(image.getPosition().x, image.getPosition().y); // Обновляем путь
		image.shift_frame(time);
	}
	// Иначе дистанция до точки назначения меньше перемещения
	else
	{
		// Создаём новые координаты
		float x = round.vecPoint[2].x;
		float y = round.vecPoint[2].y;
		// Встаём в новые координаты
		setPosition(x, y);
		// Корректировка тайлсета
		image.setNumFrameWcur(2);

		if (!nextPos())
			status = 0;
	}
}
// Преследование цели
void Object1::behavior_follow_target(float time)
{
	/*
	// Если цель есть
	if(target != NULL)
	{
	// Определяем дистанцию до цели
	float d = distance(getPosition().x, getPosition().y, target->getPosition().x,target->getPosition().y);
	// Дистанция для атаки
	float d2 = CHAR->getValue(43) + CHAR->getValue(44) + target->CHAR->getValue(43);
	// Если до цели не дотянуться
	if(d > d2)
	{
	// надо к ней двигаться

	// доступное перемещение
	float d3 = CHAR->getValue(2)*time;

	// если сократить дистанцию перемещением и всё равно не достать
	if(d - d3 > d2)
	{
	//move d3
	newTargetMove(2, target->getPosition().x,target->getPosition().y);
	move2(d3, round.angle);
	}
	else
	{
	// если достать реально
	float d4 = d - d2;
	newTargetMove(2, target->getPosition().x,target->getPosition().y);
	move2(d4, round.angle);
	// attack
	status = 3;
	}
	}
	else
	{
	behavior_attack(time);
	status = 3;
	}
	}
	*/
}
void Object1::behavior_attack(float time)
{
	if (lineAttack.attack(time) == true)
	{
		int damage = myRand1(50 - 15, 50 + 15);
		//target->update_hp(true, -1*damage);
		status = 2;
	}
}

void Object1::behavior_stop()
{
	if (status == 3)
		lineAttack.cancelAttack();
	else
		newTargetMove(1, getPosition().x, getPosition().y);
}
// Заносит данные в round и задаёт speedX и speedY
void Object1::newTargetMove(int setstatus, float x, float y)
{
	round.newPoint(image.x, image.y, x, y);
	float angle = round.angle;
	// поворот спрайта
	//if(isRotate == true) 
	//	sprite.setRotation(angle);


	//if(isShiftFrame == true)
	//{

	if (0 <= angle && angle <= 0 + 45 || 270 + 45 <= angle && angle <= 360)
		image.setNumFrameHcur(4);
	else if (90 - 45 < angle && angle <  90 + 45)
		image.setNumFrameHcur(3);
	else if (180 - 45 < angle && angle < 180 + 45)
		image.setNumFrameHcur(1);
	else if (270 - 45 < angle && angle < 270 + 45)
		image.setNumFrameHcur(2);
	//}

	float speedX = mySin(angle) * 100;//*CHAR->getValue(2);
	float speedY = -1 * myCos(angle) * 100;//*CHAR->getValue(2);

	status = setstatus;

	vecSpeed = sf::Vector2f(speedX, speedY);
}

void Object1::update_hp(bool flag, float value)
{
	int hpc = 8;
	int hpm = 5;
	//CHAR->setDValue(hpc, value);
	//CHAR->getValue(hpc);
	//if(CHAR->getValue(hpc) <= 0)                  CHAR->setValue(hpc, 0);
	//if(CHAR->getValue(hpc) > CHAR->getValue(hpm)) CHAR->setValue(hpc, CHAR->getValue(hpm));
	//lineHP.setScale(100*CHAR->getValue(hpc)/CHAR->getValue(hpm), 1);
	if (flag == true)
	{
		if (value < 0)
			text1.add(getPosition(), -10, 0, intToString(value), sf::Color(204, 0, 0));
		else
			text1.add(getPosition(), -30, 0, "+" + intToString(value), sf::Color(0, 204, 0));
	}
}

void Object1::update_mp(bool flag, float value)
{
	int mpc = 9;
	int mpm = 6;
	//CHAR->setDValue(mpc,value);
	//if(CHAR->getValue(mpc) <= 0) CHAR->setValue(mpc, 0);
	//if(CHAR->getValue(mpc) > CHAR->getValue(mpm)) CHAR->setValue(mpc, CHAR->getValue(mpm));
	//lineMP.setScale(100*CHAR->getValue(mpc)/CHAR->getValue(mpm), 1);
	if (flag == true)
	{
		if (value < 0)
			text1.add(getPosition(), 10, 0, intToString(value), sf::Color(0, 0, 204));
		else
			text1.add(getPosition(), 30, 0, "+" + intToString(value), sf::Color(0, 0, 204));
	}
}
/*
void Object1::setCharacter(std::vector<BaseChar*> &vec)
{
CHAR = new character(vec);

CHAR->add(2,NULL,100); // speed
CHAR->add(5,NULL,1000); // hp
CHAR->add(6,NULL,100); // mp
CHAR->add(8,NULL,1000); // hp
CHAR->add(9,NULL,100); // mp
CHAR->add(11,NULL,2);  // hp reg
CHAR->add(12,NULL,1);  // mp reg
CHAR->add(20,NULL,5);
CHAR->add(43,NULL,32); // R tela
CHAR->add(44,NULL,16); // R attack sword
CHAR->add(45,NULL,100); // R attack gun
}
void Object1::addChar(character* char_)
{
character* c = new character(*char_);
int size = char_->vecBaseChar.size();
//cout << "char_->vecBaseChar.size() = " << size << endl;
for(int i=0; i<char_->vecBaseChar.size(); i++)
{
//cout<<"i="<<i<<endl;
if(c->vecId[i] == 8)
{
//cout<<"c->vecId[i] == 8" << endl;
//cout << "c->vecValue[i] == "<< c->vecValue[i] << endl;
update_hp(true, c->vecValue[i]);
c->vecValue[i] = 0;
}
if(c->vecId[i] == 9)
{
update_mp(true, c->vecValue[i]);
c->vecValue[i] = 0;
}
}
CHAR->addChar(c);
}
void Object1::setChar(character* CHAR)
{
//cout << "setChar()" << endl;
this->CHAR = CHAR;
}

void Object1::setRoundCell(std::vector<_Cell*> vec)
{
vecCells = vec;
if(vec.size() != 0)
newTargetMove(1, vec[0]->getPosition().x, vec[0]->getPosition().y);
}
*/
bool Object1::nextPos()
{
	//if(vecCells.size() != 0)
	//	vecCells.erase(vecCells.begin());
	//if(vecCells.size() != 0)
	//{
	//	newTargetMove(1, vecCells[0]->getPosition().x, vecCells[0]->getPosition().y);
	//	return true;
	//}

	return false;
}
//05.04.2017
void Object1::set_nickname(std::string nickname)
{
	this->nickname.setString(nickname);
}