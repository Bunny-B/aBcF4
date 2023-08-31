#pragma once 
#include "pch.h"
class tempclass {
public:
	uint64_t* swapchain;
	uint64_t unk;
	uint64_t* swapchain0;
	uint64_t unk2;
	uint64_t* swapchain1;

};
class Screen
{
public:
	//   screen + 0x19, outputmode
	char pad00[0x58];				//0x00
	uint32_t m_Width;			//0x58 copy of m_WindowWidth
	uint32_t m_Height;			//0x5C copy of m_WindowHeight
	uint32_t m_WindowWidth;			//0x60  48 89 5C 24 ? 57 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 84 24 ? ? ? ? 48 8B 81 ? ? ? ? 48 8B DA 48 8B F9 
	uint32_t m_WindowHeight;		//0x64  48 89 5C 24 ? 57 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 84 24 ? ? ? ? 48 8B 81 ? ? ? ? 48 8B DA 48 8B F9 
	char pad01[0x88];				//0x68
	IDXGISwapChain* m_pSwapChain;		//0xF0  48 89 5C 24 ? 57 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 84 24 ? ? ? ? 48 8B 81 ? ? ? ? 48 8B DA 48 8B F9 

	/*
	  v8 = (*(__int64 (__fastcall **)(__int64, _QWORD *))(*(_QWORD *)Swapchain + 0x78i64))(Swapchain, output);
      if ( v8 < 0 && qword_TwinkleGetVideo )
        directx_error_handling(
          qword_TwinkleGetVideo,
          v8,
          "screen->swapChain->GetContainingOutput(&screen->output.assignGet())",
          0i64);
	*/
	//   Swapchain = screen[0x1E]; //IDXGISwapChain

	/*
	    v22 = (*(__int64 (__fastcall **)(__int64, int *, _QWORD *, __int64))(*(_QWORD *)output_1 + 0x48i64))(
              output_1,
              matchmod,
              screen + 0x19,
              m_device);
      if ( v22 < 0 )
      {
        if ( qword_TwinkleGetVideo )
          directx_error_handling(
            qword_TwinkleGetVideo,
            v22,
            "screen->output->FindClosestMatchingMode(&matchMode, &screen->outputMode, m_device)",
            0i64);
	*/
	//  output = screen + 0x1D;
	char pad02[0x40];              // 0xF8
};
//size 0x138 //SCreen = (_QWORD *)(*(_QWORD *)(renderer + 0x38) + 0x138i64 * itterator_v7_);
static_assert(sizeof(Screen) == 0x138);

class DxRenderer
{
public:
	Screen* m_pScreen0;                    // 0x00

	BYTE pad00[0x28];                    // 0x08
	uint64_t array_size;				 //0x30
	Screen* m_pScreen;                    // 0x38 //array of screens
	BYTE pad78[0xC0];                    // 0x40
	ID3D11Device* m_pDevice;            // 0x100
	ID3D11DeviceContext* m_pContext;    // 0x108
	char _0x0110[192];
	void* m_settings; //0x01D0 

	
};//Size=0x0110 //   else if ( *(_DWORD *)(0x140i64 * v29 + OFFSET_DXRENDERER_ + 0x4560) == 12290  48 89 4C 24 ? 53 55 56 57 41 54 41 56 41 57 48 83 EC 40 48 C7 44 24 ? ? ? ? ? 4C 8B F1 45 33 FF 

/*
ool_type_screen = v4 == -1;
  }
  if ( bool_type_screen )
  {
LABEL_20:
	IDXGIAdapter1 = a1[0x2D];
	v4 = 0;
	if ( *screen_output_assigne )
	{
	  (*(void (__fastcall **)(_QWORD))(*(_QWORD *)*screen_output_assigne + 0x10i64))(*screen_output_assigne);
	  *screen_output_assigne = 0i64;
	}
	v19 = (*(__int64 (__fastcall **)(__int64, _QWORD, _QWORD *))(*(_QWORD *)IDXGIAdapter1
															   + 0x38i64))(
			IDXGIAdapter1,
			0i64,                               // outputIndex
			screen_output_assigne);
	if ( v19 < 0 && qword_TwinkleGetVideo )
	  directx_error_handling(
		qword_TwinkleGetVideo,
		v19,
		"renderer->m_adapter->EnumOutputs(outputIndex, &screen->output.assignGet())",
		0i64);
  }
  v20 = a1[16];
  v21 = *(_DWORD *)(v20 + 44);
  v22 = *(_DWORD *)(v20 + 40);
  if ( !v21 || !v22 )
  {

  v52 = (*(__int64 (__fastcall **)(_QWORD))(**(_QWORD **)(a1 + 0x100) + 0x138i64))(*(_QWORD *)(a1 + 0x100));// ID3D11Device
*/
//*(_QWORD *)(a1 + 0x20) = *(_QWORD *)(a1 + 0x10);

