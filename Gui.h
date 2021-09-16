#pragma once

#ifndef GUI_HEADER
#define GUI_HEADER

#include <vector>
#include "Buttons.h"
#include "Memory.h"
#include <stack>


class Tab;

class Gui
{
	Tab* currentTab;
	Memory* mm;
	Graphics* graphics;
public:
	int Init(HWND hWnd);
	int UpdateAndDraw();
	void ToggleVisibility();
	void SetCurrentTab(Tab* tab);
	void AddTab(Tab* tab);
	void SetIndex(int i);
};

class Tab {
public:
	std::vector<GenericButton*> guiElements;
	Gui* pGui;
	Tab* pParent;

	Tab(Gui* gui);
	Tab(Gui* gui, Tab* parent);

	void returnToParent();

	std::vector<GenericButton*> getGuiElements();
	GenericButton* getElementAtIndex(int index);
	virtual int update(Memory* memory, int currentIndex);
};

class PlayerTab : public Tab {
public:
	ToggleButton* BtnGodmode;
	GenericButton* BtnHeal;

	SliderButton* BtnSliderWantedLvl;
	SliderButton* BtnWalkSpeed;
	SliderButton* BtnSwimSpeed;

	ToggleButton* BtnNeverWanted;
	ToggleButton* BtnNPCsIgnore;
	ToggleButton* BtnNoRagdoll;
	ToggleButton* BtnSeatbelt;
	ToggleButton* BtnWaterproof;

	PlayerTab(Gui* gui);
	PlayerTab(Gui* gui, Tab* parent);
	virtual int update(Memory* memory, int currentIndex) override;
};

class CustomizationTab : public Tab {
public:

	SliderButton* BtnVehicleNeonR;
	SliderButton* BtnVehicleNeonG;
	SliderButton* BtnVehicleNeonB;
	ToggleButton* BtnVehicleNeonFront;
	ToggleButton* BtnVehicleNeonBack;
	ToggleButton* BtnVehicleNeonLeft;
	ToggleButton* BtnVehicleNeonRight;

	SliderButton* BtnVehiclePrimaryRed;
	SliderButton* BtnVehiclePrimaryGreen;
	SliderButton* BtnVehiclePrimaryBlue;

	CustomizationTab(Gui* gui);
	CustomizationTab(Gui* gui, Tab* parent);
	virtual int update(Memory* memory, int currentIndex) override;
};

class TuningTab : public Tab {
public:
	ToggleButton* BtnMaxEngine;
	ToggleButton* BtnMaxBrakes;
	ToggleButton* BtnMaxTransmission;
	ToggleButton* BtnMaxSuspension;
	ToggleButton* BtnMaxArmor;
	ToggleButton* BtnMaxTurbo;
	TuningTab(Gui* gui);
	TuningTab(Gui* gui, Tab* parent);
	virtual int update(Memory* memory, int currentIndex) override;
};

class VehicleTab : public Tab {
public:
	CustomizationTab* customizationTab;
	TuningTab* tuningTab;

	ToggleButton* BtnVehicleGodmode;	
	GenericButton* BtnCustomization;

	SliderButton* BtnVehicleMass;
	SliderButton* BtnVehicleBuoyancy;
	SliderButton* BtnVehicleAcceleration;
	SliderButton* BtnVehicleUpshift;
	SliderButton* BtnVehicleDownshift;
	SliderButton* BtnVehicleBrakeForce;
	SliderButton* BtnVehicleHandBrakeForce;
	SliderButton* BtnVehicleTractionCurveMin;
	SliderButton* BtnVehicleTractionCurveMax;
	SliderButton* BtnVehicleSuspensionForce;
	SliderButton* BtnVehicleSuspensionHeight;
	SliderButton* BtnVehicleGravity;

	VehicleTab(Gui* gui);
	VehicleTab(Gui* gui, Tab* parent);
	virtual int update(Memory* memory, int currentIndex) override;
};

class WeaponTab : public Tab {
public:
	ToggleButton* BtnInfiniteAmmo;
	GenericButton* BtnFillAmmo;
	ToggleButton* BtnNoReload;
	WeaponTab(Gui* gui);
	WeaponTab(Gui* gui, Tab* parent);
	virtual int update(Memory* memory, int currentIndex) override;

};

class TeleportTab : public Tab {
public:
	TeleportTab(Gui* gui);
	TeleportTab(Gui* gui, Tab* parent);
	virtual int update(Memory* memory, int currentIndex) override;
};

class OnlineTab : public Tab {
public:
	GenericButton* BtnDropMoney;
	OnlineTab(Gui* gui);
	OnlineTab(Gui* gui, Tab* parent);
	virtual int update(Memory* memory, int currentIndex) override;
};

class MenuTab : public Tab {
public:
	SliderButton* BtnXPosition;
	SliderButton* BtnYPosition;
	SliderButton* BtnHue;
	MenuTab(Gui* gui);
	MenuTab(Gui* gui, Tab* parent);
	virtual int update(Memory* memory, int currentIndex) override;
};

class MainTab : public Tab {
public:

	GenericButton* BtnPlayerTab;
	GenericButton* BtnVehicleTab;
	GenericButton* BtnWeaponTab;
	GenericButton* BtnTeleportTab;
	GenericButton* BtnOnlineTab;
	GenericButton* BtnMenuSettings;
	GenericButton* BtnExit;

	PlayerTab* playerTab;
	VehicleTab* vehicleTab;
	WeaponTab* weaponTab;
	OnlineTab* onlineTab;
	MenuTab* menuTab;

	MainTab(Gui* gui);
	MainTab(Gui* gui, Tab* parent);
	virtual int update(Memory* memory, int currentIndex) override;
};
#endif
