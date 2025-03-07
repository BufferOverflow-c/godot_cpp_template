#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>

#include "entity/template_example.hpp"
#include "extension_interface.hpp"
#include "main.hpp"

namespace brain {
    void initialize_extension_module(godot::ModuleInitializationLevel init_level)
    {
        if (init_level != godot::MODULE_INITIALIZATION_LEVEL_SCENE)
            return;

        godot::ClassDB::register_runtime_class<Main>();
        godot::ClassDB::register_runtime_class<TemplateExample>();
    }

    void uninitialize_extension_module(godot::ModuleInitializationLevel init_level)
    {
        if (init_level != godot::MODULE_INITIALIZATION_LEVEL_SCENE)
            return;
    }

    extern "C"
    {
        GDExtensionBool GDE_EXPORT extension_library_init(GDExtensionInterfaceGetProcAddress addr,
                                                          GDExtensionClassLibraryPtr lib,
                                                          GDExtensionInitialization* init)
        {
            const auto init_level = godot::MODULE_INITIALIZATION_LEVEL_SCENE;
            godot::GDExtensionBinding::InitObject init_obj(addr, lib, init);

            init_obj.register_initializer(initialize_extension_module);
            init_obj.register_terminator(uninitialize_extension_module);
            init_obj.set_minimum_library_initialization_level(init_level);

            return init_obj.init();
        }
    }
}
