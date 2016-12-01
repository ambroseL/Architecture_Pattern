#ifndef _ObjManager_H_
#define _ObjManager_H_
#include "vector"
#include "cocos2d.h"
#include "BallObj.h"
#include "PaddleObj.h"
#include "MyJoints.h"
#include "WallObj.h"
//#include "GameLayer.h"

using namespace cocos2d;
/**
* ���������
*
*#include <vector>
*#include "2d/CCParticleExamples.h"
*-llib
*
* �ṩ�������ɾ�Ĳ飬ά��������ص�����
*
* @seesomething
*/

extern class GameLayer;

class ObjManager
{


public:
	typedef void (ObjManager::*ptr_func1)();
	typedef void (ObjManager::*ptr_func2)(b2Vec2 pos);

	// ����������ڿ��ƺ������������������	

	/**
	*Ĭ�Ϲ��캯��
	*/
	ObjManager();

	/**
	*��������
	*/
	~ObjManager();

	/**
	*��ʼ������
	*/
	void init();

	//�����

	/**
	*��������
	*@parameter level �ؿ��ȼ�
	*@parameter world �ؿ�������������
	*@parameter layer �ؿ�����ͼ��
	*/
	void createObj(int level, b2World* bWorld, GameLayer* Llayer);
	

	/**
	*�������ؽ�
	*@target ��ʼ��Ŀ��ê�㣨 poB����ĸ����ê�㣩
	*@frequencyHz ��Ӧ���ٶ�5.0f
	*@dampingRatio ����	0-10.7f
	*/
	MyMouseJoint* createMouseJoint( b2Vec2 target, float32 frequencyHz, float32 dampingRatio);

	/**
	*����������ɾ�������б�
	*@parameter id ��ɾ������id
	*/
	void addObj2Delete(std::string id);
	
	/**
	*�����Ӽ����ɾ�������б�
	*@parameter cps ��ɾ������ָ��
	*/
	void addParticle2Delete(ParticleSystem* cps);

	/**
	*ɾ����ɾ���б��е�����
	*/
	void deleteObj();
	
	/**
	 * ɾ����ɾ���б��е�����
	 */
	void deleteParticle();

	/**
	*����������������������
	*/
	void updateObj();
	
	/**
	*��������
	*/
	void updateBall();
	
	/**
	*���µ���
	*/
	void updatePaddle();

	/**
	*����ָ����ש��
	*/
	void updateBrickObj(std::string* ids, b2Contact* contact);

	/**
	*����ש����ͼ
	*@sid ש������
	*@ids ש��ID
	*/
	void updateTexture(char sid, std::string* ids);
	
	/**
	*���ö�Ӧ�İ�����ԭ����
	*@sid ��������
	*@ids ����ID
	*/
	void judgePack(char sid);

	//ש��Ч������
	
	/**
	*����
	*/
	void imgBrickWork(b2Vec2 pos);
	/**
	*����
	*/
	void lengthenBrickWork(b2Vec2 pos);
	void shortenBrickWork(b2Vec2 pos);
	/**
	*��͸
	*/
	void permeatBrickWork(b2Vec2 pos);
	/**
	*�ߵ�
	*/
	void reversalBrickWork(b2Vec2 pos);
	/**
	*�ٶ�
	*/
	void accelerateBrickWork(b2Vec2 pos);
	void deaccelerateBrickWork(b2Vec2 pos);

	/**
	*����
	*/
	void transmitBrickWork();
	/**
	*����
	*/
	void upgradeBrickWork(b2Vec2 pos);
	/**
	*ճ�
	*/
	void stickyBrickWork(b2Vec2 pos);


	//����Ч������

	/**
	*����
	*/
	void imgPackWork();
	/**
	*����
	*/
	void lengthenPackWork();
	void shortenPackWork();

	/**
	*��͸
	*/
	void permeatPackWork();
	/**
	*�ߵ�
	*/
	void reversalPackWork();
	/**
	*�ٶ�
	*/
	void acceleratePackWork();
	void deacceleratePackWork();
	/**
	*����
	*/
	void upgradePackWork();
	/**
	*ճ�
	*/
	void stickyPackWork();


	//����Ч����ԭ����

	/**
	*����
	*/
	void imgPackReset();
	/**
	*����
	*/
	void lengthenPackReset();
	void shortenPackReset();

	/**
	*��͸
	*/
	void permeatPackReset();
	/**
	*�ߵ�
	*/
	void reversalPackReset();
	/**
	*�ٶ�
	*/
	void acceleratePackReset();
	void deacceleratePackReset();
	/**
	*����
	*/
	void upgradePackReset();

