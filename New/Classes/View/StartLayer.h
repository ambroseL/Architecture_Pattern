#ifndef __StartLayer_H__
#define __StartLayer_H__

#include "2d/CCLayer.h"
#include "cocos2d.h"
#include "SceneManager.h"
using namespace cocos2d;

class StartLayer: public Layer
{
	SceneManager* gsm;

	static bool playBgM;//背景音乐是否播放过
public:				
	
	~StartLayer();
	
	bool init() override;//初始化的方法
	void menueExit(cocos2d::Ref*  pSender);//选项菜单回调方法
	void menueStart(cocos2d::Ref*  pSender);//开始菜单回调方法
	void menueHelp(cocos2d::Ref*  pSender);//帮助菜单回调方法
	
	void setScenemanager(SceneManager* sceneManager) { this->gsm = sceneManager; }

	CREATE_FUNC(StartLayer);
};
#endif