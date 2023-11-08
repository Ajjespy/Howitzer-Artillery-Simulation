// Prototype.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "position.h"

using namespace std;

#define WEIGHT   46.7   // Weight in KG
#define DIAMETER .15489 // diameter in m


/**************************************************
 * PROMPT
 * A generic function to prompt the user for a double
 * INPUT
 *      message : the message to display to the user
 * OUTPUT
 *      response : the user's response
 ***************************************************/
double prompt(string message)
{
    cout << message;
    double number;
    cin >> number;
    return number;
}

/*************************************************
* RADIANS FROM DEGEES
* Convert degrees to radians:
       *     radians / 2pi = degrees / 360
       * INPUT
       *     d : degrees from 0 to 360
       * OUTPUT
       *     r : radians from 0 to 2pi
       **************************************************/
double degreestoRadians(double degree)
{
    //need to create something if degrees are more than 360 to loop around and if less than zero vice versa
    double radians = (degree / 360) * 2 * (3.14159265358979323846);
    return radians;

}

/***********************************************
 * COMPUTE HORIZONTAL COMPONENT
 * Find the horizontal component of a velocity or acceleration.
 * The equation is:
 *     sin(a) = x / total
 * This can be expressed graphically:
 *      x
 *    +-----
 *    |   /
 *  y |  / total
 *    |a/
 *    |/
 * INPUT
 *     a : angle, in radians
 *     total : total velocity or acceleration
 * OUTPUT
 *     x : the vertical component of the total
 ***********************************************/
double horizontalComponent(double angle, double total)
{
    double horizontal = sin(angle) * total;
    return horizontal;
}

/***********************************************
 * COMPUTE VERTICAL COMPONENT
 * Find the vertical component of a velocity or acceleration.
 * The equation is:
 *     cos(a) = y / total
 * This can be expressed graphically:
 *      x
 *    +-----
 *    |   /
 *  y |  / total
 *    |a/
 *    |/
 * INPUT
 *     a : angle, in radians
 *     total : total velocity or acceleration
 * OUTPUT
 *     y : the vertical component of the total
 ***********************************************/
double verticalComponent(double angle, double total)
{
    double vertical = cos(angle) * total;
    return vertical;
}

/***********************************************
   * COMPUTE VELOCITY
   * Starting with a given velocity, find the new
   * velocity once acceleration is applied. This is
   * called the Kinematics equation. The
   * equation is:
   *     v = v + a t
   * INPUT
   *     v : velocity, in meters/second
   *     a : acceleration, in meters/second^2
   *     t : time, in seconds
   * OUTPUT
   *     v : new velocity, in meters/second
   ***********************************************/
double computeVelocity(double velocity, double acceleration, double time)
{
    double newVelocity = velocity + (time * acceleration);
    return newVelocity;
}
/************************************************
 * COMPUTE PYTHAGOREAN THEOREM
 * Given the horizontal and vertical components of
 * something (velocity or acceleration), determine
 * the total component. To do this, use the Pythagorean Theorem:
 *    x^2 + y^2 = t^2
 * where:
 *      x
 *    +-----
 *    |   /
 *  y |  / total
 *    | /
 *    |/
 * INPUT
 *    x : horizontal component
 *    y : vertical component
 * OUTPUT
 *    total : total component
 ***********************************************/
double pythagoreanTheorem(double horizontal, double vertical)
{
    double total = pow(horizontal, 2) + pow(vertical, 2);
    return sqrt(total);

}

/************************************************
 * COMPUTE ANGLE FROM COMPONENTS
 * Given the horizontal and vertical components of
 * velocity, determine the direction of travel
 * where 0 is pointing up (radians)
 * 
 * a = atan2(dx, dy)
 * 
 * INPUT
 *    dx : horizontal velocity (m/s)
 *    dy : vertical velocity (m/s)
 * OUTPUT
 *    angle : direction of travel (radians)
 ***********************************************/
double anglefromComponents(double dx, double dy)
{
    double angle = atan2(dx, dy);
    return angle;
}

