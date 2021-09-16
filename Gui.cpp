#include "Gui.h"

bool PressedKeys[256];
bool PressedKeysPrev[256];
int PressKeysTime[256];

bool isActive = true;
int index = 0;

std::vector<Tab*> tabList;
std::stack<int> indexStack;

int Gui::Init(HWND hWnd) {
	mm = new Memory();
	mm->SetupMemory();
	graphics = new Graphics();
	if (!graphics->Init(hWnd)) {
		delete graphics; return 0;
	};


	// Initialize Tabs
	MainTab* mainTab = new MainTab(this);
	currentTab = mainTab;

	return 1;
}

int Gui::UpdateAndDraw() {
	// Update Section
	if (!currentTab) return 0;
	int tabSize = currentTab->getGuiElements().size();

	// Toggle Menu
	if (GetAsyncKeyState(VK_NUMPAD0) & 0x8000) {
		PressKeysTime[VK_NUMPAD0]++;
		if (!PressedKeysPrev[VK_NUMPAD0] || PressKeysTime[VK_NUMPAD0] >= 15) {
			PressedKeysPrev[VK_NUMPAD0] = true;
			ToggleVisibility();
		}
	}
	else {
		PressedKeysPrev[VK_NUMPAD0] = false;
		PressKeysTime[VK_NUMPAD0] = 0;

	}

	if (isActive) {
		GenericButton* currentElement = currentTab->getElementAtIndex(index);
		if (GetAsyncKeyState(VK_NUMPAD8) & 0x8000 )
		{
			PressKeysTime[VK_NUMPAD8]++;
			if (!PressedKeysPrev[VK_NUMPAD8] || PressKeysTime[VK_NUMPAD8] >= 15) {
				PressedKeysPrev[VK_NUMPAD8] = true;
				if (index == 0) index = (tabSize - 1);
				else (index -= 1);
			}
		}
		else {
			PressedKeysPrev[VK_NUMPAD8] = false;
			PressKeysTime[VK_NUMPAD8] = 0;
		}

		if (GetAsyncKeyState(VK_NUMPAD5) & 0x8000)
		{
			PressKeysTime[VK_NUMPAD5]++;
			if (!PressedKeysPrev[VK_NUMPAD5] || PressKeysTime[VK_NUMPAD5] >= 15) {
				PressedKeysPrev[VK_NUMPAD5] = true;
				if (index == (tabSize - 1)) index = 0;
				else (index += 1);
			}
		}
		else {
			PressedKeysPrev[VK_NUMPAD5] = false;
			PressKeysTime[VK_NUMPAD5] = 0;
		}
		if (GetAsyncKeyState(VK_NUMPAD6) & 0x8000 )
		{
			PressKeysTime[VK_NUMPAD6]++;
			if (!PressedKeysPrev[VK_NUMPAD6] || PressKeysTime[VK_NUMPAD6] >= 15) {
				PressedKeysPrev[VK_NUMPAD6] = true;
				if (currentElement->getType() == SLIDER) {
					SliderButton* i = (SliderButton*)currentElement;
					if (i) i->increase();
				}
			}
		}
		else {
			PressedKeysPrev[VK_NUMPAD6] = false;
			PressKeysTime[VK_NUMPAD6] = 0;
		}
		if (GetAsyncKeyState(VK_NUMPAD4) & 0x8000)
		{
			PressKeysTime[VK_NUMPAD4]++;
			if (!PressedKeysPrev[VK_NUMPAD4] || PressKeysTime[VK_NUMPAD4] >= 15) {
				PressedKeysPrev[VK_NUMPAD4] = true;
				if (currentElement->getType() == SLIDER) {
					SliderButton* i = (SliderButton*)currentElement;
					if (i) i->decrease();
				}
			}
		}
		else {
			PressedKeysPrev[VK_NUMPAD4] = false;
			PressKeysTime[VK_NUMPAD4] = 0;
		}
		if (GetAsyncKeyState(VK_NUMPAD7) & 0x8000 )
		{
			if (currentTab->pParent) {
				if (!PressedKeysPrev[VK_NUMPAD7] || PressKeysTime[VK_NUMPAD7] >= 15) {
					PressedKeysPrev[VK_NUMPAD7] = true;
					PressKeysTime[VK_NUMPAD7]++;
					this->SetIndex(indexStack.top());
					indexStack.pop();
					this->currentTab->returnToParent();
				}
			}
		}
		else {
			PressedKeysPrev[VK_NUMPAD7] = false;
			PressKeysTime[VK_NUMPAD7] = 0;
		}
		if (GetAsyncKeyState(VK_NUMPAD9) & 0x8000)
		{
			PressKeysTime[VK_NUMPAD9]++;
			if (!PressedKeysPrev[VK_NUMPAD9] || PressKeysTime[VK_NUMPAD9] >= 15) {
				PressedKeysPrev[VK_NUMPAD9] = true;
				currentElement->Press();
			}

		}
		else {
			PressedKeysPrev[VK_NUMPAD9] = false;
			PressKeysTime[VK_NUMPAD9] = 0;
		}
	}

	// Update hacks;
	for (int i = 0; i < tabList.size(); i++) {
		Tab* tab = tabList[i];
		if(currentTab == tab) tab->update(mm, index);
		else tab->update(mm, -1);
	}
	if (currentTab->update(mm, index)) return 1;

	tabSize = currentTab->getGuiElements().size();

	// Drawing Section
	graphics->BeginDraw();
	graphics->ClearScreen(0.0f, 0.0f, 0.0f, 0.5f);
	if (isActive) {
		graphics->DrawOutlinedRectangle(0, 0, 300, 25 + (25 * tabSize), 0.41f, 0.41f, 0.41f, 0.3f);
		graphics->DrawString(L"Coco External Menu V0.1A", 45, 0, 0.0f, 1.0F, 1.0F, 1.0f);
		if (tabSize != 0) {
			for (int i = 0; i < tabSize; i++) {
				GenericButton* element = currentTab->getElementAtIndex(i);
				element->Draw(graphics, i, 0, 0, (i == index));
			}
		}
	}
	graphics->EndDraw();
	return 1;
}

