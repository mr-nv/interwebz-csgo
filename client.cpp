#include "DllMain.h"

Base::Utils::CVMTHookManager g_pClientVMT;
Base::Utils::CVMTHookManager g_pPanelVMT;
Base::Utils::CVMTHookManager g_pPredictionVMT;
Base::Utils::CVMTHookManager g_pModelRenderVMT;
Base::Utils::CVMTHookManager g_pInputVMT;
Base::Utils::CVMTHookManager g_pSurfaceVMT;

float flArrayCorrect[128][4];
CNoSpread g_NoSpread;
CAimbot g_Aimbot;

void SetCurrentCmd(ValveSDK::CInput::CUserCmd *pDest, ValveSDK::CInput::CUserCmd *pSource)
{
	pDest->command_number = pSource->command_number;
	pDest->tick_count = pSource->tick_count;
	pDest->viewangles = pSource->viewangles;
	pDest->forwardmove = pSource->forwardmove;
	pDest->sidemove = pSource->sidemove;
	pDest->upmove = pSource->upmove;
	pDest->buttons = pSource->buttons;
	pDest->impulse = pSource->impulse;
	pDest->weaponselect = pSource->weaponselect;
	pDest->weaponsubtype = pSource->weaponsubtype;
	pDest->random_seed = pSource->random_seed;
	pDest->mousedx = pSource->mousedx;
	pDest->mousedy = pSource->mousedy;
	pDest->hasbeenpredicted = pSource->hasbeenpredicted;
}

void RunCommand(CBaseEntity* pLocal, ValveSDK::CInput::CUserCmd* pUserCmd, float fCurTime)
{
	static DWORD moveData[ 400 ];
	if( !g_Valve.pMoveHelper ) return;

	static auto CURRENTCOMMANDOFFSET = *( DWORD* )( Base::Utils::PatternSearch( /*client*/XorStr<0x41, 7, 0xAFB21C5E>( "\x22\x2E\x2A\x21\x2B\x32" + 0xAFB21C5E ).s, ( PBYTE )"\x89\xBE\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x85\xFF", /*xx????x????xx*/XorStr<0x4E, 14, 0x2391A5EA>( "\x36\x37\x6F\x6E\x6D\x6C\x2C\x6A\x69\x68\x67\x21\x22" + 0x2391A5EA ).s, 0, 0 ) + 2);

	*(PDWORD)((DWORD)pLocal + CURRENTCOMMANDOFFSET) = (DWORD)pUserCmd;

	//ValveSDK::CInput::CUserCmd* pPlayerCommand = (ValveSDK::CInput::CUserCmd*)((DWORD)pLocal + CURRENTPLAYERCOMMANDOFFSET);

	//SetCurrentCmd(pPlayerCommand, pUserCmd);

	static auto dwPredictionSeedAddress = *( PDWORD* )( Base::Utils::PatternSearch(/*client*/XorStr<0x41, 7, 0xAFB21C5E>( "\x22\x2E\x2A\x21\x2B\x32" + 0xAFB21C5E ).s, ( PBYTE )"\x8B\x0D\x00\x00\x00\x00\xBA\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x83\xC4\x04", "xx????x????x????xxx", 0, 0 ) + 2 );
	static auto dwPredictionPlayerAddress = *( PDWORD* )( Base::Utils::PatternSearch(/*client*/XorStr<0x41, 7, 0xAFB21C5E>( "\x22\x2E\x2A\x21\x2B\x32" + 0xAFB21C5E ).s, ( PBYTE )"\x89\x35\x00\x00\x00\x00\xF3\x0F\x10\x46", "xx????xxxx", 0, 0 ) + 2 );

	*(PINT)(dwPredictionSeedAddress) = pUserCmd->random_seed;
	*(PDWORD)(dwPredictionPlayerAddress) = (DWORD)pLocal;

	float fOldCurTime = g_Valve.pGlobalVars->curtime;
	float fOldFrameTime = g_Valve.pGlobalVars->frametime;

	g_Valve.pGlobalVars->curtime =  fCurTime;
	g_Valve.pGlobalVars->frametime = g_Valve.pGlobalVars->interval_per_tick;

	g_Valve.pMoveHelper->SetHost( pLocal );

	g_Valve.pPred->SetupMove(pLocal, pUserCmd, 0, (PVOID)&moveData);
	g_Valve.pGameMovement->ProcessMovement(pLocal, (PVOID)&moveData);
	g_Valve.pPred->FinishMove(pLocal, pUserCmd, (PVOID)&moveData);

	g_Valve.pMoveHelper->SetHost( nullptr );

	g_Valve.pGlobalVars->curtime = fOldCurTime;
	g_Valve.pGlobalVars->frametime = fOldFrameTime;
}

