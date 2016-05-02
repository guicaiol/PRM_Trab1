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

#include <iostream>
#include <stdlib.h>
#include <vector>
#include <mutex>

#include <PlayerStageControl/player/player.hh>
#include <PlayerStageControl/player/behavior/behaviors.hh>
#include "exithandler.hh"

int main() {

    const std::string ipAddress = "localhost";
    const bool redTeam = false;

    const int player1_port = redTeam? 6665 : 6675;
    const int player2_port = redTeam? 6666 : 6676;
    const int player3_port = redTeam? 6667 : 6677;

    // Setup ExitHandler
    ExitHandler::setup();

    // Create player 1 (with gripper)
    Player player1(ipAddress.c_str(), player1_port);
    if(player1.connect()==false) {
        player1.printError();
        return EXIT_FAILURE;
    }

    // Create player 2 (with gripper)
    Player player2(ipAddress.c_str(), player2_port);
    if(player2.connect()==false) {
        player2.printError();
        return EXIT_FAILURE;
    }

    // Create player 3 (without gripper)
    Player player3(ipAddress.c_str(), player3_port);
    if(player3.connect()==false) {
        player3.printError();
        return EXIT_FAILURE;
    }

    // Objects list
    std::vector<Position> objList;
    // Mutex
    std::mutex mux;

    // Create behaviors
    Behavior_GetObjects *bh_get1 = new Behavior_GetObjects();
    bh_get1->addScanPoint(Position(3.0, -4.5), Utils::toRadians(0), Utils::toRadians(180));
    bh_get1->addScanPoint(Position(3.0, -4.5), Utils::toRadians(180), Utils::toRadians(0));
    bh_get1->addScanPoint(Position(13.0, -5.0), Utils::toRadians(0), Utils::toRadians(180));
    bh_get1->addScanPoint(Position(13.0, -5.0), Utils::toRadians(180), Utils::toRadians(0));
    bh_get1->setObjectsList(&objList, &mux);

    Behavior_GetObjects *bh_get2 = new Behavior_GetObjects();
    bh_get2->addScanPoint(Position(3.0, 5.0), Utils::toRadians(0), Utils::toRadians(180));
    bh_get2->addScanPoint(Position(3.0, 5.0), Utils::toRadians(180), Utils::toRadians(0));
    bh_get2->addScanPoint(Position(13.0, 5.0), Utils::toRadians(0), Utils::toRadians(180));
    bh_get2->addScanPoint(Position(13.0, 5.0), Utils::toRadians(180), Utils::toRadians(0));
    bh_get2->setObjectsList(&objList, &mux);

    Behavior_GetObjects *bh_get3 = new Behavior_GetObjects();
    bh_get3->addScanPoint(Position(13.0, 0.0), Utils::toRadians(10), Utils::toRadians(180));
    bh_get3->addScanPoint(Position(13.0, 0.0), Utils::toRadians(180), Utils::toRadians(10));
    bh_get3->addScanPoint(Position(23.0, -5.0), Utils::toRadians(0), Utils::toRadians(180));
    bh_get3->addScanPoint(Position(23.0, -5.0), Utils::toRadians(180), Utils::toRadians(0));
    bh_get3->addScanPoint(Position(23.0, 4.5), Utils::toRadians(0), Utils::toRadians(180));
    bh_get3->addScanPoint(Position(23.0, 4.5), Utils::toRadians(180), Utils::toRadians(0));
    bh_get3->setObjectsList(&objList, &mux);

    // Set behaviors
    player1.setBehavior(bh_get1);
    player1.setMaxLSpeed(1.2);

    player2.setBehavior(bh_get2);
    player2.setMaxLSpeed(1.2);

    player3.setBehavior(bh_get3);
    player3.setMaxLSpeed(2.0);

    // Start players
    player1.start();
    player2.start();
    player3.start();

    // Wait for exit
    ExitHandler::wait();

    // Stop
    player1.stop();
    player2.stop();
    player3.stop();
    player1.wait();
    player2.wait();
    player3.wait();

    // Delete behavior
    delete bh_get1;
    delete bh_get2;
    delete bh_get3;

    // Disconnect
    player1.disconnect();
    player2.disconnect();
    player3.disconnect();

    return EXIT_SUCCESS;
}