void Gui::ToggleVisibility() {
	isActive = !isActive;
}

void Gui::SetCurrentTab(Tab* tab) {
	indexStack.push(index);
	currentTab = tab;
}

void Gui::AddTab(Tab* tab) {
	tabList.push_back(tab);
}

void Gui::SetIndex(int i) {
	index = i;
}


//	TODO: TAB TYPES;
/*
/	TODO: GENERIC TAB;
*/
Tab::Tab(Gui* gui) {
	this->pGui = gui;
}
Tab::Tab(Gui* gui, Tab* parent) {
	this->pGui = gui;
	this->pParent = parent;
}

int Tab::update(Memory* memory, int currentIndex) {
	return 0;
}

void Tab::returnToParent() {
	if(pParent) pGui->SetCurrentTab(pParent);
}

std::vector<GenericButton*> Tab::getGuiElements() {
	return guiElements;
}

GenericButton* Tab::getElementAtIndex(int index) {
	return guiElements[index];
}

/*
/	TODO: Main TAB;
*/
MainTab::MainTab(Gui* gui) : Tab::Tab(gui) {
	playerTab = new PlayerTab(gui, this);
	vehicleTab = new VehicleTab(gui, this);
	weaponTab = new WeaponTab(gui, this);
	onlineTab = new OnlineTab(gui, this);
	menuTab = new MenuTab(gui, this);
	BtnPlayerTab = new GenericButton(L"Player", true);
	BtnVehicleTab = new GenericButton(L"Vehicle", true);
	BtnWeaponTab = new GenericButton(L"Weapon", true);
	BtnTeleportTab = new GenericButton(L"Teleport", true);
	BtnOnlineTab = new GenericButton(L"Online", true);
	BtnMenuSettings = new GenericButton(L"Menu Settings", true);
	BtnExit = new GenericButton(L"Exit");
	guiElements.push_back(BtnPlayerTab);
	guiElements.push_back(BtnVehicleTab);
	guiElements.push_back(BtnWeaponTab);
	guiElements.push_back(BtnTeleportTab);
	guiElements.push_back(BtnOnlineTab);
	guiElements.push_back(BtnMenuSettings);
	guiElements.push_back(BtnExit);
}

