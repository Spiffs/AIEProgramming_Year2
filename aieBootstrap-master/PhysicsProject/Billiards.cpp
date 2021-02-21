#include "Billiards.h"
#include <Renderer2D.h>
#include "PhysicsProjectApp.h"
#include "Input.h"

Billiards::~Billiards()
{
	// already done in PhysicsScene
	//for (auto ball : m_actors)
	//{
	//	delete ball;
	//}
	
	delete t_ballPlayer;
	delete t_cuePlayer;

	delete t_ball1;
	delete t_ball2;
	delete t_ball3;
	delete t_ball4;
	delete t_ball5;
	delete t_ball6;
	delete t_ball7;
	delete t_ball8;
	delete t_ball9;
	delete t_ball10;
	delete t_ball11;
	delete t_ball12;
	delete t_ball13;
	delete t_ball14;
	delete t_ball15;
}

void Billiards::StartUp()
{
#pragma region POINTER DEFINITIONS (BALLS)

	// play area
	m_backdrop = new Box(glm::vec2(0), glm::vec2(0), 0, 1000, 110, 60, glm::vec4(0, .5f, 0, 1));
	m_topBorder = new Box(glm::vec2(0, 50.5f), glm::vec2(0), 0, 1000, 100, 6, glm::vec4(.4f, .2f, 0, 1));
	m_bottomBorder = new Box(glm::vec2(0, -54), glm::vec2(0), 0, 1000, 100, 3, glm::vec4(.4f, .2f, 0, 1));
	m_rightBorder = new Box(glm::vec2(98, 0), glm::vec2(0), 0, 1000, 3, 55, glm::vec4(.4f, .2f, 0, 1));
	m_leftBorder = new Box(glm::vec2(-98, 0), glm::vec2(0), 0, 1000, 3, 55, glm::vec4(.4f, .2f, 0, 1));

	// player
	m_cueplayer = new Box(glm::vec2(0), glm::vec2(0), 0, 1, 10, 2, WHITE);
	m_ballPlayer = new Sphere(glm::vec2(0, 0), glm::vec2(0, 0), 3, m_radius, WHITE);

	// solid balls
	m_ball1 = new Sphere(glm::vec2(30, 0), glm::vec2(0), 2, m_radius, YELLOW);
	m_ball2 = new Sphere(glm::vec2(35, -3), glm::vec2(0), 2, m_radius, BLUE);
	m_ball3 = new Sphere(glm::vec2(40, -6), glm::vec2(0), 2, m_radius, RED);
	m_ball4 = new Sphere(glm::vec2(45, 3), glm::vec2(0), 2, m_radius, PURPLE);
	m_ball5 = new Sphere(glm::vec2(45, -9), glm::vec2(0), 2, m_radius, ORANGE);
	m_ball6 = new Sphere(glm::vec2(50, 6), glm::vec2(0), 2, m_radius, GREEN);
	m_ball7 = new Sphere(glm::vec2(50, -6), glm::vec2(0), 2, m_radius, BROWN);

	// 8 ball
	m_ball8 = new Sphere(glm::vec2(40, 0), glm::vec2(0), 2, m_radius, BLACK);

	// stripped balls
	m_ball9 = new Sphere(glm::vec2(35, 3), glm::vec2(0), 2, m_radius, YELLOW);
	m_ball10 = new Sphere(glm::vec2(40, 6), glm::vec2(0), 2, m_radius, BLUE);
	m_ball11 = new Sphere(glm::vec2(45, 9), glm::vec2(0), 2, m_radius, RED);
	m_ball12 = new Sphere(glm::vec2(45, -3), glm::vec2(0), 2, m_radius, PURPLE);
	m_ball13 = new Sphere(glm::vec2(50, 12), glm::vec2(0), 2, m_radius, ORANGE);
	m_ball14 = new Sphere(glm::vec2(50, 0), glm::vec2(0), 2, m_radius, GREEN);
	m_ball15 = new Sphere(glm::vec2(50, -12), glm::vec2(0), 2, m_radius, BROWN);
	
	
#pragma endregion

#pragma region TEXTURE
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
	m_bottomBorder->SetRotation(0);
	m_bottomBorder->SetKinematic(true);
	m_rightBorder->SetRotation(0);
	m_rightBorder->SetKinematic(true);
	m_leftBorder->SetRotation(0);
	m_leftBorder->SetKinematic(true);

	// textures

	// players
	t_ballPlayer = new aie::Texture("../bin/textures/Billiards/ballwhite.png");
	t_cuePlayer = new aie::Texture("../bin/textures/Billiards/poolcue.png");

	// full balls
	t_ball1 = new aie::Texture("../bin/textures/Billiards/ball1.png");
	t_ball2 = new aie::Texture("../bin/textures/Billiards/ball2.png");
	t_ball3 = new aie::Texture("../bin/textures/Billiards/ball3.png");
	t_ball4 = new aie::Texture("../bin/textures/Billiards/ball4.png");
	t_ball5 = new aie::Texture("../bin/textures/Billiards/ball5.png");
	t_ball6 = new aie::Texture("../bin/textures/Billiards/ball6.png");
	t_ball7 = new aie::Texture("../bin/textures/Billiards/ball7.png");

	// 8 ball		
	t_ball8 = new aie::Texture("../bin/textures/Billiards/ball8.png");

	// stripped balls
	t_ball9 = new aie::Texture("../bin/textures/Billiards/ball9.png");
	t_ball10 = new aie::Texture("../bin/textures/Billiards/ball10.png");
	t_ball11 = new aie::Texture("../bin/textures/Billiards/ball11.png");
	t_ball12 = new aie::Texture("../bin/textures/Billiards/ball12.png");
	t_ball13 = new aie::Texture("../bin/textures/Billiards/ball13.png");
	t_ball14 = new aie::Texture("../bin/textures/Billiards/ball14.png");
	t_ball15 = new aie::Texture("../bin/textures/Billiards/ball15.png");

#pragma endregion
}

