#include "LengthenBrick.h"// class implemented

/////////////// PUBLIC///////////////////////

//================= ¹¹Ôìº¯Êý ====================

LengthenBrick::LengthenBrick() :BrickObj()
{
}// LengthBrick

LengthenBrick::LengthenBrick(PhysicsComponent* physicsComponent, GraphicsComponent* graphicsComponent, std::string* id,int iHP):
BrickObj(physicsComponent, graphicsComponent, id, iHP)
{	
}// LengthBrick


LengthenBrick::~LengthenBrick()
{
}// ~LengthBrick

EntityObj* LengthenBrick::Clone()
{
	return new LengthenBrick(physicsComponent->Clone(), graphicsComponent->Clone(), 
		new std::string(id->c_str()), HP);
}


