
#include "GraphicsEditor.h"

GlobalSettings *Settings;
GuiManager *Gui_Manager;
Application *ApplicationPtr;

int main() {

    Settings = GlobalSettings::Instance();
    Gui_Manager = GuiManager::Instance();
    ApplicationPtr = new Application();

    App app(WINDOW_NAME, SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_FPS_LIMIT);

    app.CreateInterface();
    app.Run();

    delete ApplicationPtr;
    GuiManager::DeleteInstance();
    GlobalSettings::DeleteInstance();

    return 0;
}

