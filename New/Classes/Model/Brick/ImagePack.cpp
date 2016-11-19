#include "ImagePack.h"// class implemented

/////////////// PUBLIC///////////////////////

//================= ¹¹Ôìº¯Êý ====================

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
