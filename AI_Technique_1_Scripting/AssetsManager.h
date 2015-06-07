#ifndef ASSETS_MANAGER_H
#define ASSETS_MANAGER_H

#include <SFML\Graphics.hpp>
#include <string>
#include <map>

class AssetsManager
{
public:
	~AssetsManager();
	static AssetsManager&	GetReference();
	static AssetsManager*	GetPointer();
	const sf::Texture&		GetTexture(const std::string& name);

	void ReleaseTextures();
private:
	typedef std::map<std::string, sf::Texture>				TextureMap;
	typedef std::map<std::string, sf::Texture>::iterator	TextureMapIterator;	
	
	AssetsManager();
	AssetsManager(const AssetsManager& am);
	AssetsManager&	operator=(const AssetsManager& am);

	bool			AddTexture(std::string name);

	static AssetsManager	m_instance;
	TextureMap				m_textures;
	TextureMapIterator		m_textureIterator;
	

};

#endif