	/**
	*�������ԭ�����������б�
	*/
	void clearLengthenPackResetList();

	/**
	*�������ԭ�����̰����б�
	*/
	void clearShortenPackResetList();

	/**
	*�������ԭ�ĵߵ������б�
	*/
	void clearReversalPackResetList();

	/**
	*�������ԭ�ľ�������б�
	*/
	void clearImagePackResetList();

	/**
	*�������ԭ�ļ��ٰ����б�
	*/
	void clearAcceleratePackResetList();

	/**
	*�������ԭ�ļ��ٰ����б�
	*/
	void clearDeacceleratePackResetList();

	/**
	*�������ԭ�����������б�
	*/
	void clearUpgradePackResetList();

	/**
	*�������ԭ�Ĵ�͸�����б�
	*/
	void clearPermeatPackResetList();

	/**
	*��ȡ��ǰlevel��ש����
	*/
	int getBrickCount() const;

	/**
	*��ȡ����ĵ�ǰλ��
	*/
	b2Vec2 getBallPos() const;

	/**
	*�򵲰�ʩ������
	*@force ģ������
	*/
	void applyForce2Paddle(b2Vec2 force);

	/**
	*���õ������ٶ�����
	*@linearDamping ģ�����ٶ�����
	*/
	void setPaddleLinearDamping(float32 linearDamping);

	/**
	*��������
	*/
	void shootBall();

	/**
	*���õ����ٶ�
	*@Speed �����õĵ����ٶ�
	*/
	void setPaddleVelocity(b2Vec2 Speed);

	float getPaddleInitialWidth() const { return paddle->getInitialWidth(); }

	/**
	*��ȡ����ľ���
	*/
	Sprite* getPaddleSprite() const;

	b2Vec2 getBallSpeed() const { return ball->getSpeed(); }

	int getBallAttack() { return ball->getAttack(); }

	bool getBallPermeat() const { return ball->getPermeat(); }

	void setBallSpeed(const b2Vec2& speed) { ball->setSpeed(speed); }


private:

	BallObj* ball;											    /* ���� */

	PaddleObj* paddle;										    /* ���� */

	PaddleObj* imgPaddle;									    /* ���񵲰� */

	WallObj* ground;											/* ���� */

	//MyMouseJoint* mouseJoint;									/* ���ؽ�*/

	std::vector<ParticleSystem*> deleteParticleList;   /* ��ɾ���������б� */

	std::vector<std::string> deleteObjList;					    /* ��ɾ��������ID�б� */

	//����ԭ�İ����б�
	std::vector<std::string> resetLengthenPackList;				/* ���� */
	std::vector<std::string> resetShortenPackList;				/* ���� */
	std::vector<std::string> resetReversalPackList;				/* �ߵ� */
	std::vector<std::string> resetImagePackList;				/* ���� */
	std::vector<std::string> resetAcceleratePackList;			/* ���� */
	std::vector<std::string> resetDeacceleratePackList;			/* ���� */
	std::vector<std::string> resetUpgradePackList;				/* ���� */
	std::vector<std::string> resetPermeatPackList;				/* ��͸ */
	
	std::map<std::string, EntityObj*> objMap;				    /* �������������и���ID�Ͷ�Ӧ������ӳ�� */

	std::map<char, ptr_func1> packWorkFuncMap;			        /* work�������������ӳ�� */

	std::map<char, ptr_func2> brickWorkFuncMap;			        /* work�������������ӳ�� */

	std::map<char, std::string> objTexturePathMap;				/*������ͼ·�����������ӳ��*/

	int brickCount;											/* ש������ */

	int imagePackIndex;										/* �������ID */
	int reversalPackIndex;									/* �ߵ�����ID */
	int lengthenPackIndex;									/* ��������ID */
	int shortenPackIndex;									/* ���̰���ID */
	int acceleratePackIndex;								/* ���ٰ���ID */
	int deacceleratePackIndex;								/* ���ٰ���ID */
	int upgradePackIndex;									/* ��������ID */
	int permeatPackIndex;									/* ��͸����ID */
	int stickyPackIndex;									/* ճ����ID */
	int transmitBrickIndex;									/* ����ש��ID */
	int ballObjIndex;										/* ����ID */
	int mouseJointIndex;									/* ���ؽ�ID */

	GameLayer* layer;											/* �������ڲ� */
	b2World* world;											/* ���������������� */
};
#endif

