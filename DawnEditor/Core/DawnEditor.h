#pragma once

#include "Dawn/Dawn.h"

class DawnEditor : public Dawn::Application
{
   public:
    DawnEditor();

    void onUpdate() override;
    void onImGuiUpdate() override;
    void onClose() override;

   private:
    float zoom = 1.0f;

    Dawn::Texture tex1;
    Dawn::Texture tex2;

    Dawn::Entity parentsParent;
    Dawn::Entity parent;

    //get window width and height
    Dawn::Framebuffer fb = Dawn::Framebuffer(1920, 1920);

    Dawn::Scene scene = Dawn::Scene();

    //IMGUI
    float leftPanelSizeLeft = 400;
    float leftPanelSizeRight = 1920 - 440;

    ImVec2 viewportPanelSize = ImVec2(0, 0);
};