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


#include "../../include/entities/characters/Character.hpp"
#include "../../include/managers/EngineManager.hpp"
#include "../../include/managers/InputManager.hpp"
#include "../../include/managers/PhysicsManager.hpp"
#include "../../include/managers/SoundManager.hpp"
#include "../../include/managers/UIManager.hpp"
#include "../../include/entities/Arena.hpp"
#include "../../include/extra/Actions.hpp"
#include "../../include/debug.hpp"

#include <iostream>

struct ActionMapping{
    Action  action;                     //Action to map
    bool    (Character::*function)();   //Function for the action
    bool    onlyOnce;                   //Wait for input release?
    bool    enabled;                    //Enabled or not
};

//Static members
int Character::m_playerCount = 0;

// UIManager*      m_UIManager         = &UIManager::instance();
Arena*          m_arena             = 0;

Character::Character(char* p_name, float p_position[3], int p_HP, int p_MP, int p_damage, float p_velocity, const char* p_modelURL, bool p_debugMode, bool p_online) : Entity(p_position, 5.f, p_modelURL){
    m_soundManager          = &SoundManager::instance();
    m_arena                 = Arena::getInstance();
    m_client                = &Client::instance();
    m_name                  = p_name;
    m_lives                 = 3;
    m_HP                    = m_maxHP = p_HP;
    m_MP                    = m_maxMP = p_MP;
    m_damage                = p_damage;
    m_velocity              = p_velocity;
    m_stunned               = false;  
    m_blocking              = false;
    m_shielded              = false;
    m_winged                = false;    
    m_alive                 = true;
    m_respawning            = false;
    m_knockback             = false;
    m_dashing               = false;
    m_onGround              = false;
    m_ultimateCharged       = false;
    m_runningFactor         = 1.0f;
    m_orientation           = 1;

    m_knockbackDuration     = 0.25;
    m_knockbackTime         = 0;
    m_dashDuration          = 0.5;
    m_dashTime              = 0;
    m_stunDuration          = 1.0;
    m_stunTime              = 0;
    m_wingsDuration         = 10.0;
    m_wingsTime             = 0;
    m_shieldDuration        = 5.0;
    m_shieldTime            = 0;

    m_online                = p_online;
    
    mapActions();
    createJumpTable();
    setRespawnPosition(m_arena->getRespawnPosition());

    m_waitRelease           = false;
    m_keepWaiting           = false;

    m_playerIndex = Character::m_playerCount++;

    switch(m_playerIndex){
        case 0:
            lookRight();
            break;
        case 1:
            lookLeft();
            break;
    }
   
    m_debugMode = p_debugMode;
    m_physicsManager->setPlayerSensor(getId(), this);
    m_validation = 123;
}

Character::~Character(){}

void Character::createJumpTable(){
    m_maxJumps          = 2;
    m_jumping           = false;
    m_jumpCurrentTime   = 0;
    m_jumpMaxTime       = 10;
    m_jumpTable[0]      = 3.0f;
    m_jumpTable[1]      = 2.4f;
    m_jumpTable[2]      = 1.9f;
    m_jumpTable[3]      = 1.6f;
    m_jumpTable[4]      = 1.25f;
    m_jumpTable[5]      = 0.95;
    m_jumpTable[6]      = 0.75;
    m_jumpTable[7]      = 0.55;
    m_jumpTable[8]      = 0.35;
    m_jumpTable[9]      = 0.15;
}

void Character::setRespawnPosition(float p_respawnPosition[3]){
    for(int i = 0; i < 3; i++){
        m_respawnPosition[i] = p_respawnPosition[i];
    }
}

//Initializes actions mapping for this player
void Character::mapActions(){
    m_actions = new ActionMapping[(int) Action::Count + 1];
                      //Action                    //Function                      //onlyOnce  //Enabled
    m_actions[0]    = {Action::Left               , &Character::left              , false     , false};
    m_actions[1]    = {Action::Right              , &Character::right             , false     , false};
    m_actions[2]    = {Action::Jump               , &Character::jump              , true      , false};
    m_actions[3]    = {Action::Run                , &Character::run               , false     , false};
    m_actions[4]    = {Action::Block              , &Character::block             , false     , false};
    m_actions[5]    = {Action::Pick               , &Character::pick              , true      , false};
    m_actions[6]    = {Action::BasicAttack        , &Character::basicAttack       , true      , false};
    m_actions[7]    = {Action::SpecialAttackUp    , &Character::specialAttackUp   , true      , false};
    m_actions[8]    = {Action::SpecialAttackDown  , &Character::specialAttackDown , true      , false};
    m_actions[9]    = {Action::SpecialAttackSide  , &Character::specialAttackSide , true      , false};
    m_actions[10]   = {Action::UltimateAttack     , &Character::ultimateAttack    , true      , false};
    m_actions[11]   = {Action::Count              , 0                             , false     , false};
}

