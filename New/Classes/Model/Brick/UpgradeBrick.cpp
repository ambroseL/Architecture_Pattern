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
