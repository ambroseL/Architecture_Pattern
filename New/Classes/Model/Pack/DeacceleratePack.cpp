#include "DeacceleratePack.h"// class implemented

/////////////// PUBLIC///////////////////////

//================= ���캯�� ====================


DeacceleratePack::DeacceleratePack():
PackObj()
{
}// DeacceleratePack

DeacceleratePack::DeacceleratePack(PhysicsComponent* physicsComponent, GraphicsComponent* graphicsComponent, std::string* id):
PackObj(physicsComponent,graphicsComponent, id)
{
	
}// DeacceleratePack


DeacceleratePack::~DeacceleratePack()
{
}// DeacceleratePack


