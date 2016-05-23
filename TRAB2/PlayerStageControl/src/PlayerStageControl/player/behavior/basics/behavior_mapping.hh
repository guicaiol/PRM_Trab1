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

#ifndef BEHAVIOR_MAPPING_HH
#define BEHAVIOR_MAPPING_HH

#include <PlayerStageControl/player/behavior/behavior.hh>
#include <vector>
#include <opencv/cv.h>
#include <opencv/highgui.h>

class Behavior_Mapping : public Behavior {
public:
    Behavior_Mapping();
    ~Behavior_Mapping();

private:
    void run();

    // Internal
    void resetView();
    void refreshView();
    void updateAlzheimer();
    void updateMapToView();

    void drawPixel(int x, int y, unsigned char r, unsigned char g, unsigned char b);

    void drawPosition(const Position &pos, unsigned char r,  unsigned char g, unsigned char b);
    void mapLine(const Position &p1, const Position &p2);

    void nunoMapPixel(int x, int y, float inc);

    // Mapping matrix
    std::vector<std::vector<float>> _map;


    // OpenCV image
    int _width;
    int _height;
    IplImage *_image;

    // Parameters

};

#endif // BEHAVIOR_MAPPING_HH
