#ifndef _UpgradePack_H_
#define _UpgradePack_H_

#include "PackObj.h"

/**
* ����������
*
*#include "PackObj.h" <BR>
*-llib
*
* ����ʵ��������࣬�������ס�󣬶�ʱ����ʹ���幥��������һ�ȼ�
*
* @seesomething
*/
class UpgradePack :public PackObj
{
public:

	// ����������ڿ��ƺ������������������	

	/**
	*Ĭ�Ϲ��캯��
	*/
	UpgradePack();

	/**
	*���ι��캯��
	*
	*@param physicsComponent ������
	*@param graphicsComponent ͼ�񲿼�
	*@param id ����ID
	*/
	UpgradePack(PhysicsComponent* physicsComponent, GraphicsComponent* graphicsComponent, std::string* id);

	/**
	*��������
	*/
	~UpgradePack();
};
#endif
