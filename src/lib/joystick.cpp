#include "joystick.h"
#include <iostream>

#ifdef __linux__
#include <cstring>
#include <fcntl.h>
#include <linux/joystick.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#elif _WIN32
// TODO
#endif

using OpenJoystick::Joystick;

#ifdef __linux__
Joystick::Joystick(int number, int input_number)
    : m_number(number)
{

    char buffer[32];
    std::sprintf(buffer, "/dev/input/js%d", input_number);
    m_fileDescription = open(buffer, O_RDONLY | O_NONBLOCK);
    if (m_fileDescription < 0)
    {
        std::cerr << "Failed to open joystick " << input_number << std::endl;
    }

    char nbAxis;
    ioctl(m_fileDescription, JSIOCGAXES, &nbAxis);
    if (nbAxis > 0)
    {
        m_info.m_nbAxis = nbAxis;
        m_axisStates = new int32_t[nbAxis];
    }
    else
    {
        m_info.m_nbAxis = 0;
    }

    char nbButtons;
    ioctl(m_fileDescription, JSIOCGBUTTONS, &nbButtons);
    m_info.m_nbButtons = nbButtons > 0 ? nbButtons : 0;

    if (ioctl(m_fileDescription, JSIOCGNAME(sizeof(m_info.m_identifier)), m_info.m_identifier) < 0)
        strncpy(m_info.m_identifier, "Unknown", sizeof(m_info.m_identifier));

    m_valid = true;
}

Joystick::~Joystick()
{
    if (m_fileDescription >= 0)
    {
        close(m_fileDescription);
    }

    delete[] m_axisStates;
}

bool Joystick::IsButtonPressed(uint8_t button_number) const
{
    if (button_number >= m_info.m_nbButtons)
    {
        return false;
    }

    return !!(m_buttonState & (1 << button_number));
}

int32_t Joystick::GetAxisState(uint8_t axis_index) const
{
    if (axis_index >= m_info.m_nbAxis)
    {
        return 0;
    }

    return m_axisStates[axis_index];
}

void Joystick::Update()
{
    if (!m_valid)
    {
        return;
    }

    struct js_event e;

    while (read(m_fileDescription, &e, sizeof(e)) > 0)
    {
        if ((e.type & ~JS_EVENT_INIT) == JS_EVENT_BUTTON)
        {
            if (e.value)
                m_buttonState |= (1 << e.number);
            else
                m_buttonState &= ~(1 << e.number);
        }

        if ((e.type & ~JS_EVENT_INIT) == JS_EVENT_AXIS)
        {
            m_axisStates[e.number] = e.value;
        }
    }

    /* EAGAIN is returned when the queue is empty */
    if (errno != EAGAIN)
    {
        std::cerr << "Error while updating joystick." << std::endl;
        m_valid = false;
    }
}
#endif