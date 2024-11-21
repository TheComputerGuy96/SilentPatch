#ifndef __PEDSA
#define __PEDSA

#include "GeneralSA.h"

class CEntryExit;
class CEvent;
class CPed;
class CVehicle;

// This structure is very incomplete, but it is good enough for now
class NOVMT CTask
{
public:
	virtual ~CTask() { }
	virtual CTask* Clone() const = 0;
	virtual CTask* GetSubTask() const = 0;
	virtual bool IsSimpleTask() const = 0;
	virtual int GetTaskType() const = 0;
	virtual void StopTimer(const CEvent*) { }
	virtual bool MakeAbortable(CPed*, int, const CEvent*) = 0;

public:
	CTask* m_parentTask;
};
static_assert(sizeof(CTask) == 0x8, "Wrong size: CTask");

class NOVMT CTaskSimple : public CTask
{
public:
	virtual bool IsSimpleTask() const override { return true; }
	virtual bool SetPedPosition(CPed*) { return false; }
};

class NOVMT CTaskComplex : public CTask
{
private:
	CTask* m_pSubTask;

public:
	virtual bool IsSimpleTask() const override { return false; }
	virtual void SetSubTask(CTask*) = 0;
	virtual CTask* CreateNextSubTask(CPed*) = 0;
	virtual CTask* CreateFirstSubTask(CPed*) = 0;
	virtual CTask* ControlSubTask(CPed*) = 0;
};

// Stub
class NOVMT CTaskSimpleJetPack : public CTaskSimple
{
public:
	void			RenderJetPack(class CPed* pPed);
};

class NOVMT CTaskComplexSequence : public CTaskComplex
{
public:
	bool Contains(int taskID) const;

public:
	std::byte __pad1[4];
	CTask* m_taskSequence[8];
	std::byte __pad2[16];
};
static_assert(sizeof(CTaskComplexSequence) == 0x40, "Wrong size: CTaskComplexSequence");

class NOVMT CTaskComplexCarSlowBeDraggedOut : public CTaskComplex
{
public:
	CVehicle* m_pVehicle;
	int	m_status;
};
static_assert(sizeof(CTaskComplexCarSlowBeDraggedOut) == 0x14, "Wrong size: CTaskComplexCarSlowBeDraggedOut");

class CTaskManager
{
public:
	CTask* m_primaryTasks[5];
	CTask* m_secondaryTasks[6];
	CPed* m_pPed;
};
static_assert(sizeof(CTaskManager) == 0x30, "Wrong size: CTaskManager");

class CPedIntelligence
{
public:
	CPed* m_pPed;
	CTaskManager m_taskManager;

public:
	class CTaskSimpleJetPack*	GetTaskJetPack() const;
};

class CPedFlags
{
public:
	unsigned int bIsStanding : 1; // is ped standing on something
	unsigned int bWasStanding : 1; // was ped standing on something
	unsigned int bIsLooking : 1; // is ped looking at something or in a direction
	unsigned int bIsRestoringLook : 1; // is ped restoring head postion from a look
	unsigned int bIsAimingGun : 1; // is ped aiming gun
	unsigned int bIsRestoringGun : 1; // is ped moving gun back to default posn
	unsigned int bCanPointGunAtTarget : 1; // can ped point gun at target
	unsigned int bIsTalking : 1; // is ped talking(see Chat())

	unsigned int bInVehicle : 1; // is in a vehicle
	unsigned int bIsInTheAir : 1; // is in the air
	unsigned int bIsLanding : 1; // is landing after being in the air
	unsigned int bHitSomethingLastFrame : 1; // has been in a collision last fram
	unsigned int bIsNearCar : 1; // has been in a collision last fram
	unsigned int bRenderPedInCar : 1; // has been in a collision last fram
	unsigned int bUpdateAnimHeading : 1; // update ped heading due to heading change during anim sequence
	unsigned int bRemoveHead : 1; // waiting on AntiSpazTimer to remove head

