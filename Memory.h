#pragma once

#ifndef MEMORY_HEADER
#define MEMORY_HEADER

#include <iostream>
#include <Windows.h>
#include <TlHelp32.h> //PROCESSENTRY
#include <vector>

class Memory
{
private:

	const uintptr_t PLAYER_BASE_OFFSET = 0x08;

	// Entity Info
	const uintptr_t ENTITY_POS_OFFSET = 0x90;
	const uintptr_t ENTITY_GODMODE_OFFSET = 0x189;
	const uintptr_t ENTITY_HEALTH_OFFSET = 0x280;
	const uintptr_t ENTITY_MAX_HEALTH_OFFSET = 0x2A0;

	// Player Offsets
	const uintptr_t PLAYER_INFO_OFFSET = 0x10C8;
	const uintptr_t PLAYER_VEHICLE_OFFSET = 0xD30;

	// Player Info Offsets
	const uintptr_t PLAYER_INFO_NAME_OFFSET = 0xA4;
	const uintptr_t PLAYER_INFO_WANTED_LEVEL_OFFSET = 0x888;
	const uintptr_t PLAYER_INFO_SWIM_SPEED_OFFSET = 0x170;
	const uintptr_t PLAYER_INFO_RUN_SPEED_OFFSET = 0xCF0;
	const uintptr_t PLAYER_INFO_WANTED_LEVEL_CAN_CHANGE_OFFSET = 0x73C;
	const uintptr_t PLAYER_INFO_NPCS_IGNORE = 0x870;
	const uintptr_t PLAYER_RAGDOLL_OFFSET = 0x10B8;							//byte; 0x20 = off; 0x00/0x01 = on
	const uintptr_t PLAYER_SEATBELT_OFFSET = 0x140C;						//byte; 0xC8 = off; 0xC9 = on
	const uintptr_t PLAYER_WATERPROOF_OFFSET = 0x188;						//DWORD; +0x1000000 = on

	// Vehicle Offsets
	const uintptr_t VEHICLE_GOD_OFFSET = 0x189;
	const uintptr_t VEHICLE_COLOR_OPTIONS_OFFSET = 0x48;
	const uintptr_t VEHICLE_DEFORM_GOD_OFFSET = 0x944; // 0x8C = on, 0x9C = off
	const uintptr_t VEHICLE_HANDLING_OFFSET = 0x938;
	const uintptr_t VEHICLE_GRAVITY_OFFSET = 0xC5C; // float
	const uintptr_t VEHICLE_BULLETPROOF_TIRE_OFFSET = 0x943; // byte
	const uintptr_t VEHICLE_BOOST_OFFSET = 0x320; // float
	const uintptr_t VEHICLE_RECHARGE_SPEED_OFFSET = 0x324; // float
	const uintptr_t VEHICLE_MISSILES_OFFSET = 0x1280; //byte
	const uintptr_t VEHICLE_BOMBS_OFFSET = 0x1294; //byte
	const uintptr_t VEHICLE_COUNTERMEASURES_OFFSET = 0x1298;

	// Vehicle Color Offset
	const uintptr_t VEHICLE_COLOR_OFFSET = 0x20;
	const uintptr_t VEHICLE_COLOR_PRIMARY_RED_OFFSET = 0xA6; // byte
	const uintptr_t VEHICLE_COLOR_PRIMARY_GREEN_OFFSET = 0xA5; // byte
	const uintptr_t VEHICLE_COLOR_PRIMARY_BLUE_OFFSET = 0xA4; // byte
	const uintptr_t VEHICLE_COLOR_PRIMARY_ALPHA_OFFSET = 0xA7; // byte
	const uintptr_t VEHICLE_COLOR_SECONDARY_RED_OFFSET = 0xAA; // byte
	const uintptr_t VEHICLE_COLOR_SECONDARY_GREEN_OFFSET = 0xA9; // byte
	const uintptr_t VEHICLE_COLOR_SECONDARY_BLUE_OFFSET = 0xA8; // byte
	const uintptr_t VEHICLE_COLOR_SECONDARY_ALPHA_OFFSET = 0xAB; // byte