int MainTab::update(Memory* memory, int currentIndex) {

	if (BtnPlayerTab->wasPressed()) {
		this->pGui->SetCurrentTab(this->playerTab);
		this->pGui->SetIndex(0);
	}
	if (BtnVehicleTab->wasPressed()) {
		this->pGui->SetCurrentTab(this->vehicleTab);
		this->pGui->SetIndex(0);
	}
	if (BtnWeaponTab->wasPressed()) {
		this->pGui->SetCurrentTab(this->weaponTab);
		this->pGui->SetIndex(0);
	}
	if (BtnOnlineTab->wasPressed()) {
		this->pGui->SetCurrentTab(this->onlineTab);
		this->pGui->SetIndex(0);
	}
	if (BtnMenuSettings->wasPressed()) {
		this->pGui->SetCurrentTab(this->menuTab);
		this->pGui->SetIndex(0);
	}
	if (BtnExit->wasPressed()) return 1;
	return 0;
}

/*
/	TODO: Player TAB;
*/
PlayerTab::PlayerTab(Gui* gui, Tab* parent) : Tab::Tab(gui) {
	this->pParent = parent;
	BtnGodmode = new ToggleButton(L"Godmode");
	BtnHeal = new GenericButton(L"Heal Player");
	BtnSliderWantedLvl = new SliderButton(L"Wanted Level", 0, 5, 1);
	BtnWalkSpeed = new SliderButton(L"Walk Speed", 0.1, 100, 0.1f);
	BtnSwimSpeed = new SliderButton(L"Swim Speed", 0.1, 100, 0.1f);
	BtnNeverWanted = new ToggleButton(L"Never Wanted (WIP)");
	BtnNPCsIgnore = new ToggleButton(L"NPCs Ignore (WIP)");
	BtnNoRagdoll = new ToggleButton(L"No Ragdoll");
	BtnSeatbelt = new ToggleButton(L"Seatbelt");
	BtnWaterproof = new ToggleButton(L"Waterproof (WIP)");
	guiElements.push_back(BtnGodmode);
	guiElements.push_back(BtnHeal);
	guiElements.push_back(BtnSliderWantedLvl);
	guiElements.push_back(BtnWalkSpeed);
	guiElements.push_back(BtnSwimSpeed);
	guiElements.push_back(BtnNeverWanted);
	guiElements.push_back(BtnNPCsIgnore);
	guiElements.push_back(BtnNoRagdoll);
	guiElements.push_back(BtnSeatbelt);
	guiElements.push_back(BtnWaterproof);
}

int PlayerTab::update(Memory* memory, int currentIndex)  {

	if (BtnGodmode->isToggled()) memory->WriteByte(memory->Godmode, memory->WORLD_OFFSET, 0x1);
	if (BtnGodmode->wasDisabled()) memory->WriteByte(memory->Godmode, memory->WORLD_OFFSET, 0x0);

	if (BtnHeal->wasPressed()) {
		float maxHP = memory->ReadFloat(memory->MaxHP, memory->WORLD_OFFSET);
		memory->WriteFloat(memory->CurrentHP, memory->WORLD_OFFSET, maxHP);
	}

	if (currentIndex != 2) BtnSliderWantedLvl->setValue(memory->ReadDWORD(memory->WantedLevel, memory->WORLD_OFFSET));
	if (BtnSliderWantedLvl->wasPressed()) memory->WriteDWORD(memory->WantedLevel, memory->WORLD_OFFSET, BtnSliderWantedLvl->getValue());

	if (currentIndex != 3)BtnWalkSpeed->setValue(memory->ReadFloat(memory->RunSpeed, memory->WORLD_OFFSET));
	if (BtnWalkSpeed->wasPressed()) memory->WriteFloat(memory->RunSpeed, memory->WORLD_OFFSET, BtnWalkSpeed->getValue());
	
	if (currentIndex != 4)BtnSwimSpeed->setValue(memory->ReadFloat(memory->SwimSpeed, memory->WORLD_OFFSET));
	if (BtnSwimSpeed->wasPressed()) memory->WriteFloat(memory->SwimSpeed, memory->WORLD_OFFSET, BtnSwimSpeed->getValue());

	if (BtnNeverWanted->isToggled()) memory->WriteByte(memory->WantedLevelCanChange, memory->WORLD_OFFSET, 0x1);
	if (BtnNeverWanted->wasDisabled()) memory->WriteByte(memory->WantedLevelCanChange, memory->WORLD_OFFSET, 0x0);

	if (BtnNPCsIgnore->isToggled()) memory->WriteByte(memory->NpcsIgnore, memory->WORLD_OFFSET, 0x450000);
	if (BtnNPCsIgnore->wasDisabled()) memory->WriteByte(memory->NpcsIgnore, memory->WORLD_OFFSET, 0x0);

	if (BtnNoRagdoll->isToggled()) memory->WriteByte(memory->Ragdoll, memory->WORLD_OFFSET, 0x20);
	if (BtnNoRagdoll->wasDisabled()) memory->WriteByte(memory->Ragdoll, memory->WORLD_OFFSET, 0x1);

	if (BtnSeatbelt->isToggled()) memory->WriteByte(memory->Seatbelt, memory->WORLD_OFFSET, 0xC9);
	if (BtnSeatbelt->wasDisabled()) memory->WriteByte(memory->Seatbelt, memory->WORLD_OFFSET, 0xC8);

	if (BtnWaterproof->isToggled()) memory->WriteByte(memory->Waterproof, memory->WORLD_OFFSET, 0x1000000);
	if (BtnWaterproof->wasDisabled()) memory->WriteByte(memory->Waterproof, memory->WORLD_OFFSET, 0x0);

	return 0;
}

