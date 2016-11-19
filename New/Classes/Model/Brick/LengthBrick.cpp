#include "LengthBrick.h"// class implemented

/////////////// PUBLIC///////////////////////

//================= 构造函数 ====================

LengthBrick::LengthBrick() :BrickObj(),isLengthen(true)
{
}// LengthBrick

LengthBrick::LengthBrick(PhysicsComponent* physicsComponent, GraphicsComponent* graphicsComponent, std::string* id, bool bLengthen, int iHP):
BrickObj(physicsComponent, graphicsComponent, id, iHP),isLengthen(bLengthen)
{	
}// LengthBrick


LengthBrick::~LengthBrick()
{
}// ~LengthBrick

EntityObj* LengthBrick::Clone()
{
	return new LengthBrick(physicsComponent->Clone(), graphicsComponent->Clone(), 
		new std::string(id->c_str()), isLengthen, HP);
}

//==============属性存取 =====================
const bool LengthBrick::getLengthen()
{
	return this->isLengthen;
}

void LengthBrick::setLengthen(bool isLengthen)
{
	this->isLengthen = isLengthen;
}
