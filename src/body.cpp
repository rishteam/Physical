#include "body.h"

Body::Body(Point center){
    m_center = center;
}

CircleBody::CircleBody(Point center, float radius){
    m_center = center;
    m_radius = radius;

    //SFML
    m_shape.setPosition(sf::Vector2f(m_center.m_x, m_center.m_y));
    m_shape.setRadius(m_radius);

}

RectBody::RectBody(Point center, float width, float height){
    m_center = center;
    m_width = width;
    m_height = height;

    //SFML
    m_shape.setPosition(sf::Vector2f(m_center.m_x-m_width/2, m_center.m_y-m_height/2));
    m_shape.setSize(sf::Vector2f(m_width,m_height));

}

PolygonBody::PolygonBody(Point center, std::vector<Point> v){
    m_center = center;
    for( auto i : v )
        m_vec.push_back(i);

    //SFML
    m_shape.setPosition(0,0);
    m_shape.setPointCount(m_vec.size());
    for(int i = 0 ; i < m_vec.size() ; i++ ){
        Point P = m_center+m_vec[i];
        m_shape.setPoint(i, sf::Vector2f(P.m_x,P.m_y));
    }
    
}

void CircleBody::drawSFML(sf::RenderWindow &window){
    window.draw(m_shape);
}

void RectBody::drawSFML(sf::RenderWindow &window){
    window.draw(m_shape);
}

void PolygonBody::drawSFML(sf::RenderWindow &window){
    window.draw(m_shape);
}

Point CircleBody::supportPoint(Vec D){

    float K = sqrt(m_radius*m_radius/(D.m_x*D.m_x+D.m_y*D.m_y));
    D.Times(K);
    return m_center+Point(D.m_x,D.m_y);

}

Point RectBody::supportPoint(Vec D){

    if( D.m_x > 0 ){
        if( D.m_y > 0 )
            return m_center+Point( m_width/2,  m_height/2);
        return m_center+Point( m_width / 2, -m_height / 2);
    }
    if( D.m_y > 0 )
        return m_center+Point(-m_width / 2,  m_height / 2);
    return m_center+Point(-m_width / 2, -m_height / 2);

}

Point PolygonBody::supportPoint(Vec D){

    Point MAXP = m_center+m_vec[0];
    float MAXN = Vec(MAXP).InnerProduct(D);

    for(int i = 1 ; i < m_vec.size() ; i++ ){
        Point P = m_center + m_vec[i];
        float tmp = Vec(P).InnerProduct(D);
        if( tmp > MAXN ){
            MAXN = tmp;
            MAXP = P;
        }
    }
    return MAXP;

}

