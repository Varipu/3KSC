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

#ifndef RAWR
#define RAWR

#include "Character.hpp"

class Rawr: public Character{
public:
	Rawr(char* p_name, float p_position[3], int p_joystick);
    ~Rawr();
    void    jump();
    void    basicAttack();
    void    specialAttackUp();
    void    specialAttackDown();
    void    specialAttackSide();
    void    ultimateAttack();
};

#endif