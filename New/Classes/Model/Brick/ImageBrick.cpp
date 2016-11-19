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
