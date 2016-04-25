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

int main() {

    // Setup ExitHandler
    ExitHandler::setup();

    // Create player 1 (with gripper)
    Player player1("localhost", 6675);
    if(player1.connect()==false) {
        player1.printError();
        return EXIT_FAILURE;
    }

    // Create player 2 (with gripper)
    Player player2("localhost", 6676);
    if(player2.connect()==false) {
        player2.printError();
        return EXIT_FAILURE;
    }

    // Create player 3 (without gripper)
//    Player player3("localhost", 6677);
//    if(player3.connect()==false) {
//        player3.printError();
//        return EXIT_FAILURE;
//    }

    // Create behaviors
    Behavior_Gripper *bh_gripper1 = new Behavior_Gripper();
    Behavior_Gripper *bh_gripper2 = new Behavior_Gripper();
//    Behavior_NoGripper *bh_noGripper = new Behavior_NoGripper();

    // Set behaviors
    player1.setBehavior(bh_gripper1);
//    player2.setBehavior(bh_gripper2);
//    player3.setBehavior(bh_noGripper);

    // Start players
    player1.start();
//    player2.start();
//    player3.start();

    // Wait for exit
    ExitHandler::wait();

    // Stop
    player1.stop();
    player2.stop();
//    player3.stop();
    player1.wait();
//    player2.wait();
//    player3.wait();

    // Delete behavior
    delete bh_gripper1;
    delete bh_gripper2;
//    delete bh_noGripper;

    // Disconnect
    player1.disconnect();

    return EXIT_SUCCESS;
}
