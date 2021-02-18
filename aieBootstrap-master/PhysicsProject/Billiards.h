#pragma once
#include "Box.h"
#include "Sphere.h"
#include "Plane.h"
#include "Rigidbody.h"
#include <list>
#include "PhysicsScene.h"

static glm::vec4 BLUE(0, 0, 1, 1);
static glm::vec4 RED(1, 0, 0, 1);
static glm::vec4 YELLOW(1, 1, 0, 1);
static glm::vec4 GREEN(0, .6f, 0, 1);
static glm::vec4 PURPLE(0.5f, 0, 1, 1);
static glm::vec4 BROWN(0.5f, 0.3f, 0, 1);
static glm::vec4 ORANGE(1, 0.5f, 0, 1);
static glm::vec4 WHITE(1, 1, 1, 1);
static glm::vec4 BLACK(0, 0, 0, 1);

class Billiards : public PhysicsScene
{
public:
	Billiards() {}
	~Billiards() {}

	void StartUp();
	void UpdateLocal(float deltaTime);
	void Draw();

protected:
	float m_radius = 2.5f;
	 
	// play area
	Box* m_backdrop = new Box(glm::vec2(0), glm::vec2(0), 0, 1000, 110, 60, GREEN);
	Box* m_topBorder = new Box(glm::vec2(0, 50.5f), glm::vec2(0), 0, 1000, 100, 6, glm::vec4(.4f, .2f, 0, 1));
	Box* m_bottomBorder = new Box(glm::vec2(0, -54), glm::vec2(0), 0, 1000, 100, 3, glm::vec4(.4f, .2f, 0, 1));
	Box* m_rightBorder = new Box(glm::vec2(98, 0), glm::vec2(0), 0, 1000, 3, 55, glm::vec4(.4f, .2f, 0, 1));
	Box* m_leftBorder = new Box(glm::vec2(-98, 0), glm::vec2(0), 0, 1000, 3, 55, glm::vec4(.4f, .2f, 0, 1));

	// white ball (player)
	Sphere* m_ballPlayer;

	// solid balls
	Sphere* m_ball1;
	Sphere* m_ball2;
	Sphere* m_ball3;
	Sphere* m_ball4;
	Sphere* m_ball5;
	Sphere* m_ball6;
	Sphere* m_ball7;

	// 8 ball		
	Sphere* m_ball8;

	// stripped balls
	Sphere* m_ball9;
	Sphere* m_ball10;
	Sphere* m_ball11;
	Sphere* m_ball12;
	Sphere* m_ball13;
	Sphere* m_ball14;
	Sphere* m_ball15;


};

