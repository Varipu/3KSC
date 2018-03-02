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

#ifndef SOUND_MANAGER
#define SOUND_MANAGER

#include <fmod/fmod.hpp>
#include <fmod/fmod_studio.hpp>
#include <fmod/fmod_common.h>
#include <fmod/fmod_errors.h>
#include <string>
#include <map>

using namespace std;

struct Vector3 {
	float x;
	float y;
	float z;
};

class SoundEvent;

class SoundManager{
public:
    static SoundManager& instance();
    SoundManager();
    ~SoundManager();

    void createSoundEvent(const char* eventPath, const char* name);
    void playSound(const char* name);


    void setVolume(float p_vol);
    void update(bool p_paused);

    void loadBanks();
    void getEvents();
    void modifyParameter(const char* name, float num, const char* parameter);

private:
    FMOD_RESULT               m_Result;
    FMOD::Studio::System     *m_system;
    FMOD::System             *m_lowLevelSystem;
    
    FMOD::Studio::Bank*       m_masterBank;
    FMOD::Studio::Bank*       m_stringsBank;
    FMOD::Studio::Bank*       m_musicBank;

    //FMOD::Studio::EventDescription*     m_musicEvent;

    std::map<const char*, SoundEvent*> m_soundEvents;
};

class SoundEvent{
public:
    SoundEvent(FMOD::Studio::EventDescription* p_eventDescription);
    ~SoundEvent();

    void start();
    void stop();
    void pause();
    void setVolume(float p_vol);
    bool isPlaying();

    void modifyParameter(float num, const char* parameter);


protected:
    FMOD::Studio::EventInstance*    m_soundInstance;
};

#endif