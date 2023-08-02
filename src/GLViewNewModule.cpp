#include "GLViewNewModule.h"

#include "WorldList.h" //This is where we place all of our WOs
#include "ManagerOpenGLState.h" //We can change OpenGL State attributes with this
#include "Axes.h" //We can set Axes to on/off with this
#include "PhysicsEngineODE.h"

//Different WO used by this module
#include "WO.h"
#include "WOStatic.h"
#include "WOStaticPlane.h"
#include "WOStaticTrimesh.h"
#include "WOTrimesh.h"
#include "WOHumanCyborg.h"
#include "WOHumanCal3DPaladin.h"
#include "WOWayPointSpherical.h"
#include "WOLight.h"
#include "WOSkyBox.h"
#include "WOCar1970sBeater.h"
#include "Camera.h"
#include "CameraStandard.h"
#include "CameraChaseActorSmooth.h"
#include "CameraChaseActorAbsNormal.h"
#include "CameraChaseActorRelNormal.h"
#include "Model.h"
#include "ModelDataShared.h"
#include "ModelMesh.h"
#include "ModelMeshDataShared.h"
#include "ModelMeshSkin.h"
#include "WONVStaticPlane.h"
#include "WONVPhysX.h"
#include "WONVDynSphere.h"
#include "WOImGui.h" //GUI Demos also need to #include "AftrImGuiIncludes.h"
#include "AftrImGuiIncludes.h"
#include "AftrGLRendererBase.h"


#include <GL/glew.h>

#include<fstream>



using namespace Aftr;

GLViewNewModule* GLViewNewModule::New( const std::vector< std::string >& args )
{
   GLViewNewModule* glv = new GLViewNewModule( args );
   glv->init( Aftr::GRAVITY, Vector( 0, 0, -1.0f ), "aftr.conf", PHYSICS_ENGINE_TYPE::petODE );
   glv->onCreate();
   return glv;
}


GLViewNewModule::GLViewNewModule( const std::vector< std::string >& args ) : GLView( args )
{
   //Initialize any member variables that need to be used inside of LoadMap() here.
   //Note: At this point, the Managers are not yet initialized. The Engine initialization
   //occurs immediately after this method returns (see GLViewNewModule::New() for
   //reference). Then the engine invoke's GLView::loadMap() for this module.
   //After loadMap() returns, GLView::onCreate is finally invoked.

   //The order of execution of a module startup:
   //GLView::New() is invoked:
   //    calls GLView::init()
   //       calls GLView::loadMap() (as well as initializing the engine's Managers)
   //    calls GLView::onCreate()

   //GLViewNewModule::onCreate() is invoked after this module's LoadMap() is completed.
}


void GLViewNewModule::onCreate()
{
   //GLViewNewModule::onCreate() is invoked after this module's LoadMap() is completed.
   //At this point, all the managers are initialized. That is, the engine is fully initialized.

   if( this->pe != NULL )
   {
      //optionally, change gravity direction and magnitude here
      //The user could load these values from the module's aftr.conf
      this->pe->setGravityNormalizedVector( Vector( 0,0,-1.0f ) );
      this->pe->setGravityScalar( Aftr::GRAVITY );
   }
   this->setActorChaseType( STANDARDEZNAV ); //Default is STANDARDEZNAV mode
   //this->setNumPhysicsStepsPerRender( 0 ); //pause physics engine on start up; will remain paused till set to 1
}


GLViewNewModule::~GLViewNewModule()
{
   //Implicitly calls GLView::~GLView()
}


