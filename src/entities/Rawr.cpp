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

#include "../headers/entities/Rawr.hpp"
#include "../headers/managers/PhysicsManager.hpp"

Rawr::Rawr(float p_position[3], char* p_name, int p_life, int p_damage, float p_velocity, bool p_orientation) : Character(p_position, p_name, p_life, p_damage, p_velocity, p_orientation){
    
}

Rawr::~Rawr(){}

void Rawr::jump(){

}

void Rawr::basicAttack(){
    if(m_orientation){   // Looking right
        // Attack 20 units to the right
        m_atackPosition[0] = m_position[0] + 20;
        m_atackPosition[1] = m_position[1];
        m_atackPosition[2] = 0;

        // Create attack instance
        Rawr* t_attack = new Rawr(m_atackPosition, "Attack", 100, 30, 20, true);

        // Check collision
        //if(physicsManager->instance()->checkCollision(m_node, m_node)){                  // Collision comprobation crashes when getting bounding box
        //  do damage
        //}

        // Destroy attack instance
        delete t_attack;
    }
    else{   // Looking left
        // Attack 20 units to the right
        m_atackPosition[0] = m_position[0] - 20;
        m_atackPosition[1] = m_position[1];
        m_atackPosition[2] = 0;

        // Create attack instance
        Rawr* t_attack = new Rawr(m_atackPosition, "Attack", 100, 30, 20, false);

        // Check collision
        //if(physicsManager->instance()->checkCollision(m_node, m_node)){                  // Collision comprobation crashes when getting bounding box
        //  do damage
        //}

        // Destroy attack instance
        delete t_attack;
    }
}

void Rawr::specialAttack(int p_index){

}

void Rawr::ultimateAttack(){

}