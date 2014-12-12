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
#include <math.h>
 
 
////////////////////////////////////////////////////////////
///Entrypoint of application
////////////////////////////////////////////////////////////
 using namespace sf;

int main()
{
	srand( time(NULL) );
	// Create the main window
	RenderWindow window(VideoMode(800, 600, 32), "SFML First Program");
	window.setFramerateLimit(60);
	Font font;
	font.loadFromFile("C:\\Windows\\Fonts\\GARA.TTF");
 
	//create a formatted text string
	Text text;
	text.setFont(font);
	text.setStyle(Text::Underlined| Text::Italic | Text::Bold);
	text.setPosition(20,40);
	text.setCharacterSize(40); 

	Texture robotBase;
	Texture lowerArm;
	Texture upperArm;
	Texture hand;
	Texture finger;
	
	if(!robotBase.loadFromFile("robotBase.png"))
		return 1;
	if(!lowerArm.loadFromFile("lowerArm.png"))
		return 1;
	if(!upperArm.loadFromFile("upperArm.png"))
		return 1;
	if(!hand.loadFromFile("hand.png"))
		return 1;
	if(!finger.loadFromFile("finger.png"))
		return 1;

	robotBase.setSmooth(true);
	lowerArm.setSmooth(true);
	upperArm.setSmooth(true);
	hand.setSmooth(true);
	finger.setSmooth(true);

	Sprite base;
	Sprite lArm;
	Sprite uArm;
	Sprite clamp;
	Sprite fing;
	base.setTexture(robotBase);
	lArm.setTexture(lowerArm);
	uArm.setTexture(upperArm);
	clamp.setTexture(hand);
	fing.setTexture(finger);

	Vector2f basePos(400,300);
	Vector2f lArmPos(-148,-76);
	Vector2f uArmPos(-135,-18);
	Vector2f clampPos(-115,30);
	Vector2f fingPos(5,38);

	float rotUpper = 0.0f;
	float rotLower = 0.0f;
	float rotClamp = -17.0f;
	float rotFing = 0.0f;

	CircleShape circle;
	Vector2f circlePos(100,100);
	Clock clock = Clock();
	// Start game loop
	while (window.isOpen())
	{
		text.setString(std::to_string(clock.getElapsedTime().asSeconds()));
		circle.setPosition(circlePos);
		circle.setRadius(10);
		circle.setFillColor(Color::Red);

		Vector2f lArmOrgin = Vector2f(245,107);
		Transform R;

		Vector2f uArmOrgin = Vector2f(151,49);
		Transform R2;

		Vector2f clampOrgin = Vector2f(142,64);
		Transform R3;

		Vector2f fingOrgin = Vector2f(72,27);
		Transform R4;

		Transform Tbase;
		Tbase.translate(basePos); 

		Transform TlArm;
		TlArm.translate(lArmPos);

		Transform TuArm;
		TuArm.translate(uArmPos);

		Transform TClamp;
		TClamp.translate(clampPos);

		Transform TFing;
		TFing.translate(fingPos);



		R.rotate(rotLower,lArmOrgin);
		R2.rotate(rotUpper,uArmOrgin);
		R3.rotate(rotClamp,clampOrgin);
		R4.rotate(rotFing,fingOrgin);

		Transform baselArm = Tbase*TlArm*R;
		Transform baselArmuArm = baselArm*TuArm*R2;
		Transform baselArmuArmClamp = baselArmuArm*TClamp*R3;
		Transform baselArmuArmClampFing = baselArmuArmClamp*TFing*R4;

		
		// Process events
		Event Event;
		while (window.pollEvent(Event))
		{
			// Close window : exit
			if (Event.type == Event::Closed)
				window.close();
			// Escape key : exit
			if ((Event.type == Event::KeyPressed) && (Event.key.code == Keyboard::Escape))
				window.close();

		}
		if(Keyboard::isKeyPressed(Keyboard::Left)){
			basePos.x-=1;
		}
		if(Keyboard::isKeyPressed(Keyboard::Right)){
			basePos.x+=1;
		}
		if(Keyboard::isKeyPressed(Keyboard::Up)){
			if(rotUpper != 70.0f)
			{
				rotUpper+=1;
			}
		}
		if(Keyboard::isKeyPressed(Keyboard::Down)){
			if(rotUpper != -30.0f)
			{
				rotUpper-=1;
			}
		}
		if(Keyboard::isKeyPressed(Keyboard::A)){
			if(rotLower != 160.0f)
			{
				rotLower+=1;
			}
		}
		if(Keyboard::isKeyPressed(Keyboard::D)){
			if(rotLower != -20.0f)
			{
				rotLower-=1;
			}
		}
		if(Keyboard::isKeyPressed(Keyboard::W)){
			if(rotFing != 30.0f)
			{
				rotFing+=1;
			}
		}
		if(Keyboard::isKeyPressed(Keyboard::S)){
			if(rotFing != -30.0f)
			{
				rotFing-=1;
			}
		}


		window.clear();

		window.draw(base,Tbase);
		window.draw(lArm,baselArm);
		window.draw(uArm,baselArmuArm);
		window.draw(clamp,baselArmuArmClamp);
		window.draw(fing,baselArmuArmClampFing);
		window.draw(circle);
		window.draw(text);

		// Finally, display rendered frame on screen
		window.display();
	} //loop back for next frame
	return EXIT_SUCCESS;
} 