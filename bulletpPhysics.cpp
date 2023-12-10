/***********************************************************************
 
 ************************************************************************/

#include "bulletPhysics.h"

using namespace std;

void physics::setPosition(Position pos)
{
    current = pos;
}

double physics::getAngleDegrees()
{
    double pi = 22.0 / 7.0; 
    double a = angle / (2 * pi) * 360;
    return a; 
}

void physics::changeAngle(double change)
{
    //keep angle between 0 and 360
    double pi = 22.0 / 7.0;
    angle += change;
    if (angle >= pi)
        angle -= 2 * pi;
    if (angle < -pi)
        angle += 2 * pi;
}

double physics::getAngle()
{
    return angle;
}

Position physics::getPosition()
{
    return current;
}

double physics::getTime()
{
    return s;
}

double physics::getBulletAngle()
{
    return bulletAngle;
}

void physics::hitGround(double elevation)
{
    current.setMetersX(linearInterpolation(current.getReverse(), last.getReverse(), elevation));
    current.setMetersY(elevation);
}

Position physics::pointOfImpactX()
{
    return Position(((current.getMetersX() + last.getMetersX()) / 2.0), 0.0);
}

double physics::getDistance(Position pos)
{
    double difference = current.getMetersX() - pos.getMetersX();
    if (difference < 0.0)
    {
        difference *= -1.0;
    }
    return difference;
}

double physics::getSpeed()
{
    return v;
}

void physics::reset(Position pos)
{
    current = pos; 
    dx = 0.0;
    dy = 0.0;
    ddx = 0.0;
    ddy = 0.0;
    v = 827.0; 
    s = 0.0;
}

void physics::move()
{
    
    if (s == 0.0)
    {
        bulletAngle = angle;
        dx = horizontalComponent(bulletAngle, v);
        dy = verticalComponent(bulletAngle, v);
    }
    last = current;
    dragf = dragForce(pointfinder(drag, (v / pointfinder(sound, current.getMetersY()))), pointfinder(density, current.getMetersY()), v, area);
    ddx = horizontalComponent(bulletAngle, dragf);
    ddy = pointfinder(gravity, current.getMetersY()) + verticalComponent(bulletAngle, dragf);
    dx = computeVelocity(dx, ddx, t);
    dy = computeVelocity(dy, ddy, t);
    v = pythagoreanTheorem(dx, dy);
    bulletAngle = anglefromComponents(dx, dy); 
    current.setMetersX(ComputeDistance(current.getMetersX(), dx, ddx, t));
    current.setMetersY(ComputeDistance(current.getMetersY(), dy, ddy, t));
    s += t;
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
double physics::horizontalComponent(double angle, double total)
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
double physics::verticalComponent(double angle, double total)
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
double physics::computeVelocity(double velocity, double acceleration, double time)
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
double physics::pythagoreanTheorem(double horizontal, double vertical)
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
double physics::anglefromComponents(double dx, double dy)
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

double physics::ComputeDistance(double originalPosition, double velocity, double acceleration, double time)
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
double physics::circleArea(double r)
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
double physics::newtonsLaw(double item1, double item2, bool mult)
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
double physics::dragForce(double drag, double density, double v, double area)
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
double physics::linearInterpolation(const Position& p0, const Position& p1, double x)
{
    double y = (((x - p0.getMetersX()) * (p1.getMetersY() - p0.getMetersY())) / (p1.getMetersX() - p0.getMetersX())) + p0.getMetersY();
    return y;
}

double physics::pointfinder(const Position data[], double value)
{
    
    int i = 0;
    double y;

    if (value <= data[i].getMetersX())
    {
        y = data[i].getMetersY();
    }

    else if (value >= data[sizeof(data)].getMetersX())
    {
        y = data[sizeof(data)].getMetersY();
    }

    else
    {
        while (value >= data[i].getMetersX())
        {
            i++;
        }
        y = linearInterpolation(data[i - 1], data[i], value);
    }

    return y;
}