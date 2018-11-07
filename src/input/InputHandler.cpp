#include "InputHandler.h"

#include <iostream>

InputHandler::InputHandler() : inputDetected(false) {
    resetKeys();
}

InputHandler::~InputHandler() {}

bool InputHandler::hasInput() const {
    return inputDetected;
}

void InputHandler::pressKey(const SDL_Scancode &key) {
    inputDetected = true;
    keyPress[key] = true;
    keyRepeat[key] = true;
}

void InputHandler::releaseKey(const SDL_Scancode &key) {
    inputDetected = false;
    keyPress[key] = false;
    keyRepeat[key] = false;
}

bool InputHandler::isKeyPressed(const SDL_Scancode &key) {
    if(keyPress[key]) {
        keyPress[key] = false;
        return true;
    }
    return keyPress[key];
}

bool InputHandler::isKeyRepeated(const SDL_Scancode &key) {
    return keyRepeat[key];
}

void InputHandler::resetPressed() {
    for(std::map<SDL_Scancode, bool>::iterator it = keyPress.begin();
        it != keyPress.end() ; ++it) {
        it->second = false;
    }
}

void InputHandler::resetKeys() {
    inputDetected = false;
    for(std::map<SDL_Scancode, bool>::iterator it = keyPress.begin();
        it != keyPress.end() ; ++it) {
        it->second = false;
    }
    for(std::map<SDL_Scancode, bool>::iterator it = keyRepeat.begin();
        it != keyRepeat.end() ; ++it) {
        it->second = false;
    }
}