	// Vehicle Handling Offset
	const uintptr_t VEHICLE_HANDLING_MASS_OFFSET = 0xC; // float
	const uintptr_t VEHICLE_HANDLING_BUOYANCY_OFFSET = 0x40; // float
	const uintptr_t VEHICLE_HANDLING_ACCELERATION_OFFSET = 0x4C; // float
	const uintptr_t VEHICLE_HANDLING_UPSHIFT_OFFSET = 0x58; // float
	const uintptr_t VEHICLE_HANDLING_DOWNSHIFT_OFFSET = 0x5C; // float
	const uintptr_t VEHICLE_HANDLING_BRAKEFORCE_OFFSET = 0x6C; // float
	const uintptr_t VEHICLE_HANDLING_HANDBRAKEFORCE_OFFSET = 0x7C; // float
	const uintptr_t VEHICLE_HANDLING_TRACTION_CURVE_MIN_OFFSET = 0x90; // float
	const uintptr_t VEHICLE_HANDLING_TRACTION_CURVE_MAX_OFFSET = 0x94; // float
	const uintptr_t VEHICLE_HANDLING_SUSPENSION_FORCE_OFFSET = 0xBC; // float
	const uintptr_t VEHICLE_HANDLING_SUSPENSION_HEIGHT_OFFSET = 0xD0; // float
	const uintptr_t VEHICLE_HANDLING_COLLISION_DAMAGE_MP_OFFSET = 0xF0; // float
	const uintptr_t VEHICLE_HANDLING_WEAPON_DAMAGE_MP_OFFSET = 0xF4; // float
	const uintptr_t VEHICLE_HANDLING_DEFORM_MULTIPLIER_OFFSET = 0xF8; // float
	const uintptr_t VEHICLE_HANDLING_ENGINE_DAMAGE_MP_OFFSET = 0xFC; // float

	// Vehicle Tuning Offset
	const uintptr_t VEHICLE_CUSTOM_OFFSET = 0x48;
	const uintptr_t	VEHICLE_CUSTOM_EM_OFFSET = 0x3D6;			//btEngineManagementSystem; 0x3 = max
	const uintptr_t	VEHICLE_CUSTOM_BRAKES_OFFSET = 0x3D7;			//btBrakes; 0x6 = max
	const uintptr_t	VEHICLE_CUSTOM_TRANSMISSION_OFFSET = 0x3D8;		//btTransmission; 0x8 = max
	const uintptr_t	VEHICLE_CUSTOM_SUSPENSION_OFFSET = 0x3DA;			//btSuspension; 0x1B = max
	const uintptr_t	VEHICLE_CUSTOM_ARMOR_OFFSET = 0x3DB;	//btArmor; 0x1B = max
	const uintptr_t	VEHICLE_CUSTOM_TURBO_TUNING_OFFSET = 0x3DD;			//btTurboTuning; 0x1 = on
	const uintptr_t	VEHICLE_CUSTOM_NEON_LIGHT_R_OFFSET = 0x3A2;		//btNeonLightRed
	const uintptr_t	VEHICLE_CUSTOM_NEON_LIGHT_G_OFFSET = 0x3A1;		//btNeonLightGreen
	const uintptr_t	VEHICLE_CUSTOM_NEON_LIGHT_B_OFFSET = 0x3A0;		//btNeonLightBlue
	const uintptr_t	VEHICLE_CUSTOM_NEON_LIGHTS_L_OFFSET = 0x402;		//btNeonLightLeft; 0x0 = off; 0x1 = on
	const uintptr_t	VEHICLE_CUSTOM_NEON_LIGHTS_R_OFFSET = 0x403;	//btNeonLightRight; 0x0 = off; 0x1 = on
	const uintptr_t	VEHICLE_CUSTOM_NEON_LIGHTS_F_OFFSET = 0x404;	//btNeonLightFront; 0x0 = off; 0x1 = on
	const uintptr_t	VEHICLE_CUSTOM_NEON_LIGHTS_B_OFFSET = 0x405;	//btNeonLightBack; 0x0 = off; 0x1 = on
	const uintptr_t	VEHICLE_CUSTOM_TIRE_SMOKE_OFFSET = 0x3DF;	//btTyreSmoke; 0x1 = on
	const uintptr_t	VEHICLE_CUSTOM_TIRE_SMOKE_R_OFFSET = 0x3FC;	//btTyreSmokeRed
	const uintptr_t	VEHICLE_CUSTOM_TIRE_SMOKE_G_OFFSET = 0x3FD;		//btTyreSmokeGreen
	const uintptr_t	VEHICLE_CUSTOM_TIRE_SMOKE_B_OFFSET = 0x3FE;		//btTyreSmokeBlue
	const uintptr_t	VEHICLE_CUSTOM_LIMO_WINDOWS_OFFSET = 0x3FF;			//btLimoWindows; 0x1 = on

