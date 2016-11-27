#ifndef _ObjSpawner_H_
#define _ObjSpawner_H_
#include "EntityObj.h"



class ObjSpawner
{
	EntityObj* prototype;
public:
	ObjSpawner(EntityObj* prototype);
	EntityObj* spawnEntity();
	void setPrototype(EntityObj* prototype);
	~ObjSpawner();
};
#endif

