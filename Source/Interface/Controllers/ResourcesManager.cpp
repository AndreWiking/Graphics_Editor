
#include "ResourcesManager.h"

ResourcesManager* ResourcesManager::_self = nullptr;

ResourcesManager *ResourcesManager::Instance() {
    if (!_self) {
        _self = new ResourcesManager();
    }
    return _self;
}

bool ResourcesManager::DeleteInstance() {
    if (_self) {
        delete _self;
        _self = 0;
        return true;
    }
    return false;
}


void ResourcesManager::LoadStandardFonts(const ResourceItem<StandardFonts> *font_items, size_t count) {

    for (size_t i = 0; i < count; ++i){
        standard_font_id[font_items[i].type] = AddFont(font_items[i].path);
    }
}

void ResourcesManager::LoadStandardTextures(const ResourceItem<StandardTextures> *texture_items, size_t count) {

    for (size_t i = 0; i < count; ++i){
        standard_textures_id[texture_items[i].type] = AddTexture(texture_items[i].path);
    }
}

size_t ResourcesManager::AddTexture(const char *path) {
    textures.push_back(sf::Texture());
    textures.back().loadFromFile(path);
    return textures.size() - 1;
}

size_t ResourcesManager::AddFont(const char *path) {
    fonts.push_back(sf::Font());
    fonts.back().loadFromFile(path);
    return fonts.size() - 1;
}

sf::Texture &ResourcesManager::GetTexture(size_t id) {
    if (id < textures.size())
        return textures[id];
    else{
        std::cerr << "Get Texture Out Borders\n";
        return textures[zero_texture_id];
    }
}

sf::Font &ResourcesManager::GetFont(size_t id) {
    if (id < fonts.size())
        return fonts[id];
    else{
        std::cerr << "Get Font Out Borders\n";
        return fonts[zero_font_id];
    }
}

size_t ResourcesManager::GetTextureId(ResourcesManager::StandardTextures type) const {
    return standard_textures_id[type];
}

size_t ResourcesManager::GetFontId(ResourcesManager::StandardFonts type) const {
    return standard_font_id[type];
}

