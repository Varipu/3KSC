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

#include "../include/menu_screens/BattleSettingsScreen.hpp"
#include "../include/Game.hpp"

//Instance initialization
BattleSettingsScreen* BattleSettingsScreen::m_instance = nullptr;

//Returns the only instance of this class
BattleSettingsScreen* BattleSettingsScreen::instance(){
    if (!m_instance){
        m_instance = new BattleSettingsScreen(MenuState::getInstance());
    }

    return m_instance;
}

//Constructor
BattleSettingsScreen::BattleSettingsScreen(MenuState* p_menu)
    : MenuScreen(p_menu){    
    m_game              = Game::getInstance();

    createFromFile("assets/UI/menu_screens/BattleSettings.cgs");
    m_selector->setAbsolutePosition(483, m_selectedNode->element->getPosition().y, 0);
}

//Destructor
BattleSettingsScreen::~BattleSettingsScreen(){
    std::cout << "~BattleSettingsScreen" << std::endl;
}










/* ****************************** ACTIONS ****************************** */
void BattleSettingsScreen::select(){
    save();
}