class a1 //renderer
{
	char pad[0x2D];
	public:
	IDXGIAdapter1* m_adapter;//0x2D 	IDXGIAdapter1 = a1[0x2D];
	//   (unsigned int)(*(_BYTE *)(*(_QWORD *)(renderer + 0x80) + 0x79i64) != 0) + 2,  renderer->m_settings->getTripleBufferingEnable()
	char pad1[0x100 - 0x2D - 8];
	ID3D11Device* m_device;//0x100   v52 = (*(__int64 (__fastcall **)(_QWORD))(**(_QWORD **)(a1 + 0x100) + 0x138i64))(*(_QWORD *)(a1 + 0x100));// ID3D11Device

};

/*
__int64 __fastcall a1_0x60_screen(__int64 a1, __int64 a2, __int64 a3, __int64 IDXGIAdapter1, __int64 SCreen_Cytox, __int64 a6)
{
  int v6; // er11
  bool v7; // zf
  int v8; // eax
  __int64 result; // rax

  v6 = 0;
  *(_QWORD *)(a1 + 132) = *(_QWORD *)a2;
  *(_QWORD *)(a1 + 140) = *(_QWORD *)(a2 + 8);
  if ( *(_QWORD *)(a2 + 32) )
	*(_BYTE *)(a1 + 130) = *(_BYTE *)(a2 + 16);
  else
	*(_BYTE *)(a1 + 130) = 0;
  *(_BYTE *)(a1 + 131) = *(_BYTE *)(a2 + 20);
  *(_WORD *)(a1 + 128) = _InterlockedExchangeAdd((volatile signed __int32 *)(*(_QWORD *)(a1 + 32) + 784i64), 1u) + 1;
  v7 = *(_BYTE *)(a2 + 25) == 0;
  *(_QWORD *)(a1 + 48) = *(_QWORD *)(a2 + 32);
  if ( !v7 )
	v6 = 8;
  if ( *(_BYTE *)(a2 + 24) )
	v6 |= 0x10u;
  v8 = *(_DWORD *)(a2 + 20);
  if ( v8 != 63 || *(int *)(a2 + 16) < 128 || !*(_QWORD *)(a2 + 32) )
	v6 |= 2u;
  if ( v8 == 63 && *(int *)(a2 + 16) > 128 && *(_QWORD *)(a2 + 32) )
	v6 |= 0x20u;
  *(_DWORD *)(a1 + 56) = v6;
  *(_QWORD *)(a1 + 80) = a3;
  *(_QWORD *)(a1 + 0x60) = SCreen_Cytox;
  result = a6;
  *(_QWORD *)(a1 + 0x58) = IDXGIAdapter1;
  *(_QWORD *)(a1 + 104) = a6;
  return result;
}
*/
class a2__//* (_QWORD*)a2 = &unk_142317F68;
{
public:
	// *(_QWORD *)(a2 + 8) = NameThisClass;



};
class NameThisClass
{
public:
	BYTE pad00[0x38];                     // 0x00
	QWORD v6;                              // 0x38
	BYTE pad48[0x8];                      // 0x40
	QWORD a3;                              // 0x48
	QWORD SCreen_Cytox;                    // 0x50
	BYTE pad58[0x8];                      // 0x58
	QWORD class_with_ID3D11Device;         // 0x60
	QWORD a6;                              // 0x68

	// Other member functions or definitions if needed
};


class UnknownClass // unk_142317F68
{
	// Define the UnknownClass if needed
};

class A2Class
{
public:
	DWORD pad00;                              // 0x00 (Assigned: *(_DWORD *)(a2 + 0x10) = 0;)
	A2Class* ptrToA2Class;                     // 0x04 (Assigned: *(_QWORD *)a2 = &unk_142317F68;)
	NameThisClass* NameThisClassInstance;      // 0x08 (Assigned: *(_QWORD *)(a2 + 8) = NameThisClass;)
	DWORD someValueFromNameThisClassInstance;  // 0x10 (Assigned: if (NameThisClass) *(_DWORD *)(a2 + 0x10) = *(_QWORD *)(NameThisClass + 8);)

	// Other member functions or definitions if needed
};



class  pointers
{
public:
	explicit pointers();
	~pointers();
public:
	HWND m_hwnd{};
	IDXGISwapChain* m_swapchain{};
	DxRenderer* m_dxrenderer{};
	PVOID render;
	PVOID Screen_Swapchain_Relatedref;
	PVOID _unk_142317F68_a2_class;
	PVOID m_present;
};
inline pointers* g_pointers{};