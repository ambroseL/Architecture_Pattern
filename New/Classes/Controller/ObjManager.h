#ifndef _ObjManager_H_
#define _ObjManager_H_
#include "vector"
#include "cocos2d.h"
#include "BallObj.h"
#include "PaddleObj.h"

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

class ObjManager:public cocos2d::Node
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


	//�����

	/**
	*��������
	*@parameter level �ؿ��ȼ�
	*@parameter world �ؿ�������������
	*@parameter layer �ؿ�����ͼ��
	*/
	void createObj(int level, b2World* bWorld, cocos2d::Layer* Llayer);
	
	/**
	*����������ɾ�������б�
	*@parameter id ��ɾ������id
	*/
	void addObj2Delete(std::string id);
	
	/**
	*�����Ӽ����ɾ�������б�
	*@parameter cps ��ɾ������ָ��
	*/
	void addParticle2Delete(cocos2d::ParticleSystem* cps);

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
	void judgePack(char sid, std::string* ids);

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
	void clearLengthenPackResetList(float delta);

	/**
	*�������ԭ�����̰����б�
	*/
	void clearShortenPackResetList(float delta);

	/**
	*�������ԭ�ĵߵ������б�
	*/
	void clearReversalPackResetList(float delta);

	/**
	*�������ԭ�ľ�������б�
	*/
	void clearImagePackResetList(float delta);

	/**
	*�������ԭ�ļ��ٰ����б�
	*/
	void clearAcceleratePackResetList(float delta);

	/**
	*�������ԭ�ļ��ٰ����б�
	*/
	void clearDeacceleratePackResetList(float delta);

	/**
	*�������ԭ�����������б�
	*/
	void clearUpgradePackResetList(float delta);

	/**
	*�������ԭ�Ĵ�͸�����б�
	*/
	void clearPermeatPackResetList(float delta);

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

private:

	BallObj* ball;											    /* ���� */

	PaddleObj* paddle;										    /* ���� */

	PaddleObj* imgPaddle;									    /* ���񵲰� */

	std::vector<cocos2d::ParticleSystem*> deleteParticleList;   /* ��ɾ���������б� */

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

	cocos2d::Layer* layer;									/* �������ڲ� */
	b2World* world;											/* ���������������� */
};
#endif