void GLViewNewModule::updateWorld()
{
    GLView::updateWorld(); //Just call the parent's update world first.
    //If you want to add additional functionality, do it after
    //this call.
    
    //*****************Multiplayer Stuff********************************
    if (theGUI->firstPlayer == true && theGUI->connected == false)
    {
        std::cout << "connection" << std::endl;
        client = NetMessengerClient::New("127.0.0.1", "12685");
        theGUI->connected = true;
    }

    if (theGUI->secondPlayer == true && theGUI->connected == false)
    {
        std::cout << "connection" << std::endl;
        client = NetMessengerClient::New("127.0.0.1", "12683");
        theGUI->connected = true;
    }

    if (theGUI->jet == true && theGUI->jetTaken == false && theGUI->vehicleSet == false && (theGUI->firstPlayer == true || theGUI->secondPlayer == true))
    {
        theGUI->vehicleSet = true;
        NathanMsg msg;
        msg.jetGone = true;
        client->sendNetMsgSynchronousTCP(msg);
    }

    if (theGUI->spaceShip == true && theGUI->spaceShipTaken == false && theGUI->vehicleSet == false && (theGUI->firstPlayer == true || theGUI->secondPlayer == true))
    {
        theGUI->vehicleSet = true;
        NathanMsg msg; 
        msg.spaceShipGone = true;
        client->sendNetMsgSynchronousTCP(msg);
    }
    //*****************Multiplayer Stuff******************************** 
 
    // Reset game
    if (theGUI->reset == true)
    {
        firstCheck = false;
        secondCheck = false;
        thirdCheck = false;
        fourthCheck = false;
        theGUI->reset = false;
        theGUI->spaceShip = false;
        theGUI->jet = false;
        theGUI->vehicleChosen = false;
        theGUI->currVehicle = "Current Vehicle: None";
        theGUI->countdownText = "GET READY FOR THE NEXT RACE!!!";
        theGUI->winner = "Winner: -----";
        //unlock();
        multiplayerReset();

        if (theGUI->meReset == true && (theGUI->firstPlayer == true || theGUI->secondPlayer == true))
        {
            NathanMsg msg;
            msg.resetBoth = true;
            client->sendNetMsgSynchronousTCP(msg);
            theGUI->meReset = false;
        }
    }

    // ********************* Lock and unlock racer ***************************
    if (theGUI->lockRacer == true && theGUI->vehicleChosen == true)
    {
        cam->setPose(camIPose);
        setVehicle();
        user->setPose(vehicleIPose);
        redCube->setPose(vehicleIPose);
        redCube->setParentWorldObject(cam);
        redCube->lockWRTparent_using_current_relative_pose();
        theGUI->lockRacer = false;

        if ((theGUI->firstPlayer == true || theGUI->secondPlayer == true) && theGUI->vSet == false)
        {
            theGUI->vSet = true;
            NathanMsg msg;
            msg.startRace = true;
            client->sendNetMsgSynchronousTCP(msg);
        }
    }
    if (theGUI->unlockRacer == true)
    {
        cam->setPose(camIPose);
        user->setPose(vehicleIPose);
        redCube->setPose(vehicleIPose);

        //could cause issues
        jet->setPose(jetPose);
        spaceShip->setPose(spaceShipPose);

        redCube->unLockWRTparent();
        theGUI->unlockRacer = false;
    }

    if (theGUI->raceStart == true)
    {
        theGUI->countdown -= 0.01667;
        theGUI->countdownText = std::to_string(theGUI->countdown);

        if (theGUI->countdown <= 0)
        {
            theGUI->countdownText = "GO!!!";
            theGUI->onGoing = true;
            theGUI->raceStart = false;
        }
    }
    // ********************* Race Timer ***************************
    if (theGUI->onGoing == true)
    {
        theGUI->elapsedTime += 0.01667;
    }
    // ********************* Course Checkpoints ***************************
    if (cam->getPosition().x > 411 && cam->getPosition().x < 1130 && cam->getPosition().y > -1444 && cam->getPosition().y < -744
        && cam->getPosition().z > -45 && cam->getPosition().z < 700 && firstCheck == false)
    {
        firstCheck = true;
        std::cout << "here" << std::endl;
    }
    if (cam->getPosition().x > -995 && cam->getPosition().x < 272 && cam->getPosition().y > -3749 && cam->getPosition().y < -3027
        && cam->getPosition().z > 290 && cam->getPosition().z < 1009 && secondCheck == false && firstCheck == true)
    {
        secondCheck = true;
        std::cout << "here2" << std::endl;
    }
    if (cam->getPosition().x > -3730 && cam->getPosition().x < -2440 && cam->getPosition().y > -3570 && cam->getPosition().y < -2846
        && cam->getPosition().z > 273 && cam->getPosition().z < 1000 && thirdCheck == false && secondCheck == true)
    {
        thirdCheck = true;
        std::cout << "here3" << std::endl;
    }
    if (cam->getPosition().x > -2262 && cam->getPosition().x < -1400 && cam->getPosition().y > -2000 && cam->getPosition().y < -1245
        && cam->getPosition().z > 0 && cam->getPosition().z < 846 && fourthCheck == false && thirdCheck == true)
    {
        fourthCheck = true;
        std::cout << "here4" << std::endl;
    }
    // race finishes here
    if (cam->getPosition().x > 110 && cam->getPosition().x < 150 && cam->getPosition().y > -77 && cam->getPosition().y < 85
        && cam->getPosition().z > -25 && cam->getPosition().z < 65 && theGUI->raceFinshed == false && fourthCheck == true)
    {
        theGUI->raceFinshed = true; 
        theGUI->onGoing = false;
        theGUI->unlockRacer = true;
        theGUI->countdownText = "GET READY FOR THE NEXT RACE!!!";
        theGUI->countdown = 3;

        if (theGUI->bestTime == 0)
        {
            theGUI->bestTime = theGUI->elapsedTime;
        }

        if (theGUI->elapsedTime < theGUI->bestTime)
        {
            theGUI->bestTime = theGUI->elapsedTime;
        }
        theGUI->elapsedTime = 0;
        theGUI->startReset = "Start";
        theGUI->winner = "Winner: YOU!!!";

        if (theGUI->firstPlayer == true || theGUI->secondPlayer == true)
        {
            NathanMsg msg;
            msg.victory = true;
            msg.bestTime = theGUI->bestTime;
            client->sendNetMsgSynchronousTCP(msg);
        }
    }
    // ********************* Course Checkpoints ***************************
    if (theGUI->raceFinshed == true)
    {
        firstCheck = false;
        secondCheck = false;
        thirdCheck = false;
        fourthCheck = false;
        theGUI->raceFinshed = false;
        theGUI->jet = false;
        theGUI->spaceShip = false;
        theGUI->vehicleChosen = false;
        theGUI->currVehicle = "Current Vehicle: None";
        //unlock();
        multiplayerReset();
    }
   //************ Vehicle Controls ******************
   if (pressW == true && theGUI->onGoing == true) 
   {
       auto move = cam->getPosition();
       move.x += user->getLookDirection().x * speed;
       move.y += user->getLookDirection().y * speed;
       move.z += user->getLookDirection().z * speed;
       cam->setPosition(move);
       user->setPosition(redCube->getPosition());

       if (theGUI->firstPlayer == true || theGUI->secondPlayer == true)
       {
           NathanMsg msg;
           msg.otherVehicle = true;
           msg.xPos = move.x;
           msg.yPos = move.y;
           msg.zPos = move.z;
           client->sendNetMsgSynchronousTCP(msg);
       }
   }
   if (pressA == true && theGUI->onGoing == true)
   {
       cam->rotateAboutGlobalZ(-0.05);
       user->rotateAboutGlobalZ(-0.05);
       if (theGUI->firstPlayer == true || theGUI->secondPlayer == true)
       {
           NathanMsg msg;
           msg.otherVehicleRot = true;
           msg.zRot = -0.05;
           client->sendNetMsgSynchronousTCP(msg);
       }
   }
   if (pressS == true && theGUI->onGoing == true)
   {
       auto move = cam->getPosition();
       move.x -= user->getLookDirection().x * speed;
       move.y -= user->getLookDirection().y * speed;
       //move.z -= user->getLookDirection().z * speed;
       cam->setPosition(move);
       user->setPosition(redCube->getPosition());

       if (theGUI->firstPlayer == true || theGUI->secondPlayer == true)
       {
           NathanMsg msg;
           msg.otherVehicle = true;
           msg.xPos = move.x;
           msg.yPos = move.y;
           msg.zPos = move.z;
           client->sendNetMsgSynchronousTCP(msg);
       }
   }
   if (pressD == true && theGUI->onGoing == true)
   {
       cam->rotateAboutGlobalZ(0.05);
       user->rotateAboutGlobalZ(0.05);
       if (theGUI->firstPlayer == true || theGUI->secondPlayer == true)
       {
           NathanMsg msg;
           msg.otherVehicleRot = true;
           msg.zRot = 0.05;
           client->sendNetMsgSynchronousTCP(msg);
       }
   }
   if (pressSpace == true && theGUI->onGoing == true)
   {
       //cam->setPosition(cam->getPosition().x, cam->getPosition().y, cam->getPosition().z + 1);
       if (boost > 0)
       {
            boost -= 0.01667;
       }
       else
       {
           pressSpace = false;
           speed /= 2;
       }
   }
   else
   {
       if (boost <= 5)
       {
            boost += 0.01667;
       }
   }

   if (pressLshift == true && pressLctrl == false && theGUI->onGoing == true)
   {
       if (rotateUp < 40)
       {
           user->rotateAboutRelY(-0.02);
           if (theGUI->firstPlayer == true || theGUI->secondPlayer == true)
           {
               NathanMsg msg;
               msg.otherVehicleRotY = true;
               msg.yRot = -0.02;
               client->sendNetMsgSynchronousTCP(msg);
           }
           //cam->rotateAboutRelY(-0.02);
           //redCube->rotateAboutRelY(-0.02);
           rotateUp++;
       }
       //redCube->rotateAboutRelY(-0.25);
   }
   else if (pressLctrl == true && pressLshift == false && theGUI->onGoing == true)
   {
       if (rotateDown < 40)
       {
           user->rotateAboutRelY(0.02);
           //cam->rotateAboutRelY(0.02);
           //redCube->rotateAboutRelY(0.02);
           rotateDown++;
           if (theGUI->firstPlayer == true || theGUI->secondPlayer == true)
           {
               NathanMsg msg;
               msg.otherVehicleRotY = true;
               msg.yRot = 0.02;
               client->sendNetMsgSynchronousTCP(msg);
           }
       }
       //redCube->rotateAboutRelY(0.25);
   }
   else
   {
       if (rotateUp > 0)
       {
           user->rotateAboutRelY(0.02);
           if (theGUI->firstPlayer == true || theGUI->secondPlayer == true)
           {
               NathanMsg msg;
               msg.otherVehicleRotY = true;
               msg.yRot = 0.02;
               client->sendNetMsgSynchronousTCP(msg);
           }
           //cam->rotateAboutRelY(0.02);
           //redCube->rotateAboutRelY(0.02);
           rotateUp--;
       }
       if (rotateDown > 0)
       {
           user->rotateAboutRelY(-0.02);
           if (theGUI->firstPlayer == true || theGUI->secondPlayer == true)
           {
               NathanMsg msg;
               msg.otherVehicleRotY = true;
               msg.yRot = -0.02;
               client->sendNetMsgSynchronousTCP(msg);
           }
           //cam->rotateAboutRelY(-0.02);
           //redCube->rotateAboutRelY(-0.02);
           rotateDown--;
       }
   }
   //************ Vehicle Controls ******************

   theGUI->boostValue = "Boost: " + std::to_string(boost);
   if (boost >= 5)
   {
       theGUI->boostValue = "Boost: Max";
   }
   checkpointProp2->rotateAboutGlobalZ(400 * (PI / 100) * 0.0005);
   checkpointProp2b->rotateAboutGlobalZ(400 * (PI / 100) * 0.001);
   checkpointProp2b->moveRelative(checkpointProp2b->getLookDirection() * 0.01 * -500);
}


