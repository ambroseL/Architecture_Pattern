#ifndef _StickyPack_H_
#define _StickyPack_H_

#include "PackObj.h"

/**
* ճ������
*
*#include "PackObj.h" <BR>
*-llib
*
* ����ʵ��������࣬�������ס�󣬽�ʹ��ճ��ڵ����ϣ��ȴ����·���
*
* @seesomething
*/
class StickyPack :public PackObj
{
public:

	// ����������ڿ��ƺ������������������	

	/**
	*Ĭ�Ϲ��캯��
	*/
	StickyPack();

	/**
	*���ι��캯��
	*
	*@param physicsComponent ������
	*@param graphicsComponent ͼ�񲿼�
	*@param id ����ID
	*/
	StickyPack(PhysicsComponent* physicsComponent, GraphicsComponent* graphicsComponent, std::string* id);
	
	/**
	*��������
	*/
	~StickyPack();
};
#endif
