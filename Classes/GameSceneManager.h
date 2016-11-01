#ifndef _GameSceneManager_H_
#define _GameSceneManager_H_
#include "cocos2d.h"
using namespace cocos2d;
class GameSceneManager
{
/*public:
	static cocos2d::Scene* createScene();*/
public:
	//创建场景对象的方法
	void createScene();

	void gogameScene();//去游戏场景的方法
	void goRound2Scene();//去第二关的方法
	void goRound3Scene();//去第三关的方法
	Scene* welcomeScene;//欢迎界面场景指针
	Scene* gameScene;//游戏场景指针
	Scene* helpScene;
	void reStart();//第一关重新开始的方法
	void reStart2();//第二关重新开始的方法
	void reStart3();//第三关重新开始的方法
	void goWelcomeScene();//回欢迎场景的方法

	void goHelpScene();//去帮助场景
};
#endif