	// Weapon Offsets
	const uintptr_t WEAPON_MANAGER_OFFSET = 0x10D8; // From Player
	const uintptr_t WEAPON_CURRENT_OFFSET = 0x20; // From WeaponManager
	const uintptr_t WEAPON_AMMOINFO_OFFSET = 0x60; // From Weapon
	const uintptr_t WEAPON_AMMOINFO_MAX_OFFSET = 0x28;
	const uintptr_t WEAPON_AMMOINFO_CUR_1_OFFSET = 0x08;			//ptr lvl 1, ptr 1
	const uintptr_t WEAPON_AMMOINFO_CUR_2_OFFSET = 0x00;			//ptr tr lvl 2, ptr 1
	const uintptr_t WEAPON_AMMOINFO_CURAMMO_OFFSET = 0x18;			//offset to cur ammo
	const uintptr_t WEAPON_AMMOINFO_TYPE_OFFSET = 0x0C;			//offset to projectile type?
	const uintptr_t WEAPON_SPREAD_OFFSET = 0x7C;			//float set to 0
	const uintptr_t WEAPON_BULLET_DMG_OFFSET = 0xBC;			//float times 10 (so when 0, it will stay 0)
	const uintptr_t WEAPON_RELOAD_MULTIPLIER_OFFSET = 0x134;			//float times 10
	const uintptr_t WEAPON_RECOIL_OFFSET = 0x2F4;			//float set to 0
	const uintptr_t WEAPON_MODEL_HASH_OFFSET = 0x14;
	const uintptr_t WEAPON_NAME_HASH_OFFSET = 0x10;
	const uintptr_t WEAPON_RELOAD_VEHICLE_OFFSET = 0x130;
	const uintptr_t WEAPON_RANGE_OFFSET = 0x28C;
	const uintptr_t WEAPON_SPINUP_OFFSET = 0x144;
	const uintptr_t WEAPON_SPIN_OFFSET = 0x148;
	const uintptr_t WEAPON_BULLET_BATCH_OFFSET = 0x124;			//dwBulletInBatch
	const uintptr_t WEAPON_MUZZLE_VELOCITY_OFFSET = 0x11C;			//fMuzzleVelocity
	const uintptr_t WEAPON_IMPACT_TYPE_OFFSET = 0x20;			//dwImpactType; 1: Fists,3; Bullets,5: Explosives
	const uintptr_t WEAPON_IMPACT_EXPLOSION_OFFSET = 0x24;			//dwImpactExplosion
	const uintptr_t WEAPON_PENETRATION_OFFSET = 0x110;			//fPenetration
	const uintptr_t WEAPON_FORCE_ON_PED_OFFSET = 0xDC;			//fForceOnPed
	const uintptr_t WEAPON_FORCE_ON_VEHICLE_OFFSET = 0xE0;			//fForceOnVehicle(Bullet Mass)
	const uintptr_t WEAPON_FORCE_ON_HELI_OFFSET = 0xE4;			//fForceOnHeli

	uintptr_t getProcessID();
	uintptr_t getModuleBaseAddress(DWORD pID);

public:
	uintptr_t pID = NULL;
	uintptr_t baseAddress = NULL;
	HANDLE hProcess = NULL;

