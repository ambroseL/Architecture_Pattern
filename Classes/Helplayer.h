#ifndef __Helplayer_H__
#define __Helplayer_H__

#include "cocos2d.h"
#include "GameSceneManager.h"
#include "WelcomeLayer.h"

using namespace cocos2d;

//自定义的布景类
class Helplayer : public cocos2d::Layer
{
public:
	GameSceneManager* gsm;
	Sprite* bgSprite;//指向背景精灵的指针
	int currIntroIndex = 0;//当前显示的索引
	Welcomelayer* wl;//欢迎界面的指针

	virtual bool init();//初始化的方法

	void menuBack(cocos2d::Ref*  pSender);//返回菜单的回调方法
	~Helplayer();
	//Cocos2d-x中定义的一个宏，创建指定类型的对象
	//并做好相应的初始化与释放工作
	CREATE_FUNC(Helplayer);
};
#endif