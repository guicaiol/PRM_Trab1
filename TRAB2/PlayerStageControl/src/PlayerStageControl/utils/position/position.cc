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

#include "position.hh"

Position::Position() {
    setUnknown();
}

Position::Position(float x, float y) {
    set(x, y);
}

void Position::setUnknown() {
    _x = _y = 0.0;
    _known = false;
}

void Position::set(float x, float y) {
    setX(x);
    setY(y);
}

void Position::setX(float x) {
    _x = x;
    _known = true;
}

void Position::setY(float y) {
    _y = y;
    _known = true;
}

bool Position::isUnknown() const {
    return (_known==false);
}

float Position::x() const {
    return _x;
}

float Position::y() const {
    return _y;
}
