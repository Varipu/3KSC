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

#include <irrlicht.h>
using namespace irr;

class InputManager : public IEventReceiver{
    private:
    static InputManager* m_instance;
    int** m_bindings;
    bool m_keyIsDown[KEY_KEY_CODES_COUNT];

    public:
    static InputManager* instance();
    InputManager();
    ~InputManager();
    virtual bool OnEvent(const SEvent& p_event);
    virtual bool IsKeyDown(EKEY_CODE p_keyCode) const;
    void onKeyPressed(int p_key);
};

#endif