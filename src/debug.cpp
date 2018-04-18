/********************************************************************************
*********************************************************************************
	3KSC: A fighting game
    Copyright (C) 2018  Chaotic Games

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/m_licenses/>.m_

    m_You can contact Chaotic Games at: chaoticgamesdev@gmail.com
*********************************************************************************
*********************************************************************************/

#include "include/debug.hpp"
#include "include/managers/EngineManager.hpp"
#include <iostream>

Debug::Debug(b2Body* p_body, int p_num) : scene::ISceneNode(EngineManager::instance().getSceneManager()->getRootSceneNode(), EngineManager::instance().getSceneManager(), 500) {
    m_Material.Wireframe = true;
    m_Material.Lighting = false;

    int red   = rand()%(256);
    int green = rand()%(256);
    int blue  = rand()%(256);
    m_color = video::SColor(red, green, blue, 0);
    
    int t_count = -1;

    m_body = p_body;
    b2Fixture* t_fixture = m_body->GetFixtureList();
    while(t_fixture != NULL){
        b2Shape* t_shape = t_fixture->GetShape();
        if(t_shape->GetType() == 2){
            t_count++;
            if(t_count == p_num){
                m_shape = t_shape;
                b2PolygonShape* t_polyShape = static_cast<b2PolygonShape*>(t_shape);
            
                int t_bodyPositionX = m_body->GetPosition().x;
                int t_bodyPositionY = m_body->GetPosition().y;

                int t_count = t_polyShape->GetVertexCount();
                for(int i = 0; i < t_count; i++){
                    b2Vec2 t_verts = t_polyShape->GetVertex(i);
                    m_posVertex[i][0] = t_verts.x + t_bodyPositionX;
                    m_posVertex[i][1] = t_verts.y + t_bodyPositionY;
                }
                
                for(int i = 0; i < 4; i++){
                    m_Vertices[i] = video::S3DVertex(m_posVertex[i][0], m_posVertex[i][1],0, 0,0,0, m_color, 0, 0);
                }
            }
        }
        t_fixture = t_fixture->GetNext();
    }
}

void Debug::OnRegisterSceneNode(){
    if(IsVisible)
        SceneManager->registerNodeForRendering(this);

    ISceneNode::OnRegisterSceneNode();
}

void Debug::render(){
    u16 indices[] = {0,2,3, 2,1,3, 1,0,3, 2,0,1};
    video::IVideoDriver* driver = SceneManager->getVideoDriver();

    driver->setMaterial(m_Material);
    driver->setTransform(video::ETS_WORLD, AbsoluteTransformation);
    driver->drawVertexPrimitiveList(&m_Vertices[0], 4, &indices[0], 4, video::EVT_STANDARD, scene::EPT_TRIANGLES, video::EIT_16BIT);
}

const core::aabbox3d<f32>& Debug::getBoundingBox() const{
    return m_Box;
}

u32 Debug::getMaterialCount() const{
    return 1;
}

video::SMaterial& Debug::getMaterial(u32 i){
    return m_Material;
}

void Debug::update(){
    b2PolygonShape* t_polyShape = static_cast<b2PolygonShape*>(m_shape);

    int t_bodyPositionX = m_body->GetPosition().x;
    int t_bodyPositionY = m_body->GetPosition().y;

    int t_count = t_polyShape->GetVertexCount();
    //std::cout << "++++++++++++++++++" << std::endl;
    for(int i = 0; i < t_count; i++){
        b2Vec2 t_verts = t_polyShape->GetVertex(i);
        m_posVertex[i][0] = t_verts.x + t_bodyPositionX;
        m_posVertex[i][1] = t_verts.y + t_bodyPositionY;
        //std::cout << "(" << t_verts.x << "," << t_verts.y << ")\n";
    }
    
    for(int i = 0; i < 4; i++){
        m_Vertices[i] = video::S3DVertex(m_posVertex[i][0], m_posVertex[i][1],0, 0,0,0, m_color, 0, 0);
    }
}