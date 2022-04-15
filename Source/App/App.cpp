
#include "App.h"

App::App(const char *window_name, size_t width, size_t height, unsigned int fps_limit) :
canvas(window_name, width, height) {

    canvas.SetFpsLimit(fps_limit);
    Gui_Manager->SetWindow(&canvas.GetWindow());

}

void App::Run() {

    Settings->GlobalClock.restart();

    while (canvas.GetWindow().isOpen())
    {
        WorkEvents();
        Gui_Manager->WorkDeleteWidgets();

        canvas.ClearScreen();
        Gui_Manager->Draw();

        canvas.Display();

    }
}

void App::WorkEvents() {
    sf::Event event = {};
    while (canvas.GetWindow().pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            canvas.GetWindow().close();
        Gui_Manager->WorkMouseEvent(event);
    }
}

void App::CreateInterface() {

    LoadStandardResources();

    RootWidget *root = new RootWidget(ApplicationPtr->resources_manager->GetTextureId(ResourcesManager::BACKGROUND),
                                      canvas.GetScreeWidth(), canvas.GetScreeHeight());
    Gui_Manager->SetRootWidget(root);

    CreateOpenButtons(root);


    root->UpdateChildrenPos();
}

void App::CreateOpenButtons(Widget *root) {

    Vector2I pos = OpenButtonsStartPos;
    for (int i = 0; i < LogicManager::OPEN_PANEL_COUNT; ++i, pos += OpenButtonsDeltaPos)
        new OpenPanelButton(root, pos, OpenButtonsWidth, OpenButtonsHeight, static_cast<LogicManager::OpenPanel>(i));

}

void App::LoadStandardResources() {
    ApplicationPtr->resources_manager->LoadStandardTextures(standard_texture_items,
                                                            sizeof(standard_texture_items) / sizeof(standard_texture_items[0]));

    ApplicationPtr->resources_manager->LoadStandardFonts(standard_font_items,
                                                         sizeof(standard_font_items) / sizeof(standard_font_items[0]));
}

