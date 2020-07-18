#pragma once

#include <vector>
#include <math.h>
#include "point.h"

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

class Body{

public:
	Body() = default;
	Body(Point center);
	
	virtual Point supportPoint(Vec D){
		return Point();
	};

	Point getCenter(){
		return m_center;
	}

	void setCenter(Point center){
		m_center = center;
	};

	//SFML
	virtual void drawSFML(sf::RenderWindow &window){};
	virtual void changeColor(sf::Color color){};

protected:
	Point m_center;

};

class CircleBody: public Body {

public:

	CircleBody() = default;
	CircleBody(Point center, float radius);

	virtual Point supportPoint(Vec D) override;
	
	//SFML
	virtual void drawSFML(sf::RenderWindow &window) override;
	virtual void changeColor(sf::Color color) override {
		m_shape.setFillColor(color);
	};

private:
	float m_radius;
	//SFML
	sf::CircleShape m_shape;
};

class RectBody : public Body {

public:

	RectBody() = default;
	RectBody(Point center, float width, float height);

	virtual Point supportPoint(Vec D) override;

	//SFML
	virtual void drawSFML(sf::RenderWindow &window) override;
	virtual void changeColor(sf::Color color) override {
		m_shape.setFillColor(color);
	};

private:
	float m_width,m_height;
	//SFML
	sf::RectangleShape m_shape;
};

class PolygonBody : public Body{

public:

	PolygonBody();
	PolygonBody(Point center, std::vector<Point> v);

	virtual Point supportPoint(Vec D) override;

	//SFML
	virtual void drawSFML(sf::RenderWindow &window) override;
	virtual void changeColor(sf::Color color) override {
		m_shape.setFillColor(color);
	};

private:
	std::vector <Point> m_vec;
	//SFML
	sf::ConvexShape m_shape;
};