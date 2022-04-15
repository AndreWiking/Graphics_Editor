cmake_minimum_required(VERSION 3.20)
project(Graphics_Editor)

set(CMAKE_CXX_STANDARD 17)
SET(CMAKE_OSX_ARCHITECTURES "x86_64;" CACHE STRING "Build architectures for Mac OS X" FORCE)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")


# PluginAPI InversePluginLib

include_directories(/Users/andrewiking/CLionProjects/Graphics_Editor/PluginInclude)


add_executable(Graphics_Editor Source/main.cpp Source/App/Canvas.h Source/App/Canvas.cpp Source/Utils/Vector2.h Source/Utils/Color.h Source/Utils/Vector2.cpp Source/Utils/Color.cpp Source/App/App.cpp Source/App/App.h Source/Interface/Widgets/Buttons/Button.cpp Source/Interface/Widgets/Buttons/Button.h Source/Interface/Controllers/GuiManager.cpp Source/Interface/Controllers/GuiManager.h Source/Interface/Widgets/Widget.cpp Source/Interface/Widgets/Widget.h Source/Interface/Utils/Mouse.cpp Source/Interface/Utils/Mouse.h Source/Interface/Widgets/Text/Text.cpp Source/Interface/Widgets/Text/Text.h Source/Interface/Widgets/Panels/Panel.cpp Source/Interface/Widgets/Panels/Panel.h Source/GraphicsEditor.h Source/Interface/Settings/GlobalSettings.cpp Source/Interface/Settings/GlobalSettings.h Source/Interface/Controllers/ResourcesManager.cpp Source/Interface/Controllers/ResourcesManager.h Source/Interface/Widgets/Panels/PanelHeader.cpp Source/Interface/Widgets/Panels/PanelHeader.h Source/Interface/Widgets/Paint/PaintCanvas.cpp Source/Interface/Widgets/Paint/PaintCanvas.h Source/Utils/Utils2D.cpp Source/Utils/Utils2D.h Source/Interface/Widgets/Slider/Slider.cpp Source/Interface/Widgets/Slider/Slider.h Source/Interface/Widgets/Buttons/OpenPanelButton.cpp Source/Interface/Widgets/Buttons/OpenPanelButton.h Source/Interface/Widgets/Brush/BrushPanel.cpp Source/Interface/Widgets/Brush/BrushPanel.h Source/Interface/Widgets/Brush/BrushSlider.cpp Source/Interface/Widgets/Brush/BrushSlider.h Source/Interface/Widgets/Slider/SliderKnob.cpp Source/Interface/Widgets/Slider/SliderKnob.h Source/Interface/Widgets/Brush/AddBrushSizeButton.cpp Source/Interface/Widgets/Brush/AddBrushSizeButton.h Source/Interface/Widgets/ColorPicker/ColorPickerPanel.cpp Source/Interface/Widgets/ColorPicker/ColorPickerPanel.h Source/Interface/Widgets/ColorPicker/ColorSlider.cpp Source/Interface/Widgets/ColorPicker/ColorSlider.h Source/Interface/Controllers/LogicManager.cpp Source/Interface/Controllers/LogicManager.h Source/Interface/Widgets/Paint/PaintPanel.cpp Source/Interface/Widgets/Paint/PaintPanel.h Source/Interface/Widgets/Curves/CurvesPanel.cpp Source/Interface/Widgets/Curves/CurvesPanel.h Source/Interface/Widgets/Curves/CurvesField.cpp Source/Interface/Widgets/Curves/CurvesField.h Source/Interface/Widgets/Curves/CurvePoint.cpp Source/Interface/Widgets/Curves/CurvePoint.h Source/Utils/CatmullRom.cpp Source/Utils/CatmullRom.h Source/Interface/Widgets/Curves/Curve.cpp Source/Interface/Widgets/Curves/Curve.h Source/Interface/Utils/Application.cpp Source/Interface/Utils/Application.h Source/Interface/Widgets/ToolBar/Toolbar.cpp Source/Interface/Widgets/ToolBar/Toolbar.h Source/Interface/Widgets/ToolBar/Tools/PluginTool.cpp Source/Interface/Widgets/ToolBar/Tools/PluginTool.h Source/Interface/Widgets/ToolBar/Tools/Effect.cpp Source/Interface/Widgets/ToolBar/Tools/Effect.h Source/Interface/Widgets/ToolBar/ToolbarPanel.cpp Source/Interface/Widgets/ToolBar/ToolbarPanel.h Source/Plugins/PluginAPI.cpp Source/Plugins/PluginAPI.h Source/Plugins/Plugin.cpp Source/Plugins/Plugin.h Source/Plugins/PluginManager.cpp Source/Plugins/PluginManager.h Source/Interface/Widgets/ToolBar/ToolWidget.cpp Source/Interface/Widgets/ToolBar/ToolWidget.h Source/Interface/Widgets/ToolBar/ToolButton.cpp Source/Interface/Widgets/ToolBar/ToolButton.h Source/Interface/Widgets/Image.cpp Source/Interface/Widgets/Image.h Source/Interface/Widgets/ToolBar/Tools/Tool.cpp Source/Interface/Widgets/ToolBar/Tools/Tool.h)

include_directories(/usr/local/include)

find_package(SFML 2.5 COMPONENTS graphics REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(Graphics_Editor sfml-graphics)

target_link_libraries(Graphics_Editor ${CMAKE_DL_LIBS})