namespace ValveSDK
{
	class CDebugOverlay
	{
	public:
		int ScreenPosition(const Vector& vIn, Vector& vOut)
		{
			typedef int(__thiscall* OriginalFn)(PVOID, const Vector&, Vector&);
			return getvfunc<OriginalFn>(this, 13)(this, vIn, vOut);
		}
	};
}