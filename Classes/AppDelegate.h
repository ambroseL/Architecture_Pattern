#ifndef  _AppDelegate_H_
#define  _AppDelegate_H_

#include "cocos2d.h"

class  AppDelegate : private cocos2d::Application
{
public:
	AppDelegate();
	virtual ~AppDelegate();

	//��ʼ������
	virtual bool applicationDidFinishLaunching();

	//����������̨ʱ���ô˷���
	virtual void applicationDidEnterBackground();

	//���������ǰ̨ʱ����
	virtual void applicationWillEnterForeground();
};

#endif







