#include "GuiAnimation.h"

GuiAnimation::GuiAnimation()
{
	mMoveX = 0;
	mMoveY = 0;
	mMoveSpeed = 0;
	mFadeRate = 0;
}

void GuiAnimation::move(int x, int y, int speed)
{
	mMoveX = x;
	mMoveY = y;
	mMoveSpeed = speed;
}

void GuiAnimation::fadeIn(int time)
{
	mOpacity = 0;
	setChildrenOpacity(0);

	mFadeRate = time;
}

void GuiAnimation::fadeOut(int time)
{
	mOpacity = 255;
	setChildrenOpacity(255);

	mFadeRate = -time;
}

void GuiAnimation::update(int deltaTime)
{
	float mult = deltaTime * 0.05f;

	if(mMoveX != 0 || mMoveY != 0)
	{
		int offsetx = (mMoveX > mMoveSpeed) ? mMoveSpeed : mMoveX;
		int offsety = (mMoveY > mMoveSpeed) ? mMoveSpeed : mMoveY;

		offsetx = (int)(offsetx * mult);
		offsety = (int)(offsety * mult);

		moveChildren(offsetx, offsety);

		mMoveX -= offsetx;
		mMoveY -= offsety;
	}

	if(mFadeRate != 0)
	{
		int opacity = (int)mOpacity + mFadeRate;
		if(opacity > 255)
		{
			mFadeRate = 0;
			opacity = 255;
		}

		if(opacity < 0)
		{
			mFadeRate = 0;
			opacity = 0;
		}

		mOpacity = (unsigned char)opacity;
		setChildrenOpacity((unsigned char)opacity);
	}
}

void GuiAnimation::addChild(GuiImage* gui)
{
	mChildren.push_back(gui);
}

void GuiAnimation::moveChildren(int offsetx, int offsety)
{
	for(unsigned int i = 0; i < mChildren.size(); i++)
	{
		GuiImage* comp = mChildren.at(i);
		comp->setOffset(comp->getOffsetX() + offsetx, comp->getOffsetY() + offsety);
	}
}

void GuiAnimation::setChildrenOpacity(unsigned char opacity)
{
	for(unsigned int i = 0; i < mChildren.size(); i++)
	{
		mChildren.at(i)->setOpacity(opacity);
	}
}