void __stdcall MyMovePacket(int sequence_number, float input_sample_frametime, bool active, bool& SendPacket)
{
	( ( ( void( __fastcall* )( void*, void*, int, float, bool ) )g_pClientVMT.dwGetMethodAddress( 22 ) )( g_Valve.pClient, 0, sequence_number, input_sample_frametime, active ) );

	ValveSDK::CInput::CUserCmd *pUserCmd = &(*(ValveSDK::CInput::CUserCmd**)((DWORD)g_Valve.pInput + USERCMDOFFSET))[sequence_number % MULTIPLAYER_BACKUP];
	ValveSDK::CInput::CVerifiedUserCmd *pVerifiedCmd = &(*(ValveSDK::CInput::CVerifiedUserCmd**)((DWORD)g_Valve.pInput + VERIFIEDCMDOFFSET))[sequence_number % MULTIPLAYER_BACKUP];

	CBaseEntity* pMe = g_Valve.pEntList->GetClientEntity(g_Valve.pEngine->GetLocalPlayer());
	if( !pMe ) return;

	if(bMenu)
		pUserCmd->buttons &= ~IN_ATTACK;

	//SMAC proof bhop by how2 
	if(g_CVARS.CvarList[Bunnyhop] && pMe->GetMoveType() != MOVETYPE_LADDER && pMe->GetMoveType() != MOVETYPE_NOCLIP && !(pMe->GetFlags() & FL_INWATER))
	{
		static bool bLastJumped = false;
		static bool bShouldFake = false;
		
		if(!bLastJumped && bShouldFake)
		{
			bShouldFake = false;
			pUserCmd->buttons |= IN_JUMP;
		}
		else if(pUserCmd->buttons & IN_JUMP)
		{
			if(pMe->GetFlags() & FL_ONGROUND)
			{
				bLastJumped = true;
				bShouldFake = true;
			}
			else
			{
				pUserCmd->buttons &= ~IN_JUMP;
				bLastJumped = false;
			}
		}
		else
		{
			bLastJumped = false;
			bShouldFake = false;
		}
	}

	float fCurTime = g_Valve.pGlobalVars->interval_per_tick * (pMe->GetTickBase() + 1);

	Vector qOldAngle = pUserCmd->viewangles;

	if(g_CVARS.CvarList[Strafebot] && !(pMe->GetFlags() & FL_ONGROUND) && pUserCmd->sidemove == 0 && pUserCmd->forwardmove == 0 && pMe->GetVelocity().Length2D() > 10.0f)
	{
		static float fOldAbsoluteViewYaw;
		float fAbsoluteView = qOldAngle.y;

		float fDeltaAbsView = fAbsoluteView - fOldAbsoluteViewYaw;

		fOldAbsoluteViewYaw = fAbsoluteView;

		if(fDeltaAbsView > 0.0f)
			pUserCmd->sidemove = -400;
		else if(fDeltaAbsView < 0.0f)
			pUserCmd->sidemove = 400;	
	}

	RunCommand(pMe,pUserCmd,fCurTime);

	ValveSDK::CBaseCombatWeapon *pWeapon = pMe->GetActiveBaseCombatWeapon();

	//keep a tab on how many commands we queue
	static int iChokedCommands;
	int iMaxChokedCommands = 14;

	//kolonote:
	//this way we wont crash if we have no active weapon
	if(pWeapon)
	{
		float fNextPrimary = pWeapon->GetNextPrimaryAttack();

		if(g_CVARS.CvarList[Knifebot] && g_Aimbot.Main_Knifebot(pMe,pWeapon))
		{
			if(g_CVARS.CvarList[Knifebot] == 1)
				pUserCmd->buttons |= IN_ATTACK2;
			else
				pUserCmd->buttons |= IN_ATTACK;
		}

		if(!pWeapon->IsMiscWeapon())
		{
			//for triggerseed/fakeseed
			static bool bRevertBack;
			static int iOldSeq;
			static int iOldCmdNum;

			//the tick we can fire on...beware this will fail if fps are smaller than 60
			bool bCanFire = true;

			static bool bOldBullet;

			pWeapon->UpdateAccuracyPenalty();

			if((fNextPrimary > fCurTime) || bOldBullet)
				bCanFire = false;

			if(!(fNextPrimary > fCurTime))
				bOldBullet = false;

			if(pWeapon->HasAmmo())
			{
				if(g_CVARS.CvarList[RCS] && GetAsyncKeyState(VK_LBUTTON))
					g_Aimbot.Main_RCS(pUserCmd,pMe,pWeapon);

				//for rage aimbot we can check bCanFire here otherwise for legit one we dont
				if(g_CVARS.CvarList[EnableAim] == 1)
				{
					if(g_CVARS.CvarList[AimOnFire])
					{
						if(bCanFire)
							g_Aimbot.Main(pUserCmd,pMe,pWeapon);
					}
					else
					{
						g_Aimbot.Main(pUserCmd,pMe,pWeapon);
					}
				}
				else if(g_CVARS.CvarList[EnableAim] == 2)
				{
					if(g_CVARS.CvarList[AimOnFire] && GetAsyncKeyState(g_CVARS.CvarList[AimKey]))
					{
						if(bCanFire)
							g_Aimbot.Main(pUserCmd,pMe,pWeapon);
					}
					else
					{
						if(g_CVARS.CvarList[AimTime] > 0)
						{
							static DWORD dwAim = 0;
							if(GetAsyncKeyState(g_CVARS.CvarList[AimKey]))
							{
								if(dwAim == 0)
									dwAim = GetTickCount() + g_CVARS.CvarList[AimTime];

								if(dwAim > GetTickCount())
									g_Aimbot.Main(pUserCmd,pMe,pWeapon);
							}
							else
							{
								if(dwAim > 0)
									dwAim = 0;	
							}
						}
						else
						{
							if(GetAsyncKeyState(g_CVARS.CvarList[AimKey]))
								g_Aimbot.Main(pUserCmd,pMe,pWeapon);
						}			
					}
				}

				if(g_CVARS.CvarList[Triggerbot] == 1)
				{
					if(bCanFire && g_Aimbot.Triggerbot(pWeapon,pMe,pUserCmd))
						pUserCmd->buttons |= IN_ATTACK;
				}
				else if(g_CVARS.CvarList[Triggerbot] == 2 && GetAsyncKeyState(g_CVARS.CvarList[TriggerKey]))
				{
					if(bCanFire && g_Aimbot.Triggerbot(pWeapon,pMe,pUserCmd))
						pUserCmd->buttons |= IN_ATTACK;
				}
			}

			//autopistol - will slow down firerate if fps < 60
			if((pUserCmd->buttons & IN_ATTACK))
			{
				if(bCanFire)
					bOldBullet = true;
				else
				{
					if(g_CVARS.CvarList[Autopistol])
						pUserCmd->buttons &= ~IN_ATTACK;
				}
			}

			//by now checking in_attack we check the tick we can fire on
			if((pUserCmd->buttons & IN_ATTACK))
			{
				if(g_CVARS.CvarList[NoSpread] == 1)
					g_NoSpread.GetSpreadFix(pWeapon,pUserCmd->random_seed,pUserCmd->viewangles);
				else if(g_CVARS.CvarList[NoSpread] == 2)//roll is unsafe to modify on matchmaking
					g_NoSpread.GetRollSpreadFix(pWeapon,pUserCmd->random_seed,pUserCmd->viewangles);
			}

			if(g_CVARS.CvarList[NoRecoil])
				pUserCmd->viewangles -= pMe->GetPunchAngle() * 2;
			
			static Vector qClientViewAngles;
			if(g_CVARS.CvarList[PSilent] && !bCanFire)
			{			
				g_Valve.pEngine->GetViewAngles(qClientViewAngles);
			
				qClientViewAngles.x = g_NoSpread.AngleNormalize(qClientViewAngles.x);
				qClientViewAngles.y = g_NoSpread.AngleNormalize(qClientViewAngles.y);

				pUserCmd->viewangles.y = qClientViewAngles.y;

				if(!g_CVARS.CvarList[AntiAimX])
				{
					//make sure we dont modify z angle as that will ban us on mm	
					pUserCmd->viewangles.x = qClientViewAngles.x;

					if(!g_Aimbot.HasTarget())
						g_Aimbot.FixMovement(pUserCmd,qOldAngle);
				}
			}

			if((g_CVARS.CvarList[AntiAimX] || g_CVARS.CvarList[AntiAimY]) && !(pUserCmd->buttons & IN_USE) && pMe->GetMoveType() != 9)
			{
				if((pUserCmd->buttons & IN_ATTACK) && g_Aimbot.HasTarget())
					g_Aimbot.FixMovement(pUserCmd,qOldAngle);

				if(!(pUserCmd->buttons & IN_ATTACK))
				{
					//first pitch
					if(g_CVARS.CvarList[AntiAimX] == 1) //emotion
						pUserCmd->viewangles.x = 70.0f;

					if(g_CVARS.CvarList[AntiAimX] == 2) //upside down
						pUserCmd->viewangles.x = 180.0f;

					if(g_CVARS.CvarList[AntiAimX] == 3) //magicpitch
						pUserCmd->viewangles.x = 180.087936f;

					if(g_CVARS.CvarList[AntiAimY] == 1) //-180 regular/alligned
						pUserCmd->viewangles.y -= 180.0f;

					pUserCmd->viewangles.x = g_NoSpread.AngleNormalize(pUserCmd->viewangles.x);
					pUserCmd->viewangles.y = g_NoSpread.AngleNormalize(pUserCmd->viewangles.y);

					g_Aimbot.FixMovement(pUserCmd,qOldAngle,((g_CVARS.CvarList[AntiAimX] > 1) ? -1 : 1));
				}
			}
			else if(g_CVARS.CvarList[SilentAim] && g_Aimbot.HasTarget())
				g_Aimbot.FixMovement(pUserCmd,qOldAngle);

			//kolonote:
			//this is my way of doing psilent...its fkn cleaaan
			//note: be sure to have autopistol on for this cuz again it might fail if fps lower than 60 (on shit PCs)
			if(g_CVARS.CvarList[PSilent] && bCanFire && (pUserCmd->buttons & IN_ATTACK))
			{
				SendPacket = false;
				iChokedCommands++;
			}
		}
	}

	if(g_CVARS.CvarList[FakelagAmount] > 1)
	{
		static int iTickTimer;

		static int iFakelag = iTickTimer + g_CVARS.CvarList[FakelagAmount];

		if(iFakelag >= iTickTimer)
		{
			SendPacket = false;
			iChokedCommands++;
		}
		else
			iFakelag = iTickTimer + g_CVARS.CvarList[FakelagAmount];

		iTickTimer++;
	}

	//we dont wanna lagout do we ?
	if(iChokedCommands > iMaxChokedCommands)
		SendPacket = true;

	if(SendPacket)
		iChokedCommands = 0;

	pVerifiedCmd->m_cmd = *pUserCmd;
	pVerifiedCmd->m_crc = pUserCmd->GetChecksum();
}

