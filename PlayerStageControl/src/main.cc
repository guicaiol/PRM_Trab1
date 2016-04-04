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

#include <iostream>
#include <stdlib.h>

#include <PlayerStageControl/player/player.hh>
#include <PlayerStageControl/player/behavior/behaviors.hh>
#include "exithandler.hh"

int main(int argc, const char **argv) {

    // Setup ExitHandler
    ExitHandler::setup();

    // Create player
    Player player("localhost", 6675);

    // Connect
    if(player.connect()==false) {
        player.printError();
        return EXIT_FAILURE;
    }

    // Create behavior
    Behavior_GoTo *bh_goTo = new Behavior_GoTo();
    bh_goTo->setDestination(Position(23, 6));
    bh_goTo->setPosToLook(Position(0, 0));

    // Run
    player.setBehavior(bh_goTo);
    player.start();

    // Wait for exit
    ExitHandler::wait();

    // Stop
    player.stop();
    player.wait();

    // Delete behavior
    delete bh_goTo;

    // Disconnect
    player.disconnect();

    return EXIT_SUCCESS;
}