void GLViewNewModule::onResizeWindow( GLsizei width, GLsizei height )
{
   GLView::onResizeWindow( width, height ); //call parent's resize method.
}


void GLViewNewModule::onMouseDown( const SDL_MouseButtonEvent& e )
{
    //if (theGUI->onGoing == false)
    {
        GLView::onMouseDown(e);
    }
}


void GLViewNewModule::onMouseUp( const SDL_MouseButtonEvent& e )
{
   GLView::onMouseUp( e );
}


void GLViewNewModule::onMouseMove( const SDL_MouseMotionEvent& e )
{
   GLView::onMouseMove( e );
}


void GLViewNewModule::onKeyDown( const SDL_KeyboardEvent& key )
{
   GLView::onKeyDown( key );
   if( key.keysym.sym == SDLK_0 )
      this->setNumPhysicsStepsPerRender( 1 );

   if( key.keysym.sym == SDLK_w)
   {
       pressW = true;
   }
   if (key.keysym.sym == SDLK_a)
   {
       pressA = true;
   }
   if (key.keysym.sym == SDLK_s)
   {
       pressS = true;
   }
   if (key.keysym.sym == SDLK_d)
   {
       pressD = true; 
   }
   if (key.keysym.sym == SDLK_SPACE)
   {
       if (!pressSpace && boost >= 5)
       {
            pressSpace = true;
            speed *= 2;
       }
   }
   if (key.keysym.sym == SDLK_LSHIFT)
   {
       pressLshift = true;
   }
   if (key.keysym.sym == SDLK_LCTRL)
   {
       pressLctrl = true;
   }
   if (key.keysym.sym == SDLK_m)
   {
       auto curr = redCube->getLookDirection();
       std::cout << curr.x << std::endl;
       std::cout << curr.y << std::endl;
       std::cout << curr.z << std::endl;
       curr = cam->getPosition();
       std::cout << curr.x << std::endl;
       std::cout << curr.y << std::endl;
       std::cout << curr.z << std::endl;   
   }
   if (key.keysym.sym == SDLK_g)
   {
       placeAsteroid(cam->getPosition());

       /*for (size_t i = 0; i < locations.size(); i++)
       {
           std::cout << locations.at(i).toString() << std::endl;
       }*/
   }
   if (key.keysym.sym == SDLK_h)
   {
       /*td::ofstream outs;
       outs.open("route.txt");
       if (outs.fail())
       {
           std::cout << "Error: failed to open file" << std::endl;
           exit(0);
       }
       for (size_t i = 0; i < course.size(); i++)
       {
           outs << course.at(i) << std::endl;
       }
       outs.close();
       std::cout << "course saved" << std::endl;*/
       cam->setPosition(Vector(130, 3, 10));
       placeCheckpointMarker(cam->getPosition());
   }
}


