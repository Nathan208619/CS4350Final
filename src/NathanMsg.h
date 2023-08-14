#pragma once

#include "NetMsg.h"
#include "GLViewNewModule.h"

#ifdef AFTR_CONFIG_USE_BOOST

namespace Aftr
{
	class NathanMsg : public NetMsg
	{
	public:
		NetMsgMacroDeclaration(NathanMsg);

		NathanMsg();
		virtual ~NathanMsg();
		virtual bool toStream(NetMessengerStreamBuffer& os) const;
		virtual bool fromStream(NetMessengerStreamBuffer& is);
		virtual void onMessageArrived();
		virtual std::string toString() const;

		int jetGone = false;
		int jetVic = false;

		int spaceShipGone = false;
		int spaceShipVic = false;

		int startRace = false;

		int resetBoth = false;

		//vehicle vars
		int otherVehicle = false;
		int otherVehicleRot = false;
		int otherVehicleRotY = false;

		float xPos = 0;
		float yPos = 0;
		float zPos = 0;

		float yRot = 0;
		float zRot = 0;

		//winner
		int victory = false;
		float bestTime = 0;
		
		std::string address = "";
		int connection = false;
		int connectfirst = false;

	protected:

	};

} //namespace Aftr

#endif
