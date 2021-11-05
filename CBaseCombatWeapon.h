enum EItemDefinitionIndex : short
{
	WEAPON_NONE = 0,
	WEAPON_DEAGLE = 1,
	WEAPON_ELITE = 2,
	WEAPON_FIVESEVEN = 3,
	WEAPON_GLOCK = 4,
	WEAPON_AK47 = 7,
	WEAPON_AUG = 8,
	WEAPON_AWP = 9,
	WEAPON_FAMAS = 10,
	WEAPON_G3SG1 = 11,
	WEAPON_GALILAR = 13,
	WEAPON_M249 = 14,
	WEAPON_M4A1 = 16,
	WEAPON_MAC10 = 17,
	WEAPON_P90 = 19,
	WEAPON_ZONE_REPULSOR = 20,
	WEAPON_MP5SD = 23,
	WEAPON_UMP45 = 24,
	WEAPON_XM1014 = 25,
	WEAPON_BIZON = 26,
	WEAPON_MAG7 = 27,
	WEAPON_NEGEV = 28,
	WEAPON_SAWEDOFF = 29,
	WEAPON_TEC9 = 30,
	WEAPON_TASER = 31,
	WEAPON_HKP2000 = 32,
	WEAPON_MP7 = 33,
	WEAPON_MP9 = 34,
	WEAPON_NOVA = 35,
	WEAPON_P250 = 36,
	WEAPON_SHIELD = 37,
	WEAPON_SCAR20 = 38,
	WEAPON_SG556 = 39,
	WEAPON_SSG08 = 40,
	WEAPON_KNIFE_GG = 41,
	WEAPON_KNIFE = 42,
	WEAPON_FLASHBANG = 43,
	WEAPON_HEGRENADE = 44,
	WEAPON_SMOKEGRENADE = 45,
	WEAPON_MOLOTOV = 46,
	WEAPON_DECOY = 47,
	WEAPON_INCGRENADE = 48,
	WEAPON_C4 = 49,
	WEAPON_HEALTHSHOT = 57,
	WEAPON_KNIFE_T = 59,
	WEAPON_M4A1_SILENCER = 60,
	WEAPON_USP_SILENCER = 61,
	WEAPON_CZ75A = 63,
	WEAPON_REVOLVER = 64,
	WEAPON_TAGRENADE = 68,
	WEAPON_FISTS = 69,
	WEAPON_BREACHCHARGE = 70,
	WEAPON_TABLET = 72,
	WEAPON_MELEE = 74,
	WEAPON_AXE = 75,
	WEAPON_HAMMER = 76,
	WEAPON_SPANNER = 78,
	WEAPON_KNIFE_GHOST = 80,
	WEAPON_FIREBOMB = 81,
	WEAPON_DIVERSION = 82,
	WEAPON_FRAG_GRENADE = 83,
	WEAPON_SNOWBALL = 84,
	WEAPON_BUMPMINE = 85,
	WEAPON_KNIFE_BAYONET = 500,
	WEAPON_KNIFE_CSS = 503,
	WEAPON_KNIFE_FLIP = 505,
	WEAPON_KNIFE_GUT = 506,
	WEAPON_KNIFE_KARAMBIT = 507,
	WEAPON_KNIFE_M9_BAYONET = 508,
	WEAPON_KNIFE_TACTICAL = 509,
	WEAPON_KNIFE_FALCHION = 512,
	WEAPON_KNIFE_SURVIVAL_BOWIE = 514,
	WEAPON_KNIFE_BUTTERFLY = 515,
	WEAPON_KNIFE_PUSH = 516,
	WEAPON_KNIFE_CORD = 517,
	WEAPON_KNIFE_CANIS = 518,
	WEAPON_KNIFE_URSUS = 519,
	WEAPON_KNIFE_GYPSY_JACKKNIFE = 520,
	WEAPON_KNIFE_OUTDOOR = 521,
	WEAPON_KNIFE_STILETTO = 522,
	WEAPON_KNIFE_WIDOWMAKER = 523,
	WEAPON_KNIFE_SKELETON = 525,
	GLOVE_STUDDED_BROKENFANG = 4725,
	GLOVE_STUDDED_BLOODHOUND = 5027,
	GLOVE_T = 5028,
	GLOVE_CT = 5029,
	GLOVE_SPORTY = 5030,
	GLOVE_SLICK = 5031,
	GLOVE_LEATHER_HANDWRAPS = 5032,
	GLOVE_MOTORCYCLE = 5033,
	GLOVE_SPECIALIST = 5034,
	GLOVE_STUDDED_HYDRA = 5035,
	SPECIAL_AGENT_BLUEBERRIES_BUCKSHOT = 4619,
	SPECIAL_AGENT_TWO_TIMES_MCCOY_TACP = 4680,
	SPECIAL_AGENT_COMMANDOR_MAE_JAMISON = 4711,
	SPECIAL_AGENT_1ST_LIEUTENANT_FARLOW,
	SPECIAL_AGENT_JOHN_KASK,
	SPECIAL_AGENT_BIO_HAZ_SPECIALIST,
	SPECIAL_AGENT_SERGEANT_BOMBSON,
	SPECIAL_AGENT_CHEM_HAZ_SPECIALIST,
	SPECIAL_AGENT_REZAN_THE_REDSHIRT = 4718,
	SPECIAL_AGENT_SIR_BLOODY_MIAMI_DARRYL = 4726,
	SPECIAL_AGENT_SAFECRACKER_VOLTZMANN,
	SPECIAL_AGENT_LITTLE_KEV,
	SPECIAL_AGENT_GETAWAY_SALLY = 4730,
	SPECIAL_AGENT_NUMBER_K = 4732,
	SPECIAL_AGENT_SIR_BLOODY_SILENT_DARRYL = 4733,
	SPECIAL_AGENT_SIR_BLOODY_SKULLHEAD_DARRYL,
	SPECIAL_AGENT_SIR_BLOODY_DARRYL_ROYALE,
	SPECIAL_AGENT_SIR_BLOODY_LOUDMOUTH_DARRYL,
	SPECIAL_AGENT_T = 5036,
	SPECIAL_AGENT_CT = 5037,
	SPECIAL_AGENT_GROUND_REBEL = 5105,
	SPECIAL_AGENT_OSIRIS,
	SPECIAL_AGENT_SHAHMAT,
	SPECIAL_AGENT_MUHLIK,
	SPECIAL_AGENT_SOLDIER = 5205,
	SPECIAL_AGENT_ENFORCER,
	SPECIAL_AGENT_SLINGSHOT,
	SPECIAL_AGENT_STREET_SOLDIER,
	SPECIAL_AGENT_OPERATOR = 5305,
	SPECIAL_AGENT_MARKUS_DELROW,
	SPECIAL_AGENT_MICHAEL_SYFERS,
	SPECIAL_AGENT_AVA,
	SPECIAL_AGENT_3RD_COMMANDO_COMPANY = 5400,
	SPECIAL_AGENT_SEAL_TEAM_6_SOLDIER,
	SPECIAL_AGENT_BUCKSHOT,
	SPECIAL_AGENT_TWO_TIMES_MCCOY_USAF,
	SPECIAL_AGENT_RICKSAW,
	SPECIAL_AGENT_DRAGOMIR = 5500,
	SPECIAL_AGENT_MAXIMUS,
	SPECIAL_AGENT_REZAN_THE_READY,
	SPECIAL_AGENT_BLACKWOLF = 5503,
	SPECIAL_AGENT_THE_DOCTOR,
	SPECIAL_AGENT_DRAGOMIR_FOOTSOLDIERS,
	SPECIAL_AGENT_B_SQUADRON_OFFICER = 5601
};

