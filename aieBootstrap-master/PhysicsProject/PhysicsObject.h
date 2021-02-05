#pragma once
#include <glm/glm.hpp>


enum ShapeType
{
	PLANE = 0,
	SPHERE,
	SHAPE_COUNT
};

class PhysicsObject
{
public:
	virtual void FixedUpdate(glm::vec2 a_gravity, float a_timeStep) = 0;
	virtual void Debug() = 0;
	virtual void MakeGizmo() = 0;
	virtual void ResetPosition() {};
	
	ShapeType GetShapeID() { return m_shapeID; }

protected:
	ShapeType m_shapeID;

	PhysicsObject(ShapeType a_shapeID) : m_shapeID(a_shapeID) {}


};

