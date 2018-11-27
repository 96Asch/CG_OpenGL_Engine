#ifndef INPUTHANDLER_H_
#define INPUTHANDLER_H_

#include "Global.h"

#define MAX_MOUSE_BUTTON 5

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

    void onMouseMoved(const int &x,
                      const int &y,
                      const int &dx,
                      const int &dy);

    void getMousePosition(float &x, float &y);

    void getDelta(float &dx, float &dy);

    void resetClicked();

private:

    bool m_hasInput;
    bool m_keyPress[SDLK_LAST];
    bool m_keyRepeat[SDLK_LAST];

    bool firstClick;
    int mouseX, mouseY;
    int deltaX, deltaY;
    bool m_mouseClick[MAX_MOUSE_BUTTON];
    bool m_mouseHold[MAX_MOUSE_BUTTON];

    void resetKeys();

};


#endif
