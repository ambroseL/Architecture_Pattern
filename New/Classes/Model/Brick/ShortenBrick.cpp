#include "ShortenBrick.h"// class implemented

/////////////// PUBLIC///////////////////////

//================= ���캯�� ====================

ShortenBrick::ShortenBrick() :BrickObj()
{
}// ShortenBrick

ShortenBrick::ShortenBrick(PhysicsComponent* physicsComponent, GraphicsComponent* graphicsComponent, std::string* id, int iHP) :
	BrickObj(physicsComponent, graphicsComponent, id, iHP)
{
}// ShortenBrick


ShortenBrick::~ShortenBrick()
{
}// ~LengthBrick

EntityObj* ShortenBrick::Clone()
{
	return new ShortenBrick(physicsComponent->Clone(), graphicsComponent->Clone(),
		new std::string(id->c_str()), HP);
}

