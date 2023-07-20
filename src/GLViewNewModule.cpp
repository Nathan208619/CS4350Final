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

    if (theGUI->reset = true)
    {
        firstCheck = false;
        secondCheck = false;
        thirdCheck = false;
        fourthCheck = false;

        theGUI->reset = false;
        theGUI->countdownText = "GET READY FOR THE NEXT RACE!!!";
    }

    // ********************* Lock and unlock racer ***************************
    if (theGUI->lockRacer == true)
    {
        cam->setPose(camIPose);
        redCube->setPose(vehicleIPose);
        redCube->setParentWorldObject(cam);
        redCube->lockWRTparent_using_current_relative_pose();
        theGUI->lockRacer = false;
    }
    if (theGUI->unlockRacer == true)
    {
        cam->setPose(camIPose);
        redCube->setPose(vehicleIPose);

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
        firstCheck = false;
        secondCheck = false;
        thirdCheck = false;
        fourthCheck = false;

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
        std::cout << "finished" << std::endl;
    }
    // ********************* Course Checkpoints ***************************

    

   //************ Vehicle Controls ******************
   if (pressW == true) 
   {
       /*auto move = redCube->getPosition();
       move.x += redCube->getLookDirection().x * speed;
       move.y += redCube->getLookDirection().y * speed;
       move.z += redCube->getLookDirection().z * speed;
       redCube->setPosition(move);*/

       auto move = cam->getPosition();
       move.x += redCube->getLookDirection().x * speed;
       move.y += redCube->getLookDirection().y * speed;
       move.z += redCube->getLookDirection().z * speed;
       cam->setPosition(move);

       /*auto curr = cam->getPosition();
       curr.x = curr.x + cam->getLookDirection().x;
       curr.y = curr.y + cam->getLookDirection().y;
       cam->setPosition(curr);*/
   }
   if (pressA == true)
   {
       cam->rotateAboutGlobalZ(-0.05);
       redCube->rotateAboutGlobalZ(-0.25);

       /*auto curr = cam->getPosition();
       auto direction = cam->getDisplayMatrix().getZ();
       auto next = direction.crossProduct(cam->getLookDirection());
       curr = curr + next;
       cam->setPosition(curr);*/
   }
   if (pressS == true)
   {
       auto curr = cam->getPosition();
       curr.x = curr.x - cam->getLookDirection().x;
       curr.y = curr.y - cam->getLookDirection().y;
       cam->setPosition(curr);
   }
   if (pressD == true)
   {
       /*auto curr = cam->getPosition();
       auto directionZ = cam->getDisplayMatrix().getZ();
       auto nextZ = directionZ.crossProduct(cam->getLookDirection());
       curr = curr - nextZ;
       cam->setPosition(curr);*/
       

       //redCube->rotateAboutGlobalZ(0.05);
       cam->rotateAboutGlobalZ(0.05);
   }
   if (pressSpace == true)
   {
       cam->setPosition(cam->getPosition().x, cam->getPosition().y, cam->getPosition().z + 1);
   }

   if (pressLshift == true && pressLctrl == false)
   {
       if (rotateUp < 40)
       {
           //redCube->rotateAboutRelY(-0.02);
           cam->rotateAboutRelY(-0.02);
           rotateUp++;
       }
       //redCube->rotateAboutRelY(-0.25);
   }
   else if (pressLctrl == true && pressLshift == false)
   {
       if (rotateDown < 40)
       {
           cam->rotateAboutRelY(0.02);
           //redCube->rotateAboutRelY(0.02);
           rotateDown++;
       }
       //redCube->rotateAboutRelY(0.25);
   }
   else
   {
       if (rotateUp > 0)
       {
           cam->rotateAboutRelY(0.02);
           //redCube->rotateAboutRelY(0.02);
           rotateUp--;
       }
       if (rotateDown > 0)
       {
           cam->rotateAboutRelY(-0.02);
           //redCube->rotateAboutRelY(-0.02);
           rotateDown--;
       }
   }
   //************ Vehicle Controls ******************

}


void GLViewNewModule::onResizeWindow( GLsizei width, GLsizei height )
{
   GLView::onResizeWindow( width, height ); //call parent's resize method.
}


void GLViewNewModule::onMouseDown( const SDL_MouseButtonEvent& e )
{
   GLView::onMouseDown( e );
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
       pressSpace = true;
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
       pressSpace = false;
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
   std::string jet(ManagerEnvironmentConfiguration::getSMM() + "/models/jet_wheels_down_PP.wrl");
   std::string spaceStation(ManagerEnvironmentConfiguration::getSMM() + "/models/spaceStation220x130x160.wrl");
   std::string startingPillar(ManagerEnvironmentConfiguration::getLMM() + "/models/race_drag_start_and_finish_line.glb");
   std::string donut(ManagerEnvironmentConfiguration::getLMM() + "/models/donut.glb");

   
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
    redCube = WO::New(jet, Vector(1, 1, 1), MESH_SHADING_TYPE::mstAUTO);
    redCube->setPosition(62, 15, 2);
    redCube->renderOrderType = RENDER_ORDER_TYPE::roOPAQUE;
    worldLst->push_back(redCube);

    // space station
    startingLocation = WO::New(spaceStation, Vector(1, 1, 1), MESH_SHADING_TYPE::mstAUTO);
    startingLocation->setPosition(67, 175, 21);
    startingLocation->renderOrderType = RENDER_ORDER_TYPE::roOPAQUE;
    worldLst->push_back(startingLocation);

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



   createNewModuleWayPoints();

   // ADDITIONAL THINGS DONE BY ME
   cam->setPosition(45, 15, 8); // setting cam starting position
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

   vehicleIPose = redCube->getPose();
   camIPose = cam->getPose();
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
    std::ifstream ins;
    ins.open("route.txt");
    if (ins.fail())
    {
        std::cout << "error opening input file" << std::endl;
    }
    std::string holder;
    float one;
    float two;
    float three;
    int index;
    while (getline(ins, holder))
    {
        holder = holder.substr(1, holder.length() - 2);
        index = holder.find(',');
        one = std::stof(holder.substr(0, index));
        holder = holder.substr(index + 1);
        index = holder.find(',');
        two = std::stof(holder.substr(0, index));
        holder = holder.substr(index + 1);
        three = std::stof(holder);
        locations.push_back(Vector(one, two, three));
    }
    ins.close();

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
