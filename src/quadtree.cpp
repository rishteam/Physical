#include "quadtree.h"

QuadTree::QuadTree(Point center, float width, float height){
    m_center = center;
    m_width = width;
    m_height = height;
    m_data.clear();
    m_dataIdx.clear();
    for(int i = 0 ; i < 4 ; i++ )
        m_child[i] = nullptr;

    // printf("%lf %lf %lf %lf\n", m_center.m_x, m_center.m_y, m_width, m_height);
    m_color = sf::Color(rand(),rand(),rand());

}

void QuadTree::clear(){
    m_data.clear();
    m_dataIdx.clear();
    for(int i = 0 ; i < 4 ; i++ )
        delete m_child[i];
    for (int i = 0; i < 4; i++)
        m_child[i] = nullptr;
}

void QuadTree::init(Point center, float width, float height){
    m_center = center;
    m_width = width;
    m_height = height;
    m_data.clear();
    m_dataIdx.clear();
    for(int i = 0 ; i < 4 ; i++ )
        m_child[i] = nullptr;

    // printf("%lf %lf %lf %lf\n",m_center.m_x,m_center.m_y,m_width,m_height);
    m_color = sf::Color(rand(), rand(), rand());
}

void QuadTree::insert(Point P, int idx){

    // printf("insert chk\n");
    if( !contain(P) )
        return;
    // printf("insert %lf, %lf\n",P.m_x,P.m_y);

    m_data.push_back(P);
    m_dataIdx.push_back(idx);
    
    if( m_data.size() > m_capacity ){
        subdivide();
        if( m_child[0] ){
            for(int i = 0 ; i < 4 ; i++ )
                m_child[i]->insert(P,idx);
        }
    }

    // printf("%d\n",m_data.size());

}

bool QuadTree::contain(Point P){

    Point PP = P - (m_center - Point(m_width / 2, m_height / 2));
    // printf("%lf, %lf --- ",P.m_x,P.m_y);
    if( PP.m_x < 0 || PP.m_y < 0 )
        return false;

    Point tmp = (m_center + Point(m_width / 2, m_height / 2));
    // printf(" %lf, %lf\n",tmp.m_x,tmp.m_y);
    if( P.m_x > tmp.m_x || P.m_y > tmp.m_y )
        return false;
    
    return true;

}

bool QuadTree::contain(Body* B){// use AABB

    auto WH = B->getBoundaryWH();

    float minAx = m_center.m_x - m_width / 2,
          maxAx = m_center.m_x + m_width / 2,
          minAy = m_center.m_y - m_height / 2,
          maxAy = m_center.m_y + m_height / 2;
    float minBx = B->getCenter().m_x - WH.first / 2,
          maxBx = B->getCenter().m_x + WH.first / 2,
          minBy = B->getCenter().m_y - WH.second / 2,
          maxBy = B->getCenter().m_y + WH.second / 2;

    // printf("%lf %lf %lf %lf\n", minAx, maxAx, minAy, maxAy);
    // printf("%lf %lf %lf %lf\n", minBx, maxBx, minBy, maxBy);
    // printf("-----\n");

    return( maxAx > minBx && maxBx > minAx &&
            maxAy > minBy && maxBy > minAy );

}

void QuadTree::subdivide(){

    if( m_child[0] != nullptr )
        return;

    int W = m_width/2;
    int H = m_height/2;

    if( W < 10 || H < 10 )
        return;

    Point center[4] = {
        m_center + Point( W/2,  H/2),
        m_center + Point( W/2, -H/2),
        m_center + Point(-W/2, -H/2),
        m_center + Point(-W/2,  H/2)
    };

    for(int i = 0 ; i < 4 ; i++ ){
        m_child[i] = new QuadTree(center[i],W,H);
        for(int j = 0 ; j < m_data.size()-1 ; j++ )
            m_child[i]->insert(m_data[j],m_dataIdx[j]);
    }


}

std::vector<int>& QuadTree::query(std::vector<int> &V, Body *B){

    if( !contain(B) )
        return V;

    // printf("In: %d\n",V.size());

    if( m_child[0] == nullptr ){
        for(auto i : m_dataIdx )
            V.push_back(i);
        return V;
    }

    for(int i = 0 ; i < 4 ; i++ ){
        m_child[i]->query(V,B);
    }

    return V;
}

void QuadTree::drawSFML(sf::RenderWindow &window){

    m_shape.setPosition( sf::Vector2f(m_center.m_x-m_width/2,m_center.m_y-m_height/2) );
    m_shape.setSize(sf::Vector2f(m_width, m_height));
    m_shape.setFillColor(m_color);
    // m_shape.setPosition(sf::Vector2f(100.0f,100.0f));
    // m_shape.setSize(sf::Vector2f(100.0f,100.0f));
    window.draw(m_shape);

    for(int i = 0 ; i < 4 ; i++ ){
        if( m_child[i] )
            m_child[i]->drawSFML(window);
    }

}

