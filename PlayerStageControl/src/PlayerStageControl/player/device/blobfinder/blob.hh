#ifndef BLOB_H
#define BLOB_H

#include <libplayerc/playerc.h>
#include <PlayerStageControl/utils/position/position.hh>

class Blob {
public:
    Blob(playerc_blobfinder_blob_t blob);
    int getColor();
    int getArea();
    Position getCentroid();
    float getRange();
private:
    int _id;
    int _color;
    int _area;
    Position _centroid;
    float _range;
};

#endif // BLOB_H
