#include "ReversalBrick.h"// class implemented

/////////////// PUBLIC///////////////////////

//================= ���캯�� ====================

ReversalBrick::ReversalBrick():BrickObj()
{
}

ReversalBrick::ReversalBrick(PhysicsComponent* physicsComponent, GraphicsComponent* graphicsComponent, std::string* id, int iHP):
BrickObj(physicsComponent, graphicsComponent, id, iHP)
{
}


ReversalBrick::~ReversalBrick()
{
}
