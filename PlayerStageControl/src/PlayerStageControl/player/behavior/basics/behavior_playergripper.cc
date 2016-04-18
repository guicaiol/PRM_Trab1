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

#include "behavior_playergripper.hh"
#include <PlayerStageControl/player/player.hh>
#include <PlayerStageControl/player/device/devices.hh>

Behavior_PlayerGripper::Behavior_PlayerGripper() {
    _state = STATE_SEARCH;
}

void Behavior_PlayerGripper::run() {

    // Switch state machine
    switch(_state) {
        case STATE_SEARCH: {
            std::cout << "search!\n";
            state_search();
        } break;

        case STATE_GOTO: {
            std::cout << "goTo!\n";
            state_goTo();
        } break;

        case STATE_CATCH: {
            std::cout << "catch!\n";
            state_catch();
        } break;

        case STATE_RETRIEVE: {
            std::cout << "retrieve!\n";
            state_retrieve();
        } break;

        case STATE_DROP: {
            std::cout << "drop!\n";
            state_drop();
        } break;

        case STATE_GETAWAY: {
            std::cout << "getAway!\n";
            state_getaway();
        } break;

        default:
            player()->idle();
        break;
    }

}

void Behavior_PlayerGripper::state_search() {
    // Open gripper
    player()->gripper()->open();

    // Search algorithm (generate points)
    /// TODO: implement search algorithm!
    Position destination = Position(26, 3);
    player()->goTo(destination, true);

    // Check blob found, and select nearest blob
    int numBlobs = player()->blobFinder()->getNumBlobs();
    if(numBlobs > 0) {

        // Check blobs
        for(int i=0; i<numBlobs; i++) {
            Blob blob = player()->blobFinder()->getBlob(i);

            // Check blob color
            if(blob.getColor()==Colors::GREEN)
                _state = STATE_GOTO;
        }
    }

}

void Behavior_PlayerGripper::state_goTo() {

    // Go to nearest blob
    Blob nearestBlob;
    bool hasBlobs = getNearestBlob(&nearestBlob);
    if(hasBlobs==false) {
        _state = STATE_SEARCH;
        return;
    }

    // Go to nearest blob
    bool goToBlob = player()->goToBlob(nearestBlob);
    if(goToBlob)
        _state = STATE_CATCH;
}

void Behavior_PlayerGripper::state_catch() {
    // Close gripper
    player()->idle();
    player()->gripper()->close();

    // Switch state condition
    if(player()->gripper()->state()==Gripper::CLOSED)
        _state = STATE_RETRIEVE;
}

void Behavior_PlayerGripper::state_retrieve() {
    Position origin(-2.0, 0.0);

    // GoTo origin
    player()->goTo(origin, true);
    if(player()->position().x() <= 0.0 && fabs(player()->position().y()) <= 2.70) {
        player()->idle();
        _state = STATE_DROP;
    }
}

void Behavior_PlayerGripper::state_drop() {
    // Open gripper
    player()->idle();
    player()->gripper()->open();

    // Switch state condition
    if(player()->gripper()->state()==Gripper::OPEN)
        _state = STATE_GETAWAY;

}

void Behavior_PlayerGripper::state_getaway() {
    // Get away
    player()->setSpeed(-player()->maxLSpeed(), 0.0, 0.0);
    Thread::msleep(250);

    player()->setSpeed(0.0, 0.0, 2*Utils::pi());
    Thread::msleep(500);

    player()->idle();
    Thread::msleep(100);

    _state = STATE_SEARCH;
}

bool Behavior_PlayerGripper::getNearestBlob(Blob *nearestBlob) {
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
