/*
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
    along with this program.  If not, see http://www.gnu.org/licenses/.

    You can contact Chaotic Games at: chaoticgamesdev@gmail.com
*/

#ifndef ENGINE_MANAGER
#define ENGINE_MANAGER

#include "../ChaoticEngine/fachada/CEWindow.hpp"
#include "../ChaoticEngine/fachada/CEScene.hpp"
#include "../ChaoticEngine/fachada/CESceneCamera.hpp"
#include "../ChaoticEngine/fachada/CESceneLight.hpp"
#include "../ChaoticEngine/fachada/CESceneMesh.hpp"
#include "../ChaoticEngine/fachada/CEShader.hpp"

#include <vector>
#include "../entities/Entity.hpp"

class EngineManager{
private:
    std::vector<CESceneMesh*>   m_entityNodes;
    CEWindow*       m_window;
    CEScene*        m_scene;

    CESceneCamera*  m_cameraNode;

    unsigned int    m_nowTime;
    float           m_frameDeltaTime;

    float           m_resetPosition[6];
    float           m_cameraPosition[6];
    float           m_newCameraPosition[6];
    bool            m_moveCamera;
    float           m_amountTime;

    //Vectors for reading the vertex of the batllefields
    int                     m_totalVertex;
    std::vector<float>      m_VertexX;
    std::vector<float>      m_VertexY;
    std::vector<float>      m_VertexZ;

public:
    static EngineManager& instance();
    EngineManager();
    ~EngineManager();

    void                createWindow(bool p_fullscreen = true);
    bool                isWindowActive();
    bool                running();
    void                stop();

    float               updateFrameDeltaTime(float p_delta);

    void                createCamera(float p_cameraPosition[3], float p_tarjet[3]);
    void                moveCamera(float p_posX, float p_posY, float p_posZ);
    void                resetCamera();
    void                updateCamera();

    void                createLight(float p_lightPosition[3]);

    void                deleteEntity(int p_id);
    void                load3DModel(int p_id, float p_position[3], float p_scale[3], const char* p_modelURL);
    void                loadSkybox(const char* p_skyboxURLs[6]); 
    void                moveEntity(Entity* p_entity);
    void                setRotation(int p_id, float p_degrees);
    void                scale(int p_id, float p_scale[3]);
    
    void                drawScene();

    float               getFrameDeltaTime();
    CESceneMesh*        getEntityNode(int p_id);
    void                getEntityPosition(int p_id);

    void                parseOBJ(const char* p_filename);
    void                compareMaxAndMin(float p_value, float &p_max, float &p_min);
    void                pushVertex(float p_minX, float p_maxX, float p_minY, float p_maxY, float p_minZ, float p_maxZ);

    int                 getTotalVertex()    {    return m_totalVertex;  };
    std::vector<float>  getTotalVertexX()   {    return m_VertexX;      };
    std::vector<float>  getTotalVertexY()   {    return m_VertexY;      };
    std::vector<float>  getTotalVertexZ()   {    return m_VertexZ;      };

};

#endif