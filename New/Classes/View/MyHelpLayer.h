#ifndef __MyHelpLayer_H__
#define __MyHelpLayer_H__

#include "cocos2d.h"
#include "SceneManager.h"
#include "StartLayer.h"
using namespace cocos2d;

class MyHelpLayer :public cocos2d::Layer
{
	SceneManager* gsm;
	Sprite* bgSprite;//ָ�򱳾������ָ��
	int currIntroIndex = 0;//��ǰ��ʾ������
	StartLayer* wl;//��ӭ�����ָ��
	public:
	~MyHelpLayer();
	bool init() override;//��ʼ���ķ���

	void menueBack(cocos2d::Ref*  pSender);//���ز˵��Ļص�����

	void setSceneManager(SceneManager* sceneManager) { this->gsm = sceneManager; }

	CREATE_FUNC(MyHelpLayer);
};
#endif
