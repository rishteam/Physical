#pragma once

#include <vector>
#include "point.h"
#include "body.h"

class QuadTree{

public:

    QuadTree() = default;
    ~QuadTree(){
        for(int i = 0 ; i < 4 ; i++ )
            delete m_child[i];
    }
    QuadTree(Point center, float width, float height);

    void clear();
    void init(Point center, float width, float height);
    void insert(Point P, int idx);
    bool contain(Point P);
    bool contain(Body* B);
    void subdivide();

    std::vector <int>& query(std::vector<int> &V, Body* B); 
    Point SupportFun(Body* A, Body* B, Vec D);

    //SFML
    void drawSFML(sf::RenderWindow &window);

private:

    Point m_center;
    float m_width,m_height;
    int m_capacity = 10;

    QuadTree *m_child[4] = {nullptr};
    
    std::vector <Point> m_data;
    std::vector <int> m_dataIdx;

    sf::RectangleShape m_shape;
    sf::Color m_color;

};