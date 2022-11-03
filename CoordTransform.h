//
// Created by Heryu on 2022-11-02.
//

#ifndef COORDTRANSFORM_COORDTRANSFORM_H
#define COORDTRANSFORM_COORDTRANSFORM_H

namespace CoordTransform {

    class CoordTransform {
    private:
        const double x_PI = 3.14159265358979324 * 3000.0 / 180.0;
        const double PI = 3.1415926535897932384626;
        const double a = 6378245.0;
        const double ee = 0.00669342162296594323;

        bool OutOfChina(double lng, double lat);
        double TransformLat(double lng, double lat);
        double TransformLng(double lng, double lat);

    public:
        bool BD09ToGCJ02(double bdLng, double bdLat, double &gcjLng, double &gcjLat);
        bool GCJ02ToBD09(double gcjLng, double gcjLat, double &bdLng, double &bdLat);
        bool WGS84ToGCJ02(double wgsLng, double wgsLat, double &gcjLng, double &gcjLat);
        bool GCJ02ToWGS84(double gcjLng, double gcjLat, double &wgsLng, double &wgsLat);
    };

} // CoordTransform

#endif //COORDTRANSFORM_COORDTRANSFORM_H
