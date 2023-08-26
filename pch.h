// pch.h : Il s'agit d'un fichier d'en-tête précompilé.
// Les fichiers listés ci-dessous sont compilés une seule fois, ce qui améliore les performances de génération des futures builds.
// Cela affecte également les performances d'IntelliSense, notamment la complétion du code et de nombreuses fonctionnalités de navigation du code.
// Toutefois, les fichiers listés ici sont TOUS recompilés si l'un d'entre eux est mis à jour entre les builds.
// N'ajoutez pas de fichiers fréquemment mis à jour ici, car cela annule les gains de performance.

#ifndef PCH_H
#define PCH_H

// ajouter les en-têtes à précompiler ici
#include "framework.h"
#include <chrono>
#include <thread>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <functional>
#include <filesystem>
#include <format>
#include <memory>
#include <d3d11.h>
#include <d3dcompiler.h>

//on_present directx
#include <dxgi.h>

#include "range.hpp"
#include "handle.hpp"
#include "pattern.h"
#include "module.h"
#include "batch.hpp"
#include "range.hpp"


#define LOG(expr) do { std::cout << "[LOG] " << expr << std::endl; } while(false)
#define hex(value) "0x" << std::hex << std::uppercase << (DWORD64)value << std::dec << std::nouppercase

class globals
{
public:
	HWND g_hwnd{};
	HANDLE g_main_thread{};
	DWORD g_main_thread_id{};
	HINSTANCE g_hmodule{};

	//Matrix g_viewproj{};
	bool g_running{ true };
	int g_width{ 2560 };
	int g_height{ 1440 };

	bool g_fairfight;
	bool g_punkbuster;
	bool g_obs;

	ULONGLONG g_obscheck{};
	ULONGLONG g_blcheck{};
};
inline globals g_globals{};


#endif //PCH_H
