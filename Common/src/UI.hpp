/*
* Adapted from https://github.com/ocornut/imgui/discussions/3862#discussioncomment-8907750
* Thanks tseOrlando
*/

#pragma once

#include <imgui.h>

namespace Classics
{
    class CenteredControlWrapper
    {
    public:
        explicit CenteredControlWrapper(bool result) : result_(result) {}

        operator bool() const { return result_; }
    private:
        bool result_;
    };

    class CenteredControl
    {
    public:
        CenteredControl(ImVec2 window_size, float y = 0.f, float s = 0.f, float su = 0.f) : window_size_(window_size) { y_offset = y; spacing_below = s; spacing_up = su; }
        
        template<typename func>
        CenteredControlWrapper operator()(func control) const
        {
            ImVec2 original_pos = ImGui::GetCursorPos();
            ImGui::SetCursorPos(ImVec2(-10000.0f, -10000.0f));

            ImGui::PushID(10000);
            control();
            ImGui::PopID();

            ImVec2 control_size = ImGui::GetItemRectSize();

            ImGui::Dummy(ImVec2(0, spacing_up));

            ImGui::SetCursorPos(ImVec2((window_size_.x - control_size.x) * 0.5f, original_pos.y + y_offset));

            ImGui::PushID(10001);
            control();
            ImGui::PopID();

            auto result = CenteredControlWrapper(ImGui::IsItemClicked());

            ImGui::Dummy(ImVec2(0, spacing_below));

            return result;
        }
    private:
        ImVec2 window_size_;
        float y_offset;
        float spacing_below;
        float spacing_up;
    };

#define center_(control, ...) CenteredControl{ImGui::GetWindowSize(), __VA_ARGS__}([&]() { control; })
#define CENTER(control, ...) (center_(control, __VA_ARGS__))
}