/***
 * SCC0712 - Programação de Robôs Móveis
 * Universidade de São Paulo (USP) - São Carlos
 * Instituto de Ciências Matemáticas e de Computação (ICMC)
 * Autor: Guilherme Caixeta de Oliveira (gcaixetaoliveira@gmail.com) - nUSP 8504368
 *
 * This file is part of PlayerStageControl project.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 ***/

#ifndef BEHAVIOR_TEST_HH
#define BEHAVIOR_TEST_HH

#include <PlayerStageControl/player/behavior/behavior.hh>
#include <PlayerStageControl/player/device/blobfinder/blob.hh>

class Behavior_PlayerGripper : public Behavior {
public:
    Behavior_PlayerGripper();
private:
    void run();

    // State machine
    int _state;
    enum {STATE_SEARCH, STATE_GOTO, STATE_CATCH, STATE_RETRIEVE, STATE_DROP, STATE_GETAWAY};

    // States
    void state_search();
    void state_goTo();
    void state_catch();
    void state_retrieve();
    void state_drop();
    void state_getaway();

    // Internal
    bool getNearestBlob(Blob *nearestBlob);
};

#endif // BEHAVIOR_TEST_HH
