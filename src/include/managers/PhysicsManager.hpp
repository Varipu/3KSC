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

#ifndef PHYSICS_MANAGER
#define PHYSICS_MANAGER

class EngineManager;

#include "../entities/Entity.hpp"
#include "../entities/characters/Character.hpp"
#include "../managers/ContactManager.hpp"
#include <vector>
#include <Box2D.h>

class PhysicsManager{
private:
    static EngineManager*   m_engineManager;
    std::vector<b2Body*>    m_playersBody;

    b2Vec2*                 m_gravity;
    b2World*                m_world;

    int32                   m_velocityIterations;
    int32                   m_positionIterations;
    float32                 m_timeStep;

    ContactManager*         m_contactManager;

    short                   CATEGORY_PLAYER;
    short                   CATEGORY_ITEM;
    short                   CATEGORY_GROUND;

public:
    static PhysicsManager& instance();
    PhysicsManager();
    ~PhysicsManager();
    
    void                    update();
    
    void                    createPhysicBoxPlayer(int* p_id, float p_position[3], float p_dimX, float p_dimY);
    void                    setPlayerSensor(int p_id, Character* p_character);
    void                    createPhysicBoxObject(int* p_id, float p_position[3], float p_dimX, float p_dimY);
    void                    createPhysicBoxPlatform(int* p_id, float p_position[3]);
    void                    createPhysicBoxPortal(int* p_id, float p_position[3], float p_dimX, float p_dimY);
    void                    createPhysicBox(int* p_id, float p_position[3], float p_dimX, float p_dimY);

    void                    addForce();
    void                    removeForce();
    void                    updateGravity();

    float                   RaycastBetween(b2Vec2 p_p1, b2Vec2 p_p2);
    Character*              getClosestCharacter(b2Vec2 p_p1);
    float                   getDistanceToClosestCharacter(b2Vec2 p_p1);
    float                   getDistanceBetween(b2Vec2 p_p1, b2Vec2 p_p2);

    b2World*                getWorld();
    b2PolygonShape*         getShape(int p_id);
    b2Body*                 getBody(int p_id);
    void                    destroyBody(int p_id);
    int32                   getVelocityIterations();
    int32                   getPositionIterations();
    float32                 getTimeStep();

    ContactManager*         getContactManager();

    void                    applyImpulse(int p_idBody, int t_side);

    bool                    checkCollisionSimple(b2Body* p_body, bool p_stun);
    void                    checkCollisionMultiple(b2Body* p_body, b2Body* p_ignoreBody);

    bool                    fixtureCollide(b2Fixture& fixtureA, b2Fixture& fixtureB);

    void                    shockwaveBox(int p_idBody);
    void                    sparkyJump(int p_idBody);
    void                    fastGravity(int p_idBody);
    void                    machineGun(int p_idBody, bool p_orientation);
};

#endif