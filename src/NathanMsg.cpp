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
		ManagerGLView::getGLViewT<GLViewNewModule>()->theGUI->vSet = false;
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

