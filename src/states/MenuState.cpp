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

#include "../include/states/MenuState.hpp"
#include "../include/states/InGameState.hpp"
#include "../include/Game.hpp"

//Constructor
MenuState::MenuState(Game* p_game) 
    : m_game(p_game){}

//Destructor
MenuState::~MenuState(){}

void MenuState::input(){

}

void MenuState::update(){

}

void MenuState::render(){

}

//Change to next state
void MenuState::nextState(){
    m_game->setState(new InGameState(m_game));
}