#ifndef _AcceleratePack_H_
#define _AcceleratePack_H_

#include "PackObj.h"
/**
* ���ٰ�����
*
*#include "PackObj.h" <BR>
*-llib
*
* ����ʵ��������࣬�������ס�󣬽�ʹ�����ʱ���ڼ��ٻ����
*
* @seesomething
*/
class AcceleratePack :
	public PackObj
{
public:
	// ����������ڿ��ƺ������������������	

	/**
	*Ĭ�Ϲ��캯��
	*/
	AcceleratePack();

	/**
	*���ι��캯��
	*
	*@param physicsComponent ������
	*@param graphicsComponent ͼ�񲿼�
	*@param id ����ID
	*/
	AcceleratePack(PhysicsComponent* physicsComponent, GraphicsComponent* graphicsComponent, std::string* id);

	/**
	*��������
	*/
	~AcceleratePack();

};
#endif