void Billiards::UpdateLocal(float deltaTime)
{
	// game logic update
	aie::Input* input = aie::Input::getInstance();

	// debug
	if (input->isMouseButtonDown(1))
	{
		std::cout;
	}

	float distancefromball = 10;
	glm::vec2 whiteballpos = m_ballPlayer->GetPosition();
	glm::vec2 cuepos(0);
	cuepos = glm::vec2((whiteballpos.x + glm::normalize(whiteballpos.x - input->getMouseX()) * distancefromball),
					   (whiteballpos.y + glm::normalize(whiteballpos.y - input->getMouseY()) * distancefromball));
	
	m_cueplayer->SetPosition(cuepos);


	if (input->isMouseButtonDown(0))
	{

	}




	// physics update
	for (auto ball : m_actors)
	{
		ball->FixedUpdate(glm::vec2(0), deltaTime);
	}

	this->Update(deltaTime);
}

void Billiards::DrawGizmos()
{
	for (auto ball : m_actors)
	{
		ball->MakeGizmo();
	}
}

void Billiards::DrawSprites()
{
	for (auto ball : m_actors)
	{
		ball->MakeGizmo();
	}
	
#pragma region PRINTING SPRITES
	m_physicsProjectApp->GetRenderer()->drawSprite(t_ball1, m_physicsProjectApp->WorldToScreen(m_ball1->GetPosition()).x, m_physicsProjectApp->WorldToScreen(m_ball1->GetPosition()).y, 35, 35, m_ball1->GetRotation() / 8);
	m_physicsProjectApp->GetRenderer()->drawSprite(t_ball2, m_physicsProjectApp->WorldToScreen(m_ball2->GetPosition()).x, m_physicsProjectApp->WorldToScreen(m_ball2->GetPosition()).y, 35, 35, m_ball2->GetRotation() / 8);
	m_physicsProjectApp->GetRenderer()->drawSprite(t_ball3, m_physicsProjectApp->WorldToScreen(m_ball3->GetPosition()).x, m_physicsProjectApp->WorldToScreen(m_ball3->GetPosition()).y, 35, 35, m_ball3->GetRotation() / 8);
	m_physicsProjectApp->GetRenderer()->drawSprite(t_ball4, m_physicsProjectApp->WorldToScreen(m_ball4->GetPosition()).x, m_physicsProjectApp->WorldToScreen(m_ball4->GetPosition()).y, 35, 35, m_ball4->GetRotation() / 8);
	m_physicsProjectApp->GetRenderer()->drawSprite(t_ball5, m_physicsProjectApp->WorldToScreen(m_ball5->GetPosition()).x, m_physicsProjectApp->WorldToScreen(m_ball5->GetPosition()).y, 35, 35, m_ball5->GetRotation() / 8);
	m_physicsProjectApp->GetRenderer()->drawSprite(t_ball6, m_physicsProjectApp->WorldToScreen(m_ball6->GetPosition()).x, m_physicsProjectApp->WorldToScreen(m_ball6->GetPosition()).y, 35, 35, m_ball6->GetRotation() / 8);
	m_physicsProjectApp->GetRenderer()->drawSprite(t_ball7, m_physicsProjectApp->WorldToScreen(m_ball7->GetPosition()).x, m_physicsProjectApp->WorldToScreen(m_ball7->GetPosition()).y, 35, 35, m_ball7->GetRotation() / 8);
	m_physicsProjectApp->GetRenderer()->drawSprite(t_ball8, m_physicsProjectApp->WorldToScreen(m_ball8->GetPosition()).x, m_physicsProjectApp->WorldToScreen(m_ball8->GetPosition()).y, 35, 35, m_ball8->GetRotation() / 8);
	m_physicsProjectApp->GetRenderer()->drawSprite(t_ball9, m_physicsProjectApp->WorldToScreen(m_ball9->GetPosition()).x, m_physicsProjectApp->WorldToScreen(m_ball9->GetPosition()).y, 35, 35, m_ball9->GetRotation() / 8);
	m_physicsProjectApp->GetRenderer()->drawSprite(t_ball10, m_physicsProjectApp->WorldToScreen(m_ball10->GetPosition()).x, m_physicsProjectApp->WorldToScreen(m_ball10->GetPosition()).y, 35, 35, m_ball10->GetRotation() / 8);
	m_physicsProjectApp->GetRenderer()->drawSprite(t_ball11, m_physicsProjectApp->WorldToScreen(m_ball11->GetPosition()).x, m_physicsProjectApp->WorldToScreen(m_ball11->GetPosition()).y, 35, 35, m_ball11->GetRotation() / 8);
	m_physicsProjectApp->GetRenderer()->drawSprite(t_ball12, m_physicsProjectApp->WorldToScreen(m_ball12->GetPosition()).x, m_physicsProjectApp->WorldToScreen(m_ball12->GetPosition()).y, 35, 35, m_ball12->GetRotation() / 8);
	m_physicsProjectApp->GetRenderer()->drawSprite(t_ball13, m_physicsProjectApp->WorldToScreen(m_ball13->GetPosition()).x, m_physicsProjectApp->WorldToScreen(m_ball13->GetPosition()).y, 35, 35, m_ball13->GetRotation() / 8);
	m_physicsProjectApp->GetRenderer()->drawSprite(t_ball14, m_physicsProjectApp->WorldToScreen(m_ball14->GetPosition()).x, m_physicsProjectApp->WorldToScreen(m_ball14->GetPosition()).y, 35, 35, m_ball14->GetRotation() / 8);
	m_physicsProjectApp->GetRenderer()->drawSprite(t_ball15, m_physicsProjectApp->WorldToScreen(m_ball15->GetPosition()).x, m_physicsProjectApp->WorldToScreen(m_ball15->GetPosition()).y, 35, 35, m_ball15->GetRotation() / 8);
	m_physicsProjectApp->GetRenderer()->drawSprite(t_ballPlayer, m_physicsProjectApp->WorldToScreen(m_ballPlayer->GetPosition()).x, m_physicsProjectApp->WorldToScreen(m_ballPlayer->GetPosition()).y, 35, 35, m_ballPlayer->GetRotation() / 8);

	if (turn)
		m_physicsProjectApp->GetRenderer()->drawSprite(t_cuePlayer, m_physicsProjectApp->WorldToScreen(m_cueplayer->GetPosition()).x, m_physicsProjectApp->WorldToScreen(m_cueplayer->GetPosition()).y, 8, 250, m_cueplayer->GetRotation() / 8);
#pragma endregion

}
