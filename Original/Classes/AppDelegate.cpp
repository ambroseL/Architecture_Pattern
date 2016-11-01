#include "AppDelegate.h"
#include "GameSceneManager.h"
USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate()
{
}

//��ʼ������
bool AppDelegate::applicationDidFinishLaunching()
{
	//��ȡ����
	auto director = Director::getInstance();
	auto glview = director->getOpenGLView();
	//��������glview�����´���
	if (!glview)
	{
		glview = GLViewImpl::create("My Game");
	}
	//���û�����GLView
	director->setOpenGLView(glview);
	//����Ŀ��ֱ���,��ķֱ��ʵ���Ļ���Զ����»����ҽ��ж�ֱ�������Ӧ
	glview->setDesignResolutionSize(1024, 768, ResolutionPolicy::EXACT_FIT);
	//�ر�FPS����Ϣ
	director->setDisplayStats(false);
	//ϵͳģ��ʱ����
	director->setAnimationInterval(1.0 / 60);
	//��������������
	GameSceneManager* gsm = new GameSceneManager();

	//��������ӭ������ʾ
	gsm->createScene();
	//���ߵ���ʹ���Ǹ�����
	director->runWithScene(gsm->welcomeScene);

	return true;
}

//����������̨ʱ���ô˷���
void AppDelegate::applicationDidEnterBackground()
{
	//ֹͣ����
	Director::getInstance()->stopAnimation();
}

//���������ǰ̨ʱ����
void AppDelegate::applicationWillEnterForeground()
{
	//��ʼ����
	Director::getInstance()->startAnimation();
}