/*
/	TODO: Vehicle Handling TAB;
*/
CustomizationTab::CustomizationTab(Gui* gui, Tab* parent) : Tab::Tab(gui) {
	this->pParent = parent;
	BtnVehicleNeonR = new SliderButton(L"Neon Lights (Red)", 0, 255, 1.0f);
	BtnVehicleNeonG = new SliderButton(L"Neon Lights (Green)", 0, 255, 1.0f);
	BtnVehicleNeonB = new SliderButton(L"Neon Lights (Blue)", 0, 255, 1.0f);
	BtnVehicleNeonFront = new ToggleButton(L"Neon Front Lights");
	BtnVehicleNeonBack = new ToggleButton(L"Neon Back Lights");
	BtnVehicleNeonLeft = new ToggleButton(L"Neon Left Lights");
	BtnVehicleNeonRight = new ToggleButton(L"Neon R Lights");

	BtnVehiclePrimaryRed = new SliderButton(L"Primary Color (Red)", 0, 255, 1.0f);
	BtnVehiclePrimaryGreen = new SliderButton(L"Primary Color (Green)", 0, 255, 1.0f);
	BtnVehiclePrimaryBlue = new SliderButton(L"Primary Color (Blue)", 0, 255, 1.0f);

	guiElements.push_back(BtnVehicleNeonR);
	guiElements.push_back(BtnVehicleNeonG);
	guiElements.push_back(BtnVehicleNeonB);
	guiElements.push_back(BtnVehicleNeonFront);
	guiElements.push_back(BtnVehicleNeonBack);
	guiElements.push_back(BtnVehicleNeonLeft);
	guiElements.push_back(BtnVehicleNeonRight);
	guiElements.push_back(BtnVehiclePrimaryRed);
	guiElements.push_back(BtnVehiclePrimaryGreen);
	guiElements.push_back(BtnVehiclePrimaryBlue);
}

