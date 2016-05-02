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

#include "behavior_getobjects.hh"
#include <PlayerStageControl/player/player.hh>
#include <PlayerStageControl/player/device/devices.hh>

Behavior_GetObjects::Behavior_GetObjects() {
    _state = STATE_GOTO;
    _state2 = STATE_GET_GOTO;

    _hasCurrObject = false;
    _currScanIndex = 0;
}

void Behavior_GetObjects::addScanPoint(const Position &point, float scanStart, float scanEnd) {
    _points.push_back(point);
    _scans.push_back(std::make_pair(scanStart, scanEnd));
}

void Behavior_GetObjects::run() {

    // Get objects
    _mux->lock();
    if(_hasCurrObject || (_objList->empty()==false && player()->gripper()->isAvailable())) {

        if(_hasCurrObject==false) {
            // Get object from list
            _currObj = _objList->at(0);
            _objList->erase(_objList->begin());
            _hasCurrObject = true;

        } else {

            _state = STATE_GOTO;

            // Switch state machine
            switch(_state2) {
                case STATE_GET_GOTO: {
                    state_get_goTo();
                } break;

                case STATE_GET_CATCH: {
                    state_get_catch();
                } break;

                case STATE_GET_RETRIEVE: {
                    state_get_retrieve();
                } break;

                case STATE_GET_DROP: {
                    state_get_drop();
                } break;

                case STATE_GET_GETAWAY: {
                    state_get_getaway();
                } break;

                default:
                    player()->idle();
                break;
            }
        }


    // Scan
    } else {

        // Switch state machine
        switch(_state) {
            case STATE_GOTO: {
                state_goTo();
            } break;

            case STATE_SCAN: {
                state_scan();
            } break;

            default:
                player()->idle();
            break;
        }

    }
    _mux->unlock();
}

void Behavior_GetObjects::state_goTo() {
    // Get position
    Position desiredPosition = _points.at(_currScanIndex);

    Position posToGo = desiredPosition;
    if(isInRoom(desiredPosition)) {
        if(isInRoom(player()->position())){
            if(isSamePoint(getTransitionPoint(player()->position()),getTransitionPoint(desiredPosition))){
                posToGo = desiredPosition;
            }
            else{
                posToGo = getTransitionPoint(player()->position());
            }
        }
        else{
            posToGo = getTransitionPoint(desiredPosition);
        }
    }
    else{
        if(isInRoom(player()->position())){
            posToGo = getTransitionPoint(player()->position());
        }
        else{
            posToGo = desiredPosition;
        }
    }

    if(Utils::distance(player()->position(), posToGo) < 1.0) {
        posToGo = desiredPosition;
    }

    // Go to
    player()->goTo(posToGo, true);

    // Check at position
    if(player()->isAtPosition(posToGo)) {
        const float scanStart = _scans.at(_currScanIndex).first;

        // Check at scan start
        player()->lookTo(scanStart);
        if(player()->isLookingTo(scanStart)) {
            player()->idle();

            _state = STATE_SCAN;
        }
    }
}

void Behavior_GetObjects::state_scan() {
    float scanSpeed = 1.0;

    // Check scan end
    float scanEnd = _scans.at(_currScanIndex).second;
    if(player()->isLookingTo(scanEnd)) {
        player()->idle();

        _currScanIndex++;
        if(_currScanIndex >= _points.size())
            _currScanIndex = 0;
        _state = STATE_GOTO;

    } else {
        // Rotate scan
        player()->setSpeed(0.0, 0.0, scanSpeed);

        // Check blob finder
        int numBlobs = player()->blobFinder()->getNumBlobs();
        if(numBlobs > 0) {

            std::vector<Blob> greenBlobs;

            // Get green blobs
            for(int i=0; i<numBlobs; i++) {
                Blob blob = player()->blobFinder()->getBlob(i);
                if(blob.getColor()==Colors::GREEN)
                    greenBlobs.push_back(blob);
            }

            // Check if has green blobs
            if(greenBlobs.empty())
                return;

            // Choose first blob at right
            Blob chosenBlob;
            bool hasChosenBlob = false;
            for(unsigned i=0; i<greenBlobs.size(); i++) {
                Blob greenBlob = greenBlobs.at(i);

                if(greenBlob.getCentroid().x() >= 40)
                    continue;

                if(hasChosenBlob) {
                    if(greenBlob.getCentroid().x() > chosenBlob.getCentroid().x())
                        chosenBlob = greenBlob;
                } else {
                    chosenBlob = greenBlob;
                    hasChosenBlob = true;
                }
            }

            // Look to blob
            if(hasChosenBlob) {
                player()->lookToBlob(chosenBlob);
                if(player()->isLookingToBlob(chosenBlob)) {
                    player()->setSpeed(0.0, 0.0, scanSpeed/2);

                    const float x = player()->position().x() + chosenBlob.getRange()*cos(player()->orientation());
                    const float y = player()->position().y() + chosenBlob.getRange()*sin(player()->orientation());

                    // Add to list
                    Position pos(x,y);
                    bool alreadyInList = false;
                    for(unsigned int i=0; i<_objList->size(); i++) {
                        if(Utils::distance((pos), _objList->at(i)) <= 1.0) {
                            alreadyInList = true;
                            break;
                        }
                    }
                    if(alreadyInList==false) {
                        _objList->push_back(pos);
                    }
                }
            }
        }

    }

}

