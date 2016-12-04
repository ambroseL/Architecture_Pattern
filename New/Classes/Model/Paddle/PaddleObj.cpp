#include "PaddleObj.h"// class implemented

/////////////// PUBLIC///////////////////////

//================= 构造函数 ====================

PaddleObj::PaddleObj():EntityObj(), isSticky(false), isImage(false), isReversal(false), sWidth(60.0), sHeight(20.0)
{
}// PaddleObj

PaddleObj::PaddleObj(PhysicsComponent* physicsComponent, GraphicsComponent* graphicsComponent, std::string* id, bool bSticky, bool bImage, bool bReversal):
EntityObj(physicsComponent, graphicsComponent, id), isSticky(bSticky), isImage(bImage), isReversal(bReversal)
{
	cocos2d::Sprite* dSp = graphicsComponent->getSprite();
	cocos2d::Size size = dSp->getContentSize();                        //获取精灵尺寸
	float scaleX = dSp->getScaleX();								   //获取横向缩放比
	float scaleY = dSp->getScaleY();								   //获取纵向缩放比
	this->sWidth = size.width * scaleX / 2;							   //设置初始半长度
	this->sHeight = size.height * scaleY / 2;						   //设置初始半高度
	this->getPhysicsComponent()->getBody()->SetFixedRotation(true);	   //设置不可翻转
}// PaddleObj


PaddleObj::~PaddleObj()
{
}// ~PaddleObj

EntityObj* PaddleObj::Clone()
{
	return new PaddleObj(physicsComponent->Clone(), graphicsComponent->Clone(), new std::string(id->c_str()), isSticky, isImage, isReversal);
}


//==============属性存取 =====================

const bool PaddleObj::getImage()
{
	return this->isImage;
}

const bool PaddleObj::getReversal()
{
	return this->isReversal;
}

const bool PaddleObj::getSticky()
{
	return this->isSticky;
}

void PaddleObj::setReversal(bool bReversal)
{
	this->isReversal = bReversal;
}

void PaddleObj::setImage(bool bImage)
{
	this->isImage = bImage;
}

void PaddleObj::setSticky(bool bSticky)
{
	this->isSticky = bSticky;
}

const float PaddleObj::getInitialHeight()
{
	return this->sHeight;
}

const float PaddleObj::getInitialWidth()
{
	return this->sWidth;
}

//==============类的操作 =====================

void PaddleObj::Reset()
{
	
}

