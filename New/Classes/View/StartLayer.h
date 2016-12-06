#ifndef __StartLayer_H__
#define __StartLayer_H__

#include "2d/CCLayer.h"
#include "cocos2d.h"
#include "SceneManager.h"
using namespace cocos2d;
/**
* 开始场景类
*
*#include "2d/CCLayer.h"
*#include "cocos2d.h"
*#include "SceneManager.h"
*-llib
*
*游戏的开始场景，显示游戏初始界面
*提供进入、推出游戏和进入帮助页面选项
*
* @seesomething
*/

class StartLayer: public Layer
{
	SceneManager* gsm;

public:				
	// 类的生命周期控制函数

	/**
	*初始化的方法，在create时会自动调用
	*cocos2dx机制
	*/
	bool init() override;
	/**
	*Cocos2d-x中定义的一个宏，创建指定类型的对象,并做好相应的初始化与释放工作
	*/
	CREATE_FUNC(StartLayer);

	// 类操作

	/**
	*选项菜单回调方法
	*@pSender 回调函数自带默认参数
	*/
	void menueExit(cocos2d::Ref*  pSender);

	/**
	*开始菜单回调方法
	*@pSender 回调函数自带默认参数
	*/
	void menueStart(cocos2d::Ref*  pSender);

	/**
	*帮助菜单回调方法
	*@pSender 回调函数自带默认参数
	*/
	void menueHelp(cocos2d::Ref*  pSender);
	
	// 类属性存取
	/**
	*设置场景管理类
	*@parameter sceneManager 待设置的场景管理类
	*/
	void setScenemanager(SceneManager* sceneManager) { this->gsm = sceneManager; }
};
#endif