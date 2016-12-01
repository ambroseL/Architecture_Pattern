#ifndef __MyHelpLayer_H__
#define __MyHelpLayer_H__

#include "cocos2d.h"
#include "SceneManager.h"
#include "StartLayer.h"
using namespace cocos2d;

class MyHelpLayer :public cocos2d::Layer
{
	SceneManager* gsm;
	Sprite* bgSprite;//指向背景精灵的指针
	int currIntroIndex = 0;//当前显示的索引
	StartLayer* wl;//欢迎界面的指针
	public:
	~MyHelpLayer();
	bool init() override;//初始化的方法

	void menueBack(cocos2d::Ref*  pSender);//返回菜单的回调方法

	void setSceneManager(SceneManager* sceneManager) { this->gsm = sceneManager; }

	CREATE_FUNC(MyHelpLayer);
};
#endif