	const uintptr_t WORLD_OFFSET = 0x25333D8;
	const uintptr_t AMMO_OFFSET = 0x01036319;
	const uintptr_t CLIP_OFFSET = 0x010362D4;
	const uintptr_t BLIP_OFFSET = 0x1FA9720;
	const uintptr_t REPLAY_OFFSET = 0x1F0A788;
	const uintptr_t PLAYERLIST_OFFSET = 0x1DDACC8;
	const uintptr_t GLOBAL_OFFSET = 0x2D765E0;

	// Offset Arrays
	// Player Arrays
	std::vector<uintptr_t> Godmode = { PLAYER_BASE_OFFSET , ENTITY_GODMODE_OFFSET };
	std::vector<uintptr_t> CurrentHP = { PLAYER_BASE_OFFSET, ENTITY_HEALTH_OFFSET};
	std::vector<uintptr_t> MaxHP = { PLAYER_BASE_OFFSET, ENTITY_MAX_HEALTH_OFFSET };
	std::vector<uintptr_t> WantedLevel = { PLAYER_BASE_OFFSET , PLAYER_INFO_OFFSET, PLAYER_INFO_WANTED_LEVEL_OFFSET };
	std::vector<uintptr_t> RunSpeed = { PLAYER_BASE_OFFSET, PLAYER_INFO_OFFSET, PLAYER_INFO_RUN_SPEED_OFFSET };
	std::vector<uintptr_t> SwimSpeed = { PLAYER_BASE_OFFSET, PLAYER_INFO_OFFSET, PLAYER_INFO_SWIM_SPEED_OFFSET };
	std::vector<uintptr_t> WantedLevelCanChange = { PLAYER_BASE_OFFSET, PLAYER_INFO_OFFSET, PLAYER_INFO_WANTED_LEVEL_CAN_CHANGE_OFFSET };
	std::vector<uintptr_t> NpcsIgnore = { PLAYER_BASE_OFFSET, PLAYER_INFO_OFFSET, PLAYER_INFO_NPCS_IGNORE };
	std::vector<uintptr_t> Ragdoll = { PLAYER_BASE_OFFSET, PLAYER_RAGDOLL_OFFSET };
	std::vector<uintptr_t> Seatbelt = { PLAYER_BASE_OFFSET, PLAYER_SEATBELT_OFFSET };
	std::vector<uintptr_t> Waterproof = { PLAYER_BASE_OFFSET, PLAYER_WATERPROOF_OFFSET };
	// Vehicle Arrays
	std::vector<uintptr_t> VehicleGodmode = { PLAYER_BASE_OFFSET, PLAYER_VEHICLE_OFFSET, VEHICLE_GOD_OFFSET };
	std::vector<uintptr_t> VehicleGravity = { PLAYER_BASE_OFFSET, PLAYER_VEHICLE_OFFSET, VEHICLE_GRAVITY_OFFSET };
	std::vector<uintptr_t> VehicleMass = { PLAYER_BASE_OFFSET, PLAYER_VEHICLE_OFFSET, VEHICLE_HANDLING_OFFSET, VEHICLE_HANDLING_MASS_OFFSET };
	std::vector<uintptr_t> VehicleBuoyancy = { PLAYER_BASE_OFFSET, PLAYER_VEHICLE_OFFSET, VEHICLE_HANDLING_OFFSET, VEHICLE_HANDLING_BUOYANCY_OFFSET };
	std::vector<uintptr_t> VehicleAcceleration = { PLAYER_BASE_OFFSET, PLAYER_VEHICLE_OFFSET, VEHICLE_HANDLING_OFFSET, VEHICLE_HANDLING_ACCELERATION_OFFSET };
	std::vector<uintptr_t> VehicleUpshift = { PLAYER_BASE_OFFSET, PLAYER_VEHICLE_OFFSET, VEHICLE_HANDLING_OFFSET, VEHICLE_HANDLING_UPSHIFT_OFFSET };
	std::vector<uintptr_t> VehicleDownshift = { PLAYER_BASE_OFFSET, PLAYER_VEHICLE_OFFSET, VEHICLE_HANDLING_OFFSET, VEHICLE_HANDLING_DOWNSHIFT_OFFSET };
	std::vector<uintptr_t> VehicleBrakeForce = { PLAYER_BASE_OFFSET, PLAYER_VEHICLE_OFFSET, VEHICLE_HANDLING_OFFSET, VEHICLE_HANDLING_BRAKEFORCE_OFFSET };
	std::vector<uintptr_t> VehicleHandbrakeForce = { PLAYER_BASE_OFFSET, PLAYER_VEHICLE_OFFSET, VEHICLE_HANDLING_OFFSET, VEHICLE_HANDLING_HANDBRAKEFORCE_OFFSET };
	std::vector<uintptr_t> VehicleTractionCurveMin = { PLAYER_BASE_OFFSET, PLAYER_VEHICLE_OFFSET, VEHICLE_HANDLING_OFFSET, VEHICLE_HANDLING_TRACTION_CURVE_MIN_OFFSET };
	std::vector<uintptr_t> VehicleTractionCurveMax = { PLAYER_BASE_OFFSET, PLAYER_VEHICLE_OFFSET, VEHICLE_HANDLING_OFFSET, VEHICLE_HANDLING_TRACTION_CURVE_MAX_OFFSET };
	std::vector<uintptr_t> VehicleSuspensionForce = { PLAYER_BASE_OFFSET, PLAYER_VEHICLE_OFFSET, VEHICLE_HANDLING_OFFSET, VEHICLE_HANDLING_SUSPENSION_FORCE_OFFSET };
	std::vector<uintptr_t> VehicleSuspensionHeight = { PLAYER_BASE_OFFSET, PLAYER_VEHICLE_OFFSET, VEHICLE_HANDLING_OFFSET, VEHICLE_HANDLING_SUSPENSION_HEIGHT_OFFSET };
	std::vector<uintptr_t> VehicleEngine = { PLAYER_BASE_OFFSET, PLAYER_VEHICLE_OFFSET, VEHICLE_CUSTOM_OFFSET, VEHICLE_CUSTOM_EM_OFFSET };
	std::vector<uintptr_t> VehicleBrakes = { PLAYER_BASE_OFFSET, PLAYER_VEHICLE_OFFSET, VEHICLE_CUSTOM_OFFSET, VEHICLE_CUSTOM_BRAKES_OFFSET };
	std::vector<uintptr_t> VehicleTransmission = { PLAYER_BASE_OFFSET, PLAYER_VEHICLE_OFFSET, VEHICLE_CUSTOM_OFFSET, VEHICLE_CUSTOM_TRANSMISSION_OFFSET };
	std::vector<uintptr_t> VehicleSuspension = { PLAYER_BASE_OFFSET, PLAYER_VEHICLE_OFFSET, VEHICLE_CUSTOM_OFFSET, VEHICLE_CUSTOM_SUSPENSION_OFFSET };
	std::vector<uintptr_t> VehicleArmor = { PLAYER_BASE_OFFSET, PLAYER_VEHICLE_OFFSET, VEHICLE_CUSTOM_OFFSET, VEHICLE_CUSTOM_ARMOR_OFFSET };
	std::vector<uintptr_t> VehicleTurbo = { PLAYER_BASE_OFFSET, PLAYER_VEHICLE_OFFSET, VEHICLE_CUSTOM_OFFSET, VEHICLE_CUSTOM_TURBO_TUNING_OFFSET };
	std::vector<uintptr_t> VehicleNeonLightR = { PLAYER_BASE_OFFSET, PLAYER_VEHICLE_OFFSET, VEHICLE_CUSTOM_OFFSET, VEHICLE_CUSTOM_NEON_LIGHT_R_OFFSET };
	std::vector<uintptr_t> VehicleNeonLightG = { PLAYER_BASE_OFFSET, PLAYER_VEHICLE_OFFSET, VEHICLE_CUSTOM_OFFSET, VEHICLE_CUSTOM_NEON_LIGHT_G_OFFSET };
	std::vector<uintptr_t> VehicleNeonLightB = { PLAYER_BASE_OFFSET, PLAYER_VEHICLE_OFFSET, VEHICLE_CUSTOM_OFFSET, VEHICLE_CUSTOM_NEON_LIGHT_B_OFFSET };
	std::vector<uintptr_t> VehicleNeonLightsFront = { PLAYER_BASE_OFFSET, PLAYER_VEHICLE_OFFSET, VEHICLE_CUSTOM_OFFSET, VEHICLE_CUSTOM_NEON_LIGHTS_F_OFFSET };
	std::vector<uintptr_t> VehicleNeonLightsBack = { PLAYER_BASE_OFFSET, PLAYER_VEHICLE_OFFSET, VEHICLE_CUSTOM_OFFSET, VEHICLE_CUSTOM_NEON_LIGHTS_B_OFFSET };
	std::vector<uintptr_t> VehicleNeonLightsLeft = { PLAYER_BASE_OFFSET, PLAYER_VEHICLE_OFFSET, VEHICLE_CUSTOM_OFFSET, VEHICLE_CUSTOM_NEON_LIGHTS_L_OFFSET };
	std::vector<uintptr_t> VehicleNeonLightsRight = { PLAYER_BASE_OFFSET, PLAYER_VEHICLE_OFFSET, VEHICLE_CUSTOM_OFFSET, VEHICLE_CUSTOM_NEON_LIGHTS_R_OFFSET };

