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

#include "navigation.hh"
#include <PlayerStageControl/player/player.hh>
#include <PlayerStageControl/player/device/laser/laser.hh>
#include <PlayerStageControl/player/navigation/navigationalgorithm/PF/pf.hh>

Navigation::Navigation(Player *player, Laser *laser) {
    _player = player;
    _laser = laser;

    // Create NavigationAlgorithm
    _navAlg = new PF();
}

float Navigation::getDirection(const Position &destination, bool avoidObstacles) {

    // Reset nav alg
    _navAlg->reset();

    // Set origin
    _navAlg->setOrigin(_player->position());

    // Set goal
    _navAlg->setGoal(destination);

    // Add obstacles
    if(avoidObstacles) {

        // Add laser detected obstacles
        for(int i=0; i<_laser->getScanCount(); i++) {
            float range = _laser->getRange(i);
            float angle = _laser->getBearing(i);

            if(range > 5.0)
                continue;

            float globalAngle = _player->orientation() + angle;
            Position obstacle(_player->position().x() + range*cos(globalAngle), _player->position().y() + range*sin(globalAngle));

//            std::cout << "adding beam, range=" << range << ", angle=" << Utils::toDegree(angle) << ", globalAngle=" << Utils::toDegree(globalAngle) << ", pos: x=" << obstacle.x() << ", y= " << obstacle.y() << "\n";

            _navAlg->addObstacle(obstacle);
        }

    }

    return _navAlg->getDirection();
}
