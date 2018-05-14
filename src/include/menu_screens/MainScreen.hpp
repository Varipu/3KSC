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

#ifndef MAIN_SCREEN
#define MAIN_SCREEN

#include "MenuScreen.hpp"

class MainScreen : public MenuScreen{
    private:
        MainScreen(MenuState* p_menu);
        
        MenuNode*       m_playLocalNode;
        MenuNode*       m_playOnlineNode;
        MenuNode*       m_quitNode;

        sf::Sprite*     m_title;
        sf::Sprite*     m_settings;
        sf::Sprite*     m_playLocal;
        sf::Sprite*     m_playOnline;
        sf::Sprite*     m_quit;

        void clipElements()         override;
        void setElementsOrigins()   override;
        void placeElements()        override;
        void initializeNodes()      override;

    public:
        static MainScreen& instance();
        ~MainScreen();

        void render()               override;
};

#endif