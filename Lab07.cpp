/*************************************************************
 * 1. Name:
 *      Austin Jesperson
 *      Brighton Gold
 * 2. Assignment Name:
 *      M777 Howitzer Final Code
 * 3. Assignment Description:
 *      Simulate firing the M777 howitzer 15mm artillery piece
 * 4. What was the hardest part? Be as specific as possible.
 *      moving the calculations into the simlation
 * 5. How long did it take for you to complete the assignment?
 *      4 hours
 *****************************************************************/

#include <cassert>      // for ASSERT
#include "uiInteract.h" // for INTERFACE
#include "uiDraw.h"     // for RANDOM and DRAW*
#include "ground.h"     // for GROUND
#include "position.h"   // for POSITION
#include "bulletPhysics.h"
#include <queue>
using namespace std;

/*************************************************************************
 * Demo
 * Test structure to capture the LM that will move around the screen
 *************************************************************************/
class Demo
{
public:
    Demo(Position ptUpperRight) :
        ptUpperRight(ptUpperRight),
        ground(ptUpperRight),
        active(false),
        ptText(ptUpperRight)
   {
      // Set the horizontal position of the howitzer. This should be random.
      ptHowitzer.setPixelsX(random(150.0, Position(ptUpperRight).getPixelsX() - 150.0));
      
      // Generate the ground and set the vertical position of the howitzer.
      ground.reset(ptHowitzer);
      ptHowitzer.setMetersY(ground.getElevationMeters(ptHowitzer));
      bullet.setPosition(Position(ptHowitzer.getMetersX(), ground.getElevationMeters(ptHowitzer)));
      ptText.addPixelsX(-130);
      ptText.addPixelsY(-20);
      // This is to make the bullet travel across the screen. Notice how there are 
      // 20 pixels, each with a different age. This gives the appearance
      // of a trail that fades off in the distance.
      /*for (int i = 0; i < 20; i++)
      {
         projectilePath[i].setPixelsX((double)i * 2.0);
         projectilePath[i].setPixelsY(ptUpperRight.getPixelsY() / 1.5);
      }*/
   }

   Ground ground;                 // the ground
   queue<Position> projectilePath;  // path of the projectile  
   Position  ptHowitzer;          // location of the howitzer
   Position  ptUpperRight;        // size of the screen
   physics   bullet;
   Position  ptText;
   bool active;
};

/*************************************
 * All the interesting work happens here, when
 * I get called back from OpenGL to draw a frame.
 * When I am finished drawing, then the graphics
 * engine will wait until the proper amount of
 * time has passed and put the drawing on the screen.
 **************************************/
