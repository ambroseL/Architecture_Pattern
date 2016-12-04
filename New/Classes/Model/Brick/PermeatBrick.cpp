#include "PermeatBrick.h"// class implemented

/////////////// PUBLIC///////////////////////

//================= ¹¹Ôìº¯Êý ====================

PermeatBrick::PermeatBrick():BrickObj()
{
}// PermeatBrick

PermeatBrick::PermeatBrick(PhysicsComponent* physicsComponent, GraphicsComponent* graphicsComponent, std::string* id, int iHP):
BrickObj(physicsComponent, graphicsComponent, id, iHP)
{
}// PermeatBrick


PermeatBrick::~PermeatBrick()
{
}// ~PermeatBrick

EntityObj* PermeatBrick::Clone()
{
	return new PermeatBrick(physicsComponent->Clone(), graphicsComponent->Clone(), new std::string(id->c_str()), HP);
}
