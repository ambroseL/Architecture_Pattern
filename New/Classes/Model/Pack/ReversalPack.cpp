#include "ReversalPack.h"// class implemented

/////////////// PUBLIC///////////////////////

//================= ���캯�� ====================

ReversalPack::ReversalPack():PackObj()
{
}// ReversalPack

ReversalPack::ReversalPack(PhysicsComponent* physicsComponent, GraphicsComponent* graphicsComponent, std::string* id):
PackObj(physicsComponent, graphicsComponent, id)
{
	
} // ReversalPack


ReversalPack::~ReversalPack()
{
}// ~ReversalPack