void Behavior_GetObjects::state_get_goTo() {

    Position posToGo = _currObj;
    if(isInRoom(_currObj)) {
        if(isInRoom(player()->position())){
            if(isSamePoint(getTransitionPoint(player()->position()),getTransitionPoint(_currObj))){
                posToGo = _currObj;
            }
            else{
                posToGo = getTransitionPoint(player()->position());
            }
        }
        else{
            posToGo = getTransitionPoint(_currObj);
        }
    }
    else{
        if(isInRoom(player()->position())){
            posToGo = getTransitionPoint(player()->position());
        }
        else{
            posToGo = _currObj;
        }
    }

    if(Utils::distance(player()->position(), posToGo) < 1.0) {
        posToGo = _currObj;
    }

    // Go to blob position
    player()->goTo(posToGo, true);

    // Check if it's seeing the blob
    if(Utils::distance(player()->position(), posToGo) < 2.0) {

//        if(Utils::distance(player()->position(), posToGo) < 2.6) {
            player()->setCheckStall(false);
//        }

        Blob nearestBlob;
        bool hasNearestBlob = getNearestBlob(&nearestBlob);
        if(hasNearestBlob) {
            // Go to nearest blob
            bool goToBlob = player()->goToBlob(nearestBlob);
            if(goToBlob)
                _state2 = STATE_GET_CATCH;
        } else {
            // Check if was a false alarm (no blob)
            if(player()->isAtPosition(posToGo)) {
                _hasCurrObject = false;
                _state2 = STATE_GET_GOTO;
            }
        }
    }

}

void Behavior_GetObjects::state_get_catch() {
    player()->setCheckStall(false);

    // Close gripper
    player()->idle();
    player()->gripper()->close();

    // Switch state condition
    if(player()->gripper()->state()==Gripper::CLOSED)
        _state2 = STATE_GET_RETRIEVE;
}

void Behavior_GetObjects::state_get_retrieve() {
    player()->setCheckStall(true);

    Position posToGo = Position(-2.0, 0.0);
    if(isInRoom(player()->position())) {
        posToGo = getTransitionPoint(player()->position());
    }

    // GoTo origin
    player()->goTo(posToGo, true);
    if(player()->position().x() <= 0.0 && fabs(player()->position().y()) <= 2.70) {
        player()->idle();
        _state2 = STATE_GET_DROP;
    }
}

void Behavior_GetObjects::state_get_drop() {
    // Open gripper
    player()->idle();
    player()->gripper()->open();

    // Switch state condition
    if(player()->gripper()->state()==Gripper::OPEN)
        _state2 = STATE_GET_GETAWAY;
}

void Behavior_GetObjects::state_get_getaway() {
    // Get away
    player()->setSpeed(-player()->maxLSpeed(), 0.0, 0.0);
    Thread::msleep(250);

    player()->setSpeed(0.0, 0.0, 2*Utils::pi());
    Thread::msleep(500);

    player()->idle();
    Thread::msleep(100);

    _hasCurrObject = false;
    _state2 = STATE_GET_GOTO;
}

bool Behavior_GetObjects::getNearestBlob(Blob *nearestBlob) {
    bool hasNearestBlob = false;

    int numBlobs = player()->blobFinder()->getNumBlobs();
    if(numBlobs > 0) {

        // Check blobs
        for(int i=0; i<numBlobs; i++) {
            Blob blob = player()->blobFinder()->getBlob(i);

            // Check blob color
            if(blob.getColor()==Colors::GREEN) {

                if(hasNearestBlob) {
                    if(blob.getRange() < nearestBlob->getRange())
                        *nearestBlob = blob;
                } else {
                    *nearestBlob = blob;
                    hasNearestBlob = true;
                }

            }
        }
    }

    return hasNearestBlob;
}

Position Behavior_GetObjects::getTransitionPoint(Position pos) {
    Position posToGo;
    if(pos.x() <= 7.4 && pos.y() >= 3.1){
        posToGo = Position(7.5,3.0);
    }else if(pos.x() <= 7.4 && pos.y() <= -2.5){
        posToGo = Position(3.5,-1.0);;
    }else if(pos.x() >= 18.6 && pos.y() >= 2.5){
        posToGo = Position(22.5,1.0);
    }else if(pos.x() >= 18.6 && pos.y() <= -3.1){
        posToGo = Position(18.5,-3.0);
    } else{
        posToGo = pos;
    }
    return posToGo;
}

bool Behavior_GetObjects::isInRoom(Position pos) {
    bool inRoom = false;
    if(pos.x() <= 7.4 && pos.y() >= 3.1){
        inRoom = true;
    }else if(pos.x() <= 7.4 && pos.y() <= -2.5){
        inRoom = true;
    }else if(pos.x() >= 18.6 && pos.y() >= 2.5){
        inRoom = true;
    }else if(pos.x() >= 18.6 && pos.y() <= -3.1){
        inRoom = true;
    }
    return inRoom;
}

bool Behavior_GetObjects::isSamePoint(Position pos1, Position pos2){
    if((pos1.x() == pos2.x()) && (pos1.y() == pos2.y())){
        return true;
    }
    return false;
}

