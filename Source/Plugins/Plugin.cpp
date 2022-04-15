
#include "Plugin.h"

void Plugin::SetInterface() {
    typedef const PPluginInterface * (*get_plugin_interface_t)();
    dlerror();
    get_plugin_interface_t func = (get_plugin_interface_t) dlsym(handle, PGET_INTERFACE_FUNC);

    const char *dlsym_error = dlerror();
    if (dlsym_error) {
        std::cerr << "Cannot load symbol " << PGET_INTERFACE_FUNC << ": " << dlsym_error << '\n';
        error_code = LOAD_SYMBOL_FAILED;
        interface = nullptr;
    }
    else
        interface = func();
}

Plugin::Plugin(const char *lib_path) {

    handle = dlopen(lib_path, RTLD_LAZY);

    if (!handle) {
        std::cerr << "Cannot open plugin library: " << dlerror() << '\n';
        error_code = OPEN_LIB_FAILED;
    }

    SetInterface();
    Init();
}

Plugin::~Plugin() {
    (*interface->general.deinit)();
    dlclose(handle);
}

const PPluginInterface *Plugin::GetInterface() const { return interface; }

Plugin::ErrorCode Plugin::GetErrorCode() const { return error_code; }

void Plugin::Init() {
    (*interface->general.init)(&app_interface);
}
