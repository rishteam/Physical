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

    void CreatCircleBody(Point center, float radius);
    void CreatRectBody(Point center, float width, float height);
    void CreatPolygonBody(Point center, std::vector<Point> v);

    Point SupportFun(Body *A, Body *B, Vec D);
    bool Cross(Vec A, Vec B);
    bool GJKcollision(Body* A, Body* B);

    // draw at SFML
    void DisplaySFML(sf::RenderWindow &window);

private:

    std::vector <Body*> m_bodies;

};
