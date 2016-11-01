#include "AppDelegate.h"
#include "GameSceneManager.h"
USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate()
{
}

//初始化方法
bool AppDelegate::applicationDidFinishLaunching()
{
	//获取导演
	auto director = Director::getInstance();
	auto glview = director->getOpenGLView();
	//若不存在glview则重新创建
	if (!glview)
	{
		glview = GLViewImpl::create("My Game");
	}
	//设置绘制用GLView
	director->setOpenGLView(glview);
	//设置目标分辨率,别的分辨率的屏幕将自动上下或左右进行多分辨率自适应
	glview->setDesignResolutionSize(1024, 768, ResolutionPolicy::EXACT_FIT);
	//关闭FPS等信息
	director->setDisplayStats(false);
	//系统模拟时间间隔
	director->setAnimationInterval(1.0 / 60);
	//创建场景管理器
	GameSceneManager* gsm = new GameSceneManager();

	//跌换到欢迎场景显示
	gsm->createScene();
	//告诉导演使用那个场景
	director->runWithScene(gsm->welcomeScene);

	return true;
}

//当程序进入后台时调用此方法
void AppDelegate::applicationDidEnterBackground()
{
	//停止动画
	Director::getInstance()->stopAnimation();
}

//当程序进入前台时调用
void AppDelegate::applicationWillEnterForeground()
{
	//开始动画
	Director::getInstance()->startAnimation();
}
