#ifndef __StartLayer_H__
#define __StartLayer_H__

#include "2d/CCLayer.h"
#include "cocos2d.h"
#include "SceneManager.h"
using namespace cocos2d;

class StartLayer: public Layer
{
	SceneManager* gsm;

	static bool playBgM;//���������Ƿ񲥷Ź�
public:				
	
	~StartLayer();
	
	bool init() override;//��ʼ���ķ���
	void menueExit(cocos2d::Ref*  pSender);//ѡ��˵��ص�����
	void menueStart(cocos2d::Ref*  pSender);//��ʼ�˵��ص�����
	void menueHelp(cocos2d::Ref*  pSender);//�����˵��ص�����
	
	void setScenemanager(SceneManager* sceneManager) { this->gsm = sceneManager; }

	CREATE_FUNC(StartLayer);
};
#endif