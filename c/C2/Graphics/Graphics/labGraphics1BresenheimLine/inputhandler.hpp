#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H
#include <map>

class InputHandler {
public:
    InputHandler() {}

    void press(int keycode) {
        keys[keycode] = true;
    }

    void release(int keycode) {
        keys[keycode] = false;
    }

    bool is_pressed(int keycode) {
        if(keys.find(keycode) != keys.end()) {
            return keys[keycode];
        }
        return false;
    }

private:
    std::map<int, bool> keys;
};

#endif // INPUTHANDLER_H
