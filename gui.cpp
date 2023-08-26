#include "pch.h"
#include "gui.hpp"
#include "ImGui/imgui.h"


void gui::dx_init()
{
	auto& style = ImGui::GetStyle();
	style.FrameRounding = 4.0f;
	style.WindowBorderSize = 1.0f;
	style.PopupBorderSize = 1.0f;
	style.GrabRounding = 4.0f;
	style.WindowPadding = { 10.f, 10.f };
	style.PopupRounding = 0.f;
	style.FramePadding = { 8.f, 4.f };
	style.ItemSpacing = { 10.f, 8.f };
	style.ItemInnerSpacing = { 6.f, 6.f };
	style.TouchExtraPadding = { 0.f, 0.f };
	style.IndentSpacing = 21.f;
	style.ScrollbarSize = 15.f;
	style.GrabMinSize = 8.f;
	style.ChildBorderSize = 0.f;
	style.FrameBorderSize = 0.f;
	style.TabBorderSize = 0.f;
	style.WindowRounding = 4.f;
	style.ChildRounding = 3.f;
	style.ScrollbarRounding = 4.f;
	style.TabRounding = 4.f;
	style.WindowTitleAlign = { 0.5f, 0.5f };
	style.ButtonTextAlign = { 0.5f, 0.5f };
	style.DisplaySafeAreaPadding = { 3.f, 3.f };

	ImVec4* colors = ImGui::GetStyle().Colors;
	colors[ImGuiCol_Text] = ImColor(255, 255, 255);
	colors[ImGuiCol_TextDisabled] = ImColor(42, 42, 42);
	colors[ImGuiCol_WindowBg] = ImColor(18, 12, 27);
	colors[ImGuiCol_ChildBg] = ImColor(18, 12, 27);
	colors[ImGuiCol_PopupBg] = ImColor(18, 12, 27);
	colors[ImGuiCol_Border] = ImColor(35, 32, 40);
	colors[ImGuiCol_BorderShadow] = ImColor(35, 32, 40);
	colors[ImGuiCol_FrameBg] = ImColor(35, 42, 106);
	colors[ImGuiCol_FrameBgHovered] = ImColor(35, 42, 106);
	colors[ImGuiCol_FrameBgActive] = ImColor(34, 122, 180);
	colors[ImGuiCol_TitleBg] = ImColor(39, 51, 125);
	colors[ImGuiCol_TitleBgActive] = ImColor(39, 51, 125);
	colors[ImGuiCol_TitleBgCollapsed] = ImColor(39, 51, 125);
	colors[ImGuiCol_MenuBarBg] = ImColor(39, 51, 125);
	colors[ImGuiCol_ScrollbarBg] = ImColor(18, 12, 27);
	colors[ImGuiCol_ScrollbarGrab] = ImColor(18, 12, 27);
	colors[ImGuiCol_ScrollbarGrabHovered] = ImColor(34, 122, 180);
	colors[ImGuiCol_ScrollbarGrabActive] = ImColor(34, 122, 180);
	colors[ImGuiCol_CheckMark] = ImColor(255, 255, 255);
	colors[ImGuiCol_SliderGrab] = ImColor(33, 107, 167);
	colors[ImGuiCol_SliderGrabActive] = ImColor(27, 100, 151);
	colors[ImGuiCol_Button] = ImColor(33, 43, 105);
	colors[ImGuiCol_ButtonHovered] = ImColor(29, 100, 150);
	colors[ImGuiCol_ButtonActive] = ImColor(27, 100, 151);
	colors[ImGuiCol_Header] = ImColor(34, 122, 180);
	colors[ImGuiCol_HeaderHovered] = ImColor(29, 100, 150);
	colors[ImGuiCol_HeaderActive] = ImColor(34, 122, 180);
	colors[ImGuiCol_Separator] = ImColor(46, 46, 46);
	colors[ImGuiCol_SeparatorHovered] = ImColor(46, 46, 46);
	colors[ImGuiCol_SeparatorActive] = ImColor(46, 46, 46);
	colors[ImGuiCol_ResizeGrip] = ImColor(46, 46, 46);
	colors[ImGuiCol_ResizeGripHovered] = ImColor(29, 100, 150);
	colors[ImGuiCol_ResizeGripActive] = ImColor(27, 100, 151);
	colors[ImGuiCol_Tab] = ImColor(33, 43, 105);
	colors[ImGuiCol_TabHovered] = ImColor(34, 122, 180);
	colors[ImGuiCol_TabActive] = ImColor(34, 122, 180);
	colors[ImGuiCol_TabUnfocused] = ImColor(33, 43, 105);
	colors[ImGuiCol_TabUnfocusedActive] = ImColor(34, 122, 180);

	ImGui::SetNextWindowSize(ImVec2(800, 710));
}
void gui::dx_on_tick()
{
}