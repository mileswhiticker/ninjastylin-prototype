#include "Mob.hpp"

#include <OGRE/OgreSceneManager.h>
#include <OGRE/OgreEntity.h>
#include <OGRE/OgreSceneNode.h>
#include <OGRE/OgreVector3.h>

#define ENTITY_Y_OFFSET 0

Mob::Mob(std::string a_OgreName, Ogre::SceneManager& a_SceneMgr)
:	m_pMyEntity(NULL)
,	m_pMyNode(NULL)
,	m_SceneMgr(a_SceneMgr)
,	m_ForwardMove(0)
,	m_SideMove(0)
,	m_VertLook(0)
,	m_HorizLook(0)
,	m_EulerX(0)
,	m_EulerY(0)
,	m_EulerZ(0)
,	m_CurGroundHeight(0)
,	m_FallVelocity(0)
{
	static int uid = 0;
	m_NodeUID = uid++;
	m_MoveVector.normalise();
	//make an entity
	m_pMyEntity = m_SceneMgr.createEntity(a_OgreName, "penguin.mesh");

    // Create a SceneNode and attach the Entity to it, matching the camera position
    m_pMyNode = m_SceneMgr.getRootSceneNode()->createChildSceneNode(a_OgreName);
	m_pMyNode->setScale(0.25f,0.25f,0.25f);
	m_pMyNode->attachObject(m_pMyEntity);
	Ogre::Vector3 startPos = Ogre::Vector3( 1300 * float(rand() / RAND_MAX) + 100, 500,  1300 * float(rand() / RAND_MAX) + 100);
	m_pMyNode->setPosition(startPos);
}

Mob::~Mob()
{
	m_SceneMgr.destroyEntity(m_pMyEntity->getName());
	//m_SceneMgr.destroySceneNode(m_pMyNode);
}

void Mob::Update(float a_DeltaT)
{
	//walk in the direction the entity is facing
	Ogre::Vector3 curPos = m_pMyNode->getPosition();
	Ogre::Vector3 curOrientation = m_pMyNode->getOrientation() * Ogre::Vector3::NEGATIVE_UNIT_Z;
	curPos += curOrientation * m_ForwardMove * a_DeltaT * 100;

	//handle strafing
	curOrientation = m_pMyNode->getOrientation() * Ogre::Vector3::NEGATIVE_UNIT_X;
	curPos += curOrientation * m_SideMove * a_DeltaT * 100;

	//match the height of the ground as closely as possible
	if(curPos.y < (m_CurGroundHeight + 10 + ENTITY_Y_OFFSET))
	{
		curPos.y = m_CurGroundHeight + 10 + ENTITY_Y_OFFSET;	//climb up a slope, or possibly hover
		m_FallVelocity = 0;
	}
	else if(curPos.y > (m_CurGroundHeight + 10 + ENTITY_Y_OFFSET))
	{
		m_FallVelocity += 0.98f * a_DeltaT;	//only 1/10 of gravity for now, to show that we aren't bound to the terrain
		curPos.y -= m_FallVelocity;
	}
	m_pMyNode->setPosition(curPos);
	curPos.y -= ENTITY_Y_OFFSET;
}

void Mob::SetPosition(Ogre::Vector3 a_NewPos)
{
	m_pMyNode->setPosition(a_NewPos);
}

Ogre::Vector3 Mob::GetPosition()
{
	return m_pMyNode->getPosition();
}

void Mob::SetMoveForward(float a_Forward)
{
	m_ForwardMove = a_Forward;
}

void Mob::SetMoveSide(float a_Left)
{
	m_SideMove = a_Left;
}

void Mob::SetLookHoriz(float a_Left)
{
	m_HorizLook = a_Left;
}

void Mob::SetLookVert(float a_Up)
{
	m_VertLook = a_Up;
}

void Mob::SetGroundHeight(float a_Height)
{
	m_CurGroundHeight = a_Height;
}

int Mob::GetNodeUID()
{
	return m_NodeUID;
}