void GLViewNewModule::onKeyUp( const SDL_KeyboardEvent& key )
{
   GLView::onKeyUp( key );

   if (key.keysym.sym == SDLK_w)
   {
       pressW = false;
   }
   if (key.keysym.sym == SDLK_a)
   {
       pressA = false;
   }
   if (key.keysym.sym == SDLK_s)
   {
       pressS = false;
   }
   if (key.keysym.sym == SDLK_d)
   {
       pressD = false;
   }
   if (key.keysym.sym == SDLK_SPACE)
   {
   }
   if (key.keysym.sym == SDLK_LSHIFT)
   {
       pressLshift = false;
   }
   if (key.keysym.sym == SDLK_LCTRL)
   {
       pressLctrl = false;
   }
   if (key.keysym.sym == SDLK_f)
   {
       redCube->setParentWorldObject(cam);
       redCube->lockWRTparent_using_current_relative_pose();
   }
}


void Aftr::GLViewNewModule::loadMap()
{
   this->worldLst = new WorldList(); //WorldList is a 'smart' vector that is used to store WO*'s
   this->actorLst = new WorldList();
   this->netLst = new WorldList();

   ManagerOpenGLState::GL_CLIPPING_PLANE = 1000.0;
   ManagerOpenGLState::GL_NEAR_PLANE = 0.1f;
   ManagerOpenGLState::enableFrustumCulling = false;
   Axes::isVisible = true;
   this->glRenderer->isUsingShadowMapping( false ); //set to TRUE to enable shadow mapping, must be using GL 3.2+

   //this->cam->setPosition( 5,15,15 );

   std::string shinyRedPlasticCube( ManagerEnvironmentConfiguration::getSMM() + "/models/cube4x4x4redShinyPlastic_pp.wrl" );
   std::string wheeledCar( ManagerEnvironmentConfiguration::getSMM() + "/models/rcx_treads.wrl" );
   std::string grass( ManagerEnvironmentConfiguration::getSMM() + "/models/grassFloor400x400_pp.wrl" );
   std::string human( ManagerEnvironmentConfiguration::getSMM() + "/models/human_chest.wrl" );
   std::string jet1(ManagerEnvironmentConfiguration::getSMM() + "/models/jet_wheels_down_PP.wrl");
   std::string spaceStation(ManagerEnvironmentConfiguration::getSMM() + "/models/spaceStation220x130x160.wrl");
   std::string spaceShip1(ManagerEnvironmentConfiguration::getSMM() + "/models/spaceShipSmall.wrl");

   
   std::string startingPillar(ManagerEnvironmentConfiguration::getLMM() + "/models/race_drag_start_and_finish_line.glb");
   std::string donut(ManagerEnvironmentConfiguration::getLMM() + "/models/donut.glb");
   std::string planetIce(ManagerEnvironmentConfiguration::getLMM() + "/models/Spacemodels/Planet Ice/planet_ice.3ds");
   std::string earth(ManagerEnvironmentConfiguration::getLMM() + "/models/Spacemodels/Planet Earth/planet_earth.3ds");
   std::string moon(ManagerEnvironmentConfiguration::getLMM() + "/models/moon.fbx");
   std::string gate(ManagerEnvironmentConfiguration::getLMM() + "/models/Gate/gate.3ds");
   std::string satelite(ManagerEnvironmentConfiguration::getLMM() + "/models/Spacemodels/Satellite/satellite.3ds");
   std::string station(ManagerEnvironmentConfiguration::getLMM() + "/models/strawberry/strawberry.3ds");

   //SkyBox Textures readily available
   std::vector< std::string > skyBoxImageNames; //vector to store texture paths
   //skyBoxImageNames.push_back( ManagerEnvironmentConfiguration::getSMM() + "/images/skyboxes/sky_water+6.jpg" );
   //skyBoxImageNames.push_back( ManagerEnvironmentConfiguration::getSMM() + "/images/skyboxes/sky_dust+6.jpg" );
   //skyBoxImageNames.push_back( ManagerEnvironmentConfiguration::getSMM() + "/images/skyboxes/sky_mountains+6.jpg" );
   //skyBoxImageNames.push_back( ManagerEnvironmentConfiguration::getSMM() + "/images/skyboxes/sky_winter+6.jpg" );
   //skyBoxImageNames.push_back( ManagerEnvironmentConfiguration::getSMM() + "/images/skyboxes/early_morning+6.jpg" );
   //skyBoxImageNames.push_back( ManagerEnvironmentConfiguration::getSMM() + "/images/skyboxes/sky_afternoon+6.jpg" );
   //skyBoxImageNames.push_back( ManagerEnvironmentConfiguration::getSMM() + "/images/skyboxes/sky_cloudy+6.jpg" );
   //skyBoxImageNames.push_back( ManagerEnvironmentConfiguration::getSMM() + "/images/skyboxes/sky_cloudy3+6.jpg" );
   //skyBoxImageNames.push_back( ManagerEnvironmentConfiguration::getSMM() + "/images/skyboxes/sky_day+6.jpg" );
   //skyBoxImageNames.push_back( ManagerEnvironmentConfiguration::getSMM() + "/images/skyboxes/sky_day2+6.jpg" );
   //skyBoxImageNames.push_back( ManagerEnvironmentConfiguration::getSMM() + "/images/skyboxes/sky_deepsun+6.jpg" );
   //skyBoxImageNames.push_back( ManagerEnvironmentConfiguration::getSMM() + "/images/skyboxes/sky_evening+6.jpg" );
   //skyBoxImageNames.push_back( ManagerEnvironmentConfiguration::getSMM() + "/images/skyboxes/sky_morning+6.jpg" );
   //skyBoxImageNames.push_back( ManagerEnvironmentConfiguration::getSMM() + "/images/skyboxes/sky_morning2+6.jpg" );
   //skyBoxImageNames.push_back( ManagerEnvironmentConfiguration::getSMM() + "/images/skyboxes/sky_noon+6.jpg" );
   //skyBoxImageNames.push_back( ManagerEnvironmentConfiguration::getSMM() + "/images/skyboxes/sky_warp+6.jpg" );
   //skyBoxImageNames.push_back( ManagerEnvironmentConfiguration::getSMM() + "/images/skyboxes/space_Hubble_Nebula+6.jpg" );
   //skyBoxImageNames.push_back( ManagerEnvironmentConfiguration::getSMM() + "/images/skyboxes/space_gray_matter+6.jpg" );
   //skyBoxImageNames.push_back( ManagerEnvironmentConfiguration::getSMM() + "/images/skyboxes/space_easter+6.jpg" );
   //skyBoxImageNames.push_back( ManagerEnvironmentConfiguration::getSMM() + "/images/skyboxes/space_hot_nebula+6.jpg" );
   //skyBoxImageNames.push_back( ManagerEnvironmentConfiguration::getSMM() + "/images/skyboxes/space_ice_field+6.jpg" );
   //skyBoxImageNames.push_back( ManagerEnvironmentConfiguration::getSMM() + "/images/skyboxes/space_lemon_lime+6.jpg" );
   //skyBoxImageNames.push_back( ManagerEnvironmentConfiguration::getSMM() + "/images/skyboxes/space_milk_chocolate+6.jpg" );
   //skyBoxImageNames.push_back( ManagerEnvironmentConfiguration::getSMM() + "/images/skyboxes/space_solar_bloom+6.jpg" );
   skyBoxImageNames.push_back( ManagerEnvironmentConfiguration::getSMM() + "/images/skyboxes/space_thick_rb+6.jpg" );

   {
      //Create a light
      float ga = 0.1f; //Global Ambient Light level for this module
      ManagerLight::setGlobalAmbientLight( aftrColor4f( ga, ga, ga, 1.0f ) );
      WOLight* light = WOLight::New();
      light->isDirectionalLight( true );
      light->setPosition( Vector( 0, 0, 100 ) );
      //Set the light's display matrix such that it casts light in a direction parallel to the -z axis (ie, downwards as though it was "high noon")
      //for shadow mapping to work, this->glRenderer->isUsingShadowMapping( true ), must be invoked.
      light->getModel()->setDisplayMatrix( Mat4::rotateIdentityMat( { 0, 1, 0 }, 90.0f * Aftr::DEGtoRAD ) );
      light->setLabel( "Light" );
      worldLst->push_back( light );
   }
    
   {
      //Create the SkyBox
      WO* wo = WOSkyBox::New( skyBoxImageNames.at( 0 ), this->getCameraPtrPtr() );
      wo->setPosition( Vector( 0, 0, 0 ) );
      wo->setLabel( "Sky Box" );
      wo->renderOrderType = RENDER_ORDER_TYPE::roOPAQUE;
      worldLst->push_back( wo );
   }

   { 
      ////Create the infinite grass plane (the floor)
      WO* wo = WO::New( grass, Vector( 1, 1, 1 ), MESH_SHADING_TYPE::mstFLAT );
      wo->setPosition( Vector( 0, 0, 0 ) );
      wo->renderOrderType = RENDER_ORDER_TYPE::roOPAQUE;
      wo->upon_async_model_loaded( [wo]()
         {
            ModelMeshSkin& grassSkin = wo->getModel()->getModelDataShared()->getModelMeshes().at( 0 )->getSkins().at( 0 );
            grassSkin.getMultiTextureSet().at( 0 ).setTexRepeats( 5.0f );
            grassSkin.setAmbient( aftrColor4f( 0.4f, 0.4f, 0.4f, 1.0f ) ); //Color of object when it is not in any light
            grassSkin.setDiffuse( aftrColor4f( 1.0f, 1.0f, 1.0f, 1.0f ) ); //Diffuse color components (ie, matte shading color of this object)
            grassSkin.setSpecular( aftrColor4f( 0.4f, 0.4f, 0.4f, 1.0f ) ); //Specular color component (ie, how "shiney" it is)
            grassSkin.setSpecularCoefficient( 10 ); // How "sharp" are the specular highlights (bigger is sharper, 1000 is very sharp, 10 is very dull)
         } );
      wo->setLabel( "Grass" );
      worldLst->push_back( wo );
   }

   // player vehicle
    redCube = WO::New(shinyRedPlasticCube, Vector(1, 1, 1), MESH_SHADING_TYPE::mstAUTO);
    redCube->setPosition(0, 0, 0);
    redCube->renderOrderType = RENDER_ORDER_TYPE::roOPAQUE;
    worldLst->push_back(redCube);
    redCube->isVisible = false;

    jet = WO::New(jet1, Vector(1, 1, 1), MESH_SHADING_TYPE::mstAUTO);
    jet->setPosition(62, 0, 2);
    jet->renderOrderType = RENDER_ORDER_TYPE::roOPAQUE;
    worldLst->push_back(jet);

    spaceShip = WO::New(spaceShip1, Vector(1, 1, 1), MESH_SHADING_TYPE::mstAUTO);
    spaceShip->setPosition(62, 15, 2);
    spaceShip->renderOrderType = RENDER_ORDER_TYPE::roOPAQUE;
    worldLst->push_back(spaceShip);

    // space station
    startingLocation = WO::New(spaceStation, Vector(1, 1, 1), MESH_SHADING_TYPE::mstAUTO);
    startingLocation->setPosition(67, 175, 21);
    startingLocation->renderOrderType = RENDER_ORDER_TYPE::roOPAQUE;
    worldLst->push_back(startingLocation);

    //earth
    checkpointProp2 = WO::New(earth, Vector(3, 3, 3), MESH_SHADING_TYPE::mstAUTO);
    checkpointProp2->setPosition(-237, -3873, 851);
    checkpointProp2->renderOrderType = RENDER_ORDER_TYPE::roOPAQUE;
    worldLst->push_back(checkpointProp2);
    checkpointProp2->rotateAboutRelX(1);

    WO* checkpointProp2ba = WO::New(moon, Vector(0.1, 0.1, 0.1), MESH_SHADING_TYPE::mstAUTO);
    checkpointProp2ba->setPosition(-237, -3623, 851);
    checkpointProp2ba->renderOrderType = RENDER_ORDER_TYPE::roOPAQUE;
    checkpointProp2ba->upon_async_model_loaded([checkpointProp2ba]()
        {
            std::string texture(ManagerEnvironmentConfiguration::getLMM() + "/images/moon.jpg");
    ModelMeshSkin skin(ManagerTex::loadTexAsync(texture).value());
    skin.setMeshShadingType(MESH_SHADING_TYPE::mstAUTO);
    checkpointProp2ba->getModel()->getModelDataShared()->getModelMeshes().at(0)->addSkin(std::move(skin));
    checkpointProp2ba->getModel()->getModelDataShared()->getModelMeshes().at(0)->useNextSkin();
        });
    worldLst->push_back(checkpointProp2ba);
    checkpointProp2b = checkpointProp2ba;

    // starting pillar thing
    WO* startingLine = WO::New(startingPillar, Vector(5, 5, 5), MESH_SHADING_TYPE::mstAUTO);
    startingLine->upon_async_model_loaded([startingLine]()
    {
        std::string texture(ManagerEnvironmentConfiguration::getLMM() + "/images/startingLineTexture.jpg");
        ModelMeshSkin skin(ManagerTex::loadTexAsync(texture).value());
        skin.setMeshShadingType(MESH_SHADING_TYPE::mstAUTO);
        startingLine->getModel()->getModelDataShared()->getModelMeshes().at(0)->addSkin(std::move(skin));
        startingLine->getModel()->getModelDataShared()->getModelMeshes().at(0)->useNextSkin();
    });
    startingLine->setPosition(100, 0, 20);
    startingLine->renderOrderType = RENDER_ORDER_TYPE::roOPAQUE;
    worldLst->push_back(startingLine);

    // checkpoint1
    WO* checkpoint1 = WO::New(donut, Vector(100, 100, 100), MESH_SHADING_TYPE::mstAUTO);
    checkpoint1->upon_async_model_loaded([checkpoint1]()
    {
        std::string texture(ManagerEnvironmentConfiguration::getLMM() + "/images/donutTexture.jpg");
        ModelMeshSkin skin(ManagerTex::loadTexAsync(texture).value());
        skin.setMeshShadingType(MESH_SHADING_TYPE::mstAUTO);
        checkpoint1->getModel()->getModelDataShared()->getModelMeshes().at(0)->addSkin(std::move(skin));
        checkpoint1->getModel()->getModelDataShared()->getModelMeshes().at(0)->useNextSkin();
    });
    checkpoint1->setPosition(1300, -1280, 343);
    checkpoint1->renderOrderType = RENDER_ORDER_TYPE::roOPAQUE;
    worldLst->push_back(checkpoint1);
    holder = checkpoint1;
    checkpoint1->rotateAboutGlobalX(0.9);
    checkpoint1->rotateAboutGlobalZ(1);

    //checkpoint1 marker
    WO* tmpMarker = WO::New(shinyRedPlasticCube, Vector(10, 10, 10), MESH_SHADING_TYPE::mstAUTO);
    /*tmpMarker->upon_async_model_loaded([tmpMarker]()
    {
        std::string texture(ManagerEnvironmentConfiguration::getLMM() + "/images/green.jpg");
        ModelMeshSkin skin(ManagerTex::loadTexAsync(texture).value());
        skin.setMeshShadingType(MESH_SHADING_TYPE::mstAUTO);
        tmpMarker->getModel()->getModelDataShared()->getModelMeshes().at(0)->addSkin(std::move(skin));
        tmpMarker->getModel()->getModelDataShared()->getModelMeshes().at(0)->useNextSkin();

    });*/
    tmpMarker->renderOrderType = RENDER_ORDER_TYPE::roOPAQUE;
    tmpMarker->setPosition(1279, -1370, 456);
    worldLst->push_back(tmpMarker);
    marker1 = tmpMarker;

    checkpointProp3 = WO::New(satelite, Vector(1, 1, 1), MESH_SHADING_TYPE::mstAUTO);
    checkpointProp3->setPosition(-3522, -3067, 757);
    checkpointProp3->renderOrderType = RENDER_ORDER_TYPE::roOPAQUE;
    //checkpointProp3->rotateAboutGlobalZ(5);
    worldLst->push_back(checkpointProp3);

    WO* checkpointProp4 = WO::New(station, Vector(3, 3, 3), MESH_SHADING_TYPE::mstAUTO);
    checkpointProp4->setPosition(-995, -521, 679);
    checkpointProp4->renderOrderType = RENDER_ORDER_TYPE::roOPAQUE;
    worldLst->push_back(checkpointProp4);
    checkpointProp4->rotateAboutGlobalX(1);

   createNewModuleWayPoints();

   // ADDITIONAL THINGS DONE BY ME
   cam->setPosition(1.4, 1.8, 14.5); // setting cam starting position
   buildCourseAsteroidGuide(); // place asteroids
   
   theGUI = NathanGUI::New(nullptr, 1, 1);
   worldLst->push_back(theGUI);

   pressW = false;
   pressA = false;
   pressS = false;
   pressD = false;
   pressSpace = false;
   pressLshift = false;
   pressLctrl = false;

   //vehicleIPose = redCube->getPose();
   camIPose = cam->getPose();
   jetPose = jet->getPose();
   spaceShipPose = spaceShip->getPose();
}


