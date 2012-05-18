#ifndef MOB_HPP
#define MOB_HPP

#include <OGRE/OgreVector3.h>

namespace Ogre
{
	class Entity;
	class SceneNode;
	class SceneManager;
	class Camera;
};

class Mob
{
public:
	Mob(std::string a_OgreName, Ogre::SceneManager& a_SceneMgr);
	~Mob();
	//
	int GetNodeUID();
	void Update(float a_DeltaT);
	//
	void SetMoveForward(float a_Forward = 1);
	void SetMoveSide(float a_Left = 1);
	void SetLookHoriz(float a_Left = 1);
	void SetLookVert(float a_Up = 1);
	//
	void SetPosition(Ogre::Vector3 a_NewPos);
	Ogre::Vector3 GetPosition();
	//
	void SetGroundHeight(float a_Height);
	//
protected:
	Ogre::Entity* m_pMyEntity;
	Ogre::SceneNode* m_pMyNode;
	Ogre::SceneManager& m_SceneMgr;
	//
	Ogre::Degree m_EulerX;
	Ogre::Degree m_EulerY;
	Ogre::Degree m_EulerZ;
	//
	Ogre::Vector3 m_MoveVector;
	float m_ForwardMove;
	float m_SideMove;
	float m_VertLook;
	float m_HorizLook;
	//
	float m_CurGroundHeight;
	float m_FallVelocity;
	//
private:
	int m_NodeUID;
	//
};

#endif	//MOB_HPP