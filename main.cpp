#include <iostream>
#include "CoordTransform.h"
#include "math.h"

int main() {
    CoordTransform::CoordTransform ct;
    double gcjLng, gcjLat;
    double wgsLng, wgsLat;
    double bdLng =  121.50639929862295;
    double bdLat = 31.245300709577183;

    ct.BD09ToGCJ02(bdLng, bdLat, gcjLng, gcjLat);
    ct.GCJ02ToWGS84(gcjLng, gcjLat, wgsLng, wgsLat);

    ct.WGS84ToGCJ02(wgsLng, wgsLat, gcjLng, gcjLat);
    ct.GCJ02ToBD09(gcjLng, gcjLat, bdLng, bdLat);

    return 0;
}