void GLViewNewModule::createNewModuleWayPoints()
{
   // Create a waypoint with a radius of 3, a frequency of 5 seconds, activated by GLView's camera, and is visible.
   WayPointParametersBase params(this);
   params.frequency = 5000;
   params.useCamera = true;
   params.visible = true;
   WOWayPointSpherical* wayPt = WOWayPointSpherical::New( params, 3 );
   wayPt->setPosition( Vector( 50, 0, 3 ) );
   worldLst->push_back( wayPt );
}

void Aftr::GLViewNewModule::placeAsteroid(Vector location)
{
    std::string asteroid(ManagerEnvironmentConfiguration::getLMM() + "/models/asteroid.mdl");
    WO* rock = WO::New(asteroid, Vector(1, 1, 1), MESH_SHADING_TYPE::mstAUTO);
    
    rock->upon_async_model_loaded([rock]()
        {
            std::string texture(ManagerEnvironmentConfiguration::getLMM() + "/images/asteroidTexture.jpg");
    ModelMeshSkin skin(ManagerTex::loadTexAsync(texture).value());
    skin.setMeshShadingType(MESH_SHADING_TYPE::mstAUTO);
    rock->getModel()->getModelDataShared()->getModelMeshes().at(0)->addSkin(std::move(skin));
    rock->getModel()->getModelDataShared()->getModelMeshes().at(0)->useNextSkin();
        });
    
    auto x = cam->getLookDirection();
    auto y = cam->getPosition();
    rock->setPosition(location);
    rock->renderOrderType = RENDER_ORDER_TYPE::roOPAQUE;
    worldLst->push_back(rock);

    course.push_back(rock->getPosition().toString());
}

