#include "InputHandler.h"

#include <iostream>

namespace Input {

    InputHandler* INPUT = nullptr;

    InputHandler::InputHandler() : m_hasInput(false), firstClick(true) {
        resetKeys();
        INPUT = this;
    }

    InputHandler::~InputHandler() {}

    void InputHandler::pressKey(const int &key) {
        m_hasInput = true;
        m_keyPress[key] = true;
        m_keyRepeat[key] = true;
        keysPressed.push_back(key);
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
        for(auto key : keysPressed)
            m_keyPress[key] = false;
    }

    void InputHandler::resetKeys() {
        m_hasInput = false;
        for (unsigned i = 0; i < GLFW_KEY_LAST; ++i) {
            m_keyPress[i] = false;
            m_keyRepeat[i] = false;
        }
    }

    bool InputHandler::hasInput() {
        return m_hasInput;
    }

    void InputHandler::clickMouse(const int &button) {
        m_mouseClick[button] = true;
        m_mouseHold[button] = true;
    }

    void InputHandler::releaseMouse(const int &button) {
        m_mouseClick[button] = false;
        m_mouseHold[button] = false;
    }

    bool InputHandler::isMouseClicked(const int &button) {
        if(m_mouseClick[button]) {
            m_mouseClick[button] = false;
            return true;
        }
        return m_mouseClick[button];
    }

    bool InputHandler::isMouseHeld(const int &button) {
        return m_mouseHold[button];
    }

    void InputHandler::onMouseMoved(const double &x, const double &y) {
        prevX = mouseX;
        prevY = mouseY;
        mouseX = (float) x;
        mouseY = (float) y;
    }

    void InputHandler::getMousePosition(float &x, float &y) {
        x = mouseX;
        y = mouseY;
    }

    void InputHandler::getDelta(float &dx, float &dy) {
        dx = mouseX - prevX;
        dy = prevY - mouseY;
    }

    void InputHandler::resetClicked() {
        for(unsigned i = 0; i < GLFW_MOUSE_BUTTON_LAST; ++i)
            m_mouseClick[i] = false;
    }
}
