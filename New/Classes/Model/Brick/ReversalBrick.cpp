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

EntityObj* ReversalBrick::Clone()
{
	return new ReversalBrick(physicsComponent->Clone(), graphicsComponent->Clone(), new std::string(id->c_str()), HP);
}