namespace ValveSDK
{
	class CBaseCombatWeapon
	{
	public:
		float GetNextPrimaryAttack()
		{
			static int iOffset = g_NetworkedVariableManager.GetOffset(/*DT_BaseCombatWeapon*/XorStr<0x0C,20,0xCCB89A4B>("\x48\x59\x51\x4D\x71\x62\x77\x50\x7B\x78\x74\x76\x6C\x4E\x7F\x7A\x6C\x72\x70"+0xCCB89A4B).s, /*m_flNextPrimaryAttack*/XorStr<0x0D,22,0x423C055C>("\x60\x51\x69\x7C\x5F\x77\x6B\x60\x45\x64\x7E\x75\x78\x68\x62\x5D\x69\x6A\x7E\x43\x4A"+0x423C055C).s);
			return *(float*)((DWORD)this + iOffset);
		}

		bool HasAmmo()
		{
			static int iOffset = g_NetworkedVariableManager.GetOffset(/*DT_BaseCombatWeapon*/XorStr<0x5E,20,0xBED67F8D>("\x1A\x0B\x3F\x23\x03\x10\x01\x26\x09\x0A\x0A\x08\x1E\x3C\x09\x0C\x1E\x00\x1E"+0xBED67F8D).s,/*m_iClip1*/XorStr<0x7B,9,0xEBD79649>("\x16\x23\x14\x3D\x13\xE9\xF1\xB3"+0xEBD79649).s);
			return ((*(PINT)((DWORD)this + iOffset)) > 0);
		}

