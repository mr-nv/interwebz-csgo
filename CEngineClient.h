namespace ValveSDK
{
	class CEngineClient
	{
	public:
		typedef struct
		{
			__int64         unknown;            //0x0000 
			union
			{
				__int64       steamID64;          //0x0008 - SteamID64
				struct
				{
					__int32     xuid_low;
					__int32     xuid_high;
				};
			};

			char name[ 128 ];
			int userID;
			char guid[ 20 ];
			char pad[ 0x10 ];
			unsigned long steamid;
			char friendsName[ 128 ];
			bool fakeplayer;
			bool ishltv;
			CRC32_t customFiles[ 4 ];
			unsigned char filesdownloaded;
		} player_info_t;

		void GetScreenSize(int& width, int& height)
		{
			typedef void(__thiscall* OriginalFn)(PVOID, int&, int&);
			return getvfunc<OriginalFn>(this, 5)(this, width, height);
		}

		bool GetPlayerInfo(int iIndex, player_info_t *pInfo)
		{
			typedef bool(__thiscall* OriginalFn)(PVOID, int, player_info_t*);
			return getvfunc<OriginalFn>(this, 8)(this, iIndex, pInfo);
		}

		int GetLocalPlayer(VOID)
		{
			typedef int(__thiscall* OriginalFn)(PVOID);
			return getvfunc<OriginalFn>(this, 12)(this);
		}

		void ExecuteClientCmd(char const* szCommand)
		{
			typedef void(__thiscall* OriginalFn)(PVOID, char const* szCommand);
			getvfunc<OriginalFn>(this, 105)(this, szCommand);
		}

		void GetViewAngles(Vector& vAngles)
		{
			typedef void(__thiscall* OriginalFn)(PVOID, Vector&);
			return getvfunc< OriginalFn >(this, 18)(this, vAngles);
		}

		void SetViewAngles(Vector& vAngles)
		{
			typedef void(__thiscall* oSetViewAngles)(PVOID, Vector&);
			return getvfunc< oSetViewAngles >(this, 19)(this, vAngles);
		}
		
		bool IsConnected()
		{
			typedef bool(__thiscall* oGetScreenSize)(PVOID);
			return getvfunc< oGetScreenSize >(this, 27)(this);
		}

		bool IsInGame()
		{
			typedef bool(__thiscall* oLocal)(PVOID);
			return getvfunc< oLocal >(this, 26)(this);
		}

		int GetMaxClients()
		{
			typedef bool(__thiscall* oGetMaxClients)(PVOID);
			return getvfunc< oGetMaxClients >(this, 20)(this);
		}
	};
}