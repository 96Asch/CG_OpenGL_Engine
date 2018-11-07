#ifndef INPUTHANDLER_H_
#define INPUTHANDLER_H_

#include "Global.h"

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

private:

    bool m_hasInput;
    bool m_keyPress[SDLK_LAST];
    bool m_keyRepeat[SDLK_LAST];

    void resetKeys();

};


#endif