/***************************************************
 * COMPUTE DISTANCE
 * Apply inertia to compute a new position using the distance equation.
 * The equation is:
 *     s = s + v t + 1/2 a t^2
 * INPUT
 *     s : original position, in meters
 *     v : velocity, in meters/second
 *     a : acceleration, in meters/second^2
 *     t : time, in seconds
 * OUTPUT
 *     s : new position, in meters
 **************************************************/

double ComputeDistance(double originalPosition, double velocity, double acceleration, double time)
{
    double position = originalPosition + (velocity * time) + (.5 * acceleration) * pow(time, 2);

    return position;
}

/************************************************
 * COMPUTE AREA OF CIRCLE
 * Determine the area of a circle given the radius
 *
 * a = pi r^2
 * PI = 3.14159265358979323846
 * 
 * INPUT
 *    r  : radius (m)
 * OUTPUT
 *    a  : area (m^2)
 ***********************************************/
double circleArea(double r)
{
    double a = pow(r, 2.0) * 3.14159265358979323846;
    return a;
}

/************************************************
 * COMPUTE Newtons 2nd law
 * Determine which equation to use given
 * the other two units
 * 
 * f = m a
 * m = f / a
 * a = f / m
 *
 * INPUT
 *    item1 : first item should always be force if mult is false
 *    item2 : second item
 *    mult  : true for mult, false for divide
 * OUTPUT
 *    item3 : resulting item
 ***********************************************/
double newtonsLaw(double item1, double item2, bool mult)
{
    if (mult)
    {
        return item1 * item2;
    }
    else
    {
        return item1 / item2;
    }
}

/************************************************
 * COMPUTE DRAG FORCE
 * Determine the drag force of an object in newtons
 *
 * d = 1/2 c p v^2 a
 *
 * INPUT
 *    drag - c    : drag coefficient 
 *    density - p : density of the fluid/gas
 *    v           : velocity of the projectile
 *    area - a    : surface area (m^2)
 * OUTPUT
 *    d  : drag force (N)
 ***********************************************/
double dragForce(double drag, double density, double v, double area)
{
    double d = .5 * drag * density * pow(v, 2.0) * area;
    if (v > 0)
    {
        return -newtonsLaw(d, WEIGHT, false);
    }
    else
    {
        return newtonsLaw(d, WEIGHT, false); 
    }
}

Position drag[16] = { 
    Position(0.300,	0.1629),
    Position(0.500,	0.1659),
    Position(0.700,	0.2031),
    Position(0.890,	0.2597),
    Position(0.920,	0.3010),
    Position(0.960,	0.3287),
    Position(0.980,	0.4002),
    Position(1.000,	0.4258),
    Position(1.020,	0.4335),
    Position(1.060,	0.4483),
    Position(1.240,	0.4064),
    Position(1.530,	0.3663),
    Position(1.990,	0.2897),
    Position(2.870,	0.2297),
    Position(2.890,	0.2306),
    Position(5.000,	0.2656) };

Position sound[16] = {
    Position(0.0,	340.0),
    Position(1000.0,	336.0),
    Position(2000.0,	332.0),
    Position(3000.0,	328.0),
    Position(4000.0,	324.0),
    Position(5000.0,	320.0),
    Position(6000.0,	316.0),
    Position(7000.0,	312.0),
    Position(8000.0,	308.0),
    Position(9000.0,	303.0),
    Position(10000.0,	299.0),
    Position(15000.0,	295.0),
    Position(20000.0,	295.0),
    Position(25000.0,	295.0),
    Position(30000.0,	305.0),
    Position(40000.0,	324.0),
};

