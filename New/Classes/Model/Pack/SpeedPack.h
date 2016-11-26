#ifndef _SpeedPack_H_
#define _SpeedPack_H_

#include "PackObj.h"

/**
* �ٶȰ�����
*
*#include "PackObj.h" <BR>
*-llib
*
* ����ʵ��������࣬�������ס�󣬽�ʹ�����ʱ���ڼ��ٻ����
*
* @seesomething
*/


class SpeedPack :public PackObj
{
	bool isFasten;	/* �ٶ�����ֵ��Ϊtrue��ʾ���ٰ���������Ϊ���ٰ��� */
public:

	// ����������ڿ��ƺ������������������	

	/**
	*Ĭ�Ϲ��캯��
	*/
	SpeedPack();

	/**
	*���ι��캯��
	*
	*@param physicsComponent ������
	*@param graphicsComponent ͼ�񲿼�
	*@param id ����ID
	*@param isFasten �����õİ����ٶ�����ֵ��Ĭ��Ϊtrue
	*/
	SpeedPack(PhysicsComponent* physicsComponent, GraphicsComponent* graphicsComponent, std::string* id, bool isFasten=true);
	
	/**
	*��������
	*/
	~SpeedPack();

	/**
	*��¡���������
	*/
	EntityObj* Clone() override;

	//�����Դ�ȡ

	/**
	*��ȡ�����ٶ�����ֵ
	*/
	const bool getFasten();

	/**
	*���ð����ٶ�����ֵ
	*/
	void setFasten(bool isFasten);
};
#endif
