#ifndef INPUTHANDLER_H_
#define INPUTHANDLER_H_

#include <vector>

#include "Global.h"

namespace Input {

    class InputHandler;

    extern InputHandler* INPUT;

    class InputHandler {

    public:

        InputHandler();

        ~InputHandler();

        void pressKey(const int &key);

        void releaseKey(const int &key);

        bool isKeyPressed(const int &key);

        bool isKeyRepeated(const int &key);

        bool hasInput();

        void resetPressed();

        void clickMouse(const int &button);

        void releaseMouse(const int &button);

        bool isMouseClicked(const int &button);

        bool isMouseHeld(const int &button);

        void onMouseMoved(const double &x, const double &y);

        void getMousePosition(float &x, float &y);

        void getDelta(float &dx, float &dy);

        void resetClicked();

    private:

        std::vector<int> keysPressed;

        bool m_hasInput;
        bool m_keyPress[GLFW_KEY_LAST];
        bool m_keyRepeat[GLFW_KEY_LAST];

        bool firstClick;
        float mouseX, mouseY, prevX, prevY;
        bool m_mouseClick[GLFW_MOUSE_BUTTON_LAST];
        bool m_mouseHold[GLFW_MOUSE_BUTTON_LAST];

        void resetKeys();

    };
}


#endif
