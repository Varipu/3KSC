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

#ifndef CHARACTER
#define CHARACTER

#include <irrlicht.h>

#include "Entity.hpp"

using namespace irr;

class Character : public Entity{
public:
    Character();
    ~Character();
	/*
    virtual void    jump();
	virtual void    basicAttack();
    virtual void    specialAttack(int p_index);
    virtual void    ultimateAttack();
    */

protected: 
	char*   m_name;
    int     m_life;
    int     m_damage;
    float   m_velocity;
    bool    m_orientation;
};

#endif