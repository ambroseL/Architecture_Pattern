#ifndef _ReversalPack_H_
#define _ReversalPack_H_

#include "PackObj.h"

/**
* �ߵ�������
*
*#include "PackObj.h" <BR>
*-llib
*
* ����ʵ��������࣬�������ס�󣬶�ʱ����ʹ�����ƶ������������Ʒ����෴
*
* @seesomething
*/
class ReversalPack:public PackObj 
{
public:
	// ����������ڿ��ƺ������������������	

	/**
	*Ĭ�Ϲ��캯��
	*/
	ReversalPack();

	/**
	*���ι��캯��
	*
	*@param physicsComponent ������
	*@param graphicsComponent ͼ�񲿼�
	*@param id ����ID
	*/
	ReversalPack(PhysicsComponent* physicsComponent, GraphicsComponent* graphicsComponent, std::string* id);

	/**
	*��������
	*/
	~ReversalPack();
};
#endif
