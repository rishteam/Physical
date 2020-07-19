#include "world.h"

void World::CreatCircleBody(Point center, float radius, float angle){
    m_bodies.push_back(new CircleBody(center,radius,angle));
}

void World::CreatRectBody(Point center, float width, float height, float angle){
    m_bodies.push_back(new RectBody(center, width, height,angle));
}

void World::CreatPolygonBody(Point center, std::vector<Point> v, float angle){
    m_bodies.push_back(new PolygonBody(center,v,angle));
}

void World::CreatBody(Body *B){
    m_bodies.push_back(B);
}

void World::DisplaySFML(sf::RenderWindow &window){

    for( auto &B : m_bodies ){
        B -> drawSFML(window);
    }

}

Point World::SupportFun(Body* A, Body* B, Vec D){
    
    Point PA = A->supportPoint(D);
    Point PB = B->supportPoint(-D);
    // printf("PA: %lf, %lf PB: %lf, %lf D: %lf, %lf\n",PA.m_x,PA.m_y,PB.m_x,PB.m_y,D.m_x,D.m_y);
    return PA-PB;

}

bool World::Cross(Vec A, Vec B){
    if( A.m_x*B.m_y - A.m_y*B.m_x > 0.0f )
        return true;
    return false;
}

bool World::GJKcollision(Body* A, Body* B){

    // printf("start\n");

    int PointNum = 0;
    Point Simplex[3];
    Vec D(A->getCenter(), B->getCenter());
    if( D.m_x == 0 && D.m_y == 0 )
        D = Vec(1.0,0.0);
    Simplex[PointNum++] = SupportFun(A, B, D);
    Simplex[PointNum++] = SupportFun(A, B, -D);

    int cnt = 1000;
    while( cnt-- > 0 ){

        Vec V(Simplex[0],Simplex[1]);
        if( Cross( V, -Vec(Simplex[0]) ) )
            D = Vec( -V.m_y,  V.m_x);
        else D = Vec( V.m_y, -V.m_x);

        Simplex[PointNum++] = SupportFun(A, B, D);

        // printf("A: %.0lf, %.0lf\n", Simplex[2].m_x, Simplex[2].m_y);
        // printf("B: %.0lf, %.0lf\n", Simplex[1].m_x, Simplex[1].m_y);
        // printf("C: %.0lf, %.0lf\n", Simplex[0].m_x, Simplex[0].m_y);
        // printf("-----\n");

        Vec AB = (Simplex[2], Simplex[1]);
        Vec AC = (Simplex[2], Simplex[0]);

        Vec DAB,DAC;
        if( Cross( AB, -Vec(Simplex[2]) ) )
            DAB = Vec(-AB.m_y, AB.m_x);
        else DAB = Vec( AB.m_y, -AB.m_x);

        if (Cross(AC, -Vec(Simplex[2])))
            DAC = Vec(-AC.m_y, AC.m_x);
        else DAC = Vec(AC.m_y, -AC.m_x);

        if( DAB.InnerProduct(AC) > 0.0f ){
            if( DAC.InnerProduct(AB) > 0.0f )
                return true;
            Simplex[1] = Simplex[2];
            PointNum--;
            continue;
        }
        if( DAC.InnerProduct(AB) > 0.0f ){
            Simplex[0] = Simplex[2];
            PointNum--;
            continue;
        }

        return false;
    }

    return false;

}

void World::checkCollision(){

    for(auto i : m_bodies )
        i->changeColor(sf::Color::White);

    for(int i = 0 ; i < m_bodies.size() ; i++ ){
        for(int j = i+1 ; j < m_bodies.size() ; j++ ){
            if( GJKcollision(m_bodies[i],m_bodies[j]) ){
                m_bodies[i]->changeColor(sf::Color::Red);
                m_bodies[j]->changeColor(sf::Color::Red);
            }
        }
    }

}

void World::update(){

    m_bodies[0]->Roate(1);
    m_bodies[1]->Roate(1);
    checkCollision();

}