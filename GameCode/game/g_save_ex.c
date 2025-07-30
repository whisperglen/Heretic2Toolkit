
#include <stdint.h>
#include <Windows.h>
#include <psapi.h>

struct fptr_modules_s
{
	const char *name;
	uint32_t id;
	MODULEINFO data;
};

struct fptr_modules_s games_modules[] =
{
	"gamex86.dll", 1, {0},
	"quake2.dll", 2, {0},
	"Client Effects.dll", 3, {0},
	"Player.dll", 4, {0},
	"H2Common.dll", 5, {0},
	NULL, 6, {0}, //this is the main exe
	"a3dapi.dll", 7, {0},
	"A3DSnd.dll", 8, {0},
	"EAXSnd.dll", 9, {0},
	"ref_gl.dll", 10, {0},
	"ref_soft.dll", 11, {0},
	"SndDll.dll", 12, {0},
	"WinSnd.dll", 13, {0},
};

union fptr_mapping_u
{
	struct fptr_mapping_s
	{
		uint32_t off : 28; //256MB enough to offset into one of these dlls xD
		uint32_t dll : 4;  //15 different ids (0 is not included, to not create confusions with NULL pointers)
	} fld;
	void* ptr;
};

static BOOL g_modules_inited = FALSE;

static void init_modules()
{
	if ( g_modules_inited == FALSE )
	{
		for ( int i = 0; i < ARRAYSIZE( games_modules ); i++ )
		{
			struct fptr_modules_s *md = &games_modules[i];

			HMODULE dllref = GetModuleHandle( md->name );
			if ( dllref && GetModuleInformation( GetCurrentProcess(), dllref, &md->data, sizeof( md->data ) ) )
			{
				//dll memory location retrieved and can be used for remapping, we're golden
			}
			else
			{
				//something went wrong, prb dll not loaded; make this max size so we don't match any pointer
				memset( &md->data, 0xff, sizeof( md->data ) );
			}
		}
		g_modules_inited = TRUE;
	}
}

void* games_fp_to_hexp( void* in )
{
	if ( !g_modules_inited ) init_modules();

	if ( in == NULL ) return NULL;

	union fptr_mapping_u map;
	map.ptr = in;

	for ( int i = 0; i < ARRAYSIZE( games_modules ); i++ )
	{
		struct fptr_modules_s *md = &games_modules[i];
		if ( in >= md->data.lpBaseOfDll && (intptr_t)in < ((intptr_t)md->data.lpBaseOfDll + (intptr_t)md->data.SizeOfImage) )
		{
			//found
			map.fld.dll = md->id;
			map.fld.off = (intptr_t)in - (intptr_t)md->data.lpBaseOfDll;
			break;
		}
	}
	
	return map.ptr;
}

void* games_hexp_to_fp( void* in )
{
	if ( !g_modules_inited ) init_modules();

	if ( in == NULL ) return NULL;

	union fptr_mapping_u map;
	map.ptr = in;

	for ( int i = 0; i < ARRAYSIZE( games_modules ); i++ )
	{
		struct fptr_modules_s *md = &games_modules[i];
		if ( map.fld.dll == md->id )
		{
			//found
			map.ptr = (void*)((intptr_t)map.fld.off + (intptr_t)md->data.lpBaseOfDll);
			break;
		}
	}

	return map.ptr;
}