#include "Rigidbody.h"

Rigidbody::Rigidbody(ShapeType a_shapeID, glm::vec2 a_position, glm::vec2 a_velocity, float a_mass, float a_rotation) : PhysicsObject(a_shapeID)
{
	m_position = a_position;
	m_velocity = a_velocity;
	m_mass = a_mass;
	m_rotation = a_rotation;
	m_angularVelocity
}

void Rigidbody::FixedUpdate(glm::vec2 a_gravity, float a_timeStep)
{
	ApplyForce(a_gravity * GetMass() * a_timeStep, glm::vec2(0));
	m_position += GetVelocity() * a_timeStep;

	m_rotation += m_angularVelocity * a_timeStep;
}

void Rigidbody::ApplyForce(glm::vec2 a_force, glm::vec2 a_pos)
{
	m_velocity += a_force / GetMass();
	m_angularVelocity += (a_force.y * a_pos.x - a_force.x * a_pos.y) / GetMoment();
}

void Rigidbody::ResolveCollision(Rigidbody* a_otherActor, glm::vec2 a_contact, glm::vec2* a_collision,
	glm::vec2* a_collisionNormal = nullptr)
{
	// find the vector between their centers, or use the provided
	// direction of force, and make sure its normalised
	glm::vec2 normal = glm::normalize(a_collisionNormal ? 
		*a_collisionNormal : a_otherActor->GetPosition() - GetPosition());

	// get the vector perpendicular to the collision normal 
	glm::vec2 perpendicularColNorm(normal.y - normal.x);

	// these are applied to the readius from axis to the pplication of force
	float radius1 = glm::dot(a_contact - m_position, -perpendicularColNorm);
	float radius2 = glm::dot(a_contact - a_otherActor->GetPosition(), perpendicularColNorm);

	// velocity of the contact point on this object
	float cp_velocity1 = glm::dot(m_velocity, normal) - radius1 * m_angularVelocity;

	// velocity of contact point of the other object
	float cp_velocity2 = glm::dot(a_otherActor->GetPosition(), normal) + radius2 * a_otherActor->m_angularVelocity;

	if (cp_velocity1 > cp_velocity2)
	{
		float mass1 = 1.f / (1.f / m_mass + (radius1 * radius1) / GetMoment());
		float mass2 = 1.f / (1.f / a_otherActor->m_mass + (radius2 * radius2) / a_otherActor->GetMoment());

		float elasticity = 1.f;
		glm::vec2 impact = (1.f + elasticity) * mass1 * mass2 / (mass1 + mass2) * (cp_velocity1 - cp_velocity2) * normal;
		ApplyForce(-impact, a_contact - m_position);
		a_otherActor->ApplyForce(impact, a_contact - a_otherActor->GetPosition())

	}

}
