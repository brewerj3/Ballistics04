#include <math.h>
#include <stdio.h>

#include "BallisticCalc.h"

const long double gravitationalAcceleration = -9.8;
const long unsigned passesPerSecond = 1000000;
const long double airDensity = 1.204;
const long double dragCoefficiant = 0.186;
const long double pie = 3.14159265358979323846;

long double calculateRangeMetric(long double shellDiameterInMeters, long double angleOfGunDegree,
                                 long double muzzleVelocityMeterPerSecond, long double massOfShellKilograms) {
    // Calculate Constants
    const long double forceOfGravity = gravitationalAcceleration * massOfShellKilograms;
    const long double shellArea =
            (3.14159265358979323846) * ((shellDiameterInMeters / 2) * (shellDiameterInMeters / 2));

    long double currentVelocity = muzzleVelocityMeterPerSecond;
    long double forceOfAirOnShell = 0;
    long double currentShellAngleRadians = angleOfGunDegree * (3.14159265358979323846 / 180);
    unsigned currentTimeMilliseconds = 0;

    // Current Position of Shell
    long double currentXAxisPosition = 0;
    long double currentYAxisPosition = 0;

    // Next Position of Shell
    long double nextXAxisPosition = 0;
    long double nextYAxisPosition = 0;

    // Velocity by axis
    long double xAxisVelocity = 0;
    long double yAxisVelocity = 0;

    // Acceleration by axis
    long double xAxisAcceleration = 0;
    long double yAxisAcceleration = 0;

    // Force by axis
    long double xAxisForce = 0;
    long double yAxisForce = 0;

    // Change in Velocity by axis
    long double deltaX = 0;
    long double deltaY = 0;

    unsigned test = 0;

    // Loop to find range
    while ((currentYAxisPosition >= 0) && (currentTimeMilliseconds < (120 * passesPerSecond))) {
        // Find force of air on shell
        forceOfAirOnShell = -(((0.5) * dragCoefficiant * airDensity * shellArea *
                               ((currentVelocity) * (currentVelocity))));

        // Find force in both axis
        xAxisForce = (cosl(currentShellAngleRadians) * forceOfAirOnShell);
        yAxisForce = (sinl(currentShellAngleRadians) * forceOfAirOnShell) + (forceOfGravity);

        // Find acceleration in both axis
        xAxisAcceleration = (xAxisForce / massOfShellKilograms) / passesPerSecond;
        yAxisAcceleration = (yAxisForce / massOfShellKilograms) / passesPerSecond;

        // Find velocity in both axis
        xAxisVelocity = ((cosl(currentShellAngleRadians) * currentVelocity) + xAxisAcceleration);
        yAxisVelocity = ((sinl(currentShellAngleRadians) * currentVelocity) + yAxisAcceleration);

        // Find change in velocity for both axis
        deltaX = ((cosl(currentShellAngleRadians) * currentVelocity) / passesPerSecond + xAxisAcceleration);
        deltaY = ((sinl(currentShellAngleRadians) * currentVelocity) / passesPerSecond + yAxisAcceleration);

        // Update the position
        currentXAxisPosition = currentXAxisPosition + deltaX;
        currentYAxisPosition = currentYAxisPosition + deltaY;

        // Update current velocity
        currentVelocity = fabsl(sqrtl(((xAxisVelocity) * (xAxisVelocity) + (yAxisVelocity) * (yAxisVelocity))));

        // Update current shell angle
        currentShellAngleRadians = atanl((yAxisVelocity / xAxisVelocity));


        // Update current time in milliseconds
        currentTimeMilliseconds++;

#ifdef DEBUG
        printf("Time: [%5f]  | X: [%5.2f]  | Y:  [%5.2f] | Angle  [%5.2f]  | Drag: [%5.4f]  |X-Axis acceleration: [%5.4f]  | Y-Axis acceleration: [%5.4f]  | Current Velocity [%5.4f]\n",(currentTimeMilliseconds/passesPerSecond),currentXAxisPosition,currentYAxisPosition,currentShellAngleRadians,forceOfAirOnShell,xAxisAcceleration,yAxisAcceleration,currentVelocity);
#endif

    }
    return currentXAxisPosition;
}