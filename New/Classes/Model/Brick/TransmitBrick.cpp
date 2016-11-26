#include "TransmitBrick.h"// class implemented

/////////////// PUBLIC///////////////////////

//================= ¹¹Ôìº¯Êý ====================


TransmitBrick::TransmitBrick():BrickObj()
{
}// TransmitBrick

TransmitBrick::TransmitBrick(PhysicsComponent* physicsComponent, GraphicsComponent* graphicsComponent, std::string* id, int iHP): 
BrickObj(physicsComponent, graphicsComponent, id, iHP)
{	
}// TransmitBrick


TransmitBrick::~TransmitBrick()
{
}// ~TransmitBrick
