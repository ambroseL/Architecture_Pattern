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
* 物体管理类
*
*#include <vector>
*#include "2d/CCParticleExamples.h"
*-llib
*
* 提供物体的增删改查，维护物体相关的容器
*
* @seesomething
*/

extern class GameLayer;

class ObjManager
{


public:
	typedef void (ObjManager::*ptr_func1)();
	typedef void (ObjManager::*ptr_func2)(b2Vec2 pos);

	// 类的生命周期控制函数，包括构造和析构	

	/**
	*默认构造函数
	*/
	ObjManager();

	/**
	*析构函数
	*/
	~ObjManager();

	/**
	*初始化函数
	*/
	void init();

	//类操作

	/**
	*创建物体
	*@parameter level 关卡等级
	*@parameter world 关卡所在物理世界
	*@parameter layer 关卡所在图层
	*/
	void createObj(int level, b2World* bWorld, GameLayer* Llayer);
	

	/**
	*创建鼠标关节
	*@target 初始化目标锚点（ poB物体的刚体的锚点）
	*@frequencyHz 响应的速度5.0f
	*@dampingRatio 阻尼	0-10.7f
	*/
	MyMouseJoint* createMouseJoint( b2Vec2 target, float32 frequencyHz, float32 dampingRatio);

	/**
	*将物体加入待删除物体列表
	*@parameter id 待删除物体id
	*/
	void addObj2Delete(std::string id);
	
	/**
	*将粒子加入待删除粒子列表
	*@parameter cps 待删除粒子指针
	*/
	void addParticle2Delete(ParticleSystem* cps);

	/**
	*删除待删除列表中的物体
	*/
	void deleteObj();
	
	/**
	 * 删除待删除列表中的粒子
	 */
	void deleteParticle();

	/**
	*更新物理世界中现有物体
	*/
	void updateObj();
	
	/**
	*更新球体
	*/
	void updateBall();
	
	/**
	*更新挡板
	*/
	void updatePaddle();

	/**
	*更新指定的砖块
	*/
	void updateBrickObj(std::string* ids, b2Contact* contact);

	/**
	*更新砖块贴图
	*@sid 砖块类型
	*@ids 砖块ID
	*/
	void updateTexture(char sid, std::string* ids);
	
	/**
	*调用对应的包裹还原函数
	*@sid 包裹类型
	*@ids 包裹ID
	*/
	void judgePack(char sid);

	//砖块效果函数
	
	/**
	*镜像
	*/
	void imgBrickWork(b2Vec2 pos);
	/**
	*长度
	*/
	void lengthenBrickWork(b2Vec2 pos);
	void shortenBrickWork(b2Vec2 pos);
	/**
	*穿透
	*/
	void permeatBrickWork(b2Vec2 pos);
	/**
	*颠倒
	*/
	void reversalBrickWork(b2Vec2 pos);
	/**
	*速度
	*/
	void accelerateBrickWork(b2Vec2 pos);
	void deaccelerateBrickWork(b2Vec2 pos);

	/**
	*传送
	*/
	void transmitBrickWork();
	/**
	*升级
	*/
	void upgradeBrickWork(b2Vec2 pos);
	/**
	*粘黏
	*/
	void stickyBrickWork(b2Vec2 pos);


	//包裹效果函数

	/**
	*镜像
	*/
	void imgPackWork();
	/**
	*长度
	*/
	void lengthenPackWork();
	void shortenPackWork();

	/**
	*穿透
	*/
	void permeatPackWork();
	/**
	*颠倒
	*/
	void reversalPackWork();
	/**
	*速度
	*/
	void acceleratePackWork();
	void deacceleratePackWork();
	/**
	*升级
	*/
	void upgradePackWork();
	/**
	*粘黏
	*/
	void stickyPackWork();


	//包裹效果还原函数

	/**
	*镜像
	*/
	void imgPackReset();
	/**
	*长度
	*/
	void lengthenPackReset();
	void shortenPackReset();

	/**
	*穿透
	*/
	void permeatPackReset();
	/**
	*颠倒
	*/
	void reversalPackReset();
	/**
	*速度
	*/
	void acceleratePackReset();
	void deacceleratePackReset();
	/**
	*升级
	*/
	void upgradePackReset();

	/**
	*处理待还原的增长包裹列表
	*/
	void clearLengthenPackResetList();

