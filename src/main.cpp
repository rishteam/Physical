#include <bits/stdc++.h>

#include "imgui.h"
#include "imgui-SFML.h"

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "world.h"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define WINDOW_NAME "Physical"

int main()
{
	
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_NAME);
	window.setFramerateLimit(60);
	ImGui::SFML::Init(window);

	sf::Clock deltaClock;

	World worldTest;
	
	std::vector<Point> A;
	A.push_back(Point(  0, 500));
	A.push_back(Point(200,   0));
	A.push_back(Point(400,   0));
	worldTest.CreatPolygonBody(Point(0, 0), A);

	std::vector<Point> B;
	B.push_back(Point(   0, 400));
	B.push_back(Point(-100, 200));
	B.push_back(Point( 100, 200));
	worldTest.CreatPolygonBody(Point(0, 0), B);

	Body* MMouse  = new CircleBody(Point(0,0), 30);
	worldTest.CreatBody(MMouse);

	sf::CircleShape CS;
	sf::RectangleShape RS;
	CS.setFillColor(sf::Color(0xAA, 0xAA, 0xAA));
	RS.setFillColor(sf::Color(0xAA, 0xAA, 0xAA));

	// Start the game loop
	while (window.isOpen()){
		// Process events
		sf::Event event;
		while (window.pollEvent(event)){
			ImGui::SFML::ProcessEvent(event);

			switch (event.type){
				case sf::Event::Closed:
					window.close();
					break;
				default:
					break;
			}
		}
		ImGui::SFML::Update(window, deltaClock.restart());

		static float position[2];
		static float WH[2];
		static float hight = 0.0f;
		static float radius = 0.0f;
		static bool previewCirC = false;
		static bool previewRact = false;

		ImGui::Begin("CreateBody");
		ImGui::SliderFloat2("Position", position, 0.0f, 1280.0f);
		ImGui::SliderFloat2("Weight, Height", WH, 10.0f, 300.0f);
		ImGui::SliderFloat("Radius",&radius, 1.0f, 100.0f);
		ImGui::Checkbox("Preview CirCle", &previewCirC); ImGui::SameLine();
		if( ImGui::Button("Create CirCle") ){
			worldTest.CreatCircleBody(Point(position[0],position[1]),radius);
		}

		ImGui::Checkbox("Preview Ract", &previewRact); ImGui::SameLine();
		if( ImGui::Button("Create Ract") ){
			worldTest.CreatRectBody(Point(position[0],position[1]),WH[0],WH[1]);
		}
		ImGui::End();

		CS.setPosition(sf::Vector2f(position[0]-radius,position[1]-radius));
		CS.setRadius(radius);

		RS.setPosition(sf::Vector2f(position[0] - WH[0]/2, position[1] - WH[1]/2));
		RS.setSize(sf::Vector2f(WH[0],WH[1]));

		Point M(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
		MMouse->setCenter(M);

		window.clear();

		if( previewCirC )
			window.draw(CS);
		if( previewRact )
			window.draw(RS);


		worldTest.update();
		worldTest.DisplaySFML(window);

		ImGui::SFML::Render(window);

		window.display();

	}

	return EXIT_SUCCESS;

}
