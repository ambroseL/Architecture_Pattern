#ifndef  _SceneManager_H_
#define  _SceneManager_H_
#include "cocos2d.h"
using namespace cocos2d;

class SceneManager
{
public:
	void createScene();//������������ķ���
	void gogameScene();//ȥ��Ϸ�����ķ���
	void goRound2Scene();//ȥ�ڶ��صķ���
	void goRound3Scene();//ȥ�����صķ���
	void reStart();//��һ�����¿�ʼ�ķ���
	void reStart2();//�ڶ������¿�ʼ�ķ���
	void reStart3();//���������¿�ʼ�ķ���
	void goStartScene();//�ػ�ӭ�����ķ���
	void goHelpScene();//ȥ��������;
};
#endif
