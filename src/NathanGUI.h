#pragma once

#include "WOImGui.h"
#include "WOImGuiAbstract.h"
#include "AftrImGuiIncludes.h"
	
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
		bool raceFinshed;
		bool reset;
		float elapsedTime = 0;
		float bestTime = 0;


	private:
		NathanGUI(WOGUI* parentWOGUI) : IFace(this), WOImGuiAbstract(parentWOGUI) {};
		//NathanGUI(WOGUI* parentWOGUI);

		bool style1;
	};
}

