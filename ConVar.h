namespace ValveSDK
{
	class ConVar
	{
	public:
		int GetInt()
		{
			return getvfunc<int( __thiscall* )( void* )>( this, 13 )( this );
		}

		void SetValue(int iValue)
		{
			getvfunc<void( __thiscall* )( void*, int )>( this, 16 )( this, iValue );
		}
	};

	class IAppSystem
	{
	public:
		// Here's where the app systems get to learn about each other 
		virtual void func00() = 0;
		virtual void func01() = 0;
		virtual void func02() = 0;
		virtual void func03() = 0;
		virtual void func04() = 0;
	};

	class ICvar : public IAppSystem
	{
	public:
		virtual void funcy() = 0;
		virtual void funcy1() = 0;
		virtual void funcy2() = 0;
		virtual void funcy3() = 0;
		virtual void funcy4() = 0;
		virtual void funcy5() = 0;
		virtual void funcy6( ) = 0;
		virtual void funcy7( ) = 0;
		virtual void funcy8( ) = 0;
		virtual void funcy9( ) = 0;
		virtual ConVar *FindVar(const char *var_name) = 0;
		//virtual const ConVar *FindVar(const char *var_name) const = 0;
	};
}