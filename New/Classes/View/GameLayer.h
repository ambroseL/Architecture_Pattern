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
	
	b2World* world;//��������

	Sprite* lifeSp; //��������
	Sprite* transparentBackgroundSp;//͸����������
	Sprite* PauseSp;//��ͣʱ������ľ��

	int level = 1;

public:
	// ����������ڿ��ƺ���

	/**
	 *��ʼ���ķ�������createʱ���Զ�����
	 *cocos2dx����
	 */
	bool init() override;

	/**
	*Cocos2d-x�ж����һ���꣬����ָ�����͵Ķ���,��������Ӧ�ĳ�ʼ�����ͷŹ���
	*/
	CREATE_FUNC(GameLayer);

	//�����
	
	/**
	*������Ⱦ����
	*@parameter delta ���¼��
	 */
	void update(float delta);

	/**
	*����ģ�ⷽ��
	*/
	void step();

	/**
	*����¼�����
	*@parameter touch ������Ϣ
	*@parameter event �����¼�
	*/
	bool myOnTouchBegan(Touch *touch, Event *event); //��ʼ�����¼��Ĵ�����
	void myOnTouchMoved(Touch *touch, Event *event); //�����ƶ��¼��Ĵ�����
	void myOnTouchEnded(Touch *touch, Event *event); //���ؽ����¼��Ĵ�����
	void myOnTouchCancelled(Touch *touch, Event *event); //������ֹ�¼��Ĵ�����

	/**
	*�����¼�����
	*@parameter keycode ������Ϣ
	*@parameter event �����¼�
	*/
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);//���¼���ʱ�Ĵ�����
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);//�ɿ�����ʱ�Ĵ�����

	/**
	*��ͣ��Ϸ
	*/
	void toPause();

	/**
	*��ͣ�˵��ص�����
	*@pSender �ص������Դ�Ĭ�ϲ���
	*/
	void menuePause(cocos2d::Ref*  pSender);

	/**
	*�����˵��ص�����
	*@pSender �ص������Դ�Ĭ�ϲ���
	*/
	void menueReset(cocos2d::Ref*  pSender);

	/**
	*�ػ�ӭ����˵��ص�����
	*@pSender �ص������Դ�Ĭ�ϲ���
	*/
	void menueBack(cocos2d::Ref*  pSender);

	/**
	*�����˵��ص�����
	*@pSender �ص������Դ�Ĭ�ϲ���
	*/
	void menueContinue(cocos2d::Ref*  pSender);

	/**
	*��һ�ز˵��ص�����
	*@pSender �ص������Դ�Ĭ�ϲ���
	*/
	void menueNext(cocos2d::Ref*  pSender);

	/**
	*����ʱ�ķ���
	*/
	void goNext();

	/**
	*ʹ�����׼���ȥ��һ�صķ���
	*/
	void toNext();

	/**
	*������Ϸ
	*/
	void restartGame();

	/**
	*��������
	*/
	void playSound();

	/**
	*delegate��gamemanager�İ�����ԭ����
	*@parameter delta ����Ƶ��
	*/
	void resetLengthenPack(float delta);
	void resetShortenPack(float delta);
	void resetAcceleratePack(float delta);
	void resetDeacceleratePack(float delta);
	void resetReversalPack(float delta);
	void resetImagePack(float delta);
	void resetPermeatPack(float delta);
	void resetUpgradePack(float delta);

	//�����Դ�ȡ

	/**
	*��ȡ��������
	*/
	Sprite* getLifeSprite() const;

	/**
	*�Ƴ���ͣ����
	*/
	void removePauseSprite();

	/**
	*��ȡ��ǰ�ؿ��ȼ�
	*/
	int getLevel() const { return level; }

	/**
	*���õ�ǰ�ؿ��ȼ�
	*/
	void setLevel(const int& level) { this->level = level; }

	/**
	*���õ�ǰ�ĳ������ƹ�����
	*@parameter sceneManager �����õĳ���������
	*/
	void setSceneManager(SceneManager* sceneManager) const;

	/**
	*���ð�����ԭ�����Ķ�ʱ��
	*@parameter sid ��������
	*/
	void setPackresetschedule(char sid);

	/**
	*��ȡ��ǰ�ؿ��ȼ�
	*/
	void createBricks();

	/**
	*���ñ�������
	*@parameter dSp �����õı�������
	*/
	void setBackgroundSprite(Sprite* dSp);

	/**
	*��������ֵ��ʾ����
	*@parameter dSp �����õ�����ֵ��ʾ����
	*/
	void setPauseSprite(Sprite* dSp);
};
#endif
