#include "PhysicsProjectApp.h"
#include "Sphere.h"
#include "Plane.h"
#include "Box.h"
#include "Spring.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "glm\ext.hpp"
#include <Gizmos.h>

PhysicsProjectApp::PhysicsProjectApp()
{

}



PhysicsProjectApp::~PhysicsProjectApp()
{
	
}

bool PhysicsProjectApp::startup() {

	// Increases 2D line coun to maximise the number of objects we can draw.
	aie::Gizmos::create(255U, 255U, 65535U, 65535U);

	m_2dRenderer = new aie::Renderer2D();

	// TODO: remember to change this when redistributing a build!
	// the following path would be used instead: "./font/consolas.ttf"
	m_escapeFont = new aie::Font("../bin/font/consolas.ttf", 24);
	m_fpsFont = new aie::Font("../bin/font/consolas.ttf", 12);

	/*m_physicsScene = new PhysicsScene();*/
	m_billiards = new Billiards(this);

	/*m_physicsScene->SetGravity(glm::vec2(0, -25));*/

	// Lower the valu, the more accurate the simulation will be;
	// but it will increase the processing time required.
	// If it is too high it causes the sim to stutter and reduce stability.
	m_billiards->SetTimeStep(0.01f);

	/*DrawRect();*/
	//SphereAndPlane();
	//SpringTest(10);
	//TriggerTest();
	m_billiards->StartUp();

	return true;
}

void PhysicsProjectApp::shutdown() 
{
	delete m_2dRenderer;
	delete m_escapeFont;
	delete m_fpsFont;
}

void PhysicsProjectApp::update(float deltaTime)
{
	// input example
	aie::Input* input = aie::Input::getInstance();

	aie::Gizmos::clear();

	//m_physicsScene->Update(deltaTime);
	//m_physicsScene->Draw();


	m_billiards->UpdateLocal(deltaTime);
	// draw gizmos
	m_billiards->DrawGizmos();


	//if (input->isMouseButtonDown(0))
	//{
	//	int xScreen, yScreen;
	//	input->getMouseXY(&xScreen, &yScreen);
	//	glm::vec2 worldPos = ScreenToWorld(glm::vec2(xScreen, yScreen));
	//	aie::Gizmos::add2DCircle(worldPos, 5, 32, glm::vec4(0.3f));
	//	std::cout << worldPos.x << ", " << worldPos.y << std::endl;
	//}

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
	{
		quit();
	}

}

void PhysicsProjectApp::draw() {

	// wipe the screen to the background color
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	// x-axis = -100 to 100, y-axis = -56.25 to 65.25 (m_extents = 100 / 16:9)
	aie::Gizmos::draw2D(glm::ortho<float>(-m_extents, m_extents, -m_extents / m_aspectRatio, m_extents / m_aspectRatio, -1.0f, 1.0f));


	// draw sprites here
	m_billiards->Draw2DRenderer();


	//m_2dRenderer->drawSprite(new aie::Texture("../bin/textures/Billiards/ball1.png"), 0, 0, 2000, 2000, 0);

	char fps[32];
	sprintf_s(fps, 32, "FPS %i", getFPS());
	m_2dRenderer->drawText(m_fpsFont, fps, 7, 30);

	// output some text, uses the last used color
	m_2dRenderer->drawText(m_escapeFont, "Press ESC to quit", 5, 5);

	// done drawing sprites
	m_2dRenderer->end();
}

glm::vec2 PhysicsProjectApp::ScreenToWorld(glm::vec2 a_screenPos)
{
	glm::vec2 worldPos = a_screenPos;

	// we will move the center of the screen to (0, 0)
	worldPos.x -= getWindowWidth() / 2;
	worldPos.y -= getWindowHeight() / 2;

	// scale this according to the extents
	worldPos.x *= 2.f * m_extents / getWindowWidth();
	worldPos.y *= 2.f * m_extents / (m_aspectRatio * getWindowHeight());

	return worldPos;
}

glm::vec2 PhysicsProjectApp::WorldToScreen(glm::vec2 a_worldPos)
{
	glm::vec2 screenPos = a_worldPos;

	screenPos.x /= 2.f * m_extents / getWindowWidth();
	screenPos.y /= 2.f * m_extents / (m_aspectRatio * getWindowHeight());

	screenPos.x += getWindowWidth() / 2;
	screenPos.y += getWindowHeight() / 2;

	return screenPos;
}