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
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

    You can contact Chaotic Games at: chaoticgamesdev@gmail.com
*********************************************************************************
*********************************************************************************/
#include "../include/AI/Pathfinding.hpp"
#include "../include/managers/PhysicsManager.hpp"

Pathfinding::Pathfinding(){}

Pathfinding::~Pathfinding(){}

void    Pathfinding::init(std::vector<Waypoint*> p_waypoints){
    m_waypoints = p_waypoints;
}

// Returns position of the closest waypoint connected to the waypoint we last standed in
b2Vec2  Pathfinding::findPath(b2Vec2 p_p1, b2Vec2 p_p2, Waypoint* p_lastWaypoint){
    PhysicsManager physicsManager = PhysicsManager::instance();
    float t_closestDistance = 0.0f;
    Waypoint *t_closestWaypoint;
    bool t_direction;

    // Set direction
    if(p_p1.x > p_p2.x){
        t_direction = 0; // Left
    }
    else{
        t_direction = 1; // Right
    }

    if(t_direction == 0){   // Direction is left
        for(int i=0; i<m_waypoints.size(); i++){
            if(p_lastWaypoint->isConnected(m_waypoints[i])){
                if(m_waypoints[i]->m_position[0] < p_p1.x){ // If waypoint is to the left
                    b2Vec2 t_p2 = b2Vec2(m_waypoints[i]->m_position[0], m_waypoints[i]->m_position[1]);
                    float t_distanceToWaypoint = physicsManager.getDistanceBetween(p_p1, t_p2);

                    // Find closest waypoint
                    if(t_closestDistance == 0){ // No waypoint is chosen. Choose this one
                        t_closestWaypoint = m_waypoints[i];
                        t_closestDistance = t_distanceToWaypoint;
                    }
                    else if(t_distanceToWaypoint < t_closestDistance){
                        t_closestWaypoint = m_waypoints[i];
                        t_closestDistance = t_distanceToWaypoint;
                    }
                }
            }
        }
    }
    else{                   // Direction is right
         for(int i=0; i<m_waypoints.size(); i++){
            if(p_lastWaypoint->isConnected(m_waypoints[i])){
                if(!(m_waypoints[i]->m_position[0] < p_p1.x)){ // If waypoint is to the right
                    b2Vec2 t_p2 = b2Vec2(m_waypoints[i]->m_position[0], m_waypoints[i]->m_position[1]);
                    float t_distanceToWaypoint = physicsManager.getDistanceBetween(p_p1, t_p2);

                    // Find closest waypoint
                    if(t_closestDistance == 0){ // No waypoint is chosen. Choose this one
                        t_closestWaypoint = m_waypoints[i];
                        t_closestDistance = t_distanceToWaypoint;
                    }
                    else if(t_distanceToWaypoint < t_closestDistance){
                        t_closestWaypoint = m_waypoints[i];
                        t_closestDistance = t_distanceToWaypoint;
                    }
                }
            }
        }
    }

    b2Vec2 t_return = b2Vec2(t_closestWaypoint->m_position[0], t_closestWaypoint->m_position[1]);
    return t_return;
}

// Returns position of the closest waypoint to a position (connected or disconnected)
b2Vec2 Pathfinding::getClosestWaypoint(b2Vec2 p_position, bool p_direction){
    PhysicsManager physicsManager = PhysicsManager::instance();
    float t_closestDistance = 0.0f;
    Waypoint *t_closestWaypoint;

    if(p_direction == 0){   // Direction is left
        for(int i=0; i<m_waypoints.size(); i++){
            
            if(m_waypoints[i]->m_position[0] < p_position.x){ // If waypoint is to the left
                b2Vec2 t_p2 = b2Vec2(m_waypoints[i]->m_position[0], m_waypoints[i]->m_position[1]);
                float t_distanceToWaypoint = physicsManager.getDistanceBetween(p_position, t_p2);

                // Find closest waypoint
                if(t_closestDistance == 0){ // No waypoint is chosen. Choose this one
                    t_closestWaypoint = m_waypoints[i];
                    t_closestDistance = t_distanceToWaypoint;
                }
                else if(t_distanceToWaypoint < t_closestDistance){
                    t_closestWaypoint = m_waypoints[i];
                    t_closestDistance = t_distanceToWaypoint;
                }
            }
        }
    }
    else{                   // Direction is right
         for(int i=0; i<m_waypoints.size(); i++){
            
            if(!(m_waypoints[i]->m_position[0] < p_position.x)){ // If waypoint is to the right
                b2Vec2 t_p2 = b2Vec2(m_waypoints[i]->m_position[0], m_waypoints[i]->m_position[1]);
                float t_distanceToWaypoint = physicsManager.getDistanceBetween(p_position, t_p2);

                // Find closest waypoint
                if(t_closestDistance == 0){ // No waypoint is chosen. Choose this one
                    t_closestWaypoint = m_waypoints[i];
                    t_closestDistance = t_distanceToWaypoint;
                }
                else if(t_distanceToWaypoint < t_closestDistance){
                    t_closestWaypoint = m_waypoints[i];
                    t_closestDistance = t_distanceToWaypoint;
                }
            }
        }
    }

    b2Vec2 t_return = b2Vec2(t_closestWaypoint->m_position[0], t_closestWaypoint->m_position[1]);
    return t_return;
}