	unsigned int bFiringWeapon : 1; // is pulling trigger
	unsigned int bHasACamera : 1; // does ped possess a camera to document accidents
	unsigned int bPedIsBleeding : 1; // Ped loses a lot of blood if true
	unsigned int bStopAndShoot : 1; // Ped cannot reach target to attack with fist, need to use gun
	unsigned int bIsPedDieAnimPlaying : 1; // is ped die animation finished so can dead now
	unsigned int bStayInSamePlace :1; // when set, ped stays put
	unsigned int bKindaStayInSamePlace :1; // when set, ped doesn't seek out opponent or cover large distances. Will still shuffle and look for cover
	unsigned int bBeingChasedByPolice :1; // use nodes for routefind

	unsigned int bNotAllowedToDuck :1; // Is this ped allowed to duck at all?
	unsigned int bCrouchWhenShooting :1; // duck behind cars etc
	unsigned int bIsDucking :1; // duck behind cars etc
	unsigned int bGetUpAnimStarted :1; // don't want to play getup anim if under something
	unsigned int bDoBloodyFootprints :1; // unsigned int bIsLeader :1;
	unsigned int bDontDragMeOutCar :1;
	unsigned int bStillOnValidPoly :1; // set if the polygon the ped is on is still valid for collision
	unsigned int bAllowMedicsToReviveMe :1;

	unsigned int bResetWalkAnims :1;
	unsigned int bOnBoat :1; // flee but only using nodes
	unsigned int bBusJacked :1; // flee but only using nodes
	unsigned int bFadeOut :1; // set if you want ped to fade out
	unsigned int bKnockedUpIntoAir :1; // has ped been knocked up into the air by a car collision
	unsigned int bHitSteepSlope :1; // has ped collided/is standing on a steep slope (surface type)
	unsigned int bCullExtraFarAway :1; // special ped only gets culled if it's extra far away (for roadblocks)
	unsigned int bTryingToReachDryLand :1; // has ped just exited boat and trying to get to dry land

	unsigned int bCollidedWithMyVehicle :1;
	unsigned int bRichFromMugging :1; // ped has lots of cash cause they've been mugging people
	unsigned int bChrisCriminal :1; // Is a criminal as killed during Chris' police mission (should be counted as such)
	unsigned int bShakeFist :1; // test shake hand at look entity
	unsigned int bNoCriticalHits : 1; // ped cannot be killed by a single bullet
	unsigned int bHasAlreadyBeenRecorded : 1; // Used for replays
	unsigned int bUpdateMatricesRequired : 1; // if PedIK has altered bones so matrices need updated this frame
	unsigned int bFleeWhenStanding :1; //

	unsigned int bMiamiViceCop :1;  //
	unsigned int bMoneyHasBeenGivenByScript :1; //
	unsigned int bHasBeenPhotographed :1;  //
	unsigned int bIsDrowning : 1;
	unsigned int bDrownsInWater : 1;
	unsigned int bHeadStuckInCollision : 1;
	unsigned int bDeadPedInFrontOfCar :1;
	unsigned int bStayInCarOnJack :1;

	unsigned int bDontFight :1;
	unsigned int bDoomAim :1;
	unsigned int bCanBeShotInVehicle : 1;
	unsigned int bPushedAlongByCar :1; // ped is getting pushed along by car collision (so don't take damage from horz velocity)
	unsigned int bNeverEverTargetThisPed :1;
	unsigned int bThisPedIsATargetPriority :1;
	unsigned int bCrouchWhenScared :1;
	unsigned int bKnockedOffBike :1;

	unsigned int bDonePositionOutOfCollision :1;
	unsigned int bDontRender : 1;
	unsigned int bHasBeenAddedToPopulation :1;
	unsigned int bHasJustLeftCar :1;
	unsigned int bIsInDisguise :1;
	unsigned int bDoesntListenToPlayerGroupCommands :1;
	unsigned int bIsBeingArrested :1;
	unsigned int bHasJustSoughtCover :1;

