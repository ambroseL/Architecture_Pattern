#include "PackObj.h"// class implemented

/////////////// PUBLIC///////////////////////

//================= ¹¹Ôìº¯Êı ====================

PackObj::PackObj():EntityObj()
{
}// PackObj

PackObj::PackObj(PhysicsComponent* physicsComponent, GraphicsComponent* graphicsComponent, std::string* id):
EntityObj(physicsComponent, graphicsComponent, id)
{
	
}// PackObj

PackObj::~PackObj()
{
}// ~PackObj

EntityObj* PackObj::Clone()
{
	return new PackObj(physicsComponent->Clone(), graphicsComponent->Clone(), new std::string(id->c_str()));
}
