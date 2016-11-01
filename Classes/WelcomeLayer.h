#ifndef __WelcomeLayer_H__
#define __WelcomeLayer_H__

#include "cocos2d.h"
#include "GameSceneManager.h"

using namespace cocos2d;

//�Զ���Ĳ�����
class Welcomelayer : public cocos2d::Layer
{
public:
	GameSceneManager* gsm;
	static bool playBgM;//���������Ƿ񲥷Ź�

	//��ʼ���ķ���
	virtual bool init();
	//ѡ��˵��ص�����
	void menuExit(cocos2d::Ref*  pSender);
	void menuStart(cocos2d::Ref*  pSender);//��ʼ�˵��ص�����
	void menuHelp(cocos2d::Ref*  pSender);//�����˵��ص�����
	void preloadBgMusic();//���ر��� ����
	void playBgMusic();//���ű�������

	~Welcomelayer();
	//Cocos2d-x�ж����һ���꣬����ָ�����͵Ķ���
	//��������Ӧ�ĳ�ʼ�����ͷŹ���
	CREATE_FUNC(Welcomelayer);
};

#endif
