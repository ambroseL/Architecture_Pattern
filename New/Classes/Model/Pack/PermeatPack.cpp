#include "PermeatPack.h"// class implemented

/////////////// PUBLIC///////////////////////

//================= ���캯�� ====================

PermeatPack::PermeatPack():
PackObj()
{
}// PermeatPack

PermeatPack::PermeatPack(PhysicsComponent* physicsComponent, GraphicsComponent* graphicsComponent, std::string* id):
PackObj(physicsComponent,graphicsComponent, id)
{
	
}// PermeatPack

PermeatPack::~PermeatPack()
{
}// PermeatPack