	std::vector<uintptr_t> VehiclePrimaryRed = { PLAYER_BASE_OFFSET, PLAYER_VEHICLE_OFFSET, VEHICLE_COLOR_OPTIONS_OFFSET, VEHICLE_COLOR_OFFSET, VEHICLE_COLOR_PRIMARY_RED_OFFSET };
	std::vector<uintptr_t> VehiclePrimaryGreen = { PLAYER_BASE_OFFSET, PLAYER_VEHICLE_OFFSET, VEHICLE_COLOR_OPTIONS_OFFSET, VEHICLE_COLOR_OFFSET, VEHICLE_COLOR_PRIMARY_GREEN_OFFSET };
	std::vector<uintptr_t> VehiclePrimaryBlue = { PLAYER_BASE_OFFSET, PLAYER_VEHICLE_OFFSET, VEHICLE_COLOR_OPTIONS_OFFSET, VEHICLE_COLOR_OFFSET, VEHICLE_COLOR_PRIMARY_BLUE_OFFSET };
	// Weapon Arrays
	std::vector<uintptr_t> InfiniteAmmo1 = { };
	std::vector<uintptr_t> InfiniteAmmo2 = { sizeof(BYTE)};
	std::vector<uintptr_t> InfiniteAmmo3 = { 2* sizeof(BYTE) };
	std::vector<uintptr_t> FillAmmo = { PLAYER_BASE_OFFSET , WEAPON_MANAGER_OFFSET, WEAPON_CURRENT_OFFSET, WEAPON_AMMOINFO_OFFSET ,WEAPON_AMMOINFO_CURAMMO_OFFSET, VEHICLE_COLOR_PRIMARY_RED_OFFSET };
	std::vector<uintptr_t> NoReload1 = { };
	std::vector<uintptr_t> NoReload2 = { sizeof(BYTE) };
	std::vector<uintptr_t> NoReload3 = { 2 * sizeof(BYTE) };
	

	int SetupMemory();
	uintptr_t getPointerAddressVector(uintptr_t pointer, std::vector<uintptr_t> offsets);

	void WriteByte(std::vector<uintptr_t> offsets, uintptr_t sig, byte data);
	void WriteInt(std::vector<uintptr_t> offsets, uintptr_t sig, int data);
	void WriteFloat(std::vector<uintptr_t> offsets, uintptr_t sig, float data);
	void WriteDWORD(std::vector<uintptr_t> offsets, uintptr_t sig, DWORD data);

	byte ReadByte(std::vector<uintptr_t> offsets, uintptr_t sig);
	int ReadInt(std::vector<uintptr_t> offsets, uintptr_t sig);
	float ReadFloat(std::vector<uintptr_t> offsets, uintptr_t sig);
	DWORD ReadDWORD(std::vector<uintptr_t> offsets, uintptr_t sig);
};

#endif

