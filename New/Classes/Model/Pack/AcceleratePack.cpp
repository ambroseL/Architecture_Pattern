#include "AcceleratePack.h"// class implemented

/////////////// PUBLIC///////////////////////

//================= ���캯�� ====================

AcceleratePack::AcceleratePack():PackObj()
{
}//AcceleratePack

AcceleratePack::AcceleratePack(PhysicsComponent* physicsComponent, GraphicsComponent* graphicsComponent, std::string* id):
PackObj(physicsComponent, graphicsComponent, id)
{
	
}//AcceleratePack


AcceleratePack::~AcceleratePack()
{
}//AcceleratePack
