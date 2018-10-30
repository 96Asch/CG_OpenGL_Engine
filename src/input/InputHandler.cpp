#include "InputHandler.h"

InputHandler::InputHandler() {
    resetKeys();
}

InputHandler::~InputHandler() {}

void InputHandler::pressKey(const int &key) {
    keyPress[key] = true;
    keyRepeat[key] = true;
}

void InputHandler::releaseKey(const int &key) {
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

void InputHandler::resetKeys() {
    for (unsigned i = 0; i < SDLK_LAST; ++i) {
        keyPress[i] = false;
        keyRepeat[i] = false;
    }
}
