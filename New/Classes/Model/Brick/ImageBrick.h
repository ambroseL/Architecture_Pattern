#ifndef _ImageBrick_H_
#define _ImageBrick_H_
#include "BrickObj.h"

/**
* ����ש����
*
*#include "BrickObj.h" <BR>
*-llib
*
* ש��ʵ��������࣬�����������������
*
* @seesomething
*/
class ImageBrick :public BrickObj
{
public:
	// ����������ڿ��ƺ������������������	

	/**
	*Ĭ�Ϲ��캯��
	*/
	ImageBrick();

	/**
	*���ι��캯��
	*
	*@param physicsComponent ������
	*@param graphicsComponent ͼ�񲿼�
	*@param id ����ID
	*@param iHP �����õ�ש������ֵ��Ĭ��Ϊ1
	*/
	ImageBrick(PhysicsComponent* physicsComponent, GraphicsComponent* graphicsComponent, std::string* id, int iHP = 1);
	
	/**
	*��������
	*/
	~ImageBrick();
};
#endif