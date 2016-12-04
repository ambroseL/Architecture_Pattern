#ifndef  _SceneManager_H_
#define  _SceneManager_H_
#include "cocos2d.h"
using namespace cocos2d;

class SceneManager
{
public:
	void createScene();//创建场景对象的方法
	void gogameScene();//去游戏场景的方法
	void goRound2Scene();//去第二关的方法
	void goRound3Scene();//去第三关的方法
	void reStart();//第一关重新开始的方法
	void reStart2();//第二关重新开始的方法
	void reStart3();//第三关重新开始的方法
	void goStartScene();//回欢迎场景的方法
	void goHelpScene();//去帮助场景;
};
#endif
