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

#ifndef UTILS_HH
#define UTILS_HH

#include <math.h>

// Include utils classes
#include "position/position.hh"
#include "thread/thread.hh"

class Utils {
public:
    static float pi() {
        return 3.14159265358979323846;
    }

    static float twoPi() {
        return 6.28318530717958647692;
    }

    static float toDegree(float rad) {
        return rad*57.29577951308232087680;
    }

    static float toRadians(float deg) {
        return deg*0.01745329251994329577;
    }

    static float distance(const Position &pos1, const Position &pos2) {
        return sqrt(pow(pos2.x()-pos1.x(), 2)+pow(pos2.y()-pos1.y(), 2));
    }

    static float angleDiff(float ang1, float ang2) {
        float diff = fabs(ang2 - ang1);
        if(diff > Utils::pi())
            diff = Utils::twoPi() - diff;
        return diff;
    }

    static float getAngle(const Position &pos1, const Position &pos2) {
        return atan2(pos2.y()-pos1.y(), pos2.x()-pos1.x());
    }
};

#endif // UTILS_HH
