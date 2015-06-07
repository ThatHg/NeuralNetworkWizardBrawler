#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML\Graphics.hpp>

class Animation
{
public:
	Animation(const sf::Sprite& sprite, const int frameCount, const bool looping, const float updateRate);
	~Animation();
	Animation(const Animation& animation);
	Animation& operator=(const Animation& animation);

	const sf::Sprite&	GetSprite()	const;	// Get current frame
	const sf::Sprite&	GetNext();			// Increase framecounter and get the corrisponding frame
	const bool			IsLooping()	const;

	void				SetSprite(const sf::Sprite& sprite, const int frameCount);
	void				SetLooping(const bool looping);
	void				SetUpdateRate(const float rate);

	void				Reset();			// Reset to first frame and reset other values
private:
	sf::Sprite	m_sprite;
	int			m_currentFrame;
	int			m_frameCount;
	float		m_frameWidth;
	float		m_frameHeight;
	bool		m_looping;
	float		m_updateRate;			// Which rate a new frame should be choosen. (In seconds)
	sf::Clock	m_rateClock;
};

#endif