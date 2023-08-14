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
	if (beginGame == false)
	{
		ImGui::Begin("Main Menu");
		if (ImGui::Button("Single Player"))
		{
			buttonSound = buttonEngine->play2D(buttonSoundString.c_str(), false, false, true);
			buttonSound->setVolume(0.2);
			beginGame = true;
		}

		if (ImGui::Button("Multiplayer"))
		{
			buttonSound = buttonEngine->play2D(buttonSoundString.c_str(), false, false, true);
			buttonSound->setVolume(0.2);
			beginGame = true;
			secondPlayer = true;
		}

		if (ImGui::Button("Play VS CPU"))
		{
			buttonSound = buttonEngine->play2D(buttonSoundString.c_str(), false, false, true);
			buttonSound->setVolume(0.2);
			beginGame = true;
			playCPU = true;
		}

		ImGui::End();
	}
	else
	{

	ImGui::Begin("Racing Console");

	if (firstPlayer || secondPlayer)
	{
		ImGui::Text("Player One");
		ImGui::Separator();
	}

	ImGui::Text(winner.c_str());

	ImGui::Separator();

	if (ImGui::Button(startReset.c_str()))
	{
		buttonSound = buttonEngine->play2D(buttonSoundString.c_str(), false, false, true);
		buttonSound->setVolume(0.2);
		if (vehicleChosen == false)
		{
			currIssue = "Current Issue: Must choose Vehicle to race";
		}
		else if (jetTaken == false && spaceShipTaken == false && (firstPlayer == true || secondPlayer == true))
		{
			currIssue = "Current Issue: Both player must choose vehicle to begin";
		}
		else if (onGoing == false && vehicleChosen == true)
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
			meReset = true;
		}
	}

	ImGui::Separator();

	ImGui::Text(countdownText.c_str());

	if (onGoing == true)
	{
		ImGui::Separator();

		ImGui::Text(boostValue.c_str());
	}

	ImGui::Separator();

	ImGui::Text("Elapsed Time: %.2f", elapsedTime);

	ImGui::Separator();

	ImGui::Text("Best Time: %.2f", bestTime);

	if (onGoing == false && raceStart == false)
	{
		ImGui::Separator();
		
		ImGui::Text("Choose Your Vehicle: ");

		if(ImGui::Button("Jet"))
		{
			buttonSound = buttonEngine->play2D(buttonSoundString.c_str(), false, false, true);
			buttonSound->setVolume(0.2);
			if (jetTaken == true)
			{
				currIssue = "Current Issue: Another player has selected the Jet, please select another vehicle";
			}
			else
			{
				spaceShip = false;
				jet = true;
				currVehicle = "Current Vehicle: Jet";
				currIssue = currIssue = "Current Issue: None";
				vehicleChosen = true;
			}
		}
		ImGui::SameLine();
		if(ImGui::Button("SpaceShip"))
		{
			buttonSound = buttonEngine->play2D(buttonSoundString.c_str(), false, false, true);
			buttonSound->setVolume(0.2);
			if (spaceShipTaken == true)
			{
				currIssue = "Current Issue: Another player has selected the Spaceship, please select another vehicle";

			}
			else
			{
				jet = false;
				spaceShip = true;
				currVehicle = "Current Vehicle: Spaceship";
				currIssue = currIssue = "Current Issue: None";
				vehicleChosen = true;
			}
		}
	}
	
	ImGui::Separator();
	
	ImGui::Text(currVehicle.c_str());

	ImGui::Separator();

	if(ImGui::Button("Change Style"))
	{
		buttonSound = buttonEngine->play2D(buttonSoundString.c_str(), false , false, true);
		buttonSound->setVolume(0.2);
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

	ImGui::Begin("Issues");

	ImGui::Text(currIssue.c_str());

	ImGui::End();

	}//top else statement
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

	jet = false;
	spaceShip = false;
	vehicleChosen = false;
	currVehicle = "Current Vehicle: None";

	boostValue = "Boost: MAX";

	twoPlayer = false;
	beginGame = false;

	connected = false;
	firstPlayer = false;
	secondPlayer = false;

	jetTaken = false;
	jetWin = false;
	spaceShipTaken = false;
	spaceShipWin = false;

	currPlayer = "Your are neither Player";
	currIssue = "Current Issue: None";

	vSet = false;
	vehicleSet = false;
	meReset = false;

	winner = "Winner: -----";

	buttonEngine = irrklang::createIrrKlangDevice();
	buttonSoundString = ManagerEnvironmentConfiguration::getLMM() + "sounds/button.mp3";

	playCPU = false;
	CPUwin = false;

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