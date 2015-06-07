#include "AssetsManager.h"
#include <iostream>

using namespace std;

const static string PICTURE_PATH = "Assets/Pictures/";

AssetsManager AssetsManager::m_instance;
AssetsManager&	AssetsManager::GetReference()
{
	return m_instance;
}

AssetsManager*	AssetsManager::GetPointer()
{
	return &m_instance;
}

AssetsManager::AssetsManager(){}
AssetsManager::~AssetsManager()
{
	ReleaseTextures();
}

const sf::Texture& AssetsManager::GetTexture(const std::string& name)
{
	m_textureIterator = m_textures.find(name);

	if(m_textureIterator != m_textures.end())
		return m_textureIterator->second;

	if(!AddTexture(name))
		cerr << "\nERROR: could not load texture [" << name << "]";

	m_textureIterator = m_textures.find(name);
	if(m_textureIterator == m_textures.end())
		cerr << "\nERROR: unable to find texture [" << name << "]";

	return m_textureIterator->second;
}

bool AssetsManager::AddTexture(std::string name)
{
	sf::Texture tex;

	if(!tex.loadFromFile(PICTURE_PATH + name))
		return false;

	tex.setSmooth(false);

	m_textures.insert(make_pair(name, tex));

	return true;
}

void AssetsManager::ReleaseTextures()
{
	m_textures.clear();
}