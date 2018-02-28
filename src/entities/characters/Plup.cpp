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

#include "../../include/entities/characters/Plup.hpp"
#include "../../include/entities/Snowman.hpp"
#include "../../include/entities/Arena.hpp"
#include "../../include/extra/Actions.hpp"
//#include "../../include/managers/SoundManager.hpp"
#include <iostream>

Plup::Plup(char* p_name, float p_position[3], bool p_debugMode) : Character(p_name, p_position, 100, 100, 12, 80.f, "assets/models/characters/plup/plup.obj", p_debugMode
    ){
    m_maxProjectiles        = 1;
    m_currentProjectiles    = 0;
    m_projectiles           = new Projectile*[m_maxProjectiles];

    m_maxSnowmen        = 1;
    m_currentSnowmen    = 0;
    m_snowmen           = new Snowman*[m_maxSnowmen];
}

Plup::~Plup(){}

bool Plup::jump(){
    return Character::jump();
}

//Slap
bool Plup::basicAttack(){
    std::cout << m_name << ": Slap!" << std::endl;
    Character* t_currentPlayer;

    for (int i = 0; i < m_playerCount; i++){
        //Ignore myself
        if (i == m_playerIndex)
            continue;

        t_currentPlayer = Arena::getInstance()->getPlayer(i);

        //Looking at the rival
        if ((m_orientation && t_currentPlayer->getX() >= m_position[0]) ||
        (!m_orientation && t_currentPlayer->getX() <= m_position[0])){
            //Rival close enough
            if (checkCloseness(t_currentPlayer->getPosition(), 15)){
                t_currentPlayer->receiveAttack(m_damage/2, true);
            }
        }
    }
    
    return false;
}

//Range attack
bool Plup::specialAttackUp(){
    std::cout << m_name << ": Range attack" << std::endl;
    Character* t_currentPlayer;

    for (int i = 0; i < m_playerCount; i++){
        //Ignore myself
        if (i == m_playerIndex)
            continue;

        t_currentPlayer = Arena::getInstance()->getPlayer(i);

        //Rival close enough
        if (checkCloseness(t_currentPlayer->getPosition(), 35)){
            t_currentPlayer->receiveAttack(m_damage, true);
        }
    }

    return false;
}

//Snowman
bool Plup::specialAttackDown(){
    if (m_currentSnowmen < m_maxSnowmen){
        //Looking right
        if (m_orientation){
            // Place snowman 10 units to the right
            m_attackPosition[0] = m_position[0] + 10;
            m_attackPosition[1] = m_position[1];
            m_attackPosition[2] = m_position[2];
        }

        //Looking left 
        else{
            // Place snowman 10 units to the left
            m_attackPosition[0] = m_position[0] - 10;
            m_attackPosition[1] = m_position[1];
            m_attackPosition[2] = m_position[2];
        }

        //Create snowman and increase snowmen count
        m_snowmen[m_currentSnowmen++] = new Snowman(m_attackPosition, m_playerIndex);
        std::cout << m_name << ": Snowman" << std::endl;
    }

    //Snowmen AI
    for (int i = 0; i < m_currentSnowmen; i++){
        if (!m_snowmen[i]->lockNLoad()){
            delete m_snowmen[i];
            m_currentSnowmen--;
            return false;
        }
    }

    return true;
}

bool Plup::specialAttackSide(){
    //PENDING IMPLEMENTATION
    std::cout << m_name << ": Special Attack Side" << std::endl;

    return false;
}


bool Plup::ultimateAttack(){
    //PENDING IMPLEMENTATION
    std::cout << m_name << ": ULTIMATE TIME!!!" << std::endl;

    return false;
}

int Plup::getCurrentSnowmen(){
    return m_currentSnowmen;
}