#include "ObjSpawner.h"
#include "EntityObj.h"// class implemented

/////////////// PUBLIC///////////////////////

//================= 构造函数 ====================


ObjSpawner::ObjSpawner(EntityObj* prototype):prototype(prototype)
{
}

ObjSpawner::~ObjSpawner()
{
}

//==============类的操作 =====================
EntityObj* ObjSpawner::spawnEntity()
{
	return prototype->Clone();
}

//==============属性存取 =====================
void ObjSpawner::setPrototype(EntityObj* prototype)
{
	this->prototype = prototype;
}

