#include "Billiards.h"

void Billiards::StartUp()
{
#pragma region POINTER DEFINITIONS (BALLS)

	// player ball
	m_ballPlayer = new Sphere(glm::vec2(0, 0), glm::vec2(250, 0), 3, m_radius, WHITE);

	// solid balls
	m_ball1 = new Sphere(glm::vec2(30, 0), glm::vec2(0), 2, m_radius, BLUE);
	m_ball2 = new Sphere(glm::vec2(35, -3), glm::vec2(0), 2, m_radius, RED);
	m_ball3 = new Sphere(glm::vec2(40, -6), glm::vec2(0), 2, m_radius, YELLOW);
	m_ball4 = new Sphere(glm::vec2(45, 3), glm::vec2(0), 2, m_radius, GREEN);
	m_ball5 = new Sphere(glm::vec2(45, -9), glm::vec2(0), 2, m_radius, PURPLE);
	m_ball6 = new Sphere(glm::vec2(50, 6), glm::vec2(0), 2, m_radius, BROWN);
	m_ball7 = new Sphere(glm::vec2(50, -6), glm::vec2(0), 2, m_radius, ORANGE);

	// 8 ball
	m_ball8 = new Sphere(glm::vec2(40, 0), glm::vec2(0), 2, m_radius, BLACK);

	// stripped balls
	m_ball9 = new Sphere(glm::vec2(35, 3), glm::vec2(0), 2, m_radius, ORANGE);
	m_ball10 = new Sphere(glm::vec2(40, 6), glm::vec2(0), 2, m_radius, BROWN);
	m_ball11 = new Sphere(glm::vec2(45, 9), glm::vec2(0), 2, m_radius, PURPLE);
	m_ball12 = new Sphere(glm::vec2(45, -3), glm::vec2(0), 2, m_radius, GREEN);
	m_ball13 = new Sphere(glm::vec2(50, 12), glm::vec2(0), 2, m_radius, YELLOW);
	m_ball14 = new Sphere(glm::vec2(50, 0), glm::vec2(0), 2, m_radius, RED);
	m_ball15 = new Sphere(glm::vec2(50, -12), glm::vec2(0), 2, m_radius, BLUE);

#pragma endregion

	// pushing to list to draw
	AddActor(m_backdrop);
	AddActor(m_topBorder);
	AddActor(m_bottomBorder);
	AddActor(m_rightBorder);
	AddActor(m_leftBorder);
	AddActor(m_ballPlayer);
	AddActor(m_ball1);
	AddActor(m_ball2);
	AddActor(m_ball3);
	AddActor(m_ball4);
	AddActor(m_ball5);
	AddActor(m_ball6);
	AddActor(m_ball7);
	AddActor(m_ball8);
	AddActor(m_ball9);
	AddActor(m_ball10);
	AddActor(m_ball11);
	AddActor(m_ball12);
	AddActor(m_ball13);
	AddActor(m_ball14);
	AddActor(m_ball15);

	m_backdrop->SetRotation(0);
	m_backdrop->SetKinematic(true);
	m_topBorder->SetRotation(0);
	m_topBorder->SetKinematic(true);
	m_topBorder->SetElasticity(100);
	m_bottomBorder->SetRotation(0);
	m_bottomBorder->SetKinematic(true);
	m_rightBorder->SetRotation(0);
	m_rightBorder->SetKinematic(true);
	m_leftBorder->SetRotation(0);
	m_leftBorder->SetKinematic(true);
}

void Billiards::UpdateLocal(float deltaTime)
{
	//m_ballPlayer->ApplyForce(glm::vec2(1, 0), glm::vec2(0));

	for (auto ball : m_actors)
	{
		ball->FixedUpdate(glm::vec2(0), deltaTime);
	}

	

	this->Update(deltaTime);
}

void Billiards::Draw()
{

	m_backdrop->MakeGizmo();

	m_ballPlayer->MakeGizmo();

	for (auto ball : m_actors)
	{
		ball->MakeGizmo();
	}
}