Position density[20] = {
    Position(0.0,	1.2250000),
    Position(1000.0,	1.1120000),
    Position(2000.0,	1.0070000),
    Position(3000.0,	0.9093000),
    Position(4000.0,	0.8194000),
    Position(5000.0,	0.7364000),
    Position(6000.0,	0.6601000),
    Position(7000.0,	0.5900000),
    Position(8000.0,	0.5258000),
    Position(9000.0,	0.4671000),
    Position(10000.0,	0.4135000),
    Position(15000.0,	0.1948000),
    Position(20000.0,	0.0889100),
    Position(25000.0,	0.0400800),
    Position(30000.0,	0.0184100),
    Position(40000.0,	0.0039960),
    Position(50000.0,	0.0010270),
    Position(60000.0,	0.0003097),
    Position(70000.0,	0.0000828),
    Position(80000.0,	0.0000185)};

Position gravity[14] = {
    Position(0.0,	-9.807),
    Position(1000.0,	-9.804),
    Position(2000.0,	-9.801),
    Position(3000.0,	-9.797),
    Position(4000.0,	-9.794),
    Position(5000.0,	-9.791),
    Position(6000.0,	-9.788),
    Position(7000.0,	-9.785),
    Position(8000.0,	-9.782),
    Position(9000.0,	-9.779),
    Position(10000.0,	-9.776),
    Position(15000.0,	-9.761),
    Position(20000.0,	-9.745),
    Position(25000.0,	-9.730)};

/************************************************
 * COMPUTE LINEAR INTERPOLATION
 * Given two points and a partial middle point,
 * determine the entirety of the middle point
 *
 * (x - x0) / (y - y0) =  (x1 - x0) / (y1 - y0)
 * OR
 * y = ( (x - x0) * (y1 - y0) ) / (x1 - x0) + y0
 *
 * INPUT
 *    p0 : position that comes first (x0,y0)
 *    p1 : position that comes after (x1,y1)
 *    x  : known part of middle point
 * OUTPUT
 *    y  : unknown part of middle point
 ***********************************************/
double linearInterpolation(const Position& p0, const Position& p1, double x)
{
    double y = (((x - p0.getMetersX()) * (p1.getMetersY() - p0.getMetersY())) / (p1.getMetersX() - p0.getMetersX())) + p0.getMetersY();
    return y;
}

double pointfinder(const Position data[], double value)
{
    
    int i = 0;
    while (value >= data[i].getMetersX())
    {
        i++;
    }
    double y = linearInterpolation(data[i - 1], data[i], value);
    return y;
}

int main()
{
    // Prompt for input and variables to be computed
    double dx ;
    double dy ;
    double x = 0.0;
    double angle = 75.0;
    double t = .01;               //time interval
    double aRadians = degreestoRadians(angle);            // Angle in radians
    double ddx;                 // Total horizontal acceleration
    double ddy;                 // Total vertical acceleration
    double v = 827.0;                   // Total velocity
    double s = 0.0;                   // seconds passed
    double area = circleArea(DIAMETER / 2);
    double dragf;
    Position current;
    Position last;

    dx = horizontalComponent(aRadians, v); 
    dy = verticalComponent(aRadians, v);  


    
    while (current.getMetersY() >= 0) 
    {
        last = current;
        v = pythagoreanTheorem(dx, dy); 
        aRadians = anglefromComponents(dx, dy); 
        dragf = dragForce(pointfinder(drag, (v / pointfinder(sound, current.getMetersY()))), pointfinder(density, current.getMetersY()), v, area);
        ddx = horizontalComponent(aRadians, dragf);
        ddy = pointfinder(gravity, current.getMetersY()) + verticalComponent(aRadians, dragf);
        dx = computeVelocity(dx, ddx, t); 
        dy = computeVelocity(dy, ddy, t);
        current.setMetersX(ComputeDistance(current.getMetersX(), dx, ddx, t));
        current.setMetersY(ComputeDistance(current.getMetersY(), dy, ddy, t));
        s += t;
        
    }
    x = linearInterpolation(current.getReverse(), last.getReverse(), 0);
    // Output
    cout.setf(ios::fixed | ios::showpoint); 
    cout.precision(1);
    cout << "Distance : " << x << "m  Hangtime: " << s << "s\n";

}

