#ifndef _DeacceleratePack_H_
#define _DeacceleratePack_H_

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


class DeacceleratePack :public PackObj
{
public:

	// ����������ڿ��ƺ������������������	

	/**
	*Ĭ�Ϲ��캯��
	*/
	DeacceleratePack();

	/**
	*���ι��캯��
	*
	*@param physicsComponent ������
	*@param graphicsComponent ͼ�񲿼�
	*@param id ����ID
	*@param isFasten �����õİ����ٶ�����ֵ��Ĭ��Ϊtrue
	*/
	DeacceleratePack(PhysicsComponent* physicsComponent, GraphicsComponent* graphicsComponent, std::string* id);
	
	/**
	*��������
	*/
	~DeacceleratePack();

};
#endif
