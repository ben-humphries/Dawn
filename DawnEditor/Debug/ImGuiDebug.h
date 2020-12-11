#pragma once

#include "Dawn/Dawn.h"

namespace Dawn
{
    namespace Debug
    {
        void DrawDebugRect(ImVec2 min, ImVec2 size)
        {
            ImGui::GetForegroundDrawList()->AddRect(min, ImVec2(min.x + size.x, min.y + size.y), IM_COL32(255, 255, 0, 255));
        }

        void DrawDebugRect(ImVec2 size)
        {
            ImVec2 min = ImVec2(ImGui::GetWindowPos().x + ImGui::GetCursorPos().x, ImGui::GetWindowPos().y + ImGui::GetCursorPos().y);
            ImGui::GetForegroundDrawList()->AddRect(min, ImVec2(min.x + size.x, min.y + size.y), IM_COL32(255, 255, 0, 255));
        }
    }
}