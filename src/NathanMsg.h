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

	protected:

	};

} //namespace Aftr

#endif