void callBack(const Interface* pUI, void* p)
{
   // the first step is to cast the void pointer into a game object. This
   // is the first step of every single callback function in OpenGL. 
   Demo* pDemo = (Demo*)p;
   ogstream gout(Position(10.0, pDemo->ptUpperRight.getPixelsY() - 20.0));
   
   // fire that gun, start the simulation
   if (pUI->isSpace())
       pDemo->active = true;
       

   if (pDemo->active)
   {
       
        
       if (pDemo->bullet.getPosition().getMetersY() >= pDemo->ground.getElevationMeters(pDemo->bullet.getPosition()))
       {
           pDemo->bullet.move();

           // draw the ground first
           pDemo->ground.draw(gout);

           // draw the howitzer
           gout.drawHowitzer(pDemo->ptHowitzer, pDemo->bullet.getAngle(), pDemo->bullet.getTime());
            if (pDemo->projectilePath.size() <= 20)
            {
                pDemo->projectilePath.push(pDemo->bullet.getPosition());
            }
            else
            {
                pDemo->projectilePath.pop();
                pDemo->projectilePath.push(pDemo->bullet.getPosition());
            }
           // draw the projectile
           queue<Position> temp = pDemo->projectilePath;
           while (!temp.empty()) 
           {
               gout.drawProjectile(temp.front(), 0.5 * (double)(0.5 * temp.size()));
               temp.pop();
           }


           // draw some text on the screen

           gout.setf(ios::fixed | ios::showpoint);
           gout.precision(1);
           gout.setPosition(pDemo->ptText);
           gout << "altitude: "
               << pDemo->bullet.getPosition().getMetersY() - pDemo->ground.getElevationMeters(pDemo->bullet.getPosition())
               << "m\nspeed: " 
               << pDemo->bullet.getSpeed()
               << "m/s\ndistance: "
               << pDemo->bullet.getDistance(pDemo->ptHowitzer)
               << "m\nhang time: "
               << pDemo->bullet.getTime()
               << "s";
       }
       else
       {
           pDemo->bullet.hitGround(pDemo->ground.getElevationMeters(pDemo->bullet.pointOfImpactX()));
           pDemo->active = false;
           pDemo->projectilePath.push(pDemo->bullet.getPosition());

           //empty queue
           while (! pDemo->projectilePath.empty())
           {
               queue<Position> temp = pDemo->projectilePath;
               while (! temp.empty())
               {
                   gout.drawProjectile(temp.front(), 0.5 * (double)(0.5 * temp.size()));
                   temp.pop();
               }
               pDemo->projectilePath.pop();
           }
           //check if the target is hit
           //cout << computeDistance(pDemo->bullet.getPosition(), pDemo->ground.getTarget()) << endl;
           if (computeDistance(pDemo->bullet.getPosition(), pDemo->ground.getTarget()) <= 200.0)
           {
               pDemo->ptHowitzer.setPixelsX(random(150.0, Position(pDemo->ptUpperRight).getPixelsX() - 150.0));
               pDemo->ground.reset(pDemo->ptHowitzer);
               pDemo->ptHowitzer.setMetersY(pDemo->ground.getElevationMeters(pDemo->ptHowitzer));
               pDemo->bullet.reset(pDemo->ptHowitzer); 
           }
       }
        
   }
   else
   {
       //move a lot
       if (pUI->isRight())
           {
               pDemo->bullet.changeAngle(0.05);
               pDemo->bullet.reset(pDemo->ptHowitzer);
           }
       if (pUI->isLeft())
           {
               pDemo->bullet.changeAngle(-0.05);
               pDemo->bullet.reset(pDemo->ptHowitzer);
           }

       // move by a little
       if (pUI->isUp())
           {
               pDemo->bullet.changeAngle(0.003);
               pDemo->bullet.reset(pDemo->ptHowitzer);
           }
       if (pUI->isDown())
           {
               pDemo->bullet.changeAngle(-0.003);
               pDemo->bullet.reset(pDemo->ptHowitzer);
           }

       // draw the ground first
       pDemo->ground.draw(gout);

       // draw the howitzer
       gout.drawHowitzer(pDemo->ptHowitzer, pDemo->bullet.getAngle(), pDemo->bullet.getTime());

       // draw the projectile
       //for (int i = 0; i < 20; i++)
          //gout.drawProjectile(pDemo->projectilePath[i], 0.5 * (double)i);
       gout.drawProjectile(pDemo->bullet.getPosition());

       // draw some text on the screen
       gout.setf(ios::fixed | ios::showpoint);
       gout.precision(1);
       gout.setPosition(pDemo->ptText);
       gout << "Angle: "
           << pDemo->bullet.getAngleDegrees() << " Degrees    "; 
   }

   
}

double Position::metersFromPixels = 40.0;

/*********************************
 * Initialize the simulation and set it in motion
 *********************************/
#ifdef _WIN32_X
#include <windows.h>
int WINAPI wWinMain(
   _In_ HINSTANCE hInstance,
   _In_opt_ HINSTANCE hPrevInstance,
   _In_ PWSTR pCmdLine,
   _In_ int nCmdShow)
#else // !_WIN32
int main(int argc, char** argv)
#endif // !_WIN32
{
   // Initialize OpenGL
   Position ptUpperRight;
   ptUpperRight.setPixelsX(700.0);
   ptUpperRight.setPixelsY(500.0);
   Position().setZoom(40.0 /* 42 meters equals 1 pixel */);
   Interface ui(0, NULL,
      "Demo",   /* name on the window */
      ptUpperRight);

   // Initialize the demo
   Demo demo(ptUpperRight);

   // set everything into action
   ui.run(callBack, &demo);


   return 0;
}