	unsigned int bKilledByStealth :1;
	unsigned int bDoesntDropWeaponsWhenDead :1;
	unsigned int bCalledPreRender :1;
	unsigned int bBloodPuddleCreated : 1; // Has a static puddle of blood been created yet
	unsigned int bPartOfAttackWave :1;
	unsigned int bClearRadarBlipOnDeath :1;
	unsigned int bNeverLeavesGroup :1; // flag that we want to test 3 extra spheres on col model
	unsigned int bTestForBlockedPositions :1; // this sets these indicator flags for various posisions on the front of the ped

	unsigned int bRightArmBlocked :1;
	unsigned int bLeftArmBlocked :1;
	unsigned int bDuckRightArmBlocked :1;
	unsigned int bMidriffBlockedForJump :1;
	unsigned int bFallenDown :1;
	unsigned int bUseAttractorInstantly :1;
	unsigned int bDontAcceptIKLookAts :1;
	unsigned int bHasAScriptBrain : 1;

	unsigned int bWaitingForScriptBrainToLoad : 1;
	unsigned int bHasGroupDriveTask :1;
	unsigned int bCanExitCar :1;
	unsigned int CantBeKnockedOffBike :2; // 0=Default(harder for mission peds) 1=Never 2=Always normal(also for mission peds)
	unsigned int bHasBeenRendered : 1;
	unsigned int bIsCached :1;
	unsigned int bPushOtherPeds :1; // GETS RESET EVERY FRAME - SET IN TASK: want to push other peds around (eg. leader of a group or ped trying to get in a car)
	unsigned int bHasBulletProofVest :1;

	unsigned int bUsingMobilePhone :1;
	unsigned int bUpperBodyDamageAnimsOnly :1;
	unsigned int bStuckUnderCar :1;
	unsigned int bKeepTasksAfterCleanUp :1; // If true ped will carry on with task even after cleanup
	unsigned int bIsDyingStuck :1;
	unsigned int bIgnoreHeightCheckOnGotoPointTask :1; // set when walking round buildings, reset when task quits
	unsigned int bForceDieInCar:1;
	unsigned int bCheckColAboveHead:1;

	unsigned int bIgnoreWeaponRange : 1;
	unsigned int bDruggedUp : 1;
	unsigned int bWantedByPolice : 1; // if this is set, the cops will always go after this ped when they are doing a KillCriminal task
	unsigned int bSignalAfterKill: 1;
	unsigned int bCanClimbOntoBoat :1;
	unsigned int bPedHitWallLastFrame: 1; // useful to store this so that AI knows (normal will still be available)
	unsigned int bIgnoreHeightDifferenceFollowingNodes: 1;
	unsigned int bMoveAnimSpeedHasBeenSetByTask: 1;

	unsigned int bGetOutUpsideDownCar :1;
	unsigned int bJustGotOffTrain :1;
	unsigned int bDeathPickupsPersist :1;
	unsigned int bTestForShotInVehicle :1;
	unsigned int bUsedForReplay : 1; // This ped is controlled by replay and should be removed when replay is done.
};

class CPlayerPedData
{
public:
    class CWanted* m_Wanted;												// 0x0
    void* m_pClothes;											// 0x4
    CPed* m_ArrestingOfficer;									// 0x8
    CVector2D m_vecFightMovement;									// 0xC
    float m_moveBlendRatio;										// 0x14
    float m_fSprintEnergy;										// 0x18
    float m_fSprintControlCounter;								// 0x1C
    BYTE m_nChosenWeapon;										// 0x20
    BYTE m_nCarDangerCounter;									// 0x21
    DWORD m_nStandStillTimer;									// 0x24
    DWORD m_nHitAnimDelayTimer;									// 0x28
    float m_fAttackButtonCounter;								// 0x2C
    void *m_pDangerCar;											// 0x30

    DWORD m_bStoppedMoving : 1;									// 0x34
    DWORD m_bAdrenaline : 1;
    DWORD m_bHaveTargetSelected : 1;
    DWORD m_bFreeAiming : 1;
    DWORD bCanBeDamaged : 1;
    DWORD bAllMeleeAttackPtsBlocked : 1;
    DWORD m_JustBeenSnacking : 1;
    DWORD m_bRequireHandleBreath : 1;
    
