#include "StickyPack.h"// class implemented

/////////////// PUBLIC///////////////////////

//================= ���캯�� ====================

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
