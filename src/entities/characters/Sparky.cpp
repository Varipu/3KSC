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

#include "../../include/entities/characters/Sparky.hpp"
#include "../../include/entities/Arena.hpp"
#include "../../include/extra/Actions.hpp"
#include "../../include/managers/SoundManager.hpp"
#include <iostream>

Sparky::Sparky(char* p_name, float p_position[3], bool p_debugMode)
    : Character(p_name, p_position, 100, 100, 30, 50.f, "assets/models/characters/plup/plup.obj", p_debugMode){
    m_type                  = 5;
    
    m_maxProjectiles        = 1;
    m_currentProjectiles    = 0;
    m_projectiles           = new Projectile*[m_maxProjectiles];

    m_soundManager->loadBank(SoundID::S_SPARKY);
    m_soundManager->createSoundEvent("event:/characters/sparky/death"     , "s_death"       );
    m_soundManager->createSoundEvent("event:/characters/sparky/kill"      , "s_kill"        );
    m_soundManager->createSoundEvent("event:/characters/sparky/random"    , "s_random"      );
    m_soundManager->createSoundEvent("event:/characters/sparky/special"   , "s_special"     );
    m_soundManager->createSoundEvent("event:/characters/sparky/taunt"     , "s_taunt"       );
    m_soundManager->createSoundEvent("event:/characters/sparky/ultimate"  , "s_ultimate"    );
}

Sparky::~Sparky(){}

void Sparky::moveSound(){
    float t_prob = ((float)rand() / (float)RAND_MAX);
    //std::cout << "RANDOM: " << t_prob << std::endl;
    m_soundManager->modifyParameter("s_random", t_prob, "Prob");
    m_soundManager->playSound("s_random");    
}

bool Sparky::jump(){
    return Character::jump();
}

bool Sparky::basicAttack(){
    //PENDING IMPLEMENTATION
    std::cout << "Basic Attack" << std::endl;
    
    return false;
}

bool Sparky::specialAttackUp(){
    //PENDING IMPLEMENTATION
    std::cout << "Special Attack Up" << std::endl;

    return false;
}

bool Sparky::specialAttackDown(){
    //PENDING IMPLEMENTATION
    std::cout << "Special Attack Down" << std::endl;
    
    return false;
}

bool Sparky::specialAttackSide(){
    //PENDING IMPLEMENTATION
    std::cout << "Special Attack Side" << std::endl;

    return false;
}


bool Sparky::ultimateAttack(){
    //PENDING IMPLEMENTATION
    std::cout << "ULTIMATE TIME!!!" << std::endl;

    return false;
}