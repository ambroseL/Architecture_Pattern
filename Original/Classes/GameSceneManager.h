#ifndef _GameSceneManager_H_
#define _GameSceneManager_H_
#include "cocos2d.h"
using namespace cocos2d;
class GameSceneManager
{
/*public:
	static cocos2d::Scene* createScene();*/
public:
	//������������ķ���
	void createScene();

	void gogameScene();//ȥ��Ϸ�����ķ���
	void goRound2Scene();//ȥ�ڶ��صķ���
	void goRound3Scene();//ȥ�����صķ���
	Scene* welcomeScene;//��ӭ���泡��ָ��
	Scene* gameScene;//��Ϸ����ָ��
	Scene* helpScene;
	void reStart();//��һ�����¿�ʼ�ķ���
	void reStart2();//�ڶ������¿�ʼ�ķ���
	void reStart3();//���������¿�ʼ�ķ���
	void goWelcomeScene();//�ػ�ӭ�����ķ���

	void goHelpScene();//ȥ��������
};
#endif