		bool IsSilencerOn()
		{
			static int iOffsetPistol = g_NetworkedVariableManager.GetOffset(/*DT_WeaponUSP*/XorStr<0x88,13,0xD9DE2C14>("\xCC\xDD\xD5\xDC\xE9\xEC\xFE\xE0\xFE\xC4\xC1\xC3"+0xD9DE2C14).s,/*m_bSilencerOn*/XorStr<0xFD,14,0x2902C67C>("\x90\xA1\x9D\x53\x68\x6E\x66\x6A\x66\x63\x75\x47\x67"+0x2902C67C).s);
			static int iOffsetRifle = g_NetworkedVariableManager.GetOffset(/*DT_WeaponM4A1*/XorStr<0x80,14,0x78EF406B>("\xC4\xD5\xDD\xD4\xE1\xE4\xF6\xE8\xE6\xC4\xBE\xCA\xBD"+0x78EF406B).s,/*m_bSilencerOn*/XorStr<0xFD,14,0x2902C67C>("\x90\xA1\x9D\x53\x68\x6E\x66\x6A\x66\x63\x75\x47\x67"+0x2902C67C).s);
		
			int iWeaponID = GetWeaponID();

			if(iWeaponID == WEAPON_USP_SILENCER)
				return (*(PBOOL)((DWORD)this + iOffsetPistol));
			else if(iWeaponID == WEAPON_M4A1)
				return (*(PBOOL)((DWORD)this + iOffsetRifle));

			return false;
		}

		float GetSpread()
		{
			typedef float(__thiscall *GetSpread_t)(PVOID);
			return getvfunc<GetSpread_t>( this, 453 )( this );
		}

		float GetCone()
		{
			typedef float(__thiscall *GetCone_t)(PVOID);
			return getvfunc<GetCone_t>( this, 483 )( this );
		}

		void UpdateAccuracyPenalty()
		{
			typedef void(__thiscall *UpdateAccuracyPenalty_t)(PVOID);
			getvfunc<UpdateAccuracyPenalty_t>( this, 484 )( this );
		}

		short GetWeaponID()
		{
			static auto offset = g_NetworkedVariableManager.GetOffset(/*DT_BaseAttributableItem*/XorStr<0x02, 24, 0xD9AC4BA5>( "\x46\x57\x5B\x47\x67\x74\x6D\x48\x7E\x7F\x7E\x64\x6C\x7A\x64\x70\x70\x7F\x71\x5C\x62\x72\x75" + 0xD9AC4BA5 ).s, /*m_iItemDefinitionIndex*/XorStr<0x80, 23, 0x25DEA788>( "\xED\xDE\xEB\xCA\xF0\xE0\xEB\xC3\xED\xEF\xE3\xE5\xE5\xF9\xE7\xE0\xFE\xD8\xFC\xF7\xF1\xED" + 0x25DEA788 ).s );
			return *( short* )( ( DWORD )this + offset );
		}

