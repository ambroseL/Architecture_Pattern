#ifndef _PaddleObj_H_
#define _PaddleObj_H_

#include "EntityObj.h"

/**
* ����ʵ����
*
*#include "cocos2d.h" <BR>
*include "PhysicsComponent.h" <BR>
*"GraphicsComponent.h" <BR>
*-llib
*
* �洢����Ļ���������Ϣ����������״̬����ֵ
*
* @seesomething
*/
class PaddleObj :public EntityObj
{
	bool isSticky;				/* ճ�״ֵ̬ */
	bool isImage;				/* ����״ֵ̬ */
	bool isReversal;			/* �ߵ�״ֵ̬ */
	float sHeight;				/* ����ĳ�ʼ��߶� */
	float sWidth;				/* ����ĳ�ʼ���� */

public:
	// ����������ڿ��ƺ������������������	

	/**
	*Ĭ�Ϲ��캯��
	*/
	PaddleObj();

	/**
	*���ι��캯��
	*
	*@param physicsComponent ������
	*@param graphicsComponent ͼ�񲿼�
	*@param id ����ID
	*@param bSticky ճ�״ֵ̬��Ĭ��Ϊfalse
	*@param bImage ����״ֵ̬��Ĭ��Ϊfalse
	*@param bReversal �ߵ�״ֵ̬��Ĭ��Ϊfalse
	*/
	PaddleObj(PhysicsComponent* physicsComponent, GraphicsComponent* graphicsComponent, std::string* id, bool bSticky = false, bool bImage = false, bool bReversal = false);
	
	/**
	*��������
	*/
	~PaddleObj();

	/**
	*��¡���������
	*/
	EntityObj* Clone() override;


	//�����

	/**
	*���ú��������������������ֵ��ԭΪĬ��ֵ
	*/
	void Reset();

	//�����Դ�ȡ

	/**
	*��ȡճ�״ֵ̬
	*/
	const bool getSticky();

	/**
	*��ȡ����״ֵ̬
	*/
	const bool getImage();

	/**
	*��ȡ�ߵ�״ֵ̬
	*/
	const bool getReversal();

	/**
	*����ճ�״ֵ̬
	*/
	void setSticky(bool bSticky);

	/**
	*���þ���״ֵ̬
	*/
	void setImage(bool bImage);

	/**
	*���þ���״ֵ̬
	*/
	void setReversal(bool bReversal);

	/**
	*��ȡ��ʼ�߶�
	*/
	const float getInitialHeight();

	/**
	*��ȡ��ʼ���
	*/
	const float getInitialWidth();
	
};

#endif