#include "InputHandler.h"

InputHandler::InputHandler() : m_hasInput(false) {
    resetKeys();
}

InputHandler::~InputHandler() {}

void InputHandler::pressKey(const int &key) {
    m_hasInput = true;
    m_keyPress[key] = true;
    m_keyRepeat[key] = true;
}

void InputHandler::releaseKey(const int &key) {
    m_keyPress[key] = false;
    m_keyRepeat[key] = false;
    m_hasInput = false;
}

bool InputHandler::isKeyPressed(const int &key) {
    if(m_keyPress[key]) {
        m_keyPress[key] = false;
        return true;
    }
    return m_keyPress[key];
}

bool InputHandler::isKeyRepeated(const int &key) {
    return m_keyRepeat[key];
}

void InputHandler::resetPressed() {
    for(unsigned i = 0; i < SDLK_LAST; ++i)
        m_keyPress[i] = false;
}

void InputHandler::resetKeys() {
    m_hasInput = false;
    for (unsigned i = 0; i < SDLK_LAST; ++i) {
        m_keyPress[i] = false;
        m_keyRepeat[i] = false;
    }
}

bool InputHandler::hasInput() {
    return m_hasInput;
}
