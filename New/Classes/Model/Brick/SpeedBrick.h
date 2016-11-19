#ifndef _PermeatBrick_H_
#define _PermeatBrick_H_

#include "BrickObj.h"

/**
* �ٶ�ש����
*
*#include "BrickObj.h" <BR>
*-llib
*
* ש��ʵ��������࣬�����������ٶȰ���
*
* @seesomething
*/

class SpeedBrick :public BrickObj
{
	bool isFasten;/* �ٶ�����ֵ��Ϊtrue��ʾ����ש�飬����Ϊ����ש�� */

public:

	// ����������ڿ��ƺ������������������	

	/**
	*Ĭ�Ϲ��캯��
	*/
	SpeedBrick();

	/**
	*��������
	*/
	~SpeedBrick();

	/**
	*��¡���������
	*/
	EntityObj* Clone() override;

	/**
	*���ι��캯��
	*
	*@param physicsComponent ������
	*@param graphicsComponent ͼ�񲿼�
	*@param id ����ID
	*@param fasten �ٶ�����ֵ��Ĭ��Ϊtrue
	*@param iHP ש������ֵ��Ĭ��Ϊ1
	*/
	SpeedBrick(PhysicsComponent* physicsComponent, GraphicsComponent* graphicsComponent, std::string* id, bool fasten = true, int iHP = 1);
	
	//�����Դ�ȡ

	/**
	*��ȡש���ٶ�����ֵ
	*/
	const bool getFasten();

	/**
	*����ש���ٶ�����ֵ
	*/
	void setFasten(bool isFasten);
};
#endif