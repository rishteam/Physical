#include "world.h"

World::World(float width, float height){
    m_bodies.clear();
    QT.clear();
    QT.init(Point(width/2,height/2),width,height);
}

void World::CreatCircleBody(Point center, float radius, float angle){
    m_bodies.push_back(new CircleBody(center,radius,angle));
    int idx = m_bodies.size()-1;
    QT.insert(m_bodies[idx]->getCenter(), idx);
}

void World::CreatRectBody(Point center, float width, float height, float angle){
    m_bodies.push_back(new RectBody(center, width, height,angle));
    int idx = m_bodies.size()-1;
    QT.insert(m_bodies[idx]->getCenter(), idx);
}

void World::CreatPolygonBody(Point center, std::vector<Point> v, float angle){
    m_bodies.push_back(new PolygonBody(center,v,angle));
    int idx = m_bodies.size()-1;
    QT.insert(m_bodies[idx]->getCenter(), idx);
}

void World::CreatBody(Body *B){
    m_bodies.push_back(B);
    int idx = m_bodies.size()-1;
    QT.insert(m_bodies[idx]->getCenter(), idx);
}

void World::DisplaySFML(sf::RenderWindow &window){

    // QT.drawSFML(window);

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

bool World::GJKcollision(Body* A, Body* B){

    // printf("start\n");

    int PointNum = 0;
    Point Simplex[3];
    Vec D(A->getCenter(), B->getCenter());
    if( D.m_x == 0 && D.m_y == 0 )
        D = Vec(1.0,0.0);
    Simplex[PointNum++] = SupportFun(A, B, D);
    Simplex[PointNum++] = SupportFun(A, B, -D);

    while( true ){

        Vec V(Simplex[0],Simplex[1]);
        if( V.Cross( -Vec(Simplex[0]) ) )
            D = Vec( -V.m_y,  V.m_x);
        else D = Vec( V.m_y, -V.m_x);

        Simplex[PointNum++] = SupportFun(A, B, D);

        if( Vec(Simplex[2]).InnerProduct(D) < 0 )
            return false;

        Vec AB = (Simplex[2], Simplex[1]);
        Vec AC = (Simplex[2], Simplex[0]);

        Vec DAB,DAC;
        if( AB.Cross( -Vec(Simplex[2]) ) )
            DAB = Vec(-AB.m_y, AB.m_x);
        else DAB = Vec( AB.m_y, -AB.m_x);

        if( AC.Cross( -Vec(Simplex[2])))
            DAC = Vec(-AC.m_y, AC.m_x);
        else DAC = Vec(AC.m_y, -AC.m_x);

        if( DAB.InnerProduct(AC) >= 0.0f ){
            if( DAC.InnerProduct(AB) >= 0.0f )
                return true;
            Simplex[1] = Simplex[2];
            PointNum--;
            continue;
        }
        if( DAC.InnerProduct(AB) >= 0.0f ){
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

    // O(n^2)
    // clock_t startA,endA,startB,endB;
    // startA = clock();
    // for(int i = 0 ; i < m_bodies.size() ; i++ ){
    //     for(int j = i+1 ; j < m_bodies.size() ; j++ ){
    //         if( GJKcollision(m_bodies[i],m_bodies[j]) ){
    //             m_bodies[i]->changeColor(sf::Color::Red);
    //             m_bodies[j]->changeColor(sf::Color::Red);
    //         }
    //     }
    // }
    // endA = clock();
    // startB = clock();
    for(int i = 0 ; i < m_bodies.size() ; i++ ){

        std::vector <int> V;
        V.clear();

        QT.query(V,m_bodies[i]);
        // if( V.size() )
        //     printf("%d\n",V.size());
        for(int j = 0 ; j < V.size() ; j++ ){
            if( i != V[j] && GJKcollision(m_bodies[i],m_bodies[V[j]]) ){
                m_bodies[i]->changeColor(sf::Color::Red);
                m_bodies[V[j]]->changeColor(sf::Color::Red);
            }
        }

    }
    // endB = clock();

    // printf("%ld, %ld\n",endA-startA,endB-startB);

}

void World::update(){

    for(auto i : m_bodies)
        i->Roate(1);

    checkCollision();

    // QT.imguiDebug();

}