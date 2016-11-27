#include "StickyPack.h"// class implemented

/////////////// PUBLIC///////////////////////

//================= ¹¹Ôìº¯Êý ====================

StickyPack::StickyPack():
PackObj()
{
}// StickyPack

StickyPack::StickyPack(PhysicsComponent* physicsComponent, GraphicsComponent* graphicsComponent, std::string* id):
PackObj(physicsComponent, graphicsComponent, id)
{
	
}// StickyPack


StickyPack::~StickyPack()
{
}// ~StickyPack
