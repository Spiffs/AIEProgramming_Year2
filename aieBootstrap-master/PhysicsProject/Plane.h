#pragma once
#include "PhysicsObject.h"
class Plane : public PhysicsObject
{
public:
	Plane(glm::vec2 a_normal, float a_distance);
	Plane();
	~Plane();

	virtual void FixedUpdate(glm::vec2 a_gravity, float a_timestep);
	virtual void Draw() {};
	virtual void Debug() {};
	virtual void ResetPos() {};
	virtual void MakeGizmo();

	glm::vec2 GetNormal() { return m_normal; }
	float GetDistance() { return m_distanceToOrigin; }
	glm::vec4 GetColor() { return m_color; }

protected:
	glm::vec2 m_normal;
	float m_distanceToOrigin;
	glm::vec4 m_color;

};


