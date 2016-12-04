#include "PaddleObj.h"// class implemented

/////////////// PUBLIC///////////////////////

//================= ���캯�� ====================

PaddleObj::PaddleObj():EntityObj(), isSticky(false), isImage(false), isReversal(false), sWidth(60.0), sHeight(20.0)
{
}// PaddleObj

PaddleObj::PaddleObj(PhysicsComponent* physicsComponent, GraphicsComponent* graphicsComponent, std::string* id, bool bSticky, bool bImage, bool bReversal):
EntityObj(physicsComponent, graphicsComponent, id), isSticky(bSticky), isImage(bImage), isReversal(bReversal)
{
	cocos2d::Sprite* dSp = graphicsComponent->getSprite();
	cocos2d::Size size = dSp->getContentSize();                        //��ȡ����ߴ�
	float scaleX = dSp->getScaleX();								   //��ȡ�������ű�
	float scaleY = dSp->getScaleY();								   //��ȡ�������ű�
	this->sWidth = size.width * scaleX / 2;							   //���ó�ʼ�볤��
	this->sHeight = size.height * scaleY / 2;						   //���ó�ʼ��߶�
	this->getPhysicsComponent()->getBody()->SetFixedRotation(true);	   //���ò��ɷ�ת
}// PaddleObj


PaddleObj::~PaddleObj()
{
}// ~PaddleObj

EntityObj* PaddleObj::Clone()
{
	return new PaddleObj(physicsComponent->Clone(), graphicsComponent->Clone(), new std::string(id->c_str()), isSticky, isImage, isReversal);
}


//==============���Դ�ȡ =====================

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

//==============��Ĳ��� =====================

void PaddleObj::Reset()
{
	
}

