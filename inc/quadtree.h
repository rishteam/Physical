#pragma once

#include "imgui.h"
#include "imgui-SFML.h"

#include <bits/stdc++.h>
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

    void imguiDebug()
    {
        if (ImGui::TreeNode("Points"))
        {
            for (auto &p : m_data)
            {
                ImGui::PushID(&p);
                ImGui::Text("%.2f %.2f", p.m_x, p.m_y);
                ImGui::PopID();
            }
            ImGui::TreePop();
        }
        for (int i = 0; i < 4; i++)
        {
            if (!m_child[i])
                continue;
            ImGui::PushID(i);
            int tmp = m_child[i]->m_data.size();
            std::stringstream ss,aa,ab,ba,bb;
            ss << tmp;
            aa << std::fixed << std::setprecision(2) << m_child[i]->m_center.m_x-m_child[i]->m_width/2;
            ab << std::fixed << std::setprecision(2) << m_child[i]->m_center.m_y-m_child[i]->m_height/2;
            ba << std::fixed << std::setprecision(2) << m_child[i]->m_center.m_x+m_child[i]->m_width/2;
            bb << std::fixed << std::setprecision(2) << m_child[i]->m_center.m_y+m_child[i]->m_height/2;

            std::string tmps = "("+ aa.str() + ", " + ab.str() + " ) , ( " + ba.str() + ", " + bb.str() + ") :" + ss.str();

            if (ImGui::TreeNode(tmps.c_str()))
            {
                m_child[i]->imguiDebug();
                ImGui::TreePop();
            }
            ImGui::PopID();
        }
    }

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