#pragma once

#include <vector>
#include <math.h>
#include "point.h"

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

class Body{

public:
	Body() = default;
	Body(Point center, float angle = 0.0f);

	virtual Point supportPoint(Vec D){
		return Point();
	};

	Point getCenter(){
		return m_center;
	}
	void setCenter(Point center){
		m_center = center;
	};

	float getAngle(){
		return m_angle;
	}
	void setAngle(float angle){
		m_angle = angle;
		while( m_angle > 360 )
			m_angle -= 360;
		while( m_angle < -360 )
			m_angle += 360;
	}
	void Roate(float angle){
		m_angle += angle;
		while (m_angle > 360)
			m_angle -= 360;
		while (m_angle < -360)
			m_angle += 360;
	}

	//SFML
	virtual void drawSFML(sf::RenderWindow &window){};
	virtual void changeColor(sf::Color color){};

protected:

	Point m_center;
	float m_angle;

};

class CircleBody: public Body {

public:

	CircleBody() = default;
	CircleBody(Point center, float radius, float angle = 0.0f);

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
	RectBody(Point center, float width, float height, float angle = 0.0f);

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
	PolygonBody(Point center, std::vector<Point> v, float angle = 0.0f);

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