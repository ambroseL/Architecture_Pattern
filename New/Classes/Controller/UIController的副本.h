#ifndef  _UIController_H_
#define  _UIController_H_
#include "GameLayer.h"


/**
* UI������
*
*#include "GameLayer.h"
*-llib
*
* ���Ƴ����е�UI�߼���������ֵ��ʾ�����ֲ��ŵ�
*
* @saysomething
*/
class UIController
{
	GameLayer* layer;						/* ���Ƶĳ����� */

public:

	// ����������ڿ��ƺ������������������	

	/**
	*Ĭ�Ϲ��캯��
	*/
	UIController();

	/**
	*��������
	*/
	~UIController();

	//�����

	/**
	*������Ч
	*/
	void playYX();

	/**
	*����������ʾ����
	*/
	void updateLifeSprite(int HP);

	//�����Դ�ȡ

	/**
	*���ó���
	*@parameter layer �����õĳ���
	*/
	void setLayer(GameLayer* layer);	
};

#endif
