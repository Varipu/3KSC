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

#include "../include/menu_screens/CharacterOnlineScreen.hpp"
#include "../include/Game.hpp"
#include <iostream>


//Returns the only instance of this class
CharacterOnlineScreen& CharacterOnlineScreen::instance(){
    static CharacterOnlineScreen instance(MenuState::getInstance());
    return instance;
}

//Constructor
CharacterOnlineScreen::CharacterOnlineScreen(MenuState* p_menu)
    : MenuScreen(p_menu){
    
    m_game              = Game::getInstance();
}

//Destructor
CharacterOnlineScreen::~CharacterOnlineScreen(){
    std::cout << "~CharacterOnlineScreen" << std::endl;
}


//Handles the user inputs for the screen
void CharacterOnlineScreen::input(){
    MenuScreen::input();
}

//Updates the state of the screen
void CharacterOnlineScreen::update(){
    MenuScreen::update();
}

//Draws to the screen
void CharacterOnlineScreen::render(){
    
}









/* ****************************** ACTIONS ****************************** */
void CharacterOnlineScreen::select(){
    save();
}