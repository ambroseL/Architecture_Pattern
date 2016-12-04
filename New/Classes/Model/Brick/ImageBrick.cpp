#include "ImageBrick.h"// class implemented

/////////////// PUBLIC///////////////////////

//================= ¹¹Ôìº¯Êý ====================

ImageBrick::ImageBrick():BrickObj()
{
}// ImageBrick

ImageBrick::ImageBrick(PhysicsComponent* physicsComponent, GraphicsComponent* graphicsComponent, std::string* id, int iHP):
BrickObj(physicsComponent, graphicsComponent, id, iHP)
{
}// ImageBrick


ImageBrick::~ImageBrick()
{
}// ~ImageBrick

EntityObj* ImageBrick::Clone()
{
	return new ImageBrick(physicsComponent->Clone(), graphicsComponent->Clone(), new std::string(id->c_str()), HP);
}
