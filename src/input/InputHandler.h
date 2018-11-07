#ifndef INPUTHANDLER_H_
#define INPUTHANDLER_H_

#include "Global.h"
#include <map>

class InputHandler {

public:

    InputHandler();

    ~InputHandler();

    bool hasInput() const;

    void pressKey(const SDL_Scancode &key);

    void releaseKey(const SDL_Scancode &key);

    bool isKeyPressed(const SDL_Scancode &key);

    bool isKeyRepeated(const SDL_Scancode &key);

    void resetPressed();

    void resetKeys();

private:

    bool inputDetected;

    std::map<SDL_Scancode, bool> keyPress;
    std::map<SDL_Scancode, bool> keyRepeat;

};


#endif
