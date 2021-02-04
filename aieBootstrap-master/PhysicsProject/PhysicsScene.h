#pragma once
#include <glm/glm.hpp>
#include <vector>

class PhysicsObject;

class PhysicsScene
{
public:
	PhysicsScene();
	~PhysicsScene();

	void AddActor(PhysicsObject* a_actor);
	void RemoveActor(PhysicsObject* a_actor);

	// this will call the update of each physicsobject and updates internally. This will handle collision detection and resolution
	void Update(float dt);

	// called once per frame
	void MakeGizmo();
	void DebugScene();

	void SetGravity(const glm::vec2 a_gravity) { m_gravity = a_gravity; }
	glm::vec2 GetGravity() const { return m_gravity; }

	void SetTimeStep(const float a_timeStep) { m_timeStep = a_timeStep; }
	float GetTimeStep() const { return m_timeStep; }


protected:
	glm::vec2 m_gravity;
	float m_timeStep;

	std::vector<PhysicsObject*> m_actors;
};

