
#ifndef PLUGIN_H
#define PLUGIN_H

#include <dlfcn.h>
#include <iostream>
#include "PluginAPI.h"
#include <plugin_std.h>

class Plugin {
public:
    Plugin(const char *lib_path);

    ~Plugin();

    const PPluginInterface *GetInterface() const;

    enum ErrorCode{
        OK = 0, OPEN_LIB_FAILED, LOAD_SYMBOL_FAILED
    };

    ErrorCode GetErrorCode() const;

    void Init();

private:
    void *handle;
    ErrorCode error_code = OK;
    const PPluginInterface *interface;

    void SetInterface();

};


#endif //PLUGIN_H
