#pragma once
#include <math.h>

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

    Point operator+=(const Point &rhs){
        m_x += rhs.m_x;
        m_y += rhs.m_y;
        return *this;
    }

    Point operator-(const Point &rhs){
        return Point(m_x - rhs.m_x, m_y - rhs.m_y);
    }

    Point operator-=(const Point &rhs){
        m_x -= rhs.m_x;
        m_y -= rhs.m_y;
        return *this;
    }

    Point operator-() const{
        return Point(-m_x, -m_y);
    }

    Point Rotate(Point base, float angle){

        Point RotatedPoint,tmp;
        float radian = angle*M_PI/180;
        
        tmp = *this - base;
        RotatedPoint.m_x = tmp.m_x*cos(radian) - tmp.m_y*sin(radian);
        RotatedPoint.m_y = tmp.m_x*sin(radian) + tmp.m_y*cos(radian);

        RotatedPoint += base;

        return RotatedPoint;

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

    bool Cross(Vec A){
        if( m_x * A.m_y - m_y * A.m_x > 0.0f)
            return true;
        return false;
    }

};

// Point operator+(const Point &lhs, const Vec &rhs){
//     return Point(lhs.m_x+rhs.m_x,lhs.m_y+rhs.m_y);
// }
