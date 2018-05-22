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

#ifndef HUD_MANAGER
#define HUD_MANAGER

class Game;
class EngineManager;
class Arena;
class CESceneSprite;

struct PlayerHUD{
    CESceneSprite*  face;
    CESceneSprite*  bg;
    CESceneSprite*  hp;
    CESceneSprite*  mp;
    CESceneSprite*  up;
    CESceneSprite*  lives;

    ~PlayerHUD();
};

class HUDManager{
    private:
        Game*           m_game;
        EngineManager*  m_engineManager;
        Arena*          m_arena;

        PlayerHUD*      m_playerHUDs[2];
        CESceneSprite*  m_ultimateBG;
        CESceneSprite*  m_ultimateFG;

        HUDManager();
        
        void initializePlayer(int p_index);
        void initializeUB();

    public:
        static HUDManager& instance();
        ~HUDManager();

        void setHP(int p_player, int p_HP, int p_maxHP);
        void setMP(int p_player, int p_MP, int p_maxMP);
        void setLives(int p_player, int p_lives);

        void update();
        void render();
};

#endif