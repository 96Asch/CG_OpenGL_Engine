#ifndef INPUTHANDLER_H_
#define INPUTHANDLER_H_

#include "Global.h"

class InputHandler {

public:

    InputHandler();

    ~InputHandler();

    bool hasInput() const;

    void pressKey(const int &key);

    void releaseKey(const int &key);

    bool isKeyPressed(const int &key);

    bool isKeyRepeated(const int &key);

    void resetPressed();
    
    void resetKeys();

private:

    bool inputDetected;
    bool keyPress[SDLK_LAST];
    bool keyRepeat[SDLK_LAST];





};


#endif
