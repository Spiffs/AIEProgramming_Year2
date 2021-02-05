#include "PhysicsScene.h"
#include "PhysicsObject.h"
#include "Rigidbody.h"
#include <iostream>
#include <list>
#include "Sphere.h"
#include "Plane.h"

typedef bool (*fn)(PhysicsObject*, PhysicsObject*);

static fn collisionFunctionArray[] =
{
	PhysicsScene::Plane2Plane, PhysicsScene::Plane2Sphere,
	PhysicsScene::Sphere2Plane, PhysicsScene::Sphere2Sphere
};

PhysicsScene::PhysicsScene() : m_timeStep(0.01f), m_gravity(glm::vec2(0, 0))
{
}

PhysicsScene::~PhysicsScene()
{
	for (auto pActor : m_actors)
	{
		delete pActor;
	}
}

void PhysicsScene::AddActor(PhysicsObject* a_actor)
{
	m_actors.push_back(a_actor);
}

void PhysicsScene::RemoveActor(PhysicsObject* a_actor)
{
	auto it = std::find(m_actors.begin(), m_actors.end(), a_actor);

	if (it != m_actors.end())
		m_actors.erase(it);

}

void PhysicsScene::Update(float dt)
{
	static std::list<PhysicsObject*> dirty; // must remove
	static float accumulatedTime = 0.f;
	accumulatedTime += dt;

	while (accumulatedTime >= m_timeStep)
	{
		for (auto pActor : m_actors)
		{
			pActor->FixedUpdate(m_gravity, m_timeStep);
		}

		accumulatedTime -= m_timeStep;

		CheckForCollision();
	}
}

void PhysicsScene::Draw()
{
	for (auto pActor : m_actors)
	{
		pActor->MakeGizmo();
	}
}

void PhysicsScene::DebugScene()
{
	int count = 0;
	for (auto pActor : m_actors)
	{
		std::cout << count << " : ";
		pActor->Debug();
		count++;
	}
}

void PhysicsScene::CheckForCollision()
{
	int actorCount = m_actors.size();

	for (int outer = 0; outer < actorCount - 1; outer++)
	{
		for (int inner = outer + 1; inner < actorCount; inner++)
		{
			PhysicsObject* objOuter = m_actors[outer];
			PhysicsObject* objInner = m_actors[inner];
			
			int shapeID_out = objOuter->GetShapeID();
			int shapeID_in = objInner->GetShapeID();

			int functionIndex = (shapeID_out * SHAPE_COUNT) + shapeID_in;
			fn collisionFunctionPtr = collisionFunctionArray[functionIndex];

			if (collisionFunctionPtr != nullptr)
			{
				collisionFunctionPtr(objOuter, objInner);
			}
		}
	}
}

bool PhysicsScene::Plane2Plane(PhysicsObject* objPlane1, PhysicsObject* objPlane2)
{
	return false;
}

bool PhysicsScene::Plane2Sphere(PhysicsObject* objPlane, PhysicsObject* objSphere)
{
	return Sphere2Plane(objSphere, objPlane);
}

bool PhysicsScene::Sphere2Plane(PhysicsObject* objSphere, PhysicsObject* objPlane)
{
	Sphere* sphere = dynamic_cast<Sphere*>(objSphere);
	Plane* plane = dynamic_cast<Plane*>(objPlane);

	if (sphere != nullptr && plane != nullptr)
	{
		glm::vec2 collisionNormal = plane->GetNormal();
		float sphereToPlane = glm::dot(sphere->GetPosition(), collisionNormal - plane->GetDistance());
		float intersection = sphere->GetRadius() - sphereToPlane;
		float velocityOutOfPlane = glm::dot(sphere->GetVelocity(), collisionNormal);

		if (intersection > 0 && velocityOutOfPlane < 0)
		{
			sphere->ApplyForce(-sphere->GetVelocity() * sphere->GetMass());
			return true;
		}
	}

	return false;
}

bool PhysicsScene::Sphere2Sphere(PhysicsObject* obj1, PhysicsObject* obj2)
{
	Sphere* sphere1 = dynamic_cast<Sphere*>(obj1);
	Sphere* sphere2 = dynamic_cast<Sphere*>(obj2);

	if (sphere1 != nullptr && sphere2 != nullptr)
	{
		float dist = glm::distance(sphere1->GetPosition(), sphere2->GetPosition());

		float penetration = sphere1->GetRadius() + sphere2->GetRadius() - dist;
		if (penetration > 0)
		{
			sphere1->ResolveCollision(sphere2);
			return true;
		}
	}

	return false;
}

