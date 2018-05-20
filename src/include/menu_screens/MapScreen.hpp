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

#ifndef MAP_SCREEN
#define MAP_SCREEN

class Game;
class EngineManager;

#include "MenuScreen.hpp"

class MapScreen : public MenuScreen{
    private:
        MapScreen(MenuState* p_menu);

        static MapScreen*   m_instance;
        Game*               m_game;
        EngineManager*      m_engineManager;

    public:
        static MapScreen* instance();
        ~MapScreen();

        void update()   override;

        void select()   override;
        void save()     override;
};

#endif