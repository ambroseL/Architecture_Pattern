#include "SpeedPack.h"// class implemented

/////////////// PUBLIC///////////////////////

//================= 构造函数 ====================


SpeedPack::SpeedPack():
PackObj(),isFasten(true)
{
}// SpeedPack

SpeedPack::SpeedPack(PhysicsComponent* physicsComponent, GraphicsComponent* graphicsComponent, std::string* id, bool isFasten):
PackObj(physicsComponent,graphicsComponent, id),isFasten(isFasten)
{
	
}// SpeedPack


SpeedPack::~SpeedPack()
{
}// SpeedPack


EntityObj* SpeedPack::Clone()
{
	return new SpeedPack(physicsComponent->Clone(), graphicsComponent->Clone(), new std::string(id->c_str()), isFasten);
}

 //==============属性存取 =====================
const bool SpeedPack::getFasten()
{
	return this->isFasten;
}

void SpeedPack::setFasten(bool isFasten)
{
	this->isFasten = isFasten;
}
