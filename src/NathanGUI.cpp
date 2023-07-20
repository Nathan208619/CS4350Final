#include "NathanGUI.h"

using namespace Aftr;

NathanGUI* NathanGUI::New(WOGUI* parentWOGUI, float width, float height)
{
	NathanGUI* theGUI = new NathanGUI(parentWOGUI);
	theGUI->onCreate(width, height);
	return theGUI;
}

NathanGUI::~NathanGUI() 
{
};

void NathanGUI::onUpdateWO()
{
};

void NathanGUI::drawImGui_for_this_frame()
{
	ImGui::Begin("Racing Console");

	if (ImGui::Button(startReset.c_str()))
	{
		if (onGoing == false)
		{
			startReset = "Reset";
			raceStart = true;
			lockRacer = true;
		}
		else
		{
			startReset = "Start";
			reset = true;
			onGoing = false;
			unlockRacer = true;
			elapsedTime = 0;
			countdown = 3;
		}
	}

	ImGui::Separator();

	ImGui::Text(countdownText.c_str());

	ImGui::Separator();

	ImGui::Text("Elapsed Time: %.2f", elapsedTime);

	ImGui::Separator();

	ImGui::Text("Best Time: %.2f", bestTime);
	
	ImGui::Separator();

	if(ImGui::Button("Change Style"))
	{
		if (style1 == false)
		{
			ImGui::StyleColorsLight();
			style1 = true;
		}
		else
		{
			bobcatStyle();
			style1 = false;
		}
	}

	ImGui::End();
}

void NathanGUI::onCreate(float width, float height)
{
	WOImGuiAbstract::onCreate(width, height);
	style1 = false;
	raceStart = false;
	raceFinshed = false;
	onGoing = false;
	reset = false;
	lockRacer = false;
	unlockRacer = false;
	startReset = "Start";
	countdownText = "GET READY!!!";

	float elapsedTime = 0;
	float bestTime = 0;
	float countdown = 3;

	bobcatStyle();
}

void NathanGUI::bobcatStyle()
{
	ImGuiStyle* textColor = &ImGui::GetStyle();
	textColor->Colors[ImGuiCol_Text] = ImVec4(1.00, 1.00, 1.00, 1.0); // text color
	textColor->Colors[ImGuiCol_WindowBg] = ImVec4(0.72, 0.72, 0.72, 1.0); // background color
	textColor->Colors[ImGuiCol_TitleBgActive] = ImVec4(.19, 0.30, 0.19, 1.0); // top bar color

	textColor->Colors[ImGuiCol_FrameBg] = ImVec4(.19, 0.30, 0.19, 1.0); // slider brackground color
	textColor->Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.34, 0.48, 0.39, 1.0); // slider background hover color
	textColor->Colors[ImGuiCol_FrameBgActive] = ImVec4(.19, 0.30, 0.19, 1.0); // slider highlighted color

	textColor->Colors[ImGuiCol_Button] = ImVec4(.19, 0.30, 0.19, 1.0);//button color
	textColor->Colors[ImGuiCol_ButtonHovered] = ImVec4(0.34, 0.48, 0.39, 1.0);//button color
	textColor->Colors[ImGuiCol_ButtonActive] = ImVec4(0.14, 0.26, 0.18, 1.0);//button color

	textColor->Colors[ImGuiCol_SliderGrab] = ImVec4(0.56, 0.57, 0.56, 1.0);//slider bar color
	textColor->Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.69, 0.71, 0.69, 1.0);//slider bar active color
}