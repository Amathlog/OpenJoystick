#include <cstdint>
#include <iostream>
#include <joystick.h>

int main()
{
    OpenJoystick::Joystick js(0, 0);
    if (!js.IsValid())
    {
        return -1;
    }

    std::cout << "Joystick 0 (" << js.GetInfo().m_identifier << ") connected." << std::endl;
    std::cout << (int)js.GetInfo().m_nbButtons << " buttons and " << (int)js.GetInfo().m_nbAxis << " axis."
              << std::endl;

    uint32_t previous_button_state = 0;

    while (true)
    {
        js.Update();
        uint32_t button_state = js.GetButtonsState();
        if (button_state != previous_button_state)
        {
            uint32_t diff = button_state ^ previous_button_state;
            for (uint32_t i = 0; i < 32; ++i)
            {
                if (!!(diff & (1 << i)))
                {
                    bool pressed = !!(button_state & (1 << i));
                    std::cout << "Button " << i << " was " << (pressed ? "pressed" : "released") << std::endl;
                }
            }

            previous_button_state = button_state;
        }
    }

    return 0;
}