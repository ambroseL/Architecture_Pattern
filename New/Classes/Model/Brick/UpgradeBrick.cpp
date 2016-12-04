#include "UpgradeBrick.h"// class implemented

/////////////// PUBLIC///////////////////////

//================= ¹¹Ôìº¯Êý ====================

UpgradeBrick::UpgradeBrick():BrickObj()
{
}// UpgradeBrick

UpgradeBrick::UpgradeBrick(PhysicsComponent* physicsComponent, GraphicsComponent* graphicsComponent, std::string* id, int iHP): 
BrickObj(physicsComponent, graphicsComponent, id, iHP)
{
}// UpgradeBrick


UpgradeBrick::~UpgradeBrick()
{
}// UpgradeBrick

EntityObj* UpgradeBrick::Clone()
{
	return new UpgradeBrick(physicsComponent->Clone(), graphicsComponent->Clone(), new std::string(id->c_str()), HP);
}
