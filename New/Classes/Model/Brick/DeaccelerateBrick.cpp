#include "DeaccelerateBrick.h"// class implemented

/////////////// PUBLIC///////////////////////

//================= ¹¹Ôìº¯Êý ====================

DeaccelerateBrick::DeaccelerateBrick()
{
}

DeaccelerateBrick::DeaccelerateBrick(PhysicsComponent* physicsComponent, GraphicsComponent* graphicsComponent, std::string* id, int iHP):
BrickObj(physicsComponent, graphicsComponent, id, iHP)
{
	
}// SpeedBrick


DeaccelerateBrick::~DeaccelerateBrick()
{
}



EntityObj* DeaccelerateBrick::Clone()
{
	return new DeaccelerateBrick(physicsComponent->Clone(), graphicsComponent->Clone(), new std::string(id->c_str()), HP);
}