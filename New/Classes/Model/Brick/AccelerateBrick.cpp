#include "AccelerateBrick.h"// class implemented

/////////////// PUBLIC///////////////////////

//================= ¹¹Ôìº¯Êý ====================

AccelerateBrick::AccelerateBrick():BrickObj()
{
}// AccelerateBrick

AccelerateBrick::AccelerateBrick(PhysicsComponent* physicsComponent, GraphicsComponent* graphicsComponent, std::string* id, int iHP):
BrickObj(physicsComponent, graphicsComponent, id, iHP)
{
}// AccelerateBrickBrick

AccelerateBrick::~AccelerateBrick()
{
}// ~AccelerateBrick

EntityObj* AccelerateBrick::Clone()
{
	return new AccelerateBrick(physicsComponent->Clone(), graphicsComponent->Clone(), new std::string(id->c_str()),HP);
}


