#include "Billiards.h"
#include <Renderer2D.h>
#include "PhysicsProjectApp.h"
#include "Input.h"
#include <Gizmos.h>
#include <sstream>

Billiards::~Billiards()
{
	delete m_fontSize11;
	delete m_fontSize20;
	delete m_fontSize30;

}

void Billiards::StartUp()
{
#pragma region POINTER DEFINITIONS

	m_fontSize11 = new aie::Font("../bin/font/SuperLegendBoy.ttf", 11);
	m_fontSize20 = new aie::Font("../bin/font/SuperLegendBoy.ttf", 20);
	m_fontSize30 = new aie::Font("../bin/font/SuperLegendBoy.ttf", 30);

	// play area
	m_backdrop = new Box(glm::vec2(0), glm::vec2(0), 0, 1000, 110, 60, glm::vec4(0, .5f, 0, 1));
	m_topBorder = new Box(glm::vec2(0, 50.5f), glm::vec2(0), 0, 1000, 100, 15, glm::vec4(.4f, .2f, 0, 1));
	m_bottomBorder = new Box(glm::vec2(0, -54), glm::vec2(0), 0, 1000, 100, 15, glm::vec4(.4f, .2f, 0, 1));
	m_rightBorder = new Box(glm::vec2(98, 0), glm::vec2(0), 0, 1000, 15, 55, glm::vec4(.4f, .2f, 0, 1));
	m_leftBorder = new Box(glm::vec2(-98, 0), glm::vec2(0), 0, 1000, 15, 55, glm::vec4(.4f, .2f, 0, 1));

	// hole boxes for asthetics
	m_linerTopLeft = new Box(glm::vec2(-85, 38), glm::vec2(0), 0, 1000, 3, 3, glm::vec4(0.2f, 0.1f, 0, 1));
	m_linerTopMiddle = new Box(glm::vec2(0, 38), glm::vec2(0), 0, 1000, 6, 3, glm::vec4(0.2f, 0.1f, 0, 1));
	m_linerTopRight = new Box(glm::vec2(85, 38), glm::vec2(0), 0, 1000, 3, 3, glm::vec4(0.2f, 0.1f, 0, 1));
	m_linerBottomLeft = new Box(glm::vec2(-85, -42), glm::vec2(0), 0, 1000, 3, 3, glm::vec4(0.2f, 0.1f, 0, 1));
	m_linerBottomMiddle = new Box(glm::vec2(0, -42), glm::vec2(0), 0, 1000, 6, 3, glm::vec4(0.2f, 0.1f, 0, 1));
	m_linerBottomRight = new Box(glm::vec2(85, -42), glm::vec2(0), 0, 1000, 3, 3, glm::vec4(0.2f, 0.1f, 0, 1));

	// holes
	m_sinkTopLeft = new Sphere(glm::vec2(-82, 35), glm::vec2(0), 1000, 5, glm::vec4(.1f, .1f, .1f, 1));
	m_sinkTopMiddle = new Sphere(glm::vec2(0, 35), glm::vec2(0), 1000, 5, glm::vec4(.1f, .1f, .1f, 1));
	m_sinkTopRight = new Sphere(glm::vec2(82, 35), glm::vec2(0), 1000, 5, glm::vec4(.1f, .1f, .1f, 1));
	m_sinkBottomLeft = new Sphere(glm::vec2(-82, -39), glm::vec2(0), 1000, 5, glm::vec4(.1f, .1f, .1f, 1));
	m_sinkBottomMiddle = new Sphere(glm::vec2(0, -39), glm::vec2(0), 1000, 5, glm::vec4(.1f, .1f, .1f, 1));
	m_sinkBottomRight = new Sphere(glm::vec2(82, -39), glm::vec2(0), 1000, 5, glm::vec4(.1f, .1f, .1f, 1));

	// player
	m_cueplayer = new Box(glm::vec2(0), glm::vec2(0), 0, 1, 10, 2, WHITE);
	m_ballPlayer = new Sphere(glm::vec2(0, 0), glm::vec2(0, 0), 3, m_radius, WHITE);

	// player UI
	m_player1SurroundBox = new Box(glm::vec2(-43.5, 45), glm::vec2(0), 0, 1, 20.25, 3.75, glm::vec4(0.2f, 0.1f, 0, 1));
	m_player1InnerBox = new Box(glm::vec2(-43.5, 45), glm::vec2(0), 0, 1, 19.75, 3.25, glm::vec4(.4f, .2f, 0, 1));

	m_player2SurroundBox = new Box(glm::vec2(56.5, 45), glm::vec2(0), 0, 1, 20.25, 3.75, glm::vec4(0.2f, 0.1f, 0, 1));
	m_player2InnerBox = new Box(glm::vec2(56.5, 45), glm::vec2(0), 0, 1, 19.75, 3.25, glm::vec4(.4f, .2f, 0, 1));


	// solid balls
	m_ball1 = new Sphere(glm::vec2(30, 0), glm::vec2(0), 2, m_radius, YELLOW, Solid);
	m_ball2 = new Sphere(glm::vec2(35, -3), glm::vec2(0), 2, m_radius, BLUE, Solid);
	m_ball3 = new Sphere(glm::vec2(40, -6), glm::vec2(0), 2, m_radius, RED, Solid);
	m_ball4 = new Sphere(glm::vec2(45, 3), glm::vec2(0), 2, m_radius, PURPLE, Solid);
	m_ball5 = new Sphere(glm::vec2(45, -9), glm::vec2(0), 2, m_radius, ORANGE, Solid);
	m_ball6 = new Sphere(glm::vec2(50, 6), glm::vec2(0), 2, m_radius, GREEN, Solid);
	m_ball7 = new Sphere(glm::vec2(50, -6), glm::vec2(0), 2, m_radius, BROWN, Solid);

	// 8 ball
	m_ball8 = new Sphere(glm::vec2(40, 0), glm::vec2(0), 2, m_radius, BLACK);

	// stripped balls
	m_ball9 = new Sphere(glm::vec2(35, 3), glm::vec2(0), 2, m_radius, YELLOW, Stripped);
	m_ball10 = new Sphere(glm::vec2(40, 6), glm::vec2(0), 2, m_radius, BLUE, Stripped);
	m_ball11 = new Sphere(glm::vec2(45, 9), glm::vec2(0), 2, m_radius, RED, Stripped);
	m_ball12 = new Sphere(glm::vec2(45, -3), glm::vec2(0), 2, m_radius, PURPLE, Stripped);
	m_ball13 = new Sphere(glm::vec2(50, 12), glm::vec2(0), 2, m_radius, ORANGE, Stripped);
	m_ball14 = new Sphere(glm::vec2(50, 0), glm::vec2(0), 2, m_radius, GREEN, Stripped);
	m_ball15 = new Sphere(glm::vec2(50, -12), glm::vec2(0), 2, m_radius, BROWN, Stripped);

	// textures

	// players
	t_ballPlayer = new aie::Texture("textures/Billiards/ballwhite.png");
	t_cuePlayer = new aie::Texture("textures/Billiards/poolcue.png");

	// full balls
	t_ball1 = new aie::Texture("textures/Billiards/ball1.png"); m_textures.push_back(t_ball1);
	t_ball2 = new aie::Texture("textures/Billiards/ball2.png"); m_textures.push_back(t_ball2);
	t_ball3 = new aie::Texture("textures/Billiards/ball3.png"); m_textures.push_back(t_ball3);
	t_ball4 = new aie::Texture("textures/Billiards/ball4.png"); m_textures.push_back(t_ball4);
	t_ball5 = new aie::Texture("textures/Billiards/ball5.png"); m_textures.push_back(t_ball5);
	t_ball6 = new aie::Texture("textures/Billiards/ball6.png"); m_textures.push_back(t_ball6);
	t_ball7 = new aie::Texture("textures/Billiards/ball7.png"); m_textures.push_back(t_ball7);

	// 8 ball		
	t_ball8 = new aie::Texture("textures/Billiards/ball8.png"); m_textures.push_back(t_ball9);

	// stripped balls
	t_ball9 = new aie::Texture("textures/Billiards/ball9.png");	 m_textures.push_back(t_ball9);
	t_ball10 = new aie::Texture("textures/Billiards/ball10.png"); m_textures.push_back(t_ball10);
	t_ball11 = new aie::Texture("textures/Billiards/ball11.png"); m_textures.push_back(t_ball11);
	t_ball12 = new aie::Texture("textures/Billiards/ball12.png"); m_textures.push_back(t_ball12);
	t_ball13 = new aie::Texture("textures/Billiards/ball13.png"); m_textures.push_back(t_ball13);
	t_ball14 = new aie::Texture("textures/Billiards/ball14.png"); m_textures.push_back(t_ball14);
	t_ball15 = new aie::Texture("textures/Billiards/ball15.png"); m_textures.push_back(t_ball15);

#pragma endregion

#pragma region VISUALS

	// play area
	AddActor(m_backdrop);
	m_backdrop->SetRotation(0);
	m_backdrop->SetKinematic(true);
	AddActor(m_topBorder);
	m_topBorder->SetRotation(0);
	m_topBorder->SetKinematic(true);
	AddActor(m_bottomBorder);
	m_bottomBorder->SetRotation(0);
	m_bottomBorder->SetKinematic(true);
	AddActor(m_rightBorder);
	m_rightBorder->SetRotation(0);
	m_rightBorder->SetKinematic(true);
	AddActor(m_leftBorder);
	m_leftBorder->SetRotation(0);
	m_leftBorder->SetKinematic(true);

	AddActor(m_linerTopLeft);
	m_linerTopLeft->SetTrigger(true);
	AddActor(m_linerTopMiddle);
	m_linerTopMiddle->SetTrigger(true);
	AddActor(m_linerTopRight);
	m_linerTopRight->SetTrigger(true);
	AddActor(m_linerBottomLeft);
	m_linerBottomLeft->SetTrigger(true);
	AddActor(m_linerBottomMiddle);
	m_linerBottomMiddle->SetTrigger(true);
	AddActor(m_linerBottomRight);
	m_linerBottomRight->SetTrigger(true);

	AddActor(m_sinkTopLeft);
	m_sinkTopLeft->SetTrigger(true);
	AddActor(m_sinkTopMiddle);
	m_sinkTopMiddle->SetTrigger(true);
	AddActor(m_sinkTopRight);
	m_sinkTopRight->SetTrigger(true);
	AddActor(m_sinkBottomLeft);
	m_sinkBottomLeft->SetTrigger(true);
	AddActor(m_sinkBottomMiddle);
	m_sinkBottomMiddle->SetTrigger(true);
	AddActor(m_sinkBottomRight);
	m_sinkBottomRight->SetTrigger(true);

	// player UI
	AddActor(m_player1SurroundBox);
	AddActor(m_player1InnerBox);
	AddActor(m_player2SurroundBox);
	AddActor(m_player2InnerBox);


	// pushing to list to draw
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

#pragma endregion
}

