#ifndef _ShortenPack_H_
#define _ShortenPack_H_
#include "PackObj.h"

/**
* ���̰�����
*
*#include "PackObj.h" <BR>
*-llib
*
* ����ʵ��������࣬�������ס�󣬽�ʹ��������������
*
* @seesomething
*/
class ShortenPack :public PackObj
{
public:// ����������ڿ��ƺ������������������	

	/**
    *Ĭ�Ϲ��캯��	   
    *
	*/
	ShortenPack();

	/**
	*���ι��캯��
	*
	*@param physicsComponent ������
	*@param graphicsComponent ͼ�񲿼�
	*@param id ����ID
	*/
	ShortenPack(PhysicsComponent* physicsComponent, GraphicsComponent* graphicsComponent, std::string* id);


	/**
	*��������
	*/
	~ShortenPack();
};
#endif