		bool IsMiscWeapon()
		{
			short iWeaponID = GetWeaponID();

			return (iWeaponID == WEAPON_KNIFE || iWeaponID == WEAPON_C4 
				|| iWeaponID == WEAPON_HEGRENADE || iWeaponID == WEAPON_SMOKEGRENADE
				|| iWeaponID == WEAPON_FLASHBANG || iWeaponID == WEAPON_DECOY
				|| iWeaponID == WEAPON_FLASHBANG || iWeaponID == WEAPON_INCGRENADE
				|| iWeaponID == WEAPON_KNIFE_T || (iWeaponID >= WEAPON_KNIFE_BAYONET && iWeaponID <= WEAPON_KNIFE_WIDOWMAKER));
		}

		void* GetWeaponData( )
		{
			return getvfunc<void*( __thiscall* )( void* )>( this, 454 )( this );
		}
	};
}

class CCSWeaponData
{
public:
	byte pad0[ 0x14 ];			// 0x0000
	int iMaxClip1;					// 0x0014
	int iMaxClip2;					// 0x0018
	int iDefaultClip1;				// 0x001C
	int iDefaultClip2;				// 0x0020
	int iPrimaryMaxReserveAmmo;		// 0x0024
	int iSecondaryMaxReserveAmmo;	// 0x0028
	const char* szWorldModel;		// 0x002C
	const char* szViewModel;		// 0x0030
	const char* szDroppedModel;		// 0x0034
	BYTE pad1[ 0x50 ];			// 0x0038
	const char* szHudName;			// 0x0088
	const char* szWeaponName;		// 0x008C
	byte pad2[ 0x2 ];			// 0x0090
	bool bIsMeleeWeapon;			// 0x0092
	byte pad3[ 0x9 ];			// 0x0093
	float flWeaponWeight;			// 0x009C
	byte pad4[ 0x4 ];			// 0x00A0
	int iSlot;						// 0x00A4
	int iPosition;					// 0x00A8
	byte pad5[ 0x1C ];			// 0x00AC
	int nWeaponType;				// 0x00C8
	byte pad6[ 0x4 ];			// 0x00CC
	int iWeaponPrice;				// 0x00D0
	int iKillAward;					// 0x00D4
	const char* szAnimationPrefix;	// 0x00D8
	float flCycleTime;				// 0x00DC
	float flCycleTimeAlt;			// 0x00E0
	byte pad8[ 0x8 ];			// 0x00E4
	bool bFullAuto;					// 0x00EC
	byte pad9[ 0x3 ];			// 0x00ED
	int iDamage;					// 0x00F0
	float flHeadShotMultiplier;		// 0x00F4
	float flArmorRatio;				// 0x00F8
	int iBullets;					// 0x00FC
	float flPenetration;			// 0x0100
	byte pad10[ 0x8 ];			// 0x0104
	float flRange;					// 0x010C
	float flRangeModifier;			// 0x0110
	float flThrowVelocity;			// 0x0114
	byte pad11[ 0xC ];			// 0x0118
	bool bHasSilencer;				// 0x0124
	byte pad12[ 0xF ];			// 0x0125
	float flMaxSpeed[ 2 ];			// 0x0134
	byte pad13[ 0x4 ];			// 0x013C
	float flSpread[ 2 ];				// 0x0140
	float flInaccuracyCrouch[ 2 ];	// 0x0148
	float flInaccuracyStand[ 2 ];		// 0x0150
	byte pad14[ 0x8 ];			// 0x0158
	float flInaccuracyJump[ 2 ];		// 0x0160
	float flInaccuracyLand[ 2 ];		// 0x0168
	float flInaccuracyLadder[ 2 ];	// 0x0170
	float flInaccuracyFire[ 2 ];		// 0x0178
	float flInaccuracyMove[ 2 ];		// 0x0180
	float flInaccuracyReload;		// 0x0188
	int iRecoilSeed;				// 0x018C
	float flRecoilAngle[ 2 ];			// 0x0190
	float flRecoilAngleVariance[ 2 ];	// 0x0198
	float flRecoilMagnitude[ 2 ];		// 0x01A0
	float flRecoilMagnitudeVariance[ 2 ]; // 0x01A8
	int iSpreadSeed;				// 0x01B0
};