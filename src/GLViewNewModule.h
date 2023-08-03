#pragma once

#include "GLView.h"
#include "NathanGUI.h"

#include "NetMsg.h"
#include "NetMessengerClient.h"
#include "NetMsgCreateWO.h"
#include "NathanMsg.h"

#include "irrKlang.h"


namespace Aftr
{
    class CameraStandard;

/**
   \class GLViewNewModule
   \author Scott Nykl 
   \brief A child of an abstract GLView. This class is the top-most manager of the module.

   Read \see GLView for important constructor and init information.

   \see GLView

    \{
*/

class GLViewNewModule : public GLView
{
public:
   static GLViewNewModule* New( const std::vector< std::string >& outArgs );
   virtual ~GLViewNewModule();
   virtual void updateWorld(); ///< Called once per frame
   virtual void loadMap(); ///< Called once at startup to build this module's scene
   virtual void createNewModuleWayPoints();
   virtual void onResizeWindow( GLsizei width, GLsizei height );
   virtual void onMouseDown( const SDL_MouseButtonEvent& e );
   virtual void onMouseUp( const SDL_MouseButtonEvent& e );
   virtual void onMouseMove( const SDL_MouseMotionEvent& e );
   virtual void onKeyDown( const SDL_KeyboardEvent& key );
   virtual void onKeyUp( const SDL_KeyboardEvent& key );

   NathanGUI* theGUI; // GUI
   std::vector<std::string> course; // holds locations of objects so that they can be replaced automatically
   std::vector<Vector> locations;

   // user vehicles
   WO* redCube;
   WO* jet;
   WO* spaceShip;
   WO* user;

   WO* startingLocation;// starting location
   WO* startingLine; // starting line
   WO* marker1;

   WO* holder; // for rotation
   WO* checkpointProp2;
   WO* checkpointProp2b;
   WO* checkpointProp3;

   bool firstCheck = false;
   bool secondCheck = false;
   bool thirdCheck = false;
   bool fourthCheck = false;


   bool pressW;
   bool pressA;
   bool pressS;
   bool pressD;
   bool pressSpace;
   bool pressLshift;
   bool pressLctrl;

   int turn = 0;
   int rotateUp = 0;
   int rotateDown = 0;

   float speed = 2;
   float boost = 5;

   Mat4 vehicleIPose;
   Mat4 camIPose;

   Mat4 jetPose;
   Mat4 spaceShipPose;

   // space object functions
   void placeAsteroid(Vector location);
   void buildCourseAsteroidGuide();
   void placeCheckpointMarker(Vector location);
   void setVehicle();
   void unlock();
   void multiplayerReset();

   //multiplayer stuff
   NetMessengerClient* client;

   //noise
   irrklang::ISoundEngine* backgroundMusic;
   std::string background;

   irrklang::ISoundEngine* vehicleDriving;
   //drivingSound = vehicleDriving->play2D(driving.c_str(), true, false, true);
   irrklang::ISound* drivingSound;
   std::string driving;

   irrklang::ISoundEngine* vehicleBoosting;
   irrklang::ISound* boostSound;
   std::string boosting;
   
   irrklang::ISoundEngine* victorySound;
   irrklang::ISound* winSound;
   std::string vicSound;

   irrklang::ISoundEngine* countdownEngine;
   irrklang::ISound* countdownSound;
   std::string countdownString;

protected:
   GLViewNewModule( const std::vector< std::string >& args );
   virtual void onCreate();   
};

/** \} */

} //namespace Aftr
