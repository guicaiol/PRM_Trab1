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

#include "behavior_test.hh"
#include <PlayerStageControl/player/player.hh>
#include <PlayerStageControl/player/device/devices.hh>

Behavior_Test::Behavior_Test() {
    _hasSelectedBlob = false;

    _state = STATE_SEARCH;
}

void Behavior_Test::run() {

    // Switch state machine
    switch(_state) {
        case STATE_SEARCH: {
            search();
        } break;

        case STATE_GOTO: {
            goTo();
        }

        default:
            player()->idle();
        break;
    }

}

void Behavior_Test::search() {
    // Search algorithm (generate points)
    Position destination = Position(26, 3);
    player()->goTo(destination, true);

    // Check blob found, and select nearest blob
    int numBlobs = player()->blobFinder()->getNumBlobs();
    if(numBlobs > 0) {

        // Check blobs
        for(int i=0; i<numBlobs; i++) {
            Blob blob = player()->blobFinder()->getBlob(i);

            // Check blob color
            if(blob.getColor()==Colors::GREEN) {

                if(_hasSelectedBlob) {
                    if(blob.getRange() < _selectedBlob.getRange())
                        _selectedBlob = blob;
                } else {
                    _selectedBlob = blob;
                    _hasSelectedBlob = true;
                }

            }

        }
    }

    // Switch state condition: blob found
    if(_hasSelectedBlob)
        _state = STATE_GOTO;
}

void Behavior_Test::goTo() {

    player()->idle();


}
