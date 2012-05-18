#include "PlayerEntity.hpp"

#include <OGRE/OgreSceneManager.h>
#include <OGRE/OgreEntity.h>
#include <OGRE/OgreSceneNode.h>
#include <OGRE/OgreVector3.h>
//#include <OGRE/SdkTrays.h>
#include <OGRE/OgreCamera.h>

#define ENTITY_Y_OFFSET 50

PlayerEntity::PlayerEntity(std::string a_OgreName, Ogre::SceneManager& a_SceneMgr, Ogre::Camera* a_pCamera)
:	Mob(a_OgreName, a_SceneMgr)
,	m_pCamera(a_pCamera)
{
	m_pCamera->setPosition(m_pMyNode->getPosition());
	m_pCamera->setOrientation(m_pMyNode->getOrientation());
}

PlayerEntity::~PlayerEntity()
{
	Mob::~Mob();
}

void PlayerEntity::Update(float a_DeltaT)
{
	Mob::Update(a_DeltaT);

	//bind the camera to the entity position, but bind the entity to the camera orientation
	if(m_pCamera)
	{
		m_pCamera->setPosition(m_pMyNode->getPosition());
		m_pMyNode->setOrientation(m_pCamera->getOrientation());
	}
}

Ogre::Camera* PlayerEntity::GetCamera()
{
	return m_pCamera;
}
