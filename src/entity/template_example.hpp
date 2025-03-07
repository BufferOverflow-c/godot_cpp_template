#pragma once

#include <godot_cpp/classes/sprite2d.hpp>
#include <godot_cpp/core/class_db.hpp>

namespace brain {
    class TemplateExample : public godot::Sprite2D
    {
        GDCLASS(TemplateExample, godot::Sprite2D)
    public:
        TemplateExample();
        ~TemplateExample();

        void _process(const double delta) override;

        double get_speed() const
        {
            return speed;
        }

        double get_amplitude() const
        {
            return amplitude;
        }

        void set_speed(const double p_speed)
        {
            speed = p_speed;
        }

        void set_amplitude(const double p_amplitude)
        {
            amplitude = p_amplitude;
        }

    protected:
        static void _bind_methods()
        {
            godot::ClassDB::bind_method(godot::D_METHOD("get_speed"), &TemplateExample::get_speed);
            godot::ClassDB::bind_method(godot::D_METHOD("set_speed", "p_speed"),
                                        &TemplateExample::set_speed);

            godot::ClassDB::bind_method(godot::D_METHOD("get_amplitude"),
                                        &TemplateExample::get_amplitude);
            godot::ClassDB::bind_method(godot::D_METHOD("set_amplitude", "p_amplitude"),
                                        &TemplateExample::set_amplitude);

            ADD_PROPERTY(godot::PropertyInfo(godot::Variant::FLOAT, "speed",
                                             godot::PROPERTY_HINT_RANGE, "0,20,0.01"),
                         "set_speed", "get_speed");
            ADD_PROPERTY(godot::PropertyInfo(godot::Variant::FLOAT, "amplitude"), "set_amplitude",
                         "get_amplitude");

            ADD_SIGNAL(godot::MethodInfo("position_changed",
                                         godot::PropertyInfo(godot::Variant::OBJECT, "node"),
                                         godot::PropertyInfo(godot::Variant::VECTOR2, "new_pos")));
        }

    private:
        double time_passed{};
        double amplitude{};
        double speed{};
        time_t time_emit{};
    };
}
