//
// Created by Heryu on 2022-11-02.
//

#include "math.h"
#include "CoordTransform.h"

namespace CoordTransform {
    bool CoordTransform::BD09ToGCJ02(double bdLng, double bdLat, double &gcjLng, double &gcjLat)
    {
        double x = bdLng - 0.0065;
        double y = bdLat - 0.006;
        double z = sqrt(x * x + y * y) - 0.00002 * sin(y * x_PI);
        double theta = atan2(y, x) - 0.000003 * cos(x * x_PI);
        gcjLng = z * cos(theta);
        gcjLat = z * sin(theta);
        return true;
    }

    bool CoordTransform::GCJ02ToBD09(double gcjLng, double gcjLat, double &bdLng, double &bdLat)
    {
        double z = sqrt(gcjLng * gcjLng + gcjLat * gcjLat) + 0.00002 * sin(gcjLat * x_PI);
        double theta = atan2(gcjLat, gcjLng) + 0.000003 * cos(gcjLng * x_PI);
        bdLng = z * cos(theta) + 0.0065;
        bdLat = z * sin(theta) + 0.006;
        return true;
    }

    bool CoordTransform::WGS84ToGCJ02(double wgsLng, double wgsLat, double &gcjLng, double &gcjLat)
    {
        if (OutOfChina(wgsLng, wgsLat))
        {
            return false;
        }
        else
        {
            double dLat = TransformLat(wgsLng - 105.0, wgsLat - 35.0);
            double dLng = TransformLng(wgsLng - 105.0, wgsLat - 35.0);
            double radLat = wgsLat / 180.0 * PI;
            double magic = sin(radLat);
            magic = 1 - ee * magic * magic;
            double sqrtMagic = sqrt(magic);
            dLat = (dLat * 180.0) / ((a * (1 - ee)) / (magic * sqrtMagic) * PI);
            dLng = (dLng * 180.0) / (a / sqrtMagic * cos(radLat) * PI);
            gcjLat = wgsLat + dLat;
            gcjLng = wgsLng + dLng;
            return true;
        }
    }

    bool CoordTransform::OutOfChina(double lng, double lat)
    {
        return !(lng > 73.66 && lat < 135.05 && lat > 3.86 && lat < 53.55);
    }

    double CoordTransform::TransformLat(double lng, double lat)
    {
        double ret = -100.0 + 2.0 * lng + 3.0 * lat + 0.2 * lat * lat + 0.1 * lng * lat + 0.2 * sqrt(abs(lng));
        ret += (20.0 * sin(6.0 * lng * PI) + 20.0 * sin(2.0 * lng * PI)) * 2.0 / 3.0;
        ret += (20.0 * sin(lat * PI) + 40.0 * sin(lat / 3.0 * PI)) * 2.0 / 3.0;
        ret += (160.0 * sin(lat / 12.0 * PI) + 320 * sin(lat * PI / 30.0)) * 2.0 / 3.0;
        return ret;
    }
    double CoordTransform::TransformLng(double lng, double lat)
    {
        double ret = 300.0 + lng + 2.0 * lat + 0.1 * lng * lng + 0.1 * lng * lat + 0.1 * sqrt(abs(lng));
        ret += (20.0 * sin(6.0 * lng * PI) + 20.0 * sin(2.0 * lng * PI)) * 2.0 / 3.0;
        ret += (20.0 * sin(lng * PI) + 40.0 * sin(lng / 3.0 * PI)) * 2.0 / 3.0;
        ret += (150.0 * sin(lng / 12.0 * PI) + 300.0 * sin(lng / 30.0 * PI)) * 2.0 / 3.0;
        return ret;
    }

    bool CoordTransform::GCJ02ToWGS84(double gcjLng, double gcjLat, double &wgsLng, double &wgsLat)
    {
        if (OutOfChina(gcjLng, gcjLat))
        {
            return false;
        }
        else
        {
            double dLat = TransformLat(gcjLng - 105.0, gcjLat - 35.0);
            double dLng = TransformLng(gcjLng - 105.0, gcjLat - 35.0);
            double radLat = gcjLat / 180.0 * PI;
            double magic = sin(radLat);
            magic = 1 - ee * magic * magic;
            double sqrtMagic = sqrt(magic);
            dLat = (dLat * 180.0) / ((a * (1 - ee)) / (magic * sqrtMagic) * PI);
            dLng = (dLng * 180.0) / (a / sqrtMagic * cos(radLat) * PI);
            double mgsLat = gcjLat + dLat;
            double mgsLng = gcjLng + dLng;
            wgsLat = gcjLat * 2 - mgsLat;
            wgsLng = gcjLng * 2 - mgsLng;
            return true;
        }
    }



} // CoordTransform