int CustomizationTab::update(Memory* memory, int currentIndex) {

	if (currentIndex != 0) BtnVehicleNeonR->setValue(memory->ReadByte(memory->VehicleNeonLightR, memory->WORLD_OFFSET));
	if (BtnVehicleNeonR->wasPressed()) memory->WriteByte(memory->VehicleNeonLightR, memory->WORLD_OFFSET, BtnVehicleNeonR->getValue());

	if (currentIndex != 1) BtnVehicleNeonG->setValue(memory->ReadByte(memory->VehicleNeonLightG, memory->WORLD_OFFSET));
	if (BtnVehicleNeonG->wasPressed()) memory->WriteByte(memory->VehicleNeonLightG, memory->WORLD_OFFSET, BtnVehicleNeonG->getValue());

	if (currentIndex != 2) BtnVehicleNeonB->setValue(memory->ReadByte(memory->VehicleNeonLightB, memory->WORLD_OFFSET));
	if (BtnVehicleNeonB->wasPressed()) memory->WriteByte(memory->VehicleNeonLightB, memory->WORLD_OFFSET, BtnVehicleNeonB->getValue());

	if (BtnVehicleNeonFront->isToggled()) memory->WriteByte(memory->VehicleNeonLightsFront, memory->WORLD_OFFSET, 0x1);
	if (BtnVehicleNeonFront->wasDisabled()) memory->WriteByte(memory->VehicleNeonLightsFront, memory->WORLD_OFFSET, 0x0);

	if (BtnVehicleNeonBack->isToggled()) memory->WriteByte(memory->VehicleNeonLightsBack, memory->WORLD_OFFSET, 0x1);
	if (BtnVehicleNeonBack->wasDisabled()) memory->WriteByte(memory->VehicleNeonLightsBack, memory->WORLD_OFFSET, 0x0);

	if (BtnVehicleNeonLeft->isToggled()) memory->WriteByte(memory->VehicleNeonLightsLeft, memory->WORLD_OFFSET, 0x1);
	if (BtnVehicleNeonLeft->wasDisabled()) memory->WriteByte(memory->VehicleNeonLightsLeft, memory->WORLD_OFFSET, 0x0);

	if (BtnVehicleNeonRight->isToggled()) memory->WriteByte(memory->VehicleNeonLightsRight, memory->WORLD_OFFSET, 0x1);
	if (BtnVehicleNeonRight->wasDisabled()) memory->WriteByte(memory->VehicleNeonLightsRight, memory->WORLD_OFFSET, 0x0);

	if (currentIndex != 7) BtnVehiclePrimaryRed->setValue(memory->ReadByte(memory->VehiclePrimaryRed, memory->WORLD_OFFSET));
	if (BtnVehiclePrimaryRed->wasPressed()) memory->WriteByte(memory->VehiclePrimaryRed, memory->WORLD_OFFSET, BtnVehiclePrimaryRed->getValue());

	if (currentIndex != 8) BtnVehiclePrimaryGreen->setValue(memory->ReadByte(memory->VehiclePrimaryGreen, memory->WORLD_OFFSET));
	if (BtnVehiclePrimaryGreen->wasPressed()) memory->WriteByte(memory->VehiclePrimaryGreen, memory->WORLD_OFFSET, BtnVehiclePrimaryGreen->getValue());

	if (currentIndex != 9) BtnVehiclePrimaryBlue->setValue(memory->ReadByte(memory->VehiclePrimaryBlue, memory->WORLD_OFFSET));
	if (BtnVehiclePrimaryBlue->wasPressed()) memory->WriteByte(memory->VehiclePrimaryBlue, memory->WORLD_OFFSET, BtnVehiclePrimaryBlue->getValue());

	return 0;
}

/*
/	TODO: Vehicle Tuning TAB;
*/
TuningTab::TuningTab(Gui* gui, Tab* parent) : Tab::Tab(gui) {
	this->pParent = parent;
	BtnMaxEngine = new ToggleButton(L"Max Engine");
	BtnMaxBrakes = new ToggleButton(L"Max Brakes");
	BtnMaxTransmission = new ToggleButton(L"Max Transmission");
	BtnMaxSuspension = new ToggleButton(L"Max Suspension");
	BtnMaxArmor = new ToggleButton(L"Max Armor");
	BtnMaxTurbo = new ToggleButton(L"Max Turbo");

	guiElements.push_back(BtnMaxEngine);
	guiElements.push_back(BtnMaxBrakes);
	guiElements.push_back(BtnMaxTransmission);
	guiElements.push_back(BtnMaxSuspension);
	guiElements.push_back(BtnMaxArmor);
	guiElements.push_back(BtnMaxTurbo);
}

