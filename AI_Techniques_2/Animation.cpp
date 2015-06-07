#include "Animation.h"
#include "GlobalClock.h"

Animation::Animation(const sf::Sprite& sprite, const int frameCount, const bool looping, const float updateRate) :
	m_sprite(sprite),
	m_currentFrame(0),
	m_frameCount(frameCount),
	m_frameWidth(m_sprite.getTextureRect().width/frameCount),
	m_frameHeight(m_sprite.getTextureRect().height),
	m_looping(looping),
	m_updateRate(updateRate)
{
	m_sprite.setTextureRect(sf::IntRect(int(m_frameWidth * m_currentFrame), 0, int(m_frameWidth), int(m_frameHeight)));
	m_rateClock.restart();
}

Animation::~Animation()
{
}

Animation::Animation(const Animation& animation) :
	m_sprite(animation.m_sprite),
	m_currentFrame(animation.m_currentFrame),
	m_frameCount(animation.m_frameCount),
	m_frameWidth(animation.m_frameWidth),
	m_frameHeight(animation.m_frameHeight),
	m_looping(animation.m_looping),
	m_updateRate(animation.m_updateRate),
	m_rateClock(animation.m_rateClock)
{
}
Animation& Animation::operator=(const Animation& animation)
{
	m_sprite		= animation.m_sprite;
	m_currentFrame	= animation.m_currentFrame;
	m_frameCount	= animation.m_frameCount;
	m_frameWidth	= animation.m_frameWidth;
	m_frameHeight	= animation.m_frameHeight;
	m_looping		= animation.m_looping;
	m_updateRate	= animation.m_updateRate;
	m_rateClock		= animation.m_rateClock;

	return *this;
}

const sf::Sprite& Animation::GetSprite() const
{
	return m_sprite;
}

const sf::Sprite& Animation::GetNext()
{
	if(m_rateClock.getElapsedTime().asSeconds() >= m_updateRate * (0.00006 / GlobalClock::Ref().ElapsedTime().asSeconds()))
	{
		m_currentFrame++;
		if(m_currentFrame >= m_frameCount)
		{
			if(m_looping)
				m_currentFrame = 0;
			else
				m_currentFrame -= 1; 
		}
		m_sprite.setTextureRect(sf::IntRect(int(m_frameWidth * m_currentFrame), 0, int(m_frameWidth), int(m_frameHeight)));
		m_rateClock.restart();
	}
	
	return m_sprite;
}

const bool Animation::IsLooping() const
{
	return m_looping;
}

void Animation::SetSprite(const sf::Sprite& sprite, const int frameCount)
{
	m_frameWidth	= sprite.getTextureRect().width/frameCount;
	m_frameHeight	= sprite.getTextureRect().height;
	m_sprite		= sprite;
	m_frameCount	= frameCount;

	Reset();
}

void Animation::SetLooping(const bool looping)
{
	m_looping = looping;
}

void Animation::SetUpdateRate(const float rate)
{
	m_updateRate = rate;
}

void Animation::Reset()
{
	m_currentFrame = 0;
	m_rateClock.restart();
	m_sprite.setTextureRect(sf::IntRect(int(m_frameWidth * m_currentFrame), 0, int(m_frameWidth), int(m_frameHeight)));
}