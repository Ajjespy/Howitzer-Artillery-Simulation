#pragma once

#include <iostream>
#include "position.h"

using namespace std;

class physics
{
public:
   physics()         : current(), last(), dx(0.0), dy(0.0), angle(0.0), t(0.5), ddx(0.0), ddy(0.0), v(827.0), s(0.0), area(0.0188424), dragf(0.0), WEIGHT(46.7), bulletAngle(0.0){}
   physics(Position start, double angle): current(start), last(), dx(0.0), dy(0.0), angle(angle), t(0.5), ddx(0.0), ddy(0.0), v(827.0), s(0.0), area(0.0188424), dragf(0.0), WEIGHT(46.7), bulletAngle(0.0){}
   void setPosition(Position pos);
   void changeAngle(double change);
   double getAngle();
   double getBulletAngle();
   Position getPosition();
   void move();
   double getTime();
   void hitGround(double elevation);
   Position pointOfImpactX();
   void reset(Position pos);
   double getDistance(Position pos);
   double getSpeed();
   double getAngleDegrees();

private:
   double horizontalComponent(double angle, double total);
   double verticalComponent(double angle, double total);
   double computeVelocity(double velocity, double acceleration, double time);
   double pythagoreanTheorem(double horizontal, double vertical);
   double anglefromComponents(double dx, double dy);
   double ComputeDistance(double originalPosition, double velocity, double acceleration, double time);
   double circleArea(double r);
   double newtonsLaw(double item1, double item2, bool mult);
   double dragForce(double drag, double density, double v, double area);
   double linearInterpolation(const Position& p0, const Position& p1, double x);
   double pointfinder(const Position data[], double value);

   Position current ;
   Position last;
   double dx ;
   double dy ;
   double angle ;
   double bulletAngle;
   double t ;               //time interval
   double ddx;                 // Total horizontal acceleration
   double ddy;                 // Total vertical acceleration
   double v;                   // Total velocity
   double s;                   // seconds passed
   const double area;
   double dragf;
   const double WEIGHT;

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
    Position(40000.0,	324.0),};

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

    /*int main()
{
    double dx ;
    double dy ;
    double x = 0.0;
    double angle = 75.0;
    double t = .01;               //time interval
    double ddx;                 // Total horizontal acceleration
    double ddy;                 // Total vertical acceleration
    double v = 827.0;                   // Total velocity
    double s = 0.0;                   // seconds passed
    double area;
    double dragf;
    Position current;
    Position last;

    dx = horizontalComponent(angle, v);  
    dy = verticalComponent(angle, v);   


    
    while (current.getMetersY() >= 0) 
    {
        last = current;
        v = pythagoreanTheorem(dx, dy); 
        angle = anglefromComponents(dx, dy); 
        dragf = dragForce(pointfinder(drag, (v / pointfinder(sound, current.getMetersY()))), pointfinder(density, current.getMetersY()), v, area);
        ddx = horizontalComponent(angle , dragf);
        ddy = pointfinder(gravity, current.getMetersY()) + verticalComponent(angle, dragf);
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

   }*/
}; 


