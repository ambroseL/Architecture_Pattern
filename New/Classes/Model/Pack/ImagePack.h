#ifndef _ImagePack_H_
#define _ImagePack_H_
#include "PackObj.h"

/**
* ���������
*
*#include "PackObj.h" <BR>
*-llib
*
* ����ʵ��������࣬�������ס�󣬽�����һ�����񵲰�
*
* @seesomething
*/

class ImagePack :public PackObj
{
public:
	// ����������ڿ��ƺ������������������	

	/**
	*Ĭ�Ϲ��캯��
	*/
	ImagePack();

	/**
	*���ι��캯��
	*
	*@param physicsComponent ������
	*@param graphicsComponent ͼ�񲿼�
	*@param id ����ID
	*/	
	ImagePack(PhysicsComponent* physicsComponent, GraphicsComponent* graphicsComponent, std::string* id);
	
	/**
	*��������
	*/
	~ImagePack();
};
#endif