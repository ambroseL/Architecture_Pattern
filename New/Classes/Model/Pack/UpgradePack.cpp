#include "UpgradePack.h"// class implemented

/////////////// PUBLIC///////////////////////

//================= ���캯�� ====================

UpgradePack::UpgradePack():
PackObj()
{
}// UpgradePack

UpgradePack::UpgradePack(PhysicsComponent* physicsComponent, GraphicsComponent* graphicsComponent, std::string* id):
PackObj(physicsComponent,graphicsComponent, id)
{
}// UpgradePack


UpgradePack::~UpgradePack()
{
}// ~UpgradePack
