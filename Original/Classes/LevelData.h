#ifndef _LevelData_H_
#define _LevelData_H_

#include "cocos2d.h"
#include "Beginlayer.h"
#include <Box2D/Box2D.h>

using namespace std;
class LevelData
{
public:
	LevelData(int level, b2World* world, Layer* layer, std::map<std::string, PhyObject*> &pom);
	static int brickcount;//��Ҫ�����ש������
	static float speed;//����ٶȵȼ�
};

#endif