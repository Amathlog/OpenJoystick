#include <cstdint>

namespace OpenJoystick
{

struct JoystickInfo
{
    char m_identifier[128];
    uint8_t m_nbButtons;
    uint8_t m_nbAxis;
};

class Joystick
{
public:
    Joystick(int number, int input_number);
    ~Joystick();

    int GetNumber() const { return m_number; }
    bool IsValid() const { return m_valid; }
    const JoystickInfo& GetInfo() const { return m_info; }
    uint32_t GetButtonsState() const { return m_buttonState; }

    bool IsButtonPressed(uint8_t button_number) const;
    int32_t GetAxisState(uint8_t axis_index) const;
    void Update();

private:
    JoystickInfo m_info;
    int32_t* m_axisStates = nullptr;
    uint32_t m_buttonState = 0;
    int m_number;
    int m_fileDescription = 0;
    bool m_valid = false;
};
} // namespace OpenJoystick