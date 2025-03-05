#include <Windows.h> //imports windows api

DWORD history[7] = {0, 0, 0, 0, 0, 0, 0}; //history of last 7 typed letters

char typed = 0; //if the word "WINDOWS" is typed

void simulate_key_press(DWORD key, char ctrl) { //this will simulate key presses
    INPUT input;
    input.type = INPUT_KEYBOARD;
    input.ki.wScan = MapVirtualKey(key, MAPVK_VK_TO_VSC);
    input.ki.time = 0;
    input.ki.dwExtraInfo = 0;

    if (ctrl == 1) {
        input.ki.wVk = VK_CONTROL; //presses the control key
        input.ki.dwFlags = 0;
        SendInput(1, &input, sizeof(INPUT));
    }

    input.ki.wVk = key;
    input.ki.dwFlags = 0;
    SendInput(1, &input, sizeof(INPUT)); //sends the key press

    Sleep(1); //1 ms pause

    input.ki.dwFlags = KEYEVENTF_KEYUP; //unpresses the key
    SendInput(1, &input, sizeof(INPUT)); //sends the key unpress

    if (ctrl == 1) { //if parameter ctrl is 1, then press the control key
        input.ki.wVk = VK_CONTROL;
        input.ki.dwFlags = KEYEVENTF_KEYUP;
        SendInput(1, &input, sizeof(INPUT));
    }
}

LRESULT CALLBACK low_level_keyboard_proc(int n_code, WPARAM w_param, LPARAM l_param) { //this is the callback function, if WIDNOWS was typed, then it will simulate the key press
    if (typed == 1) {
        typed = 0; //changes the value of typed to 0 (so windows can be typed again)
        simulate_key_press(VK_BACK, 0); //deletes last letter
    }
    if (n_code == HC_ACTION) {
        KBDLLHOOKSTRUCT *keyboard = (KBDLLHOOKSTRUCT *)l_param;
        switch (w_param) {
            case WM_KEYDOWN:
            case WM_SYSKEYDOWN:
                for (int i = 0; i < 6; i++) {
                    history[i] = history[i + 1];
                }
                history[6] = keyboard->vkCode;

                if (history[0] == 'W' && history[1] == 'I' && history[2] == 'N' && history[3] == 'D' && history[4] == 'O' && history[5] == 'W' && history[6] == 'S') {
                    simulate_key_press(VK_BACK, 0); //press backspace once to delete text prediction (on google etc.)
                    simulate_key_press(VK_BACK, 1); //press backspace and control to remove the rest of the word
                    simulate_key_press('L', 0);
                    simulate_key_press('I', 0);
                    simulate_key_press('N', 0);
                    simulate_key_press('U', 0);
                    simulate_key_press('X', 0);
                    typed = 1;
                }
        }
    }

    return CallNextHookEx(NULL, n_code, w_param, l_param);
}

int main() {
    HHOOK keyboard_hook = SetWindowsHookEx(WH_KEYBOARD_LL, low_level_keyboard_proc, NULL, 0); //sets the hook
    if (keyboard_hook == NULL) {
        return 1;
    }
    
    MSG message;
    while (GetMessage(&message, NULL, 0, 0)) { //this should be for capturing the typed letters (not 100% sure)
        TranslateMessage(&message);
        DispatchMessage(&message);
    }
    
    UnhookWindowsHookEx(keyboard_hook);
    return 0;
}
