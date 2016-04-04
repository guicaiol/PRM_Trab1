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

#include "pf.hh"

#define REPULSIVE_K 0.01
#define FACTOR 1.6

PF::PF() {

}

void PF::reset() {
    _origin.set(0, 0);
    _goal.set(0, 0);
    _resultantForce.setVector(0, 0);
}

void PF::setOrigin(const Position &origin) {
    _origin = origin;
}

void PF::setGoal(const Position &goal) {
    _goal = goal;
    addAttractive(getVector(_origin, _goal));
}

void PF::addObstacle(const Position &obst) {
    addRepulsive(getVector(obst, _origin), REPULSIVE_K);
}

float PF::getDirection() {
    float resultantAngle = atan2(_resultantForce.y(), _resultantForce.x());
    return resultantAngle;
}

void PF::addRepulsive(const Vector &v, float k) {
    addForce(applyDistanceFunction(v, k));
}

void PF::addAttractive(const Vector &v) {
    addForce(v.getUnitary());
}

void PF::addForce(const Vector &v) {
    _resultantForce += v;
}

Vector PF::applyDistanceFunction(Vector v, float k) {
    const float d = v.getModule();
    return (v.getUnitary() * k)/pow(d, FACTOR);
}

Vector PF::getVector(const Position &v1, const Position &v2) {
    return Vector(v2.x()-v1.x(), v2.y()-v1.y());
}