void Billiards::UpdateLocal(float deltaTime)
{
	this->Update(deltaTime);

	// game logic update
	aie::Input* input = aie::Input::getInstance();

	// get mouse screen position then convert to world
	int mousex, mousey;
	input->getMouseXY(&mousex, &mousey);
	// convert to world and convert ints to floats
	glm::vec2 mousexy(m_physicsProjectApp->ScreenToWorld(glm::vec2(mousex, mousey)));

	// set mouse start pos on down
	if (input->isMouseButtonDown(0) && turn && turnUpdate)
	{
		m_mousePosOnDown = mousexy;
		turnUpdate = false;
	}
	// reset and take next turn
	else if (glm::abs(m_ballPlayer->GetVelocity().x) < 0.1f && glm::abs(m_ballPlayer->GetVelocity().y) < 0.1f && !turn)
	{
		// next turn logic
		turnUpdate = true;
		turn = true;
		m_mousePosOnDown = glm::vec2(NULL);
		m_distanceFromBall = 30;

		// players turn update logic
		if (m_playersTurn == 1)
			m_playersTurn = 2;
		else if (m_playersTurn == 2)
			m_playersTurn = 1;
	}

	// get white ball world position
	glm::vec2 whiteballpos = m_ballPlayer->GetPosition();

	// set distance to ball, also calculates the limitations of the power
	if (input->isMouseButtonDown(0))
	{
		m_distanceFromBall = 30;
		float distancefromballmod = 0;
		distancefromballmod += (glm::distance(mousexy, m_ballPlayer->GetPosition()) - glm::distance(m_mousePosOnDown, m_ballPlayer->GetPosition()));

		if (distancefromballmod < 0)
			distancefromballmod = 0;
		else if (distancefromballmod > 30)
			distancefromballmod = 30;

		m_distanceFromBall += distancefromballmod;
	}

	// get the direction
	glm::vec2 cuepos(0);
	// find the position for the cue
	glm::vec2 normal(glm::normalize(mousexy - whiteballpos));
	cuepos = glm::vec2((whiteballpos.x + normal.x * m_distanceFromBall),
		(whiteballpos.y + normal.y * m_distanceFromBall));
	// direction to the ball
	float direction = glm::atan(normal.y, normal.x);

	// set the position and the rotation
	m_cueplayer->SetRotation((direction * 8) + -12.5f);
	m_cueplayer->SetPosition(cuepos);

	//______________________________________________________________________________________________________________________________________


	glm::vec2 hitnormal(glm::normalize(whiteballpos - mousexy));
	// hit ball
	if (input->isMouseButtonUp(0) && m_mousePosOnDown != glm::vec2(NULL) && turn)
	{
		float force = 10 * (m_distanceFromBall - 30);
		m_ballPlayer->ApplyForce(hitnormal * glm::vec2(force), m_ballPlayer->GetPosition());

		turn = false;
	}

#pragma region SINK LOGIC

	// sink hole logic (kinda repetitive)
	m_sinkTopLeft->triggerEnter = [=](Rigidbody* other) {
		if (other != m_ballPlayer && other->IsKinematic() == false)
			SunkBall(other); };

	m_sinkTopMiddle->triggerEnter = [=](Rigidbody* other) {
		if (other != m_ballPlayer && other->IsKinematic() == false)
			SunkBall(other); };

	m_sinkTopRight->triggerEnter = [=](Rigidbody* other) {
		if (other != m_ballPlayer && other->IsKinematic() == false)
			SunkBall(other); };

	m_sinkBottomLeft->triggerEnter = [=](Rigidbody* other) {
		if (other != m_ballPlayer && other->IsKinematic() == false)
			SunkBall(other); };

	m_sinkBottomMiddle->triggerEnter = [=](Rigidbody* other) {
		if (other != m_ballPlayer && other->IsKinematic() == false)
			SunkBall(other); };

	m_sinkBottomRight->triggerEnter = [=](Rigidbody* other) {
		if (other != m_ballPlayer && other->IsKinematic() == false)
			SunkBall(other); };

	// set position to display queue

#pragma endregion

	glm::vec2 firstPosStripped(-60, 45);
	for (auto ball : m_sunkStrippedBalls)
	{
		ball->SetRotation(0);
		ball->SetPosition(firstPosStripped);
		firstPosStripped.x += 5.5f;
	}

	glm::vec2 firstPosSolid(40, 45);
	for (auto ball : m_sunkSolidBalls)
	{
		ball->SetRotation(0);
		ball->SetPosition(firstPosSolid);
		firstPosSolid.x += 5.5f;
	}

	// physics update
	for (auto ball : m_actors)
	{
		ball->FixedUpdate(glm::vec2(0), deltaTime);
	}
}

