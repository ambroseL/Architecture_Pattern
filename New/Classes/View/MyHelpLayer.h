#ifndef __MyHelpLayer_H__
#define __MyHelpLayer_H__

#include "cocos2d.h"
#include "SceneManager.h"
#include "StartLayer.h"
using namespace cocos2d;

/**
* ����������
*
*#include "cocos2d.h" <BR>
*#include "cocos2d.h"
*#include "SceneManager.h"
*#include "StartLayer.h"
*-llib
*
* ����������ʾ��Ϸ���淨˵��
*
* @seesomething
*/

class MyHelpLayer :public cocos2d::Layer
{
	SceneManager* gsm;
	Sprite* bgSprite;						/*  ָ�򱳾������ָ��  */
	int currIntroIndex = 0;					/* ��ǰ��ʾ������ */
	StartLayer* wl;							/*  ��ӭ�����ָ��  */

public:
	// ����������ڿ��ƺ���

	/**
	*��ʼ���ķ�������createʱ���Զ�����
	*cocos2dx����
	*/
	bool init() override;
	CREATE_FUNC(MyHelpLayer);

	
	// �����

	/**
	*���ز˵��Ļص�����
	*@parameter pSender �ص������Դ�Ĭ�ϲ���
	*/
	void menueBack(cocos2d::Ref*  pSender);

	// �����Դ�ȡ
	/**
	*���ó���������
	*@parameter sceneManager �����õĳ���������
	*/
	void setSceneManager(SceneManager* sceneManager) { this->gsm = sceneManager; }
};
#endif
