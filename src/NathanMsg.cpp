#include "NetMsgCreateWO.h"
#ifdef AFTR_CONFIG_USE_BOOST

#include <iostream>
#include <sstream>
#include <string>
#include "AftrManagers.h"
#include "Vector.h"
#include "WO.h"
#include "GLView.h"
#include "WorldContainer.h"
#include "NetMsgCreateWOReply.h"
#include "NathanMsg.h"

using namespace Aftr;

NetMsgMacroDefinition(NathanMsg);

NathanMsg::NathanMsg()
{
	//this->xPos = 0;
	this->jetGone = false;
	this->jetVic = false;
	this->spaceShipGone = false;
	this->spaceShipVic = false;
	this->startRace = false;
	this->resetBoth = false;
	this->otherVehicle = false;
	this->otherVehicleRot = false;
	this->victory = false;
	this->bestTime = 0;
	this->xPos = 0;
	this->yPos = 0;
	this->zPos = 0;
	this->yRot = 0;
	this->zRot = 0;
}

NathanMsg::~NathanMsg()
{
}

bool NathanMsg::toStream(NetMessengerStreamBuffer& os) const
{
	//os << this->xPos;
	os << this->jetGone;
	os << this->jetVic;
	os << this->spaceShipGone;
	os << this->spaceShipVic;
	os << this->startRace;
	os << this->resetBoth;
	os << this->otherVehicle;
	os << this->otherVehicleRot;
	os << this->victory;
	os << this->bestTime;
	os << this->xPos;
	os << this->yPos;
	os << this->zPos;
	os << this->yRot;
	os << this->zRot;
	return true;
}

bool NathanMsg::fromStream(NetMessengerStreamBuffer& is)
{
	//is >> this->xPos;
	is >> this->jetGone;
	is >> this->jetVic;
	is >> this->spaceShipGone;
	is >> this->spaceShipVic;
	is >> this->startRace;
	is >> this->resetBoth;
	is >> this->otherVehicle;
	is >> this->otherVehicleRot;
	is >> this->victory;
	is >> this->bestTime;
	is >> this->xPos;
	is >> this->yPos;
	is >> this->zPos;
	is >> this->yRot;
	is >> this->zRot;
	return true;
}

void NathanMsg::onMessageArrived()
{
	//std::cout << "Message has arrived... " << this->toString() << "\n";
	if (jetGone == true)
	{
		ManagerGLView::getGLViewT<GLViewNewModule>()->theGUI->jetTaken = true;
	}
	if (spaceShipGone == true)
	{
		ManagerGLView::getGLViewT<GLViewNewModule>()->theGUI->spaceShipTaken = true;
	}
	if (startRace == true)
	{
		ManagerGLView::getGLViewT<GLViewNewModule>()->theGUI->startReset = "Reset";
		ManagerGLView::getGLViewT<GLViewNewModule>()->theGUI->raceStart = true;
		ManagerGLView::getGLViewT<GLViewNewModule>()->theGUI->lockRacer = true;
		ManagerGLView::getGLViewT<GLViewNewModule>()->theGUI->vSet = true;
	}
	if (resetBoth == true)
	{
		ManagerGLView::getGLViewT<GLViewNewModule>()->theGUI->reset = true;
		ManagerGLView::getGLViewT<GLViewNewModule>()->theGUI->onGoing = false;
		ManagerGLView::getGLViewT<GLViewNewModule>()->theGUI->unlockRacer = true;
		ManagerGLView::getGLViewT<GLViewNewModule>()->theGUI->elapsedTime = 0;
		ManagerGLView::getGLViewT<GLViewNewModule>()->theGUI->countdown = 3;
		ManagerGLView::getGLViewT<GLViewNewModule>()->theGUI->startReset = "Start";
	}
	if (otherVehicle == true)
	{
		if (ManagerGLView::getGLViewT<GLViewNewModule>()->theGUI->spaceShip == true)
		{
			ManagerGLView::getGLViewT<GLViewNewModule>()->jet->setPosition(xPos, yPos, zPos);
		}
		else
		{
			ManagerGLView::getGLViewT<GLViewNewModule>()->spaceShip->setPosition(xPos, yPos, zPos);
		}
	}
	if (otherVehicleRot == true)
	{
		if (ManagerGLView::getGLViewT<GLViewNewModule>()->theGUI->spaceShip == true)
		{
			ManagerGLView::getGLViewT<GLViewNewModule>()->jet->rotateAboutGlobalZ(zRot);
		}
		else
		{
			ManagerGLView::getGLViewT<GLViewNewModule>()->spaceShip->rotateAboutGlobalZ(zRot);
		}
	}
	if (victory == true)
	{
		ManagerGLView::getGLViewT<GLViewNewModule>()->theGUI->raceFinshed = true;
		ManagerGLView::getGLViewT<GLViewNewModule>()->theGUI->onGoing = false;
		ManagerGLView::getGLViewT<GLViewNewModule>()->theGUI->unlockRacer = true;
		ManagerGLView::getGLViewT<GLViewNewModule>()->theGUI->countdownText = "GET READY FOR THE NEXT RACE!!!";
		ManagerGLView::getGLViewT<GLViewNewModule>()->theGUI->countdown = 3;
		ManagerGLView::getGLViewT<GLViewNewModule>()->theGUI->onGoing = false;
		ManagerGLView::getGLViewT<GLViewNewModule>()->theGUI->bestTime = bestTime;
		ManagerGLView::getGLViewT<GLViewNewModule>()->theGUI->elapsedTime = 0;
		ManagerGLView::getGLViewT<GLViewNewModule>()->theGUI->startReset = "Start";
	}
	std::cout << "Message Recieved" << std::endl;
}

std::string NathanMsg::toString() const
{
	std::stringstream ss;

	ss << NetMsg::toString();
	//ss << "   Payload: " << Vector(xPos, yPos, zPos).toString() << "...\n";
	return ss.str();
}

#endif

