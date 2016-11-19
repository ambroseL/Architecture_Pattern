#include "BallObj.h"  // class implemented

/////////////// PUBLIC///////////////////////

//================= ���캯�� ====================
BallObj::BallObj():
EntityObj(),attack(1),speedState(Normal),isPermeat(false),sSpeed(b2Vec2(0, 0))
{
}// BallObj

BallObj::BallObj(PhysicsComponent* physicsComponent, GraphicsComponent* graphicsComponent, std::string* id, int attack, b2Vec2 bSpeed, SpeedState speedState, bool isPermeat):
EntityObj(physicsComponent, graphicsComponent, id),attack(attack),sSpeed(bSpeed),speedState(speedState),isPermeat(isPermeat)
{	
}// BallObj


BallObj::~BallObj()
{
}// ~BallObj

EntityObj* BallObj::Clone()								
{
	return new BallObj(this->getPhysicsComponent()->Clone(), this->getGraphicsComponent()->Clone(), new std::string(this->getID()->c_str()), this->attack, this->sSpeed, this->speedState, this->isPermeat);
}


//==============��Ĳ��� =====================

void BallObj::Reset()
{
}


//==============���Դ�ȡ =====================

const b2Vec2 BallObj::getInitialSpeed()
{
	SpeedState m = Slow;
	return sSpeed;
}

const int BallObj::getAttack()
{
	int attack = 0;
	attack = this->attack;
	return attack;
}

void BallObj::setAttack(int iAttack)
{
	this->attack = iAttack;
}

const float BallObj::getRadius()
{
	return getWidth();
}

void BallObj::setRadius(float fRadius)
{
	this->setHeight(fRadius);
	this->setWidth(fRadius);
}

//==============״̬��ѯ   =====================

const bool BallObj::getPermeat()
{
	return isPermeat;
}

void BallObj::setPermeat(bool isPermeat)
{
	this->isPermeat = isPermeat;
}


const SpeedState BallObj::getSpeedState()
{
	return speedState;
}

void BallObj::setSpeedState(SpeedState speedState)
{
	this->speedState = speedState;
}


