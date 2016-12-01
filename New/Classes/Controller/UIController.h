#ifndef  _UIController_H_
#define  _UIController_H_

#include "2d/CCSprite.h"
//#include "GameLayer.h"

using namespace cocos2d;

extern class GameLayer;

class UIController
{
	GameLayer* layer;
public:

	UIController();

	~UIController();

	void setLayer(GameLayer* layer);

	void playYX();//播放音效的方法

	void updateLifeSprite(int HP);

	
};

#endif
