#include "LengthenPack.h"// class implemented

/////////////// PUBLIC///////////////////////

//================= ���캯�� ====================

LengthenPack::LengthenPack():
PackObj()
{
}// LengthPack

LengthenPack::LengthenPack(PhysicsComponent* physicsComponent, GraphicsComponent* graphicsComponent, std::string* id):
PackObj(physicsComponent,graphicsComponent, id)
{
	
}// LengthPack

LengthenPack::~LengthenPack()
{
}// LengthPack
