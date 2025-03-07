#include "template_example.hpp"

namespace brain {
    TemplateExample::TemplateExample()
    {
        time_passed = 0.0;
        amplitude = 10.0;
        speed = 1.0;
        time_emit = 0.0;
    }

    TemplateExample::~TemplateExample()
    {
    }

    void TemplateExample::_process(const double delta)
    {
        time_passed += speed * delta;

        godot::Vector2 new_position = godot::Vector2(
            amplitude + (amplitude * sin(time_passed * 2.0)),
            amplitude + (amplitude * cos(time_passed * 1.5)));

        set_position(new_position);

        time_emit += delta;
        if (time_emit > 1.0)
        {
            emit_signal("position_changed", this, new_position);
            time_emit = 0.0;
        }
    }
}