//Receives an attack from other player
//Parameters: damage, can you block it?
void Character::receiveAttack(int p_damage, bool p_block, int p_knockback, bool p_checked){
    std::cout<<"character11111"<<std::endl;
    if(m_online && !p_checked){
        if(m_client->getPlayer() == m_playerIndex){
            m_client->attacked(p_damage, p_block, p_knockback);
        }
        else return;  //ignorar ataques que no sean de tu jugador
    }

    std::cout<<"character ataque"<<std::endl;
    if((p_block && m_actions[(int) Action::Block].enabled) || m_shielded){
        changeHP(-p_damage/2);
        //std::cout << m_name << " blocked an attack and now has " << m_HP << " HP." << std::endl << std::endl;
    }else{
        changeHP(-p_damage);
        //std::cout << m_name << " took an attack and now has " << m_HP << " HP." << std::endl << std::endl;
    }

    if(p_knockback == 2) //knockback sin direccion
        setKnockback();
    else if(p_knockback != 0)
        knockback(p_knockback);
}

//Increases or decreases life
void Character::changeHP(int p_variation){
    m_HP += p_variation;

    if (m_HP <= 0)
        die();
    else if(m_HP > m_maxHP)
        m_HP = m_maxHP;

    //HUD Stuff
    // m_UIManager->setHP(m_playerIndex, m_HP);
}

//Increases or decreases magic
void Character::addMP(int p_variation){
    m_MP += p_variation;

    if(m_MP > m_maxMP)
        m_MP = m_maxMP;

    //HUD Stuff
    // m_UIManager->setMP(m_playerIndex, m_MP);
}

//Check if we can do an action. If we can, substract the MP and return true, if not, return false.
bool Character::useMP(int p_MP){
    //We have enough MP for doing the action
    if(m_MP >= p_MP){
        m_MP -= p_MP;
        return true;
    }

    return false;
}

//Activates shield
void Character::shield(){
    m_shielded = true;
    m_shieldTime = m_inputManager->getMasterClock() + m_shieldDuration;
}

//Activates wings, if not already active
void Character::wings(){
    if(!m_winged){
        m_velocity *= 1.5;
        m_winged = true;
    }

    m_wingsTime = m_inputManager->getMasterClock() + m_wingsDuration;
}

void Character::removeWings(){
    if(!m_winged){
        m_velocity /= 1.5;
        m_winged = false;
    }
}

//Decreases number of lives
void Character::die(){
    m_lives--;
    //std::cout << "Me quedan " << m_lives << " vidas." << std::endl;
    m_HP = 0;
    //m_alive = false;
    m_knockback = false;
    m_stunned   = false;
    m_shielded = false;

    removeWings();

    if(m_lives >= 0)
        respawn();
    else
        m_arena->pleaseKill(m_playerIndex);

    //HUD Stuff
    //Delete when m_lives == 0
}

void Character::lookLeft(){
    m_orientation = -1;
    this->rotate(0);
}

void Character::lookRight(){
    m_orientation = 1;
    this->rotate(180);
}

bool Character::isJumping(){
    return m_actions[(int) Action::Jump].enabled;
}

//Calls action functions when they are active
void Character::doActions(){
    ActionMapping* t_iterator = m_actions;

    while(t_iterator->function){
        //We call the function, it'll return false when action finishes
        if(t_iterator->enabled)
            t_iterator->enabled = (this->*(t_iterator->function))();
        
        ++t_iterator;
    }
}

void Character::input(){
    m_inputManager->updateActions(m_playerIndex);
    
    //For movement
    m_frameDeltaTime = m_engineManager->getFrameDeltaTime();

    //Block
    m_actions[(int) Action::Block].enabled = m_inputManager->checkAction(Action::Block, m_playerIndex);

    //Input blocked if stunned, blocking or dead
    if(!m_stunned && !m_actions[(int) Action::Block].enabled && m_alive){
        ActionMapping* t_iterator   = m_actions;
        
        //Loop through actions to enable them
        while(t_iterator->function){    
            if (t_iterator->onlyOnce){
                if (m_inputManager->checkAction(t_iterator->action, m_playerIndex)){
                    m_keepWaiting = true;

                    if (!m_waitRelease){
                        t_iterator->enabled = true;
                        m_waitRelease = true;
                    }
                }                
            }

            else{
                t_iterator->enabled = m_inputManager->checkAction(t_iterator->action, m_playerIndex);
            }
            m_inputManager->setAction(t_iterator->action, m_playerIndex, false);
            ++t_iterator;
        }

        m_waitRelease = m_keepWaiting;
        m_keepWaiting = false;
    }    
}

