#include "StickyBrick.h"// class implemented

/////////////// PUBLIC///////////////////////

//================= ¹¹Ôìº¯Êý ====================

StickyBrick::StickyBrick():BrickObj()
{
}// StickyBrick

StickyBrick::StickyBrick(PhysicsComponent* physicsComponent, GraphicsComponent* graphicsComponent, std::string* id, int iHP):
BrickObj(physicsComponent, graphicsComponent, id, iHP)
{
}// StickyBrick


StickyBrick::~StickyBrick()
{
}// ~StickyBrick
