#include <bits/stdc++.h>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "world.h"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define WINDOW_NAME "Physical"

int main()
{
	
	// sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_NAME);
	// window.setFramerateLimit(60);

	World worldTest;
	
	// worldTest.CreatCircleBody(Point(100,100),20);
	
	std::vector<Point> A;
	A.push_back(Point(0, 5));
	A.push_back(Point(2, 0));
	A.push_back(Point(4, 0));
	Body* PA = new PolygonBody(Point(0,0),A);

	std::vector<Point> B;
	B.push_back(Point( 0, 4));
	B.push_back(Point(-1, 2));
	B.push_back(Point( 1, 2));
	Body* PB = new PolygonBody(Point(0,0), B);

	if( worldTest.GJKcollision(PA,PB) )
		printf("Coll");
	else
		printf("fuck");
	

	// Start the game loop
	// while (window.isOpen()){
	// 	// Process events
	// 	sf::Event event;
	// 	while (window.pollEvent(event))
	// 	{

	// 		switch (event.type){
	// 			case sf::Event::Closed:
	// 				window.close();
	// 				break;
	// 			case sf::Event::EventType::KeyPressed:
	// 				break;
	// 			case sf::Event::EventType::KeyReleased:
	// 				break;
	// 			case sf::Event::MouseButtonPressed:
	// 				break;
	// 			default:
	// 				break;
	// 		}

	// 	}

	// 	worldTest.DisplaySFML(window);
	// 	window.display();

	// }

	return EXIT_SUCCESS;

}
