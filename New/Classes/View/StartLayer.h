#ifndef __StartLayer_H__
#define __StartLayer_H__

#include "2d/CCLayer.h"
#include "cocos2d.h"
#include "SceneManager.h"
using namespace cocos2d;
/**
* ��ʼ������
*
*#include "2d/CCLayer.h"
*#include "cocos2d.h"
*#include "SceneManager.h"
*-llib
*
*��Ϸ�Ŀ�ʼ��������ʾ��Ϸ��ʼ����
*�ṩ���롢�Ƴ���Ϸ�ͽ������ҳ��ѡ��
*
* @seesomething
*/

class StartLayer: public Layer
{
	SceneManager* gsm;

public:				
	// ����������ڿ��ƺ���

	/**
	*��ʼ���ķ�������createʱ���Զ�����
	*cocos2dx����
	*/
	bool init() override;
	/**
	*Cocos2d-x�ж����һ���꣬����ָ�����͵Ķ���,��������Ӧ�ĳ�ʼ�����ͷŹ���
	*/
	CREATE_FUNC(StartLayer);

	// �����

	/**
	*ѡ��˵��ص�����
	*@pSender �ص������Դ�Ĭ�ϲ���
	*/
	void menueExit(cocos2d::Ref*  pSender);

	/**
	*��ʼ�˵��ص�����
	*@pSender �ص������Դ�Ĭ�ϲ���
	*/
	void menueStart(cocos2d::Ref*  pSender);

	/**
	*�����˵��ص�����
	*@pSender �ص������Դ�Ĭ�ϲ���
	*/
	void menueHelp(cocos2d::Ref*  pSender);
	
	// �����Դ�ȡ
	/**
	*���ó���������
	*@parameter sceneManager �����õĳ���������
	*/
	void setScenemanager(SceneManager* sceneManager) { this->gsm = sceneManager; }
};
#endif