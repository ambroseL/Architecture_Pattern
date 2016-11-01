#ifndef __WelcomeLayer_H__
#define __WelcomeLayer_H__

#include "cocos2d.h"
#include "GameSceneManager.h"

using namespace cocos2d;

//自定义的布景类
class Welcomelayer : public cocos2d::Layer
{
public:
	GameSceneManager* gsm;
	static bool playBgM;//背景音乐是否播放过

	//初始化的方法
	virtual bool init();
	//选项菜单回调方法
	void menuExit(cocos2d::Ref*  pSender);
	void menuStart(cocos2d::Ref*  pSender);//开始菜单回调方法
	void menuHelp(cocos2d::Ref*  pSender);//帮助菜单回调方法
	void preloadBgMusic();//加载背景 音乐
	void playBgMusic();//播放背景音乐

	~Welcomelayer();
	//Cocos2d-x中定义的一个宏，创建指定类型的对象
	//并做好相应的初始化与释放工作
	CREATE_FUNC(Welcomelayer);
};

#endif
