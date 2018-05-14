/*
    3KSC: A fighting game
    Copyright (C);

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

#ifndef ONLINE_MODE_SCREEN
#define ONLINE_MODE_SCREEN

#include "MenuScreen.hpp"

class OnlineModeScreen : public MenuScreen{
    private:
        OnlineModeScreen(MenuState* p_menu);
        
        MenuNode*   m_createNode;
        MenuNode*   m_joinNode;

        sf::Sprite* m_create;
        sf::Sprite* m_join;

        void clipElements()         override;
        void setElementsOrigins()   override;
        void placeElements()        override;
        void initializeNodes()      override;

    public:
        static OnlineModeScreen& instance();
        ~OnlineModeScreen();

        void render()               override;
};

#endif