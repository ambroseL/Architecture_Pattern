#ifndef __Helplayer_H__
#define __Helplayer_H__

#include "cocos2d.h"
#include "GameSceneManager.h"
#include "WelcomeLayer.h"

using namespace cocos2d;

//�Զ���Ĳ�����
class Helplayer : public cocos2d::Layer
{
public:
	GameSceneManager* gsm;
	Sprite* bgSprite;//ָ�򱳾������ָ��
	int currIntroIndex = 0;//��ǰ��ʾ������
	Welcomelayer* wl;//��ӭ�����ָ��

	virtual bool init();//��ʼ���ķ���

	void menuBack(cocos2d::Ref*  pSender);//���ز˵��Ļص�����
	~Helplayer();
	//Cocos2d-x�ж����һ���꣬����ָ�����͵Ķ���
	//��������Ӧ�ĳ�ʼ�����ͷŹ���
	CREATE_FUNC(Helplayer);
};
#endif