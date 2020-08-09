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

int main(){

	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_NAME);
	window.setFramerateLimit(60);
	ImGui::SFML::Init(window);

	sf::Clock deltaClock;

	World worldTest(WINDOW_WIDTH,WINDOW_HEIGHT);
	

	// float S = 5.0f;

	// std::vector<Point> A;
	// A.push_back(Point( 0*S, 50*S));
	// A.push_back(Point(20*S,  0*S));
	// A.push_back(Point(40*S,  0*S));
	// worldTest.CreatPolygonBody(Point(640, 360), A);

	// worldTest.CreatRectBody(Point(600,350),50*S,5*S);

	// S = 1.0f;
	// std::vector<Point> B;
	// B.push_back(Point(   0*S,  40*S));
	// B.push_back(Point(  20*S,  20*S));
	// B.push_back(Point(  30*S, -20*S));
	// worldTest.CreatPolygonBody(Point(640, 360), B);

	int MAXN = 10;
	srand( time(NULL) );
	
	// Body* MMouse  = new CircleBody(Point(0,0), 10);
	// worldTest.CreatBody(MMouse);

	sf::CircleShape CS;
	sf::RectangleShape RS;
	CS.setFillColor(sf::Color(0xAA, 0xAA, 0xAA));
	RS.setFillColor(sf::Color(0xAA, 0xAA, 0xAA));

	sf::Clock clk;
	int cnt = 0, fps = 0;

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

		static float position[2] = {640,360};
		static float WH[2] = {100,10};
		static float hight = 10.0f;
		static float radius = 10.0f;
		static float angle = 10.0f;
		static bool previewCirC = false;
		static bool previewRact = false;

		ImGui::Begin("CreateBody");
		ImGui::SliderFloat2("Position", position, 0.0f, 1280.0f);
		ImGui::SliderFloat2("Weight, Height", WH, 10.0f, 300.0f);
		ImGui::SliderFloat("Radius", &radius, 1.0f, 100.0f);
		ImGui::SliderFloat("Angle", &angle, -360.0f, 360.0f);
		ImGui::Checkbox("Preview CirCle", &previewCirC);
		ImGui::SameLine();
		if (ImGui::Button("Create CirCle")){
			worldTest.CreatCircleBody(Point(position[0], position[1]), radius, angle);
		}

		ImGui::Checkbox("Preview Ract", &previewRact);
		ImGui::SameLine();
		if (ImGui::Button("Create Ract")){
			worldTest.CreatRectBody(Point(position[0], position[1]), WH[0], WH[1], angle);
		}
		if ( ImGui::Button("Random 10 rect") ){
			for (int i = 0; i < MAXN; i++){
				worldTest.CreatRectBody(
					Point(rand() % 1280, rand() % 720),
					rand() % 100, rand() % 100, rand() % 360);
			}
		}
		ImGui::Text("%d",worldTest.BodySize());
		if(clk.getElapsedTime().asSeconds() >= 1.f)
        {
		    fps = cnt;
		    cnt = 0;
		    clk.restart();
        }
		ImGui::Text("FPS = %d", fps);
		ImGui::End();

		CS.setPosition(sf::Vector2f(position[0] - radius, position[1] - radius));
		CS.setRadius(radius);


		RS.setRotation(angle);
		Point R(position[0] - WH[0] / 2, position[1] - WH[1] / 2);
		R = R.Rotate(Point(position[0],position[1]),angle);
		RS.setPosition(sf::Vector2f(R.m_x,R.m_y));
		RS.setSize(sf::Vector2f(WH[0], WH[1]));

		// Point M(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
		// MMouse->setCenter(M);

		window.clear();

		if( previewCirC )
			window.draw(CS);
		if( previewRact )
			window.draw(RS);


		worldTest.update();
		worldTest.DisplaySFML(window);

		ImGui::SFML::Render(window);

		window.display();
		cnt++;

	}

	return EXIT_SUCCESS;

}
