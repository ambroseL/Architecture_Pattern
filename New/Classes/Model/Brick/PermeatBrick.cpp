#include "PermeatBrick.h"// class implemented

/////////////// PUBLIC///////////////////////

//================= ���캯�� ====================

PermeatBrick::PermeatBrick():BrickObj()
{
}// PermeatBrick

PermeatBrick::PermeatBrick(PhysicsComponent* physicsComponent, GraphicsComponent* graphicsComponent, std::string* id, int iHP):
BrickObj(physicsComponent, graphicsComponent, id, iHP)
{
}// PermeatBrick


PermeatBrick::~PermeatBrick()
{
}// ~PermeatBrick
