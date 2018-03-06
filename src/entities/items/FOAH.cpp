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

#include "../../include/entities/items/FOAH.hpp"
#include "../../include/managers/PhysicsManager.hpp"
#include "../../include/entities/Arena.hpp"
#include <iostream>

//Constructor
FOAH::FOAH(float p_position[3])
    : Item(p_position, "assets/models/items/life_tank.obj"){
    m_physicsManager    = &PhysicsManager::instance();
    m_arena             = Arena::getInstance();
}

//Destructor
FOAH::~FOAH(){
    delete m_physicsManager;
    delete m_arena;
}

//Enemies beware
void FOAH::use(){
    std::cout << m_arena->getPlayer(m_owner)->getName() <<" got a F.O.A.H." << std::endl
    << std::endl;
}

//Sets the owner of the item
void FOAH::setOwner(int p_owner){
    m_owner = p_owner;
}