//Update state of player
void Character::update(){
    //Specific update for each character
    updatePlayer();
    float t_currentTime = m_inputManager->getMasterClock();

    if(m_winged && t_currentTime >= m_wingsTime)
        removeWings();

    if(m_shielded && t_currentTime >= m_shieldTime)
        m_shielded = false;
    
    if(m_stunned && t_currentTime > m_stunTime){
        m_stunDuration = 1.0;
        m_stunned      = false;
    }else
        doActions();

    if(m_knockback && t_currentTime >= m_knockbackTime)
        m_knockback = false;

    if(!m_respawning)
        updatePosition(m_actions[(int) Action::Jump].enabled, m_knockback, m_dashing);
    else{
        updatePosition(true, m_knockback, m_dashing);
        m_respawning = false;
    }
    
    if(m_debugMode)
        m_playerDebug->update();

    //Increase magic every second and with attacks
    if(getY() < -250 || getY() > 250 || getX() < -250 || getX() > 250)
        die();
}

//Returns the type of the player
int Character::getType(){
    return m_type;
}

//Returns if the player is an NPC
bool Character::isNPC(){
    return m_inputManager->getInputDevice(m_playerIndex) == -2;
}

//Returns the damage of the player
int Character::getDamage(){
    return m_damage;
}

//Returns the index of the player
int Character::getIndex(){
    return m_playerIndex;
}

//Returns the name of the player
char* Character::getName(){
    return m_name;
}

//Returns the HP of the player
int Character::getHP(){
    return m_HP;
}

//Returns the mp of the player
int Character::getMP(){
    return m_MP;
}

int Character::getOrientation(){
    return m_orientation;
}

void Character::setStunned(float p_time){
    if(p_time != 0)
        m_stunDuration = p_time;
    else
        m_stunDuration = m_stunDuration/2;
    
    m_stunned = true;
    m_stunTime = m_inputManager->getMasterClock() + m_stunDuration;
}

void Character::modeDebug(){
    if(m_debugMode){
        m_playerDebug = new Debug(666, m_physicsManager->getBody(getId()));
    }
}

void Character::respawn(){
    m_respawning = true;
    m_HP = m_maxHP;
    m_MP = m_maxMP;

    moveTo(m_respawnPosition);
    //m_UIManager->setHP(m_playerIndex, m_HP);
    //m_UIManafer->setMP(m_playerIndex, m_MP);
}

void Character::onTouchGround(){
    m_onGround = true;
    m_maxJumps = 2;
}

void Character::onLeaveGround(){
    m_onGround = false;
    m_maxJumps = 1;
}

void Character::setUltimateCharged(){
    m_ultimateCharged = true;
}

//ACTIONS
bool Character::moveToPath(float p_position[2]){
    m_flagAIJump = !m_flagAIJump;
    // Move
    if(p_position[0] > this->getX())
        this->right();
    else
        this->left();

    // Jump if enemy is above
    if(p_position[1] > (this->getY() + 15.0f)){
        if(m_flagAIJump)
            m_inputManager->setAction(Action::Jump, m_playerIndex);
    }

    return false;
}

bool Character::left(){
    moveX(m_velocity * m_frameDeltaTime * m_runningFactor * -1);
    lookLeft();
    m_runningFactor = 1.0f;

    return false;
}

bool Character::right(){
    moveX(m_velocity * m_frameDeltaTime * m_runningFactor);
    lookRight();
    m_runningFactor = 1.0f;

    return false;
}

bool Character::jump(){
    // Start or continue jump movement
    if(m_jumpCurrentTime < m_jumpMaxTime && m_maxJumps > 0){
        moveY(m_jumpTable[m_jumpCurrentTime++]*3.0f);
    }
    // Jump has ended. Starting to go down
    else{
        // If there is collision
        m_maxJumps--;
        m_jumpCurrentTime = 0;
        return false; // We are on the floor. Reset jump
    }

    return true;
}

bool Character::run(){
    if(m_winged)
        m_runningFactor = 1.5f;
    else
        m_runningFactor = 2.0f;
    
    return false;
}

bool Character::block(){
    m_actions[(int) Action::Block].enabled = true;

    return false;
}

bool Character::pick(){
    m_arena->catchItem(m_playerIndex, m_position);
    
    return false;
}

bool Character::basicAttack(){}

bool Character::specialAttackUp(){}

bool Character::specialAttackDown(){}

bool Character::specialAttackSide(){}

bool Character::ultimateAttack(){}

void Character::setKnockback(){
    m_knockbackTime = m_inputManager->getMasterClock() + m_knockbackDuration;
    m_knockback = true;
}

void Character::knockback(int p_orientation){
    if(!m_knockback){
        setKnockback();
        m_physicsManager->applyImpulse(getId(), p_orientation);
    }
}

int  Character::getCurrentSnowmen(){}

void Character::onPortal(){}

void Character::leavePortal(){}

int Character::getValidation(){
    return m_validation;
}