////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "stdafx.h"
#ifdef _DEBUG
#pragma comment(lib,"sfml-graphics-d.lib")
#pragma comment(lib,"sfml-audio-d.lib")
#pragma comment(lib,"sfml-system-d.lib")
#pragma comment(lib,"sfml-window-d.lib")
#pragma comment(lib,"sfml-network-d.lib")
#else
#pragma comment(lib,"sfml-graphics.lib")
#pragma comment(lib,"sfml-audio.lib")
#pragma comment(lib,"sfml-system.lib")
#pragma comment(lib,"sfml-window.lib")
#pragma comment(lib,"sfml-network.lib")
#endif
#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib")
#include "SFML/Graphics.hpp"
#include "SFML/OpenGL.hpp"
#include <iostream>
#include <cmath>
#include <vector>
 
#include "Robot.h"
 
////////////////////////////////////////////////////////////
///Entrypoint of application
////////////////////////////////////////////////////////////
 using namespace sf;

void createBalloon(std::vector<Sprite> &balloons,Texture const &balloon){
	Vector2f location(rand() % 500,rand() % 400);
	balloons.push_back(Sprite(balloon));
	balloons.rbegin()->setPosition(location);
}

void PopDemRinkyDinks(std::vector<Sprite> &rinkyDinks, Robot const &robert, Vector2f justTheTip) {
	RobotPart* part = robert.getNextPart();

	while(part->getNextPart() != 0)
			part = part->getNextPart();

	//transform just the tip into the correct position for collison
	justTheTip = part->getTransformation().transformPoint(justTheTip);

	for(auto iterator_i_barely_knew_her = rinkyDinks.begin(); iterator_i_barely_knew_her != rinkyDinks.end(); ++iterator_i_barely_knew_her) {
		if(iterator_i_barely_knew_her->getGlobalBounds().contains( justTheTip )) {
			//POPA DA BALLOGNEZ!
			rinkyDinks.erase( iterator_i_barely_knew_her );
			return;
		}
	}
}

int main()
{
	srand( time(NULL) );
	// Create the main window
	RenderWindow window(VideoMode(800, 600, 32), "SFML First Program");
	window.setFramerateLimit(60);
	Font font;
	font.loadFromFile("C:\\Windows\\Fonts\\Arial.TTF");
	std::vector<Sprite> balloons;
 
	//create a formatted text string
	Text text;
	text.setFont(font);
	text.setStyle(Text::Underlined| Text::Italic | Text::Bold);
	text.setPosition(20,40);
	text.setCharacterSize(40); 
	Clock c = Clock();

	Texture robotBase;
	Texture lowerArm;
	Texture upperArm;
	Texture hand;
	Texture finger;
	Texture balloon;



	
	if(!robotBase.loadFromFile("robot-base.png"))
		return EXIT_FAILURE;
	if(!lowerArm.loadFromFile("robot-lower-arm.png"))
		return EXIT_FAILURE;
	if(!upperArm.loadFromFile("robot-upper-arm.png"))
		return EXIT_FAILURE;
	if(!hand.loadFromFile("robot-hand.png"))
		return EXIT_FAILURE;
	if(!finger.loadFromFile("robot-finger.png"))
		return EXIT_FAILURE;
	if(!balloon.loadFromFile("balloon.png"))
		return EXIT_FAILURE;


	Robot iRobot(Vector2f(600,400), robotBase);
	iRobot.AttachPart( new RobotPart(Vector2f(100, 48), Vector2f(-100, -100), lowerArm, Keyboard::Down, Keyboard::Up, 70, 0));
	iRobot.AttachPart( new RobotPart(Vector2f(15, 10), Vector2f(-178, -44), upperArm, Keyboard::S, Keyboard::W, 70, 0));
	iRobot.AttachPart( new RobotPart(Vector2f(60, 128), Vector2f(-107, -33), hand, Keyboard::A, Keyboard::D, 70, 0));
	iRobot.AttachPart( new RobotPart(Vector2f(62, 134), Vector2f(-31, -6), finger, Keyboard::Q, Keyboard::E, 70, 0));
	iRobot.Update(Event());

	for(int i = 0; i <= 5; i ++){
		createBalloon(balloons,balloon);
	}

	while (window.isOpen())
	{

		// Process events
		Event Event;
		if(balloons.size() > 0)
		{
			text.setString(std::to_string(c.getElapsedTime().asSeconds()));
		}
		while (window.pollEvent(Event))
		{
			// Close window : exit
			if (Event.type == Event::Closed)
				window.close();
			// Escape key : exit
			if ((Event.type == Event::KeyPressed) && (Event.key.code == Keyboard::Escape))
				window.close();
			if(Event.type == Event::KeyPressed) {
				iRobot.Update(Event);
				PopDemRinkyDinks( balloons, iRobot, Vector2f(7, 50) /* BLAZE IT */ );
			}
		}

		window.clear();

	//	window.draw(rBase,Tbase);
	//	window.draw(lArm,baselArm);
	//	window.draw(uArm,baselArmuArm);
	//	window.draw(rHand,baselArmuArmHand);
	//	window.draw(rFing,baselArmuArmHandFing);


		for(auto itr = balloons.begin(); itr!=balloons.end();++itr){
			window.draw(*itr);
			
		}
		iRobot.Draw( window );

		window.draw(text);

		// Finally, display rendered frame on screen
		window.display();
	} //loop back for next frame
	return EXIT_SUCCESS;
} 