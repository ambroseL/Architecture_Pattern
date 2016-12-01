#ifndef _BallObj_H_
#define _BallObj_H_

#include "EntityObj.h"

/**
* ������
*
*#include "EntityObj.h" <BR>
*-llib
*
* ����Ϊmodel�࣬�洢����Ļ���������Ϣ����������������֮�������Ӧ�Ĺ��������ٶ�״̬, ��͸״̬����ʼ�ٶ�
*
* @seesomething
*/



/* �����ٶȵ�����״̬ */
enum SpeedState
{
	Slow = 0,	/* ����״̬ */
	Fast = 1,	/* ����״̬ */
	Normal = 2	/* ����״̬ */
};


class BallObj :public EntityObj
{
	int attack;					/* ���幥���� */

	SpeedState speedState;		/* �����˶�״̬ */

	bool isPermeat;				/* �����Ƿ��ڴ�͸״̬ */

	b2Vec2 initialSpeed;				/* ������ٶ� */

	b2Vec2 constantSpeed;				/* ���嵱ǰ���ٶ� */

public:

	// ����������ڿ��ƺ������������������	
	
	/**
	*Ĭ�Ϲ��캯��
	*/
	BallObj();
	
	/**
	*���ι��캯��
	*
	*@param physicsComponent ������
	*@param graphicsComponent ͼ�񲿼�
	*@param id ����ID
	*@param attack ���幥������Ĭ��ֵΪ1
	*@param bSpeed ������ٶȣ�Ĭ��ֵΪ0
	*@param speedState �����˶�״̬��Ĭ��ֵΪslow
	*@param isPermeat �����Ƿ��ڴ�͸״̬������ש����ײʱ��������ֱ�ӽ�ש���ƻ���Ĭ��ֵΪfalse
	*/
	BallObj(PhysicsComponent* physicsComponent, GraphicsComponent* graphicsComponent, std::string* id, int attack = 1, 
		b2Vec2 bSpeed = b2Vec2(0,0), SpeedState speedState = Normal, bool isPermeat = false);
	
	/**
	*��������
	*/
	~BallObj();
	
	/**
	*��¡���������
	*/
	EntityObj* Clone() override;

	//�����
	
	/**
	*���ú��������������������ֵ��ԭΪĬ��ֵ
	*/
	void Reset();

	//�����Դ�ȡ
	
	/**
	*��ȡ����ĳ��ٶ�
	*/
	const b2Vec2 getInitialSpeed();

	/**
	*��������ĳ��ٶ�
	*/
	void setInitialSpeed(b2Vec2 initialSpeed);

	/**
	*��ȡ����Ĺ�����
	*/
	const int getAttack();

	/**
	*��������Ĺ�����
	*@parameter iAttack �����õ����幥������ֵ
	*/
	void setAttack(int iAttack);

	/**
	*��ȡ����İ뾶
	*/
	const float getRadius();

	/**
	*��������İ뾶
	*@param fRadius �����õ�����뾶��ֵ
	*/
	void setRadius(float fRadius);

	/**
	*��ȡ�����ʵʱ���ٶ�
	*/
	b2Vec2 getConstantSpeed();

	/**
	*���������ʵʱ���ٶ�
	*@param speed �����õ��������ٶ�
	*/
	void setConstantSpeed(b2Vec2 speed);

	//���״̬���ü���ѯ
	
	/**
	*����������ٶ�״̬
	*@param speedState �����˶�״̬
	*/
	void setSpeedState(SpeedState speedState);

	/**
	*��ȡ����ĵ�ǰ�ٶ�״̬
	*/
	const SpeedState getSpeedState();

	/**
	*��ȡ�����Ƿ��ڴ�͸״̬
	*/
	const bool getPermeat();

	/**
	*��������Ĵ�͸״̬
	*/
	void setPermeat(bool isPermeat);
	

};

#endif