int TuningTab::update(Memory* memory, int currentIndex) {
	if (BtnMaxEngine->isToggled()) memory->WriteByte(memory->VehicleEngine, memory->WORLD_OFFSET, 0x3);
	if (BtnMaxEngine->wasDisabled()) memory->WriteByte(memory->VehicleEngine, memory->WORLD_OFFSET, 0x0);

	if (BtnMaxBrakes->isToggled()) memory->WriteByte(memory->VehicleBrakes, memory->WORLD_OFFSET, 0x6);
	if (BtnMaxBrakes->wasDisabled()) memory->WriteByte(memory->VehicleBrakes, memory->WORLD_OFFSET, 0x0);

	if (BtnMaxTransmission->isToggled()) memory->WriteByte(memory->VehicleTransmission, memory->WORLD_OFFSET, 0x8);
	if (BtnMaxTransmission->wasDisabled()) memory->WriteByte(memory->VehicleTransmission, memory->WORLD_OFFSET, 0x0);

	if (BtnMaxSuspension->isToggled()) memory->WriteByte(memory->VehicleSuspension, memory->WORLD_OFFSET, 0x1B);
	if (BtnMaxSuspension->wasDisabled()) memory->WriteByte(memory->VehicleSuspension, memory->WORLD_OFFSET, 0x0);

	if (BtnMaxArmor->isToggled()) memory->WriteByte(memory->VehicleArmor, memory->WORLD_OFFSET, 0x1B);
	if (BtnMaxArmor->wasDisabled()) memory->WriteByte(memory->VehicleArmor, memory->WORLD_OFFSET, 0x0);

	if (BtnMaxTurbo->isToggled()) memory->WriteByte(memory->VehicleTurbo, memory->WORLD_OFFSET, 0x1);
	if (BtnMaxTurbo->wasDisabled())  memory->WriteByte(memory->VehicleTurbo, memory->WORLD_OFFSET, 0x0);

	return 0;
}

/*
/	TODO: Vehicle TAB;
*/
VehicleTab::VehicleTab(Gui* gui, Tab* parent) : Tab::Tab(gui) {
	this->pParent = parent;
	customizationTab = new CustomizationTab(gui, this);
	tuningTab = new TuningTab(gui, this);
	BtnVehicleGodmode = new ToggleButton(L"Vehicle Godmode");
	BtnCustomization = new GenericButton(L"Customization", true);
	BtnVehicleGravity = new SliderButton(L"Vehicle Gravity", -24, 24, 0.1f);
	BtnVehicleMass = new SliderButton(L"Mass", 1, 100000, 1.0f);
	BtnVehicleBuoyancy = new SliderButton(L"Buoyancy", 1, 100000, 1.0f);
	BtnVehicleAcceleration = new SliderButton(L"Acceleration", 0.1, 100000, 0.1f);
	BtnVehicleUpshift = new SliderButton(L"Upshift", 0.1, 100000, 0.1f);
	BtnVehicleDownshift = new SliderButton(L"Downshift", 0.1, 100000, 0.1f);
	BtnVehicleBrakeForce = new SliderButton(L"Brake Force", 0.1, 100000, 0.1f);
	BtnVehicleHandBrakeForce = new SliderButton(L"Hand Brake Force", 0.1, 100000, 0.1f);
	BtnVehicleTractionCurveMin = new SliderButton(L"Traction Curve Min.", 0.1, 100000, 0.1f);
	BtnVehicleTractionCurveMax = new SliderButton(L"Traction Curve Max.", 0.1, 100000, 0.1f);
	BtnVehicleSuspensionForce = new SliderButton(L"Suspension Force", 0.1, 100000, 0.1f);
	BtnVehicleSuspensionHeight = new SliderButton(L"Suspension Height", -10000, 100000, 0.1f);

	guiElements.push_back(BtnVehicleGodmode);
	guiElements.push_back(BtnCustomization);
	guiElements.push_back(BtnVehicleGravity);
	guiElements.push_back(BtnVehicleMass);
	guiElements.push_back(BtnVehicleBuoyancy);
	guiElements.push_back(BtnVehicleAcceleration);
	guiElements.push_back(BtnVehicleUpshift);
	guiElements.push_back(BtnVehicleDownshift);
	guiElements.push_back(BtnVehicleBrakeForce);
	guiElements.push_back(BtnVehicleHandBrakeForce);
	guiElements.push_back(BtnVehicleTractionCurveMin);
	guiElements.push_back(BtnVehicleTractionCurveMax);
	guiElements.push_back(BtnVehicleSuspensionForce);
	guiElements.push_back(BtnVehicleSuspensionHeight);


}

