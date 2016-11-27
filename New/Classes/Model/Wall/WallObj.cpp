#include "WallObj.h"// class implemented

/////////////// PUBLIC///////////////////////

//================= ¹¹Ôìº¯Êı ====================

WallObj::WallObj():
EntityObj()
{
}// WallObj

WallObj::WallObj(PhysicsComponent* physicsComponent, GraphicsComponent* graphicsComponent, std::string* id):
EntityObj(physicsComponent,graphicsComponent, id)
{
}// WallObj

WallObj::~WallObj()
{
}// ~WallObj


EntityObj* WallObj::Clone()
{
	return new WallObj(physicsComponent->Clone(),graphicsComponent->Clone(), new std::string(id->c_str()));
}