	/**
	*处理待还原的缩短包裹列表
	*/
	void clearShortenPackResetList();

	/**
	*处理待还原的颠倒包裹列表
	*/
	void clearReversalPackResetList();

	/**
	*处理待还原的镜像包裹列表
	*/
	void clearImagePackResetList();

	/**
	*处理待还原的加速包裹列表
	*/
	void clearAcceleratePackResetList();

	/**
	*处理待还原的减速包裹列表
	*/
	void clearDeacceleratePackResetList();

	/**
	*处理待还原的升级包裹列表
	*/
	void clearUpgradePackResetList();

	/**
	*处理待还原的穿透包裹列表
	*/
	void clearPermeatPackResetList();

	/**
	*获取当前level的砖块数
	*/
	int getBrickCount() const;

	/**
	*获取球体的当前位置
	*/
	b2Vec2 getBallPos() const;

	/**
	*向挡板施加拉力
	*@force 模拟拉力
	*/
	void applyForce2Paddle(b2Vec2 force);

	/**
	*设置挡板线速度阻尼
	*@linearDamping 模拟线速度阻尼
	*/
	void setPaddleLinearDamping(float32 linearDamping);

	/**
	*发射球体
	*/
	void shootBall();

	/**
	*设置挡板速度
	*@Speed 待设置的挡板速度
	*/
	void setPaddleVelocity(b2Vec2 Speed);

	float getPaddleInitialWidth() const { return paddle->getInitialWidth(); }

	/**
	*获取挡板的精灵
	*/
	Sprite* getPaddleSprite() const;

	b2Vec2 getBallSpeed() const { return ball->getSpeed(); }

	int getBallAttack() { return ball->getAttack(); }

	bool getBallPermeat() const { return ball->getPermeat(); }

	void setBallSpeed(const b2Vec2& speed) { ball->setSpeed(speed); }


private:

	BallObj* ball;											    /* 球体 */

	PaddleObj* paddle;										    /* 挡板 */

	PaddleObj* imgPaddle;									    /* 镜像挡板 */

	WallObj* ground;											/* 地面 */

	//MyMouseJoint* mouseJoint;									/* 鼠标关节*/

	std::vector<ParticleSystem*> deleteParticleList;   /* 待删除的粒子列表 */

	std::vector<std::string> deleteObjList;					    /* 待删除的物体ID列表 */

	//待还原的包裹列表
	std::vector<std::string> resetLengthenPackList;				/* 增长 */
	std::vector<std::string> resetShortenPackList;				/* 缩短 */
	std::vector<std::string> resetReversalPackList;				/* 颠倒 */
	std::vector<std::string> resetImagePackList;				/* 镜像 */
	std::vector<std::string> resetAcceleratePackList;			/* 加速 */
	std::vector<std::string> resetDeacceleratePackList;			/* 减速 */
	std::vector<std::string> resetUpgradePackList;				/* 升级 */
	std::vector<std::string> resetPermeatPackList;				/* 穿透 */
	
	std::map<std::string, EntityObj*> objMap;				    /* 物理世界中现有刚体ID和对应物体间的映射 */

	std::map<char, ptr_func1> packWorkFuncMap;			        /* work函数与类名间的映射 */

	std::map<char, ptr_func2> brickWorkFuncMap;			        /* work函数与类名间的映射 */

	std::map<char, std::string> objTexturePathMap;				/*物体贴图路径与类名间的映射*/

	int brickCount;											/* 砖块总数 */

	int imagePackIndex;										/* 镜像包裹ID */
	int reversalPackIndex;									/* 颠倒包裹ID */
	int lengthenPackIndex;									/* 增长包裹ID */
	int shortenPackIndex;									/* 缩短包裹ID */
	int acceleratePackIndex;								/* 加速包裹ID */
	int deacceleratePackIndex;								/* 减速包裹ID */
	int upgradePackIndex;									/* 升级包裹ID */
	int permeatPackIndex;									/* 穿透包裹ID */
	int stickyPackIndex;									/* 粘黏包裹ID */
	int transmitBrickIndex;									/* 传送砖块ID */
	int ballObjIndex;										/* 球体ID */
	int mouseJointIndex;									/* 鼠标关节ID */

	GameLayer* layer;											/* 物体所在层 */
	b2World* world;											/* 物体所在物理世界 */
};
#endif