DWORD dwOriginCreateMove;
void __declspec(naked) __fastcall hkdCreateMove( void* ecx, void* edx, int sequence_number, float input_sample_frametime, bool active)
{
	__asm
	{
		push ebp
		mov ebp, esp
		push ebx
		lea ecx, [esp]
		push ecx
		push dword ptr[active]
		push dword ptr[input_sample_frametime]
		push dword ptr[sequence_number]
		call MyMovePacket
		pop ebx
		pop ebp
		retn 0Ch
	}
	/*PBYTE pSendPacket = (PBYTE)(*(PDWORD)(dwEBP) - 0x1);

	bool bSendThisPacket = *pSendPacket;

	MyMovePacket(sequence_number,input_sample_frametime,active,bSendThisPacket);

	*pSendPacket = bSendThisPacket;*/
}

void StorePunchAngle(CBaseEntity* player)
{
	int nTickBase = player->GetTickBase();

	int iStorage = 9 * nTickBase % 128;

	flArrayCorrect[iStorage][0] = nTickBase;

	//at this point punchangle isnt compressed and we can retrieve it then just predict it when we call processmovement inside createmove
	//Vector* qPunchangle = reinterpret_cast< Vector* >(reinterpret_cast< int >(player)+g_NetworkedVariableManager->GetOffset("DT_BasePlayer", "m_aimPunchAngle"));

	Vector qPunchangle = player->GetPunchAngle();
	flArrayCorrect[iStorage][1] = qPunchangle.x;
	flArrayCorrect[iStorage][2] = qPunchangle.y;
	flArrayCorrect[iStorage][3] = qPunchangle.z;
}

