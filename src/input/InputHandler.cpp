#include "InputHandler.h"

#include <iostream>

InputHandler::InputHandler() : inputDetected(false) {
    resetKeys();
}

InputHandler::~InputHandler() {}

bool InputHandler::hasInput() const {
    return inputDetected;
}

void InputHandler::pressKey(const int &key) {
    inputDetected = true;
    keyPress[key] = true;
    keyRepeat[key] = true;
}

void InputHandler::releaseKey(const int &key) {
    inputDetected = false;
    keyPress[key] = false;
    keyRepeat[key] = false;
}

bool InputHandler::isKeyPressed(const int &key) {
    if(keyPress[key]) {
        keyPress[key] = false;
        return true;
    }
    return keyPress[key];
}

bool InputHandler::isKeyRepeated(const int &key) {
    return keyRepeat[key];
}

void InputHandler::resetPressed() {
    for(unsigned i = 0; i < SDLK_LAST; ++i)
        keyPress[i] = false;
}

void InputHandler::resetKeys() {
    inputDetected = false;
    for (unsigned i = 0; i < SDLK_LAST; ++i) {
        keyPress[i] = false;
        keyRepeat[i] = false;
    }
}
