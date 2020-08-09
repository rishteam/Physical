#include "body.h"

Body::Body(Point center, float angle){
    m_center = center;
    m_angle = angle;
}

Point Body::getCenter(){
    return m_center;
}
void Body::setCenter(Point center){
    m_center = center;
};

float Body::getAngle(){
    return m_angle;
}
void Body::setAngle(float angle){
    m_angle = angle;
    while (m_angle > 360)
        m_angle -= 360;
    while (m_angle < -360)
        m_angle += 360;
}
void Body::Roate(float angle){
    m_angle += angle;
    while (m_angle > 360)
        m_angle -= 360;
    while (m_angle < -360)
        m_angle += 360;
}

CircleBody::CircleBody(Point center, float radius, float angle){
    m_center = center;
    m_radius = radius;
    m_angle = angle;
}

RectBody::RectBody(Point center, float width, float height, float angle){  
    m_center = center;
    m_width = width;
    m_height = height;
    m_angle = angle;
}

PolygonBody::PolygonBody(Point center, std::vector<Point> v, float angle){
    
    m_center = Point(0,0);
    for( auto i : v ){
        m_vec.push_back(i+center);
        m_center += (i+center);
    }
    
    m_center.m_x /= v.size();
    m_center.m_y /= v.size();

    for(int i = 0 ; i < m_vec.size() ; i++ ){
        m_vec[i] -= m_center;
    }
    
    m_angle = angle;

}

Point CircleBody::supportPoint(Vec D){

    float K = sqrt(m_radius*m_radius/(D.m_x*D.m_x+D.m_y*D.m_y));
    D.Times(K);
    return m_center+Point(D.m_x,D.m_y);

}

Point RectBody::supportPoint(Vec D){

    Point tmpP[4] = {
        (m_center + Point( m_width / 2,  m_height / 2)).Rotate(m_center,m_angle),
        (m_center + Point( m_width / 2, -m_height / 2)).Rotate(m_center,m_angle),
        (m_center + Point(-m_width / 2,  m_height / 2)).Rotate(m_center,m_angle),
        (m_center + Point(-m_width / 2, -m_height / 2)).Rotate(m_center,m_angle)
    };

    Point MAXP = tmpP[0];
    float MAXN = Vec(MAXP).InnerProduct(D);

    for(int i = 1 ; i < 4 ; i++ ){
        Point P = tmpP[i];
        float tmpF = Vec(P).InnerProduct(D);
        if( tmpF > MAXN ){
            MAXN =tmpF;
            MAXP = P;
        }
    }

    return MAXP;

}

Point PolygonBody::supportPoint(Vec D){

    Point MAXP = m_center+m_vec[0];
    MAXP = MAXP.Rotate(m_center,m_angle);
    float MAXN = Vec(MAXP).InnerProduct(D);

    for(int i = 1 ; i < m_vec.size() ; i++ ){
        Point P = m_center + m_vec[i];
        P = P.Rotate(m_center,m_angle);
        float tmp = Vec(P).InnerProduct(D);
        if( tmp > MAXN ){
            MAXN = tmp;
            MAXP = P;
        }
    }
    return MAXP;

}

std::pair<float, float> CircleBody::getBoundaryWH(){
    return std::make_pair(m_radius,m_radius);
}

std::pair<float, float> RectBody::getBoundaryWH(){
    
    Point tmp[4] = {
        Point(m_center.m_x - m_width / 2, m_center.m_y - m_height / 2),
        Point(m_center.m_x - m_width / 2, m_center.m_y + m_height / 2),
        Point(m_center.m_x + m_width / 2, m_center.m_y - m_height / 2),
        Point(m_center.m_x + m_width / 2, m_center.m_y + m_height / 2)
    };

    float maxW,maxH,minW,minH;
    minW = minH = 1e8;
    for(int i = 0 ; i < 4 ; i++ ){
        tmp[i] = tmp[i].Rotate(m_center,m_angle);
        maxW = std::max(maxW, tmp[i].m_x);
        maxH = std::max(maxH, tmp[i].m_y);
        minW = std::min(minW, tmp[i].m_x);
        minH = std::min(minH, tmp[i].m_y);
        // printf("X: %lf %lf, Y: %lf %lf\n", minW, maxW, minH, maxH);
    }
    // printf("---\n");

    return std::make_pair(maxW-minW,maxH-minH);

}

std::pair<float, float> PolygonBody::getBoundaryWH(){

    float maxW, maxH, minW, minH;
    for(int i = 0 ; i < m_vec.size() ; i++ ){
        Point P = (m_center + m_vec[i]).Rotate(m_center, m_angle);
        maxW = std::max(maxW, P.m_x);
        maxH = std::max(maxH, P.m_y);
        minW = std::min(minW, P.m_x);
        minH = std::min(minH, P.m_y);

        // printf("X: %lf %lf, Y: %lf %lf\n", minW,maxW,minH,maxH);
    }
    // printf("---\n");

    return std::make_pair(maxW - minW, maxH - minH);

}

// SFML
void CircleBody::drawSFML(sf::RenderWindow &window){

    m_shape.setPosition(sf::Vector2f(m_center.m_x - m_radius, m_center.m_y - m_radius));
    m_shape.setRadius(m_radius);

    window.draw(m_shape);
}

void RectBody::drawSFML(sf::RenderWindow &window){

    Point R(m_center.m_x - m_width / 2, m_center.m_y - m_height / 2);
    R = R.Rotate(m_center,m_angle);
    m_shape.setPosition(sf::Vector2f(R.m_x,R.m_y));
    m_shape.setSize(sf::Vector2f(m_width, m_height));
    m_shape.setRotation(m_angle);

    window.draw(m_shape);

}

void PolygonBody::drawSFML(sf::RenderWindow &window){
    
    m_shape.setPosition(0, 0);
    m_shape.setPointCount(m_vec.size());
    for (int i = 0; i < m_vec.size(); i++)
    {
        Point P = (m_center + m_vec[i]).Rotate(m_center,m_angle);
        m_shape.setPoint(i, sf::Vector2f(P.m_x, P.m_y));
    }
    //m_shape.setRotation(m_angle);

    window.draw(m_shape);

}
