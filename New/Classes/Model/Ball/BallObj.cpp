#include "BallObj.h"  // class implemented

/////////////// PUBLIC///////////////////////

//================= 构造函数 ====================
BallObj::BallObj():
EntityObj(),attack(1),speedState(Normal),isPermeat(false), initialSpeed(b2Vec2(0, 0)),constantSpeed(b2Vec2(0, 0))
{
}// BallObj

BallObj::BallObj(PhysicsComponent* physicsComponent, GraphicsComponent* graphicsComponent, std::string* id, int attack, b2Vec2 bSpeed, SpeedState speedState, bool isPermeat):
EntityObj(physicsComponent, graphicsComponent, id),attack(attack),initialSpeed(bSpeed),constantSpeed(bSpeed),speedState(speedState),isPermeat(isPermeat)
{	
}// BallObj


BallObj::~BallObj()
{
}// ~BallObj

EntityObj* BallObj::Clone()								
{
	return new BallObj(this->getPhysicsComponent()->Clone(), this->getGraphicsComponent()->Clone(), new std::string(this->getID()->c_str()), this->attack, this->initialSpeed, this->speedState, this->isPermeat);
}


//==============类的操作 =====================

void BallObj::Reset()
{
}


//==============属性存取 =====================

const b2Vec2 BallObj::getInitialSpeed()
{
	return this->initialSpeed;
}

void BallObj::setInitialSpeed(b2Vec2 initialSpeed)
{
	this->initialSpeed = initialSpeed;
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

b2Vec2 BallObj::getConstantSpeed()
{
	return this->constantSpeed;
}

void BallObj::setConstantSpeed(b2Vec2 speed)
{
	this->constantSpeed = speed;
}

//==============状态查询   =====================

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


