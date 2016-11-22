#include "LengthPack.h"// class implemented

/////////////// PUBLIC///////////////////////

//================= 构造函数 ====================

LengthPack::LengthPack():
PackObj(),isLengthen(true)
{
}// LengthPack

LengthPack::LengthPack(PhysicsComponent* physicsComponent, GraphicsComponent* graphicsComponent, std::string* id, bool isLengthen):
PackObj(physicsComponent,graphicsComponent, id),isLengthen(isLengthen)
{
	
}// LengthPack

LengthPack::~LengthPack()
{
}// LengthPack

EntityObj* LengthPack::Clone()
{
	return new LengthPack(physicsComponent->Clone(), graphicsComponent->Clone(), new std::string(id->c_str()), isLengthen);
}

//==============属性存取 =====================

const bool LengthPack::getLengthen()
{
	return this->isLengthen;
}

void LengthPack::setLengthen(bool isLengthen)
{
	this->isLengthen = isLengthen;
}
