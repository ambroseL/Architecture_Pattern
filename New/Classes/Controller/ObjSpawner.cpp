#include "ObjSpawner.h"
#include "EntityObj.h"// class implemented

/////////////// PUBLIC///////////////////////

//================= ���캯�� ====================


ObjSpawner::ObjSpawner(EntityObj* prototype):prototype(prototype)
{
}

ObjSpawner::~ObjSpawner()
{
}

//==============��Ĳ��� =====================
EntityObj* ObjSpawner::spawnEntity()
{
	return prototype->Clone();
}

//==============���Դ�ȡ =====================
void ObjSpawner::setPrototype(EntityObj* prototype)
{
	this->prototype = prototype;
}

