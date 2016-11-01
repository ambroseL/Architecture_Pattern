#ifndef  _AppDelegate_H_
#define  _AppDelegate_H_

#include "cocos2d.h"

class  AppDelegate : private cocos2d::Application
{
public:
	AppDelegate();
	virtual ~AppDelegate();

	//初始化方法
	virtual bool applicationDidFinishLaunching();

	//当程序进入后台时调用此方法
	virtual void applicationDidEnterBackground();

	//当程序进入前台时调用
	virtual void applicationWillEnterForeground();
};

#endif







