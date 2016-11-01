#ifndef _Beginlayer_H_
#define _Beginlayer_H_
#include "cocos2d.h"
#include "Joints.h"
#include "Box2D/Box2D.h"
#include "GameSceneManager.h"
#include "WelcomeLayer.h"
#include <vector>
using namespace cocos2d;
class Beginlayer : public Layer
{
public:
	b2World* world;//��������
	Size visibleSize;//�ɼ�����ߴ�
	Point origin;//ԭ������
	Sprite* backgroundsp;//��������
	bool isWin = false;//���ؿ��Ƿ�ʤ��
	bool isPauseEnble = true;//��ͣ�˵��ܲ�����
	GameSceneManager* gsm;//���������ߵ�ָ��
	Welcomelayer* wl;//��ӭ����ָ��

	Sprite* lifeSp;//��ʾʣ�����
	Sprite* toumingBgSp;//͸����������
	bool isPause = false;//�Ƿ���ͣ�ı��
	Sprite* PauseSp;//��ͣʱ������ľ��
	void playYX();//������Ч�ķ���
	void toNext();//ʹ�����׼���ȥ��һ�صķ���
	void setLevel(int cnt) { level = cnt; }
	static int level;//�ؿ���
	
	bool keyright = false;//�Ҽ��Ƿ񱻰�ס
	bool keyleft = false;//����Ƿ񱻰�ס

	//ɾ���б�
	std::vector<ParticleFire*> listForFire;    //����Ҫɾ��������Ч��
	std::vector<b2Body*> listDestroy;        //Ҫ���ٵĸ����б�
	std::vector<std::string> listForDel;    //����Ҫɾ���ĸ���ID

	//ÿ���б���ഢ����Ҫ��ԭ�İ���
	std::vector<std::string> listForPackL;//����
	std::vector<std::string> listForPackB;//����
	std::vector<std::string> listForPackR;//�ߵ�
	std::vector<std::string> listForPackI;//����
	std::vector<std::string> listForPackA;//����
	std::vector<std::string> listForPackD;//����
	std::vector<std::string> listForPackU;//����
	std::vector<std::string> listForPackF;//��͸

	std::map<std::string, PhyObject*> pom;   //�������������ﻹ���ڵĸ���ID�;������
	
	Paddle* paddle;//�����ָ��

	Ball* ball;//���ָ��

	PhyObject* package;//������ָ��

	Menu* pauseMenu;//��ͣ�˵���ָ��

	void toPause();

	int index;

	void judgePack(char sid, std::string* ids);//�ð������뻹ԭ�����б�ķ���
	//��ԭ����Ч���ķ���
	void L_Reset(float delta);
	void B_Reset(float delta);
	void R_Reset(float delta);
	void I_Reset(float delta);
	void A_Reset(float delta);
	void D_Reset(float delta);
	void U_Reset(float delta);
	void F_Reset(float delta);

	void Cut(float delta);//�������ӵķ���

	void RestartGame();

	//��������ģ��
	void step();
	PhyObject* ground;

	//��������
	void update(float delta);

	//��ʼ���ķ���
	virtual bool init();

	//�رղ˵��ص�����
	void menuClose(cocos2d::Ref*  pSender);

	//��ͣ�˵��ص�����
	void menuPause(cocos2d::Ref*  pSender);

	//�����˵��ص�����
	void menuReset(cocos2d::Ref*  pSender);

	//�����˵��ص�����
	void menuContinue(cocos2d::Ref*  pSender);

	//�ػ�ӭ����˵��ص�����
	void menuBack(cocos2d::Ref*  pSender);

	//��һ�ز˵��ص�����
	void menuNext(cocos2d::Ref*  pSender);

	//����ʱ�ķ���
	void goNext();
	
	MouseJoint* mj;

	//����¼�����
	bool myOnTouchBegan(Touch *touch, Event *event); //��ʼ�����¼��Ĵ�����
	void myOnTouchMoved(Touch *touch, Event *event); //�����ƶ��¼��Ĵ�����
	void myOnTouchEnded(Touch *touch, Event *event); //���ؽ����¼��Ĵ�����
	void myOnTouchCancelled(Touch *touch, Event *event); //������ֹ�¼��Ĵ�����

	//�����¼�����
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);//���¼���ʱ�Ĵ�����
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);//�ɿ�����ʱ�Ĵ�����
	//~Beginlayer();
	//Cocos2d-x�ж����һ���꣬����ָ�����͵Ķ���
	//��������Ӧ�ĳ�ʼ�����ͷŹ���
	CREATE_FUNC(Beginlayer);
};
#endif
