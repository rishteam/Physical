#pragma once

#include "body.h"
#include <vector>

class World{

public:
    
    World() = default;
    ~World(){
        for( auto i : m_bodies)
            delete i;
    }

    void CreatCircleBody(Point center, float radius, float angle = 0.0f);
    void CreatRectBody(Point center, float width, float height, float angle = 0.0f);
    void CreatPolygonBody(Point center, std::vector<Point> v, float angle = 0.0f);
    void CreatBody(Body* B);

    Point SupportFun(Body *A, Body *B, Vec D);
    bool Cross(Vec A, Vec B);
    bool GJKcollision(Body* A, Body* B);

    void checkCollision();
    void update();
    
    // draw at SFML
    void DisplaySFML(sf::RenderWindow &window);

private:

    std::vector <Body*> m_bodies;

};