void __stdcall hkdRunCommand(CBaseEntity* pEntity, ValveSDK::CInput::CUserCmd* pUserCmd, void* moveHelper)
{
	( ( ( void( __thiscall* )( void*, CBaseEntity*, ValveSDK::CInput::CUserCmd*, void* ) )g_pPredictionVMT.dwGetMethodAddress( 19 ) )( g_Valve.pPred, pEntity, pUserCmd, moveHelper ) );

	g_Valve.pMoveHelper = (ValveSDK::ImoveHelper*)moveHelper;

	StorePunchAngle(pEntity);
}

void __fastcall hkdFrameStageNotify(void* ecx, void*, ClientFrameStage_t curStage)
{
	if( !g_Valve.pEngine->IsInGame( ) || !g_Valve.pEngine->IsConnected( ) ) return ( ( ( void( __thiscall* )( void*, ClientFrameStage_t ) )g_pClientVMT.dwGetMethodAddress( 37 ) )( ecx, curStage ) );

	static int iAimPunchOffset = g_NetworkedVariableManager.GetOffset(/*DT_BasePlayer*/XorStr<0xC2, 14, 0xCFD8B52B>( "\x86\x97\x9B\x87\xA7\xB4\xAD\x99\xA6\xAA\xB5\xA8\xBC" + 0xCFD8B52B ).s, /*m_aimPunchAngle*/XorStr<0xEA, 16, 0x4D0C6C95>( "\x87\xB4\x8D\x84\x83\xBF\x85\x9F\x91\x9B\xB5\x9B\x91\x9B\x9D" + 0x4D0C6C95 ).s );
	static int iViewPunchOffset = g_NetworkedVariableManager.GetOffset(/*DT_BasePlayer*/XorStr<0xC2, 14, 0xCFD8B52B>( "\x86\x97\x9B\x87\xA7\xB4\xAD\x99\xA6\xAA\xB5\xA8\xBC" + 0xCFD8B52B ).s, /*m_viewPunchAngle*/XorStr<0x8B, 17, 0x3D2ECC5D>( "\xE6\xD3\xFB\xE7\xEA\xE7\xC1\xE7\xFD\xF7\xFD\xD7\xF9\xFF\xF5\xFF" + 0x3D2ECC5D ).s );
	static int iFallVelocityOffset = g_NetworkedVariableManager.GetOffset(/*DT_CSPlayer*/XorStr<0xAA,12,0x6F938DD5>("\xEE\xFF\xF3\xEE\xFD\xFF\xDC\xD0\xCB\xD6\xC6"+0x6F938DD5).s, /*m_flFallVelocity*/XorStr<0xC4,17,0x8454FEF5>("\xA9\x9A\xA0\xAB\x8E\xA8\xA6\xA7\x9A\xA8\xA2\xA0\xB3\xB8\xA6\xAA"+0x8454FEF5).s);
	static int iBaseVelocityOffset = g_NetworkedVariableManager.GetOffset(/*DT_CSPlayer*/XorStr<0x34,12,0x959D9DAB>("\x70\x61\x69\x74\x6B\x69\x56\x5A\x45\x58\x4C"+0x959D9DAB).s,/*m_vecBaseVelocity*/XorStr<0x44,18,0xF97A7797>("\x29\x1A\x30\x22\x2B\x0B\x2B\x38\x29\x1B\x2B\x23\x3F\x32\x3B\x27\x2D"+0xF97A7797).s);

	static Vector qOldPunch, qOldViewPunch;

	if(g_CVARS.CvarList[NoVisRecoil] && g_Valve.pEngine->IsInGame() && curStage == FRAME_RENDER_START)
	{
		CBaseEntity* pMe = g_Valve.pEntList->GetClientEntity(g_Valve.pEngine->GetLocalPlayer());

		Vector* qPunch = ( Vector* )( ( DWORD )pMe + iAimPunchOffset );
		Vector* qViewPunch = ( Vector* )( ( DWORD )pMe + iViewPunchOffset );

		qOldPunch = *qPunch;
		qOldViewPunch = *qViewPunch;

		qPunch->Init(0.0f,0.0f,0.0f);
		qViewPunch->Init( );
	
		( ( ( void( __thiscall* )( void*, ClientFrameStage_t ) )g_pClientVMT.dwGetMethodAddress( 37 ) )( ecx, curStage ) );

		*qPunch = qOldPunch;
		*qViewPunch = qOldViewPunch;
	}
	else
	{
		( ( ( void( __thiscall* )( void*, ClientFrameStage_t ) )g_pClientVMT.dwGetMethodAddress( 37 ) )( ecx, curStage ) );
	}

	if (curStage == FRAME_NET_UPDATE_POSTDATAUPDATE_START && g_Valve.pEngine->GetLocalPlayer() > 0)
	{
		CBaseEntity* pMe = g_Valve.pEntList->GetClientEntity(g_Valve.pEngine->GetLocalPlayer());

		if(pMe)
		{
			//general fixes
			PFLOAT pfFallVelocity = (PFLOAT)((DWORD)pMe + iFallVelocityOffset);

			if(*pfFallVelocity > 0.03124f && *pfFallVelocity < 0.03126f)
				*pfFallVelocity = 0.0f;

			Vector *vBaseVelocity = (Vector*)((DWORD)pMe + iBaseVelocityOffset);

			if(vBaseVelocity->x > -0.000999f && vBaseVelocity->x < -0.0009f)
				vBaseVelocity->x = 0.0f;

			if(vBaseVelocity->y > -0.000999f && vBaseVelocity->y < -0.0009f)
				vBaseVelocity->y = 0.0f;

			if(vBaseVelocity->z > -0.000999f && vBaseVelocity->z < -0.0009f)
				vBaseVelocity->z = 0.0f;

			int nTickBase = pMe->GetTickBase();
			static bool bKinda[4];
			static bool bRecoil,bCheckit,bChecknow;
			static float flIsee;
			float *flTouche = flArrayCorrect[9 * nTickBase % 128];

			bKinda[0] = flTouche[0] == nTickBase;

			Vector qPunch = pMe->GetPunchAngle();

			static Vector vPunch;

			vPunch.x = qPunch.x;
			vPunch.y = qPunch.y;
			vPunch.z = qPunch.z;

			static Vector vStoredPunch;

			vStoredPunch.x = flTouche[1];
			vStoredPunch.y = flTouche[2];
			vStoredPunch.z = flTouche[3];

			float flTesting = Vector(vStoredPunch - vPunch).Length();

			bKinda[1] = 0.33000001f > flTesting;

			if(bKinda[0])
				bRecoil = bKinda[1];
			else
			{
				int iNewTickbase = nTickBase - 1;
				int v5 = 1;
				int iUpdatetick = nTickBase - 1;

				while( v5 < 128 )
				{
					flTouche = flArrayCorrect[9 * iNewTickbase % 128];
					bCheckit = flTouche[0] == nTickBase;

					Vector newqPunch = pMe->GetPunchAngle();

					static Vector newvPunch;

					newvPunch.x = newqPunch.x;
					newvPunch.y = newqPunch.y;
					newvPunch.z = newqPunch.z;

					static Vector newvStoredPunch;

					newvStoredPunch.x = flTouche[1];
					newvStoredPunch.y = flTouche[2];
					newvStoredPunch.z = flTouche[3];

					flIsee = Vector(newvStoredPunch - newvPunch).Length();
					bChecknow = 0.33000001f > flIsee;

					if(bCheckit)
						break;

					++v5;

					iNewTickbase = iUpdatetick-- - 1;
				}

				bRecoil = bChecknow;
			}
			if(bRecoil)
			{
				Vector *pPunchangle = (Vector*)((DWORD)pMe + iAimPunchOffset);

				pPunchangle->x = flTouche[1];
				pPunchangle->y = flTouche[2];
				pPunchangle->z = flTouche[3];
			}
		}
	}
}

