#ifndef  _GameLayer_H_
#define  _GameLayer_H_

#include "cocos2d.h"
#include "Box2D/Dynamics/b2World.h"
#include "Joints.h"
#include "SceneManager.h"

using namespace cocos2d;
/**
* ����Ϸ������
*
*#include "cocos2d.h"
*#include "Box2D/Dynamics/b2World.h"
*#include "Joints.h"
*#include "SceneManager.h"
*-llib
*
*��Ϸ�������������а�ť�������Ϊlayer��child
*��������ʱ���ø��º�������Ⱦ��Ϸ����
*���߼���صĲ�������delegate����ʽ�������������ദ��
*
* @seesomething
*/
extern class GameManager;

class GameLayer: public Layer
{	
	GameManager* gameManager;
	SceneManager* sceneManager;
	
	b2World* world;//��������

	Sprite* lifeSp; //��������
	Sprite* transparentBackgroundSp;//͸����������
	Sprite* PauseSp;//��ͣʱ������ľ��

	int level;

	public:
	
	//��������
	void update(float delta);

	//��ʼ���ķ���
	bool init() override;

	//��ȡ��������
	Sprite* getLifeSprite() const;

	//����ģ�ⷽ��
	void step();

	void setBackgroundSprite(Sprite* dSp);

	void setPauseSprite(Sprite* dSp);

	void removePauseSprite();

	//����¼�����
	bool myOnTouchBegan(Touch *touch, Event *event); //��ʼ�����¼��Ĵ�����
	void myOnTouchMoved(Touch *touch, Event *event); //�����ƶ��¼��Ĵ�����
	void myOnTouchEnded(Touch *touch, Event *event); //���ؽ����¼��Ĵ�����
	void myOnTouchCancelled(Touch *touch, Event *event); //������ֹ�¼��Ĵ�����

	//�����¼�����
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);//���¼���ʱ�Ĵ�����
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);//�ɿ�����ʱ�Ĵ�����

	void toPause();

	//��ͣ�˵��ص�����
	void menuePause(cocos2d::Ref*  pSender);

	//�����˵��ص�����
	void menueReset(cocos2d::Ref*  pSender);

	//�ػ�ӭ����˵��ص�����
	void menueBack(cocos2d::Ref*  pSender);

	//�����˵��ص�����
	void menueContinue(cocos2d::Ref*  pSender);

	//��һ�ز˵��ص�����
	void menueNext(cocos2d::Ref*  pSender);

	//����ʱ�ķ���
	void goNext();

	// ʹ�����׼���ȥ��һ�صķ���
	void toNext();

	void restartGame();

	//����ԭ����
	void resetPack(float32 delta);

	//������ԭ����
	void checkResetList();

	//������ײʱ����Ч
	void playSound();

	//��ȡ��ǰ�ؿ��ȼ�
	int getLevel() const { return level; }

	//���õ�ǰ�ؿ��ȼ�
	void setLevel(const int& level)  { this->level = level; }

	//���õ�ǰ�ĳ������ƹ�����
	void setSceneManager(SceneManager* sceneManager) { this->sceneManager = sceneManager; }

	//��ȡ��ǰ�ĳ������ƹ�����
	SceneManager* getSceneManager() const { return this->sceneManager; }
																	 
	CREATE_FUNC(GameLayer);//Cocos2d-x�ж����һ���꣬����ָ�����͵Ķ���,��������Ӧ�ĳ�ʼ�����ͷŹ���
};
#endif
