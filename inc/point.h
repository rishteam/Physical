#pragma once


// struct Vec;
struct Point {
    
    float m_x, m_y;

    friend class Vec;

    Point() = default;
    Point(float x,float y){
        m_x = x, m_y = y;
    }

    Point operator+(const Point &rhs){
        return Point(m_x + rhs.m_x, m_y + rhs.m_y);
    }

    Point operator-(const Point &rhs){
        return Point(m_x - rhs.m_x, m_y - rhs.m_y);
    }

    Point operator-() const{
        return Point(-m_x, -m_y);
    }

    // void MoveVec(Vec V){
    //     return Point(m_x+V.m_x,m_y+V.m_y);
    // }

};

struct Vec {
    
    float m_x, m_y;
    
    Vec() = default;
    Vec(float x, float y){
        m_x = x, m_y = y;
    }
    Vec(Point A){
        m_x = A.m_x;
        m_y = A.m_y;
    }
    Vec(Point A, Point B){
        m_x = B.m_x - A.m_x;
        m_y = B.m_y - A.m_y;
    }

    Vec operator+(const Vec &rhs){
        return Vec(m_x + rhs.m_x, m_y + rhs.m_y);
    }

    Vec operator-(const Vec &rhs){
        return Vec(m_x - rhs.m_x, m_y - rhs.m_y);
    }

    Vec operator-() const {
        return Vec(-m_x, -m_y);
    }

    void Times(float K){
        m_x *= K;
        m_y *= K;
    }

    float InnerProduct(Vec A){
        return m_x * A.m_x + m_y * A.m_y;
    }

};

// Point operator+(const Point &lhs, const Vec &rhs){
//     return Point(lhs.m_x+rhs.m_x,lhs.m_y+rhs.m_y);
// }
