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

#ifndef BLOB_H
#define BLOB_H

#include <libplayerc/playerc.h>
#include <PlayerStageControl/utils/position/position.hh>
#include <PlayerStageControl/utils/color/color.hh>

class Blob {
public:
    Blob();
    Blob(playerc_blobfinder_blob_t blob);

    // Getters
    Colors::Color getColor() const;
    int getArea() const;
    Position getCentroid() const;
    float getRange() const;

private:
    int _id;
    int _color;
    int _area;
    Position _centroid;
    float _range;
};

#endif // BLOB_H