int VehicleTab::update(Memory* memory, int currentIndex) {
	if (BtnVehicleGodmode->isToggled()) memory->WriteByte(memory->VehicleGodmode, memory->WORLD_OFFSET, 0x1);
	if (BtnVehicleGodmode->wasDisabled()) memory->WriteByte(memory->VehicleGodmode, memory->WORLD_OFFSET, 0x0);


	if (BtnCustomization->wasPressed()) {
		this->pGui->SetCurrentTab(this->customizationTab);
		this->pGui->SetIndex(0);
	}

	if (currentIndex != 2) BtnVehicleGravity->setValue(memory->ReadFloat(memory->VehicleGravity, memory->WORLD_OFFSET));
	if (BtnVehicleGravity->wasPressed()) memory->WriteFloat(memory->VehicleGravity, memory->WORLD_OFFSET, BtnVehicleGravity->getValue());

	if (currentIndex != 3) BtnVehicleMass->setValue(memory->ReadFloat(memory->VehicleMass, memory->WORLD_OFFSET));
	if (BtnVehicleMass->wasPressed()) memory->WriteFloat(memory->VehicleMass, memory->WORLD_OFFSET, BtnVehicleMass->getValue());

	if (currentIndex != 4) BtnVehicleBuoyancy->setValue(memory->ReadFloat(memory->VehicleBuoyancy, memory->WORLD_OFFSET));
	if (BtnVehicleBuoyancy->wasPressed()) memory->WriteFloat(memory->VehicleBuoyancy, memory->WORLD_OFFSET, BtnVehicleBuoyancy->getValue());

	if (currentIndex != 5) BtnVehicleAcceleration->setValue(memory->ReadFloat(memory->VehicleAcceleration, memory->WORLD_OFFSET));
	if (BtnVehicleAcceleration->wasPressed()) memory->WriteFloat(memory->VehicleAcceleration, memory->WORLD_OFFSET, BtnVehicleAcceleration->getValue());

	if (currentIndex != 6) BtnVehicleUpshift->setValue(memory->ReadFloat(memory->VehicleUpshift, memory->WORLD_OFFSET));
	if (BtnVehicleUpshift->wasPressed()) memory->WriteFloat(memory->VehicleUpshift, memory->WORLD_OFFSET, BtnVehicleUpshift->getValue());

	if (currentIndex != 7) BtnVehicleDownshift->setValue(memory->ReadFloat(memory->VehicleDownshift, memory->WORLD_OFFSET));
	if (BtnVehicleDownshift->wasPressed()) memory->WriteFloat(memory->VehicleDownshift, memory->WORLD_OFFSET, BtnVehicleDownshift->getValue());

	if (currentIndex != 8) BtnVehicleBrakeForce->setValue(memory->ReadFloat(memory->VehicleBrakeForce, memory->WORLD_OFFSET));
	if (BtnVehicleBrakeForce->wasPressed()) memory->WriteFloat(memory->VehicleBrakeForce, memory->WORLD_OFFSET, BtnVehicleBrakeForce->getValue());

	if (currentIndex != 9) BtnVehicleHandBrakeForce->setValue(memory->ReadFloat(memory->VehicleHandbrakeForce, memory->WORLD_OFFSET));
	if (BtnVehicleHandBrakeForce->wasPressed()) memory->WriteFloat(memory->VehicleHandbrakeForce, memory->WORLD_OFFSET, BtnVehicleHandBrakeForce->getValue());

	if (currentIndex != 10) BtnVehicleTractionCurveMin->setValue(memory->ReadFloat(memory->VehicleTractionCurveMin, memory->WORLD_OFFSET));
	if (BtnVehicleTractionCurveMin->wasPressed()) memory->WriteFloat(memory->VehicleTractionCurveMin, memory->WORLD_OFFSET, BtnVehicleTractionCurveMin->getValue());

	if (currentIndex != 11) BtnVehicleTractionCurveMax->setValue(memory->ReadFloat(memory->VehicleTractionCurveMax, memory->WORLD_OFFSET));
	if (BtnVehicleTractionCurveMax->wasPressed()) memory->WriteFloat(memory->VehicleTractionCurveMax, memory->WORLD_OFFSET, BtnVehicleTractionCurveMax->getValue());

	if (currentIndex != 12) BtnVehicleSuspensionForce->setValue(memory->ReadFloat(memory->VehicleSuspensionForce, memory->WORLD_OFFSET));
	if (BtnVehicleSuspensionForce->wasPressed()) memory->WriteFloat(memory->VehicleSuspensionForce, memory->WORLD_OFFSET, BtnVehicleSuspensionForce->getValue());

	if (currentIndex != 13) BtnVehicleSuspensionHeight->setValue(memory->ReadFloat(memory->VehicleSuspensionHeight, memory->WORLD_OFFSET));
	if (BtnVehicleSuspensionHeight->wasPressed()) memory->WriteFloat(memory->VehicleSuspensionHeight, memory->WORLD_OFFSET, BtnVehicleSuspensionHeight->getValue());
	return 0;
}