#define T_INVIS g_CVARS.CvarList[Chams_T_InVis],g_CVARS.CvarList[Chams_T_InVis + 1], g_CVARS.CvarList[Chams_T_InVis + 2]
#define CT_INVIS g_CVARS.CvarList[Chams_CT_InVis],g_CVARS.CvarList[Chams_CT_InVis + 1], g_CVARS.CvarList[Chams_CT_InVis + 2]

#define T_VIS g_CVARS.CvarList[Chams_T_Vis],g_CVARS.CvarList[Chams_T_Vis + 1], g_CVARS.CvarList[Chams_T_Vis + 2]
#define CT_VIS g_CVARS.CvarList[Chams_CT_Vis],g_CVARS.CvarList[Chams_CT_Vis + 1], g_CVARS.CvarList[Chams_CT_Vis + 2]

void __stdcall hkdDrawModelExecute(void* rendercontext, const ValveSDK::DrawModelState_t &state, const ValveSDK::ModelRenderInfo_t &pInfo, matrix3x4_t *pCustomBoneToWorld)
{
	//idgaf cba to use inline asm here when i can just unhook and clean call with 1 line
	g_pModelRenderVMT.UnHook();

	static ValveSDK::IMaterial *pNew = CreateMaterial(FALSE,FALSE);
	static ValveSDK::IMaterial *pIgnoreNew = CreateMaterial(FALSE,TRUE);

	static ValveSDK::IMaterial *pBrightNew = CreateMaterial(TRUE,FALSE);
	static ValveSDK::IMaterial *pBrightIgnoreNew = CreateMaterial(TRUE,TRUE);

	const char *pszModelName = g_Valve.pModel->GetModelName(pInfo.pModel);

	static std::string sModelStr = /*models/player*/XorStr<0x3C,14,0x7E5C758B>("\x51\x52\x5A\x5A\x2C\x32\x6D\x33\x28\x24\x3F\x22\x3A"+0x7E5C758B).s;

	bool bPlayerModel = strstr(pszModelName,sModelStr.data());

	static ValveSDK::IMaterial *pPlayerMaterial[32];
	static CBaseEntity *pEntity = NULL;
	static bool bTeamCheck;
	static bool bHands;
	
	if(g_CVARS.CvarList[XQZ] && bPlayerModel)
	{
		pEntity = g_Valve.pEntList->GetClientEntity(pInfo.entity_index);

		if(pEntity)
		{
			CBaseEntity *pLocal = g_Valve.pEntList->GetClientEntity(g_Valve.pEngine->GetLocalPlayer());
			
			bTeamCheck = ((pEntity->GetHealth() >= 1) && (!g_CVARS.CvarList[ChamsEnemyOnly] || (g_CVARS.CvarList[ChamsEnemyOnly] && pEntity->GetTeamNum() != pLocal->GetTeamNum())));	

			if(bTeamCheck)
			{
				g_Valve.pModel->GetModelMaterials(pInfo.pModel,1,pPlayerMaterial);

				if(pPlayerMaterial[0])
					pPlayerMaterial[0]->SetMaterialVarFlag(ValveSDK::MATERIAL_VAR_IGNOREZ,true);
			}
		}
	}

	if(g_CVARS.CvarList[Chams] && bPlayerModel)
	{
		if(g_CVARS.CvarList[Chams] == 2)
			FullCham((g_CVARS.CvarList[BrightChams] ? pBrightIgnoreNew : pIgnoreNew),pInfo,CT_INVIS,T_INVIS,true);
		else
			FullCham((g_CVARS.CvarList[BrightChams] ? pBrightNew : pNew),pInfo,CT_VIS,T_VIS);

		if(g_CVARS.CvarList[ModelAlpha] < 255 && g_CVARS.CvarList[ModelAlpha] != 0)
		{
			float fAlphaAdjusted = g_CVARS.CvarList[ModelAlpha] / 255;

			if(g_Valve.pRenderView->GetBlend() != fAlphaAdjusted)
				g_Valve.pRenderView->SetBlend(fAlphaAdjusted);
		}

		g_Valve.pModelRender->DrawModelExecute(rendercontext, state,pInfo,pCustomBoneToWorld);

		if(g_CVARS.CvarList[Chams] == 2)
		{
			FullCham((g_CVARS.CvarList[BrightChams] ? pBrightNew : pNew),pInfo,CT_VIS,T_VIS);

			g_Valve.pModelRender->DrawModelExecute(rendercontext,state,pInfo,pCustomBoneToWorld);
		}

		g_Valve.pModelRender->ForcedMaterialOverride(NULL);
	}
	else if(g_CVARS.CvarList[ModelAlpha] < 255 && g_CVARS.CvarList[ModelAlpha] != 0)
	{
		if(bPlayerModel)
		{
			float fAlphaAdjusted = g_CVARS.CvarList[ModelAlpha] / 255;

			if(g_Valve.pRenderView->GetBlend() != fAlphaAdjusted)
				g_Valve.pRenderView->SetBlend(fAlphaAdjusted);
		}

		g_Valve.pModelRender->DrawModelExecute(rendercontext,state,pInfo,pCustomBoneToWorld);
		g_Valve.pModelRender->ForcedMaterialOverride(NULL);
	}
	else
	{
		g_Valve.pModelRender->DrawModelExecute(rendercontext,state,pInfo,pCustomBoneToWorld);
		g_Valve.pModelRender->ForcedMaterialOverride(NULL);
	}

	if(g_CVARS.CvarList[XQZ] && bPlayerModel && pPlayerMaterial[0])
		pPlayerMaterial[0]->SetMaterialVarFlag(ValveSDK::MATERIAL_VAR_IGNOREZ,false);

	g_pModelRenderVMT.ReHook();
}