void Billiards::DrawGizmos()
{
	for (auto ball : m_actors)
	{
		ball->MakeGizmo();
	}
}

void Billiards::Draw2DRenderer()
{
#pragma region Printing Other

	// stripped player UI (Player 1)
	glm::vec2 player1text(-62, 50);
	player1text = m_physicsProjectApp->WorldToScreen(player1text);
	m_physicsProjectApp->GetRenderer()->drawText(m_fontSize20, "Player 1: ", player1text.x, player1text.y);

	// solid player UI (Player 2)
	glm::vec2 player2text(38, 50);
	player2text = m_physicsProjectApp->WorldToScreen(player2text);
	m_physicsProjectApp->GetRenderer()->drawText(m_fontSize20, "Player 2: ", player2text.x, player2text.y);

	// players turn logic
	std::string playersturns = std::to_string(m_playersTurn);
	const char* playersturnc = playersturns.c_str();

	// players turn text
	glm::vec2 playerturn11(-5.8, 52);
	glm::vec2 playerturn20(-6, 49);
	glm::vec2 playerturn30(-2, 45);
	playerturn11 = m_physicsProjectApp->WorldToScreen(playerturn11);
	playerturn20 = m_physicsProjectApp->WorldToScreen(playerturn20);
	playerturn30 = m_physicsProjectApp->WorldToScreen(playerturn30);
	m_physicsProjectApp->GetRenderer()->drawText(m_fontSize11, "PLAYERS", playerturn11.x, playerturn11.y);
	m_physicsProjectApp->GetRenderer()->drawText(m_fontSize20, "TURN", playerturn20.x, playerturn20.y);
	m_physicsProjectApp->GetRenderer()->drawText(m_fontSize30, playersturnc, playerturn30.x, playerturn30.y);

#pragma endregion

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

void Billiards::SunkBall(Rigidbody* other)
{
	other->SetTrigger(true);
	other->SetKinematic(true);
	if (other->GetBilliardType() == Stripped)
		m_sunkStrippedBalls.push_back(other);
	else if (other->GetBilliardType() == Solid)
		m_sunkSolidBalls.push_back(other);
	else if (other->GetBilliardType() == EightBall)
		m_gameover = true;
}