/*
/	TODO: Weapon TAB;
*/
WeaponTab::WeaponTab(Gui* gui, Tab* parent) : Tab::Tab(gui) {
	this->pParent = parent;
	BtnInfiniteAmmo = new ToggleButton(L"Infinite Ammo");
	BtnFillAmmo = new GenericButton(L"Fill Ammo", false);
	BtnNoReload = new ToggleButton(L"No Reload");
	guiElements.push_back(BtnInfiniteAmmo);
	guiElements.push_back(BtnFillAmmo);
	guiElements.push_back(BtnNoReload);
}

int WeaponTab::update(Memory* memory, int currentIndex) {
	if (BtnInfiniteAmmo->isToggled()) {
		memory->WriteByte(memory->InfiniteAmmo1, memory->AMMO_OFFSET, 0x90);
		memory->WriteByte(memory->InfiniteAmmo2, memory->AMMO_OFFSET, 0x90);
		memory->WriteByte(memory->InfiniteAmmo3, memory->AMMO_OFFSET, 0x90);
	}
	if (BtnInfiniteAmmo->wasDisabled()) {
		memory->WriteByte(memory->InfiniteAmmo1, memory->AMMO_OFFSET, 0x41);
		memory->WriteByte(memory->InfiniteAmmo2, memory->AMMO_OFFSET, 0x2B);
		memory->WriteByte(memory->InfiniteAmmo3, memory->AMMO_OFFSET, 0xD1);
	}
	if (BtnFillAmmo->wasPressed()) memory->WriteDWORD(memory->FillAmmo, memory->WORLD_OFFSET, 999);

	if (BtnNoReload->isToggled()) {
		memory->WriteByte(memory->NoReload1, memory->CLIP_OFFSET, 0x90);
		memory->WriteByte(memory->NoReload2, memory->CLIP_OFFSET, 0x90);
		memory->WriteByte(memory->NoReload3, memory->CLIP_OFFSET, 0x90);
	}
	if (BtnNoReload->wasDisabled()) {
		memory->WriteByte(memory->NoReload1, memory->CLIP_OFFSET, 0x41);
		memory->WriteByte(memory->NoReload2, memory->CLIP_OFFSET, 0x2B);
		memory->WriteByte(memory->NoReload3, memory->CLIP_OFFSET, 0xC9);
	}
	return 0;
}

OnlineTab::OnlineTab(Gui* gui, Tab* parent) : Tab::Tab(gui) {
	this->pParent = parent;
	BtnDropMoney = new GenericButton(L"Drop Money", false);
	guiElements.push_back(BtnDropMoney);
}

int OnlineTab::update(Memory* memory, int currentIndex) {
	if (BtnDropMoney->wasPressed()) {
		
	}
	return 0;
}

MenuTab::MenuTab(Gui* gui, Tab* parent) : Tab::Tab(gui) {
	this->pParent = parent;
	BtnXPosition = new SliderButton(L"X Position", 0, 1920, 1.0f, false);
	BtnYPosition = new SliderButton(L"Y Position", 0, 1080, 1.0f, false);
	BtnHue = new SliderButton(L"Hue", 0, 360, 1.0f, false);
	guiElements.push_back(BtnXPosition);
	guiElements.push_back(BtnYPosition);
	guiElements.push_back(BtnHue);
}

int MenuTab::update(Memory* memory, int currentIndex) {
	if (BtnXPosition->wasPressed());
	if (BtnYPosition->wasPressed());
	if (BtnHue->wasPressed());
	return 0;
}