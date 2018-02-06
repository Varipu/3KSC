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

#ifndef INPUT_MANAGER
#define INPUT_MANAGER

#include "../entities/Character.hpp"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Joystick.hpp>
#include <SFML/System/Clock.hpp>

class InputManager{
    public:
        static InputManager* instance();
        InputManager();
        ~InputManager();
        void    onKeyPressed(int p_key);
        bool    isKeyPressed(int p_key);
        bool    isConnected(int p_joystick);
        bool    isButtonPressed(int p_joystick, int p_button);
        float   getAxisPosition(int p_joystick, int p_axis);
        void    updateJoysticks();
        void    assignDevice(int p_device, int p_player, bool p_inGame = false);
        void    updateInputs(int p_player);
    
    private:
        static InputManager*    m_instance;
        int**                   m_bindings;   
        sf::Keyboard::Key       m_keys[101];
        sf::Joystick::Axis      m_axis[8];

        //Input device for each player [0-3]: Joysticks, -1: Keyboard, -2: NPC
        int*    m_inputDevices;

        //Conditions for each Input (they change depending on keyboard/joystick control)
        bool*   m_upInput;
        bool*   m_downInput;
        bool*   m_leftInput;
        bool*   m_rightInput;
        bool*   m_jumpInput;
        bool*   m_runInput;
        bool*   m_blockInput;
        bool*   m_pickInput;
        bool*   m_basicAttackInput;
        bool*   m_specialAttackUpInput;
        bool*   m_specialAttackDownInput;
        bool*   m_specialAttackSideInput;
        bool*   m_ultimateAttackInput;
        bool*   m_waitRelease;
};

#endif