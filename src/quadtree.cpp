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

bool QuadTree::contain(Body* B){// use GJK

    Body* A = new RectBody(m_center,m_width,m_height);

    int PointNum = 0;
    Point Simplex[3];
    Vec D(A->getCenter(), B->getCenter());
    if (D.m_x == 0 && D.m_y == 0)
        D = Vec(1.0, 0.0);
    Simplex[PointNum++] = SupportFun(A, B, D);
    Simplex[PointNum++] = SupportFun(A, B, -D);

    while (true){

        Vec V(Simplex[0], Simplex[1]);
        if ( V.Cross( -Vec(Simplex[0])))
            D = Vec(-V.m_y, V.m_x);
        else
            D = Vec(V.m_y, -V.m_x);

        Simplex[PointNum++] = SupportFun(A, B, D);

        if (Vec(Simplex[2]).InnerProduct(D) < 0){
            delete A;
            return false;
        }

        Vec AB = (Simplex[2], Simplex[1]);
        Vec AC = (Simplex[2], Simplex[0]);

        Vec DAB, DAC;
        if ( AB.Cross( -Vec(Simplex[2])))
            DAB = Vec(-AB.m_y, AB.m_x);
        else
            DAB = Vec(AB.m_y, -AB.m_x);

        if ( AC.Cross( -Vec(Simplex[2])))
            DAC = Vec(-AC.m_y, AC.m_x);
        else
            DAC = Vec(AC.m_y, -AC.m_x);

        if (DAB.InnerProduct(AC) >= 0.0f){
            if (DAC.InnerProduct(AB) >= 0.0f){
                delete A;
                return true;
            }
            Simplex[1] = Simplex[2];
            PointNum--;
            continue;
        }
        if (DAC.InnerProduct(AB) >= 0.0f){
            Simplex[0] = Simplex[2];
            PointNum--;
            continue;
        }

        break;

    }

    delete A;
    return false;

}

Point QuadTree::SupportFun(Body *A, Body *B, Vec D){

    Point PA = A->supportPoint(D);
    Point PB = B->supportPoint(-D);
    // printf("PA: %lf, %lf PB: %lf, %lf D: %lf, %lf\n",PA.m_x,PA.m_y,PB.m_x,PB.m_y,D.m_x,D.m_y);
    return PA - PB;
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

