#include "SpeedBrick.h"// class implemented

/////////////// PUBLIC///////////////////////

//================= 构造函数 ====================

SpeedBrick::SpeedBrick():BrickObj(),isFasten(true)
{
}// SpeedBrick

SpeedBrick::SpeedBrick(PhysicsComponent* physicsComponent, GraphicsComponent* graphicsComponent, std::string* id, bool bFasten, int iHP):
BrickObj(physicsComponent, graphicsComponent, id, iHP), isFasten(bFasten)
{
}// SpeedBrick

SpeedBrick::~SpeedBrick()
{
}// ~SpeedBrick

EntityObj* SpeedBrick::Clone()
{
	return new SpeedBrick(physicsComponent->Clone(), graphicsComponent->Clone(), new std::string(id->c_str()), this->isFasten, HP);
}

//==============属性存取 =====================
const bool SpeedBrick::getFasten()
{
	return this->isFasten;
}

void SpeedBrick::setFasten(bool isFasten)
{
	this->isFasten = isFasten;
}


