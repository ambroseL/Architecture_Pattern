#include "ImagePack.h"// class implemented

/////////////// PUBLIC///////////////////////

//================= ���캯�� ====================

ImagePack::ImagePack():
PackObj()
{
}// ImagePack


ImagePack::ImagePack(PhysicsComponent* physicsComponent, GraphicsComponent* graphicsComponent, std::string* id):
PackObj(physicsComponent,graphicsComponent,id)
{
	
}// ImagePack


ImagePack::~ImagePack()
{
}// ~ImagePack
