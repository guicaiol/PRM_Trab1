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

void draw_point(IplImage *image, int x, int y, unsigned char r, unsigned char g, unsigned char b) {
  image->imageData[3*((y*100)+x)]=b;
  image->imageData[3*((y*100)+x)+1]=g;
  image->imageData[3*((y*100)+x)+2]=r;
}

int main() {

    const std::string ipAddress = "localhost";
    const bool redTeam = true;

    const int player1_port = redTeam? 6665 : 6675;
//    const int player2_port = redTeam? 6666 : 6676;
//    const int player3_port = redTeam? 6667 : 6677;

    // Setup ExitHandler
    ExitHandler::setup();

    // Create player 1
    Player player1(ipAddress.c_str(), player1_port);
    if(player1.connect()==false) {
        player1.printError();
        return EXIT_FAILURE;
    }

    // Create behaviors
    Behavior_Mapping *bh1 = new Behavior_Mapping();

    // Set behaviors
    player1.setBehavior(bh1);
    player1.setMaxLSpeed(1.2);

    // Start players
    player1.start();

    // Wait for exit
    ExitHandler::wait();

    // Stop
    player1.stop();
    player1.wait();

    // Delete behavior
    delete bh1;

    // Disconnect
    player1.disconnect();

    return EXIT_SUCCESS;
}
