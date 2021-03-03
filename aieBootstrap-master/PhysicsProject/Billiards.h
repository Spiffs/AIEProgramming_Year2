#pragma once
#include "Box.h"
#include "Sphere.h"
#include "Plane.h"
#include "Rigidbody.h"
#include "PhysicsScene.h"
#include <Texture.h>
#include <vector>

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
	Billiards(PhysicsProjectApp* a_physicsProjectApp) : PhysicsScene(a_physicsProjectApp) {}
	~Billiards();

	void StartUp();
	void UpdateLocal(float deltaTime);
	void DrawGizmos();
	void DrawSprites();

protected:
	float m_radius = 2.5f;

	// update variables	
	bool turn;
	bool turnUpdate;
	
	glm::vec2 m_mousePosOnDown = glm::vec2(NULL);
	float m_distanceFromBall = 30;

	std::vector<aie::Texture*> m_textures;
	std::vector<Rigidbody*> m_sunkBalls;

	// play area
	Box* m_backdrop;
	Box* m_topBorder;
	Box* m_bottomBorder;
	Box* m_rightBorder;
	Box* m_leftBorder;
	//holes
	Sphere* m_sinkTopLeft;
	Sphere* m_sinkTopMiddle;
	Sphere* m_sinkTopRight;
	Sphere* m_sinkBottomLeft;
	Sphere* m_sinkBottomMiddle;
	Sphere* m_sinkBottomRight;
	// hole boxes
	Box* m_linerTopLeft;
	Box* m_linerTopMiddle;
	Box* m_linerTopRight;
	Box* m_linerBottomLeft;
	Box* m_linerBottomMiddle;
	Box* m_linerBottomRight;


	// player
	Sphere* m_ballPlayer;
	Box* m_cueplayer;

	// full balls
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
	 
#pragma region TEXTURES

	// textures

	// player
	aie::Texture* t_ballPlayer;
	aie::Texture* t_cuePlayer;

	// full balls
	aie::Texture* t_ball1;
	aie::Texture* t_ball2;
	aie::Texture* t_ball3;
	aie::Texture* t_ball4;
	aie::Texture* t_ball5;
	aie::Texture* t_ball6;
	aie::Texture* t_ball7;

	// 8 ball		
	aie::Texture* t_ball8;

	// stripped balls
	aie::Texture* t_ball9;
	aie::Texture* t_ball10;
	aie::Texture* t_ball11;
	aie::Texture* t_ball12;
	aie::Texture* t_ball13;
	aie::Texture* t_ball14;
	aie::Texture* t_ball15;


#pragma endregion
};

