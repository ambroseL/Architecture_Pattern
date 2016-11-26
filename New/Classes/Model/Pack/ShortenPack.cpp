#include "ShortenPack.h"/ class implemented

/////////////// PUBLIC///////////////////////

//================= ¹¹Ôìº¯Êý ====================

ShortenPack::ShortenPack():PackObj()
{
}// ShortenPack


ShortenPack::~ShortenPack()
{
}// ShortenPack

ShortenPack::ShortenPack(PhysicsComponent* physicsComponent, GraphicsComponent* graphicsComponent, std::string* id):
PackObj(physicsComponent, graphicsComponent, id)
{
	
}// ShortenPack
