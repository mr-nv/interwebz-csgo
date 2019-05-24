void __fastcall hkdCreateMove(void* ecx, void* edx, int sequence_number, float input_sample_frametime, bool active);
void __stdcall hkdRunCommand(CBaseEntity* pEntity, ValveSDK::CInput::CUserCmd* pUserCmd, void* moveHelper);
void __fastcall hkdFrameStageNotify(void* ecx, void*, ClientFrameStage_t curStage);
void __stdcall hkdPaintTraverse(unsigned vguiPanel, bool forceRepaint, bool allowForce);
void __stdcall hkdDrawModelExecute(void* rendercontext, const ValveSDK::DrawModelState_t &state, const ValveSDK::ModelRenderInfo_t &pInfo, matrix3x4_t *pCustomBoneToWorld = NULL);
ValveSDK::CInput::CUserCmd* __fastcall hkdGetUserCmd( void* ecx, void*, int slot, int sequence_number );
int __stdcall hkdIN_KeyEvent(int eventcode,ValveSDK::ButtonCode_t keynum,const char *pszCurrentBinding);
void __stdcall hkdFinishMove(CBaseEntity *player, ValveSDK::CInput::CUserCmd *ucmd, PVOID move);
void __fastcall hkdLockCursor( void* ecx, void* );

extern DWORD dwOriginCreateMove;
extern Base::Utils::CVMTHookManager g_pClientVMT;
extern Base::Utils::CVMTHookManager g_pPanelVMT;
extern Base::Utils::CVMTHookManager g_pPredictionVMT;
extern Base::Utils::CVMTHookManager g_pModelRenderVMT;
extern Base::Utils::CVMTHookManager g_pInputVMT;
extern Base::Utils::CVMTHookManager g_pSurfaceVMT;