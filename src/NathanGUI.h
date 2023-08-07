#pragma once

#include "WOImGui.h"
#include "WOImGuiAbstract.h"
#include "AftrImGuiIncludes.h"
#include "irrKlang.h"

	
namespace Aftr
{
	class NathanGUI : public WOImGuiAbstract
	{
	public:
		static NathanGUI* New(WOGUI* parentWOGUI, float width = 1, float height = 1);

		virtual ~NathanGUI();
		virtual void onUpdateWO() override;
		virtual void drawImGui_for_this_frame() override;
		virtual void onCreate(float width, float height) override;

		void bobcatStyle();

		bool raceStart;
		bool onGoing;
		bool raceFinshed;
		bool reset;
		bool lockRacer;
		bool unlockRacer;

		float elapsedTime = 0;
		float bestTime = 0;
		float countdown = 3;
		std::string startReset;
		std::string countdownText;

		bool jet;
		bool spaceShip;
		bool vehicleChosen;
		std::string currVehicle;

		std::string boostValue;

		bool twoPlayer;
		bool beginGame;

		bool connected;
		bool firstPlayer;
		bool secondPlayer;

		bool jetTaken;
		bool jetWin;
		bool spaceShipTaken;
		bool spaceShipWin;

		std::string currPlayer;
		std::string currIssue;

		bool vehicleSet;
		bool vSet;
		bool meReset;

		std::string winner;

		irrklang::ISoundEngine* buttonEngine;
		irrklang::ISound* buttonSound;
		std::string buttonSoundString;

		bool playCPU;
		bool CPUwin;

	private:
		NathanGUI(WOGUI* parentWOGUI) : IFace(this), WOImGuiAbstract(parentWOGUI) {};
		//NathanGUI(WOGUI* parentWOGUI);

		bool style1;
	};
}

