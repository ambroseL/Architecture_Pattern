#include "ObjSpawner.h"
#include "EntityObj.h"


ObjSpawner::ObjSpawner(EntityObj* prototype):prototype(prototype)
{
}

ObjSpawner::~ObjSpawner()
{
}

EntityObj* ObjSpawner::spawnEntity()
{
	return prototype->Clone();
}