int __stdcall hkdIN_KeyEvent(int eventcode,ValveSDK::ButtonCode_t keynum,const char *pszCurrentBinding)
{
	int iRet = ( ( ( int( __thiscall* )( void*, int, ValveSDK::ButtonCode_t, const char* ) )g_pClientVMT.dwGetMethodAddress( 21 ) )( g_Valve.pClient, eventcode, keynum, pszCurrentBinding ) );

	if(keynum == ValveSDK::MOUSE_WHEEL_UP)
	{
		ListItemArray[g_Menu.GetSmallTabIndex(1)].MoveUp(1);	
		return 0;
	}

	if(keynum == ValveSDK::MOUSE_WHEEL_DOWN)
	{
		ListItemArray[g_Menu.GetSmallTabIndex(1)].MoveDown(1);
		return 0;
	}

	return iRet;
}

ValveSDK::CInput::CUserCmd* __fastcall hkdGetUserCmd( void* ecx, void*, int slot, int sequence_number )
{
	return (&(*(ValveSDK::CInput::CUserCmd**)((DWORD)g_Valve.pInput + USERCMDOFFSET))[sequence_number % MULTIPLAYER_BACKUP]);
}

void __stdcall hkdFinishMove(CBaseEntity *player, ValveSDK::CInput::CUserCmd *ucmd, PVOID move)
{
	( ( ( void( __thiscall* )( void*, CBaseEntity*, ValveSDK::CInput::CUserCmd*, PVOID ) )g_pPredictionVMT.dwGetMethodAddress( 21 ) )( g_Valve.pPred, player, ucmd, move ) );

	Vector vNewAbsVelocity = player->GetVelocity() + player->GetBaseVelocity();

	//fix gay ass strafe spread (damn you valve)
	*(Vector*)((DWORD)player + 0x94) = vNewAbsVelocity;
}

void __fastcall hkdLockCursor( void* ecx, void* )
{
	if( bMenu ) g_Valve.pSurface->UnlockCursor( );
	else ( ( ( void( __thiscall* )( void* ) )g_pSurfaceVMT.dwGetMethodAddress( 67 ) )( ecx ) );
}