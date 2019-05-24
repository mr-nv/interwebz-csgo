namespace ValveSDK
{
	enum OverrideType_t
	{
		OVERRIDE_NORMAL = 0,
		OVERRIDE_BUILD_SHADOWS,
		OVERRIDE_DEPTH_WRITE,
		OVERRIDE_WHATEVER
	};

	struct DrawModelState_t
	{
		studiohdr_t*			m_pStudioHdr;
		PVOID					m_pStudioHWData;
		PVOID					m_pRenderable;
		const matrix3x4_t		*m_pModelToWorld;
		int						m_decals;
		int						m_drawFlags;
		int						m_lod;
	};

	struct ModelRenderInfo_t
	{
		Vector origin;
		Vector angles; 
		char pad[ 4 ];
		PVOID pRenderable;
		const model_t *pModel;
		const matrix3x4_t *pModelToWorld;
		const matrix3x4_t *pLightingOffset;
		const Vector *pLightingOrigin;
		int flags;
		int entity_index;
		int skin;
		int body;
		int hitboxset;
		unsigned short instance;

		ModelRenderInfo_t()
		{
			pModelToWorld = NULL;
			pLightingOffset = NULL;
			pLightingOrigin = NULL;
		}
	};

	enum MaterialVarFlags_t
	{
		MATERIAL_VAR_DEBUG					  = (1 << 0),
		MATERIAL_VAR_NO_DEBUG_OVERRIDE		  = (1 << 1),
		MATERIAL_VAR_NO_DRAW				  = (1 << 2),
		MATERIAL_VAR_USE_IN_FILLRATE_MODE	  = (1 << 3),

		MATERIAL_VAR_VERTEXCOLOR			  = (1 << 4),
		MATERIAL_VAR_VERTEXALPHA			  = (1 << 5),
		MATERIAL_VAR_SELFILLUM				  = (1 << 6),
		MATERIAL_VAR_ADDITIVE				  = (1 << 7),
		MATERIAL_VAR_ALPHATEST				  = (1 << 8),
		MATERIAL_VAR_MULTIPASS				  = (1 << 9),
		MATERIAL_VAR_ZNEARER				  = (1 << 10),
		MATERIAL_VAR_MODEL					  = (1 << 11),
		MATERIAL_VAR_FLAT					  = (1 << 12),
		MATERIAL_VAR_NOCULL					  = (1 << 13),
		MATERIAL_VAR_NOFOG					  = (1 << 14),
		MATERIAL_VAR_IGNOREZ				  = (1 << 15),
		MATERIAL_VAR_DECAL					  = (1 << 16),
		MATERIAL_VAR_ENVMAPSPHERE			  = (1 << 17),
		MATERIAL_VAR_NOALPHAMOD				  = (1 << 18),
		MATERIAL_VAR_ENVMAPCAMERASPACE	      = (1 << 19),
		MATERIAL_VAR_BASEALPHAENVMAPMASK	  = (1 << 20),
		MATERIAL_VAR_TRANSLUCENT              = (1 << 21),
		MATERIAL_VAR_NORMALMAPALPHAENVMAPMASK = (1 << 22),
		MATERIAL_VAR_NEEDS_SOFTWARE_SKINNING  = (1 << 23),
		MATERIAL_VAR_OPAQUETEXTURE			  = (1 << 24),
		MATERIAL_VAR_ENVMAPMODE				  = (1 << 25),
		MATERIAL_VAR_SUPPRESS_DECALS		  = (1 << 26),
		MATERIAL_VAR_HALFLAMBERT			  = (1 << 27),
		MATERIAL_VAR_WIREFRAME                = (1 << 28),
		MATERIAL_VAR_ALLOWALPHATOCOVERAGE     = (1 << 29),

		// NOTE: Only add flags here that either should be read from
		// .vmts or can be set directly from client code. Other, internal
		// flags should to into the flag enum in IMaterialInternal.h
	};

	class IMaterial
	{
	public:
		// Get the name of the material.  This is a full path to 
	// the vmt file starting from "hl2/materials" (or equivalent) without
	// a file extension.
		virtual const char* GetName( ) const = 0;

		virtual const char* GetTextureGroupName( ) const = 0;

		// Get the preferred size/bitDepth of a preview image of a material.
		// This is the sort of image that you would use for a thumbnail view
		// of a material, or in WorldCraft until it uses materials to render.
		// separate this for the tools maybe
		virtual /*PreviewImageRetVal_t*/int GetPreviewImageProperties( int* width, int* height, /*ImageFormat**/void* imageFormat, bool* isTranslucent ) const = 0;

		// Get a preview image at the specified width/height and bitDepth.
		// Will do resampling if necessary.(not yet!!! :) )
		// Will do color format conversion. (works now.)
		virtual /*PreviewImageRetVal_t*/int GetPreviewImage( unsigned char* data, int width, int height, char imageFormat ) const = 0;

		//
		virtual int GetMappingWidth( ) = 0;

		virtual int GetMappingHeight( ) = 0;

		virtual int GetNumAnimationFrames( ) = 0;

		// For material subrects (material pages).  Offset(u,v) and scale(u,v) are normalized to texture.
		virtual bool InMaterialPage( void ) = 0;

		virtual void GetMaterialOffset( float* pOffset ) = 0;

		virtual void GetMaterialScale( float* pScale ) = 0;

		virtual IMaterial* GetMaterialPage( void ) = 0;

		// find a vmt variable.
		// This is how game code affects how a material is rendered.
		// The game code must know about the params that are used by
		// the shader for the material that it is trying to affect.
		virtual /*IMaterialVar**/void* FindVar( const char* varName, bool* found, bool complain = true ) = 0;

		// The user never allocates or deallocates materials.  Reference counting is
		// used instead.  Garbage collection is done upon a call to 
		// IMaterialSystem::UncacheUnusedMaterials.
		virtual void IncrementReferenceCount( void ) = 0;

		virtual void DecrementReferenceCount( void ) = 0;

		inline void AddRef( )
		{
			IncrementReferenceCount( );
		}

		inline void Release( )
		{
			DecrementReferenceCount( );
		}

		// Each material is assigned a number that groups it with like materials
		// for sorting in the application.
		virtual int GetEnumerationID( void ) const = 0;

		virtual void GetLowResColorSample( float s, float t, float* color ) const = 0;

		// This computes the state snapshots for this material
		virtual void RecomputeStateSnapshots( ) = 0;

		// Are we translucent?
		virtual bool IsTranslucent( ) = 0;

		// Are we alphatested?
		virtual bool IsAlphaTested( ) = 0;

		// Are we vertex lit?
		virtual bool IsVertexLit( ) = 0;

		// Gets the vertex format
		virtual /*VertexFormat_t*/int GetVertexFormat( ) const = 0;

		// returns true if this material uses a material proxy
		virtual bool HasProxy( void ) const = 0;

		virtual bool UsesEnvCubemap( void ) = 0;

		virtual bool NeedsTangentSpace( void ) = 0;

		virtual bool NeedsPowerOfTwoFrameBufferTexture( bool bCheckSpecificToThisFrame = true ) = 0;

		virtual bool NeedsFullFrameBufferTexture( bool bCheckSpecificToThisFrame = true ) = 0;

		// returns true if the shader doesn't do skinning itself and requires
		// the data that is sent to it to be preskinned.
		virtual bool NeedsSoftwareSkinning( void ) = 0;

		// Apply constant color or alpha modulation
		virtual void AlphaModulate( float alpha ) = 0;

		virtual void ColorModulate( float r, float g, float b ) = 0;

		// Material Var flags...
		virtual void SetMaterialVarFlag( MaterialVarFlags_t flag, bool on ) = 0;

		virtual bool GetMaterialVarFlag( MaterialVarFlags_t flag ) const = 0;

		// Gets material reflectivity
		virtual void GetReflectivity( Vector& reflect ) = 0;

		// Gets material property flags
		virtual bool GetPropertyFlag( /*MaterialPropertyTypes_t*/int type ) = 0;

		// Is the material visible from both sides?
		virtual bool IsTwoSided( ) = 0;

		// Sets the shader associated with the material
		virtual void SetShader( const char* pShaderName ) = 0;

		// Can't be const because the material might have to precache itself.
		virtual int GetNumPasses( void ) = 0;

		// Can't be const because the material might have to precache itself.
		virtual int GetTextureMemoryBytes( void ) = 0;

		// Meant to be used with materials created using CreateMaterial
		// It updates the materials to reflect the current values stored in the material vars
		virtual void Refresh( ) = 0;

		// GR - returns true is material uses lightmap alpha for blending
		virtual bool NeedsLightmapBlendAlpha( void ) = 0;

		// returns true if the shader doesn't do lighting itself and requires
		// the data that is sent to it to be prelighted
		virtual bool NeedsSoftwareLighting( void ) = 0;

		// Gets at the shader parameters
		virtual int ShaderParamCount( ) const = 0;

		virtual /*IMaterialVar***/void** GetShaderParams( void ) = 0;

		// Returns true if this is the error material you get back from IMaterialSystem::FindMaterial if
		// the material can't be found.
		virtual bool IsErrorMaterial( ) const = 0;

		virtual void Unused( ) = 0;

		// Gets the current alpha modulation
		virtual float GetAlphaModulation( ) = 0;

		virtual void GetColorModulation( float* r, float* g, float* b ) = 0;

		// Is this translucent given a particular alpha modulation?
		virtual bool IsTranslucentUnderModulation( float fAlphaModulation = 1.0f ) const = 0;

		// fast find that stores the index of the found var in the string table in local cache
		virtual /*IMaterialVar**/void* FindVarFast( char const* pVarName, unsigned int* pToken ) = 0;

		// Sets new VMT shader parameters for the material
		virtual void SetShaderAndParams( void* pKeyValues ) = 0;

		virtual const char* GetShaderName( ) const = 0;

		virtual void DeleteIfUnreferenced( ) = 0;

		virtual bool IsSpriteCard( ) = 0;

		virtual void CallBindProxy( void* proxyData ) = 0;

		virtual void RefreshPreservingMaterialVars( ) = 0;

		virtual bool WasReloadedFromWhitelist( ) = 0;

		virtual bool SetTempExcluded( bool bSet, int nExcludedDimensionLimit ) = 0;

		virtual int GetReferenceCount( ) const = 0;
	};

	class Color
	{
	public:
		Color(int r,int g,int b,int a)
		{
			_color[0] = (unsigned char)r;
			_color[1] = (unsigned char)g;
			_color[2] = (unsigned char)b;
			_color[3] = (unsigned char)a;
		}

		unsigned char _color[4];
	};

	typedef unsigned short MaterialHandle_t;

	class IMaterialSystem
	{
	public:
		/*void UncacheMaterials()
		{
			typedef void(__thiscall* OriginalFn)(PVOID);
			getvfunc<OriginalFn>(this, 65)(this);
		}*/

		IMaterial *CreateMaterial(const char *pMaterialName, PVOID pVMTKeyValues)
		{
			typedef IMaterial*(__thiscall* OriginalFn)(PVOID,const char*,PVOID);
			return getvfunc<OriginalFn>(this, 83)(this,pMaterialName,pVMTKeyValues);
		}

		IMaterial *FindMaterial(char const* pMaterialName, const char *pTextureGroupName, bool complain = true, const char *pComplainPrefix = NULL)
		{
			typedef IMaterial*(__thiscall* OriginalFn)(PVOID,char const*,const char*,bool,const char*);
			return getvfunc<OriginalFn>(this, 84)(this,pMaterialName,pTextureGroupName,complain,pComplainPrefix);
		}

		/*bool IsMaterialLoaded(const char *pMaterialName)
		{
			typedef bool(__thiscall* OriginalFn)(PVOID,const char*);
			return getvfunc<OriginalFn>(this, 72)(this,pMaterialName);
		}*/

		MaterialHandle_t FirstMaterial()
		{
			typedef MaterialHandle_t(__thiscall* OriginalFn)(PVOID);
			return getvfunc<OriginalFn>(this, 86)(this);
		}

		MaterialHandle_t NextMaterial(MaterialHandle_t h)
		{
			typedef MaterialHandle_t(__thiscall* OriginalFn)(PVOID,MaterialHandle_t);
			return getvfunc<OriginalFn>(this, 87)(this,h);
		}

		MaterialHandle_t InvalidMaterial()
		{
			typedef MaterialHandle_t(__thiscall* OriginalFn)(PVOID);
			return getvfunc<OriginalFn>(this, 88)(this);
		}

		IMaterial *GetMaterial(MaterialHandle_t h)
		{
			typedef IMaterial*(__thiscall* OriginalFn)(PVOID,MaterialHandle_t);
			return getvfunc<OriginalFn>(this, 89)(this,h);
		}

		int	GetNumMaterials()
		{
			typedef int(__thiscall* OriginalFn)(PVOID);
			return getvfunc<OriginalFn>(this, 90)(this); // unknown
		}
	};

	class IVModelRender
	{
	public:
		virtual int		vfunc00() = 0;
		virtual void	ForcedMaterialOverride( IMaterial *newMaterial, OverrideType_t nOverrideType = OVERRIDE_NORMAL, int a = 0 ) = 0;
		virtual bool	vfunc02() = 0;
		virtual int		vfunc03() = 0;
		virtual int		vfunc04() = 0;
		virtual int		vfunc05() = 0;
		virtual int		vfunc06() = 0;
		virtual int		vfunc07() = 0;
		virtual int		vfunc08() = 0;
		virtual int		vfunc09() = 0;
		virtual int		vfunc10() = 0;
		virtual int		vfunc11() = 0;
		virtual int		vfunc12() = 0;
		virtual int		vfunc13() = 0;
		virtual int		vfunc14() = 0;
		virtual int		vfunc15() = 0;
		virtual int		vfunc16() = 0;
		virtual int		vfunc17() = 0;
		virtual int		vfunc18() = 0;
		virtual void a( ) = 0;
		virtual void b( ) = 0;
		virtual void DrawModelExecute(void* rendercontext, const DrawModelState_t &state, const ModelRenderInfo_t &pInfo, matrix3x4_t *pCustomBoneToWorld = NULL ) = 0;
	};

	class IVRenderView
	{
	public:

		virtual void vfunc00() = 0;
		virtual void vfunc01() = 0;
		virtual void vfunc02() = 0;
		virtual void vfunc03() = 0;

		virtual void SetBlend( float blend ) = 0;
		virtual float GetBlend( void ) = 0;

		virtual void SetColorModulation( float const* blend ) = 0;
		virtual void GetColorModulation( float* blend ) = 0;
	};

	class ISurface
	{
	public:
		void DrawSetColor(int r, int g, int b, int a)
		{
			typedef void(__thiscall* OriginalFn)(PVOID, int, int, int, int);
			getvfunc<OriginalFn>(this, 15)(this, r, g, b, a);
		}

		void DrawFilledRect(int x0, int y0, int x1, int y1)
		{
			typedef void(__thiscall* OriginalFn)(PVOID, int, int, int, int);
			getvfunc<OriginalFn>(this, 16)(this, x0, y0, x1, y1);
		}

		void DrawLine(int x0, int y0, int x1, int y1)
		{
			typedef void(__thiscall* OriginalFn)(PVOID, int, int, int, int);
			getvfunc<OriginalFn>(this, 19)(this, x0, y0, x1, y1);
		}

		void DrawSetTextFont(unsigned long font)
		{
			typedef void(__thiscall* OriginalFn)(PVOID, unsigned long);
			getvfunc<OriginalFn>(this, 23)(this, font);
		}
		 
		void DrawSetTextColor(Color col)
		{
			typedef void(__thiscall* OriginalFn)(PVOID, int, int, int, int);
			getvfunc<OriginalFn>(this, 25)(this, col._color[0], col._color[ 1 ], col._color[ 2 ], col._color[ 3 ] );
		}

		void DrawSetTextPos(int x, int y)
		{
			typedef void(__thiscall* OriginalFn)(PVOID, int, int);
			getvfunc<OriginalFn>(this, 26)(this, x, y);
		}

		void DrawPrintText(const wchar_t *text, int textLen)
		{
			typedef void(__thiscall* OriginalFn)(PVOID, const wchar_t *, int, int);
			return getvfunc<OriginalFn>(this, 28)(this, text, textLen, 0);
		}

		unsigned long CreateFont()
		{
			typedef unsigned int(__thiscall* OriginalFn)(PVOID);
			return getvfunc<OriginalFn>(this, 71)(this);
		}

		void SetFontGlyphSet(unsigned long &font, const char *windowsFontName, int tall, int weight, int blur, int scanlines, int flags)
		{
			typedef void(__thiscall* OriginalFn)(PVOID, unsigned long, const char*, int, int, int, int, int, int, int);
			getvfunc<OriginalFn>(this, 72)(this, font, windowsFontName, tall, weight, blur, scanlines, flags, 0, 0);
		}

		void GetTextSize(unsigned long font, const wchar_t *text, int &wide, int &tall)
		{
			typedef void(__thiscall* OriginalFn)(void*, unsigned long font, const wchar_t *text, int &wide, int &tall);
			getvfunc<OriginalFn>(this, 79)(this, font, text, wide, tall);
		}

		void UnlockCursor( )
		{
			getvfunc<void( __thiscall* )( void* )>( this, 66 )( this );
		}
	};
}