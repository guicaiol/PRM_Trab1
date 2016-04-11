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
