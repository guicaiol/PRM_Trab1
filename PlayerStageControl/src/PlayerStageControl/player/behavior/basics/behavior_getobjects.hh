/***
 * SCC0712 - Programação de Robôs Móveis
 * Universidade de São Paulo (USP) - São Carlos
 * Instituto de Ciências Matemáticas e de Computação (ICMC)
 * Autores: Guilherme Caixeta de Oliveira (gcaixetaoliveira@gmail.com) - nUSP 8504368
 *          Luiz Felipe Machado Votto     (luizvotto@gmail.com)        - nUSP 8504006
 *          Nuno Bernardes Barcellos      (nunobarcellos@gmail.com)    - nUSP 8955132
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

#ifndef BEHAVIOR_GETOBJECTS_HH
#define BEHAVIOR_GETOBJECTS_HH

#include <PlayerStageControl/player/behavior/behavior.hh>
#include <PlayerStageControl/player/device/blobfinder/blob.hh>

#include <vector>
#include <mutex>

class Behavior_GetObjects : public Behavior {
public:
    Behavior_GetObjects();

    void addScanPoint(const Position &point, float scanStart, float scanEnd);
    void setObjectsList(std::vector<Position> *list, std::mutex *mux) { _objList = list; _mux = mux; }
private:
    void run();

    // State machine
    int _state;
    enum {STATE_GOTO, STATE_SCAN};

    int _state2;
    enum {STATE_GET_GOTO, STATE_GET_CATCH, STATE_GET_RETRIEVE, STATE_GET_DROP, STATE_GET_GETAWAY};

    // States
    void state_goTo();
    void state_scan();

    // States
    void state_get_goTo();
    void state_get_catch();
    void state_get_retrieve();
    void state_get_drop();
    void state_get_getaway();

    // Points to follow
    std::vector<Position> _points;
    std::vector<std::pair<float,float> > _scans;
    unsigned _currScanIndex;

    // Objects list
    std::vector<Position> *_objList;
    // Mutex
    bool _hasCurrObject;
    std::mutex *_mux;
    Position _currObj;

    bool getNearestBlob(Blob *nearestBlob);
    Position getTransitionPos(Position pos);
    bool isInRoom(Position pos);
};

#endif // BEHAVIOR_GETOBJECTS_HH