    DWORD m_GroupStuffDisabled : 1;								// 0x35
    DWORD m_GroupAlwaysFollow : 1;
    DWORD m_GroupNeverFollow : 1;
    DWORD m_bInVehicleDontAllowWeaponChange : 1;
    DWORD m_bRenderWeapon : 1;
	DWORD m_bUnused1 : 1;
	DWORD m_bUnused2 : 1;
	DWORD m_bUnused3 : 1;

	DWORD m_bCopMode : 1;										// 0x36

    DWORD m_PlayerGroup;										// 0x38

    DWORD m_AdrenalineEndTime;									// 0x3C
    BYTE m_nDrunkenness;										// 0x40
    BYTE m_bFadeDrunkenness;									// 0x41
    BYTE m_nDrugLevel;											// 0x42
    BYTE m_nScriptLimitToGangSize;								// 0x43
    float m_fBreath;											// 0x44
    DWORD m_MeleeWeaponAnimReferenced;							// 0x48
    DWORD m_MeleeWeaponAnimReferencedExtra;						// 0x4C
    float m_fFPSMoveHeading;									// 0x50
    float m_fLookPitch;											// 0x54
    float m_fSkateBoardSpeed;									// 0x58
    float m_fSkateBoardLean;									// 0x5C

    void *m_pSpecialAtomic;										// 0x60
    float m_fGunSpinSpeed;										// 0x64
    float m_fGunSpinAngle;										// 0x68

    DWORD m_LastTimeFiring;										// 0x6C
    DWORD m_nTargetBone;										// 0x70
    CVector m_vecTargetBoneOffset;								// 0x74
    DWORD m_busFaresCollected;									// 0x80
    BYTE m_bPlayerSprintDisabled;								// 0x84
    BYTE m_bDontAllowWeaponChange;								// 0x85
    BYTE m_bForceInteriorLighting;								// 0x86
    WORD m_DPadDownPressedInMilliseconds;						// 0x88
    WORD m_DPadUpPressedInMilliseconds;							// 0x8A
    BYTE m_wetness;												// 0x8C
    BYTE m_playersGangActive;									// 0x8D
    BYTE m_waterCoverPerc;										// 0x8E
    FLOAT m_waterHeight;										// 0x90
    DWORD m_FireHSMissilePressedTime;							// 0x94
    void* m_LastHSMissileTarget;
    DWORD m_nModelIndexOfLastBuildingShot;
    DWORD m_LastHSMissileLOSTime  :31;
    DWORD m_bLastHSMissileLOS     :1;
    void* m_pCurrentProstitutePed;
    void* m_pLastProstituteShagged;
};

class NOVMT CPed : public CPhysical
{
public:
	BYTE				__pad1[820];
	CPedFlags			pedFlags;
	class CPedIntelligence*	pPedIntelligence;
	CPlayerPedData*		pPlayerData;
	unsigned char		PedCreatedBy;
	BYTE				__pad7[76];
	int					iMoveAnimGroup;
	BYTE				__pad2[28];
	RwObject*			m_pWeaponObject;
	RwFrame*			m_pMuzzleFlashFrame;
	BYTE				__pad10[68];
	float				fHealth;
	float				fMaxHealth;
	float				fArmour;
	BYTE				__pad8[12];
	float				m_fCurrentRotation;
	float				m_fTargetRotation;
	BYTE				__pad3[44];
	CVehicle*			pVehicle;
	BYTE				__pad9[8];
	DWORD				pedType;
	BYTE				__pad4[4];
	CWeapon				weaponSlots[13];
	BYTE				__pad5[12];
	BYTE				m_bActiveWeapon;
	BYTE				__pad65[20];
	unsigned char		bFightingStyle, bFightingStyleExtra;
	BYTE				__pad6[92];
	CEntryExit*			pCurrentEntryExit;
	BYTE				__pad64[12];

public:
	inline bool			Save_Stub()
		{ return CPed::Save(); }
	inline bool			Load_Stub()
		{ return CPed::Load(); }

