/***********************************************************************
 * Source File:
 *    PHYSICS
 * Author:
 *    <your name here>
 * Summary:
 *    Laws of motion, effects of gravity, wind resistance, etc.
 ************************************************************************/

#include "physics.h"
#include <stdexcept>
using namespace std;

/*********************************************************
 * LINEAR INTERPOLATION
 * From a list of domains and ranges, linearly interpolate.
 *********************************************************/
double linearInterpolation(const Mapping mapping[], int numMapping, double domain)
{
    if (numMapping < 2) {
        throw invalid_argument("At least two mappings are required for interpolation.");
    }

    for (int i = 0; i < numMapping - 1; ++i) {
        if (domain >= mapping[i].domain && domain <= mapping[i + 1].domain) {
            return linearInterpolation(mapping[i].domain, mapping[i].range,
                                       mapping[i + 1].domain, mapping[i + 1].range,
                                       domain);
        }
    }

    if (domain < mapping[0].domain)
        return mapping[0].range;
    if (domain > mapping[numMapping - 1].domain)
        return mapping[numMapping - 1].range;

    throw std::out_of_range("Domain is out of range for the provided mappings.");
}

/*********************************************************
 * GRAVITY FROM ALTITUDE
 * Determine gravity coefficient based on altitude
 *********************************************************/
double gravityFromAltitude(double altitude)
{
    Mapping gravityMap[] = {
        {0, 9.807},
        {3666.6, 9.795},
        {5500, 9.7895},
        {8848.86, 9.77945},
        {10000, 9.776},
        {43333, 9.674},
        {80000, 9.564}
    };
    const int numMapping = sizeof(gravityMap) / sizeof(gravityMap[0]);
    return linearInterpolation(gravityMap, numMapping, altitude);
}

/*********************************************************
 * DENSITY FROM ALTITUDE
 * Determine the density of air based on altitude
 *********************************************************/
double densityFromAltitude(double altitude)
{
    Mapping densityMap[] = {
        {0, 1.225},
        {3666.6, 0.849372},
        {5500, 0.69825},
        {8848.86, 0.4759719},
        {10000, 0.4135000},
        {43333, 0.0030063},
        {80000, 0.0000185}
    };
    const int numMapping = sizeof(densityMap) / sizeof(densityMap[0]);
    return linearInterpolation(densityMap, numMapping, altitude);
}

/*********************************************************
 * SPEED OF SOUND FROM ALTITUDE
 * Determine the speed of sound at a given altitude.
 ********************************************************/
double speedSoundFromAltitude(double altitude)
{
    Mapping speedSoundMap[] = {
        {0, 340.0},
        {3666, 325.336},
        {5500, 318.0},
        {8848, 303.76},
        {10000, 299.0},
        {43333, 328.3329},
        {80000, 269.0}
    };
    const int numMapping = sizeof(speedSoundMap) / sizeof(speedSoundMap[0]);
    return linearInterpolation(speedSoundMap, numMapping, altitude);
}

/*********************************************************
 * DRAG FROM MACH
 * Determine the drag coefficient based on Mach number.
 *********************************************************/
double dragFromMach(double speedMach)
{
    Mapping dragMap[] = {
        {0.0, 0.0},
        {0.1, 0.0543},
        {0.6, 0.1845},
        {1.0, 0.4258},
        {3.14159, 0.2347},
        {5.0, 0.2656}
    };
    const int numMapping = sizeof(dragMap) / sizeof(dragMap[0]);
    return linearInterpolation(dragMap, numMapping, speedMach);
}