void Aftr::GLViewNewModule::buildCourseAsteroidGuide()
{
    //std::ifstream ins;
    //ins.open("route.txt");
    //if (ins.fail())
    //{
    //    std::cout << "error opening input file" << std::endl;
    //}
    //std::string holder;
    //float one;
    //float two;
    //float three;
    //int index;
    //while (getline(ins, holder))
    //{
    //    holder = holder.substr(1, holder.length() - 2);
    //    index = holder.find(',');
    //    one = std::stof(holder.substr(0, index));
    //    holder = holder.substr(index + 1);
    //    index = holder.find(',');
    //    two = std::stof(holder.substr(0, index));
    //    holder = holder.substr(index + 1);
    //    three = std::stof(holder);
    //    locations.push_back(Vector(one, two, three));
    //}
    //ins.close();

    //checkpointProp2b->setParentWorldObject(checkpointProp2);
    //checkpointProp2b->lockWRTparent_using_current_relative_pose();

    locations = {
        Vector(236.506, 113.390, 21.773),
Vector(391.430, 110.097, 91.316),
Vector(573.930, 60.054, 166.316),
Vector(725.876, -9.899, 253.316),
Vector(814.832, -161.630, 253.316),
Vector(863.709, -320.975, 253.316),
Vector(919.280, -463.160, 278.782),
Vector(944.646, -643.704, 281.296),
Vector(950.588, -849.878, 281.296),
Vector(947.607, -1020.220, 278.933),
Vector(978.916, -1193.430, 323.301),
Vector(995.553, -1362.113, 345.301),
Vector(993.222, -1538.248, 374.301),
Vector(1044.629, -1721.803, 376.707),
Vector(1073.794, -1877.435, 380.707),
Vector(1102.542, -2024.432, 380.707),
Vector(1132.823, -2179.269, 380.707),
Vector(1155.984, -2392.667, 369.940),
Vector(1182.634, -2572.075, 388.940),
Vector(1204.094, -2765.544, 388.940),
Vector(1133.398, -2998.009, 388.940),
Vector(1014.860, -3176.734, 388.940),
Vector(857.226, -3262.437, 388.940),
Vector(621.400, -3292.238, 388.940),
Vector(402.558, -3314.138, 388.940),
Vector(233.969, -3391.287, 443.038),
Vector(99.735, -3448.478, 499.038),
Vector(-8.179, -3514.325, 554.038),
Vector(-149.444, -3580.873, 617.038),
Vector(-310.555, -3634.781, 652.296),
Vector(-473.494, -3679.557, 673.296),
Vector(-605.326, -3719.297, 701.296),
Vector(-741.383, -3758.692, 730.296),
Vector(-888.095, -3781.162, 757.296),
Vector(-1026.955, -3789.731, 762.215),
Vector(-1183.967, -3795.473, 762.215),
Vector(-1346.867, -3801.430, 762.215),
Vector(-1487.264, -3844.188, 758.559),
Vector(-1681.366, -3901.935, 757.866),
Vector(-1853.544, -3957.406, 722.321),
Vector(-1976.812, -3991.289, 718.457),
Vector(-2114.882, -4019.716, 668.320),
Vector(-2286.107, -4036.417, 631.117),
Vector(-2481.235, -4053.304, 608.060),
Vector(-2616.980, -3994.028, 608.060),
Vector(-2786.920, -3913.663, 608.060),
Vector(-2876.852, -3776.702, 608.060),
Vector(-2955.295, -3622.598, 612.132),
Vector(-3027.712, -3463.137, 612.132),
Vector(-3085.143, -3332.064, 612.132),
Vector(-3135.147, -3217.395, 612.132),
Vector(-3189.981, -3091.715, 612.132),
Vector(-3242.484, -2971.571, 612.132),
Vector(-3323.605, -2802.942, 630.256),
Vector(-3395.737, -2646.669, 630.256),
Vector(-3454.666, -2474.583, 630.256),
Vector(-3503.567, -2314.759, 630.256),
Vector(-3547.772, -2170.165, 630.256),
Vector(-3530.047, -2010.028, 630.256),
Vector(-3480.787, -1837.153, 648.256),
Vector(-3391.411, -1729.041, 684.994),
Vector(-3331.049, -1581.685, 684.994),
Vector(-3201.875, -1458.285, 684.994),
Vector(-3071.385, -1320.456, 673.269),
Vector(-2931.780, -1187.241, 613.342),
Vector(-2766.686, -1174.214, 554.423),
Vector(-2624.884, -1144.151, 545.221),
Vector(-2483.999, -1120.847, 487.499),
Vector(-2329.827, -1114.670, 448.518),
Vector(-2172.659, -1202.132, 473.138),
Vector(-2043.182, -1281.853, 473.138),
Vector(-1935.412, -1348.019, 473.138),
Vector(-1788.557, -1439.177, 473.138),
Vector(-1644.539, -1530.946, 473.138),
Vector(-1495.678, -1421.569, 456.133),
Vector(-1346.442, -1283.740, 485.133),
Vector(-1230.022, -1172.143, 485.133),
Vector(-1119.883, -1068.486, 485.133),
Vector(-1003.183, -970.842, 485.133),
Vector(-907.984, -847.763, 489.206),
Vector(-789.509, -666.954, 507.206),
Vector(-695.226, -523.079, 512.206),
Vector(-598.788, -375.910, 512.206),
Vector(-505.212, -283.680, 453.943),
Vector(-423.456, -195.618, 364.154),
Vector(-346.571, -127.377, 249.512),
Vector(-255.849, -56.803, 166.936),
Vector(-146.823, 2.623, 100.446),
Vector(-58.883, 62.126, 62.975),
Vector(47.884, -93.147, 15.692),
Vector(161.508, -131.118, 46.780),
Vector(256.269, -116.752, 92.781),
Vector(406.104, -121.619, 124.780),
Vector(546.208, -206.314, 163.780),
Vector(604.148, -349.227, 272.607),
Vector(593.128, -522.037, 314.626),
Vector(605.657, -698.916, 292.447),
Vector(638.291, -892.957, 288.562),
Vector(658.070, -1069.351, 299.045),
Vector(657.687, -1237.488, 341.915),
Vector(647.147, -1387.298, 359.567),
Vector(628.417, -1573.474, 385.647),
Vector(660.767, -1791.029, 390.046),
Vector(716.216, -1969.027, 398.696),
Vector(709.880, -2141.969, 407.751),
Vector(720.366, -2285.354, 401.731),
Vector(726.525, -2439.256, 412.145),
Vector(730.541, -2640.930, 415.837),
Vector(709.906, -2777.067, 415.221),
Vector(581.230, -2925.672, 437.678),
Vector(361.916, -3004.935, 433.072),
Vector(143.818, -3057.008, 413.124),
Vector(17.871, -3116.069, 438.124),
Vector(-117.086, -3124.769, 475.124),
Vector(-212.035, -3149.142, 541.124),
Vector(-319.969, -3170.580, 613.124),
Vector(-450.264, -3217.403, 648.124),
Vector(-577.476, -3192.643, 664.124),
Vector(-726.219, -3201.990, 708.124),
Vector(-849.709, -3225.649, 741.124),
Vector(259.853, -3032.574, 452.684),
Vector(473.674, -2970.601, 450.464),
Vector(-998.702, -3306.531, 754.671),
Vector(-1203.666, -3374.694, 758.379),
Vector(-1099.538, -3356.866, 775.379),
Vector(-1302.160, -3416.375, 774.747),
Vector(-1410.049, -3453.371, 790.458),
Vector(-1548.956, -3483.854, 786.771),
Vector(-1729.926, -3558.839, 789.293),
Vector(-1882.120, -3551.836, 765.668),
Vector(-2017.552, -3546.261, 751.128),
Vector(-2141.349, -3582.676, 751.128),
Vector(-2267.034, -3619.904, 728.937),
Vector(-2429.076, -3579.812, 705.856),
Vector(-2567.777, -3521.839, 674.013),
Vector(-2645.492, -3426.908, 666.244),
Vector(-2724.803, -3313.839, 639.158),
Vector(-2806.741, -3187.065, 621.737),
Vector(-2875.568, -3066.344, 620.667),
Vector(-2913.931, -2910.990, 626.768),
Vector(-2918.369, -2751.685, 640.768),
Vector(-2993.897, -2587.672, 637.598),
Vector(-3044.589, -2487.384, 640.120),
Vector(-3113.929, -2350.713, 647.093),
Vector(-3177.524, -2205.806, 638.852),
Vector(-3207.134, -2086.811, 640.059),
Vector(-102.454, -196.874, 97.000),
Vector(-169.010, -352.368, 210.000),
Vector(-247.731, -450.445, 361.000),
Vector(-314.344, -529.350, 446.000),
Vector(-411.163, -610.021, 512.000),
Vector(-488.271, -749.859, 528.000),
Vector(-549.786, -857.555, 528.000),
Vector(-669.319, -1015.911, 520.368),
Vector(-753.718, -1201.470, 514.954),
Vector(-816.154, -1348.884, 514.954),
Vector(-929.846, -1490.045, 524.954),
Vector(-1019.830, -1603.526, 545.954),
Vector(-1122.657, -1710.770, 504.252),
Vector(-1266.405, -1853.681, 500.401),
Vector(-1460.195, -1910.708, 500.401),
Vector(-1687.271, -1929.177, 513.401),
Vector(-1853.011, -1914.673, 536.401),
Vector(-2035.341, -1842.166, 528.249),
Vector(-3182.717, -1937.917, 650.346),
Vector(-3097.503, -1759.428, 669.379),
Vector(-2888.135, -1696.219, 668.698),
Vector(-2784.144, -1652.946, 616.152),
Vector(-2643.096, -1633.161, 584.252),
Vector(-2505.997, -1542.818, 546.568),
Vector(-2345.620, -1511.505, 521.279),
Vector(-2241.492, -1593.806, 527.248),
Vector(-2132.952, -1725.405, 518.133),
Vector(102, 75, -28),
Vector(102, -65, -28)
    };

    for (size_t i = 0; i < locations.size(); i++)
    {
        placeAsteroid(locations.at(i));
    }
}
void Aftr::GLViewNewModule::placeCheckpointMarker(Vector location)
{
    std::string cube(ManagerEnvironmentConfiguration::getSMM() + "/models/cube4x4x4redShinyPlastic_pp.wrl");
    WO* marker = WO::New(cube, Vector(10, 40, 25), MESH_SHADING_TYPE::mstAUTO);
    //WO* marker = WO::New(cube, Vector(10, 10, 10), MESH_SHADING_TYPE::mstAUTO);
    auto x = cam->getLookDirection();
    auto y = cam->getPosition();
    marker->setPosition(location);
    marker->renderOrderType = RENDER_ORDER_TYPE::roOPAQUE;
    worldLst->push_back(marker);
}

void Aftr::GLViewNewModule::setVehicle()
{
    // jet
    if (theGUI->jet == true)
    {
        user = jet;
        vehicleIPose = jet->getPose();
        redCube->setPosition(user->getPosition());
        cam->setPosition(48.5, 0, 8);
    }
    //spaceShip
    if (theGUI->spaceShip == true)
    {
        user = spaceShip;
        vehicleIPose = spaceShip->getPose();
        redCube->setPosition(user->getPosition());
        cam->setPosition(45, 15, 8);
    }
}

void Aftr::GLViewNewModule::unlock()
{
    firstCheck = false;
    secondCheck = false;
    thirdCheck = false;
    fourthCheck = false;
    theGUI->jet = false;
    theGUI->spaceShip = false;

    theGUI->raceFinshed = false;
    theGUI->reset = false;
}

void Aftr::GLViewNewModule::multiplayerReset()
{
    theGUI->jetTaken = false;
    theGUI->spaceShipTaken = false;
    theGUI->vSet = false;
    theGUI->vehicleSet = false;
}