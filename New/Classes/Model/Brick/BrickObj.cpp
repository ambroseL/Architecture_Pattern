#include "BrickObj.h"// class implemented

/////////////// PUBLIC///////////////////////

//================= 构造函数 ====================

BrickObj::BrickObj():EntityObj(),HP(1)
{
}// BrickObj


BrickObj::BrickObj(PhysicsComponent* physicsComponent, GraphicsComponent* graphicsComponent, std::string* id, int iHP):
EntityObj(physicsComponent,graphicsComponent,id),HP(iHP)
{	
}// BrickObj


BrickObj::~BrickObj()
{
}// ~BrickObj

EntityObj* BrickObj::Clone()
{
	return new BrickObj(physicsComponent->Clone(), graphicsComponent->Clone(), new std::string(id->c_str()),HP);
}

//==============属性存取 =====================

const int BrickObj::getHP()
{
	return this->HP;
}

void BrickObj::setHP(int iHP) 
{
	this->HP = iHP;
}