	virtual bool		Save() = 0;
	virtual bool		Load() = 0;

	inline DWORD		GetPedType() 
							{ return pedType; };
	inline CPedFlags&	GetPedFlags() 
							{ return pedFlags; };
	inline CVehicle*	GetVehiclePtr() 
							{ return pVehicle; };
	inline CWeapon*	GetWeaponSlots() 
							{ return weaponSlots; };
	inline int			GetMoveAnimGroup() 
							{ return iMoveAnimGroup; };
	inline void			SetMoveAnimGroup(int a) 
							{ iMoveAnimGroup = a; };
	inline CPedIntelligence*	GetPedIntelligencePtr() 
							{ return pPedIntelligence; };
	inline float		GetHealth() 
							{ return fHealth; };
	inline float		GetArmour() 
							{ return fArmour; };
	inline CPlayerPedData*	GetPlayerData() 
							{ return pPlayerData; };
	inline BYTE			GetActiveWeapon() 
							{ return m_bActiveWeapon; };

	inline void			SetCurrentHeading(float fVal)
		{ m_fCurrentRotation = fVal; }
	inline void			SetTargetHeading(float fVal)
		{ m_fTargetRotation = fVal; }

	bool				IsPlayer() const
		{ return pedType == 0 || pedType == 1; }

	uint8_t				GetWeaponSkill();
	void				ResetGunFlashAlpha();
	void				SetGunFlashAlpha(bool bSecondWeapon);
	void				Say(uint16_t phrase, uint32_t param2 = 0, float volume = 1.0f, bool param4 = false, bool param5 = false, bool param6 = false);

	void				RenderWeapon(bool bWeapon, bool bMuzzleFlash, bool bForShadow);
	void				RenderForShadow();

	static void (CPed::*orgGiveWeapon)(uint32_t weapon, uint32_t ammo, bool flag);
	void				GiveWeapon_SP( uint32_t weapon, uint32_t ammo, bool flag );

	// Extension to accommodate for SA-MP hooking GetWeaponSkill in RenderWeaponPedsForPC dynamically
	static inline uint8_t (CPed::*orgGetWeaponSkillForRenderWeaponPedsForPC)() = &GetWeaponSkill;
	uint8_t				GetWeaponSkillForRenderWeaponPedsForPC()
	{
		return std::invoke( orgGetWeaponSkillForRenderWeaponPedsForPC, this );
	}

	uint8_t				GetWeaponSkillForRenderWeaponPedsForPC_SAMP();

	static inline void (CPed::*orgSay)(uint16_t phrase, uint32_t param2, float volume, bool param4, bool param5, bool param6);
	template<uint16_t blackSample>
	void				Say_SampleBlackList(uint16_t phrase, uint32_t param2 = 0, float volume = 1.0f, bool param4 = false, bool param5 = false, bool param6 = false)
	{
		if ( !(phrase == blackSample) )
		{
			std::invoke(orgSay, this, phrase, param2, volume, param4, param5, param6);
		}
	}
};

constexpr uint16_t CONTEXT_GLOBAL_CAR_HIT_PED = 36; // CPed::Say enum

class NOVMT CPlayerPed : public CPed
{
private:
	CPed*				m_pMouseLockOnRecruitPed;
	int					m_iMouseLockOnRecruitTimer;

public:
	static void (CPlayerPed::*orgDoStuffToGoOnFire)();

	void DoStuffToGoOnFire()
	{
		(this->*orgDoStuffToGoOnFire)();
	}
};

static_assert(sizeof(CPed) == 0x79C, "Wrong size: CPed");
static_assert(sizeof(CPlayerPed) == 0x7A4, "Wrong size: CPlayerPed");

class CClothes
{
public:
	static void (*RebuildPlayer)(CPlayerPed* ped, bool bForReplay);
};


#endif
