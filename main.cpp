#include <ctime>
#include <iostream>
#include <windows.h>

using namespace std;

unsigned char grid[4][4] = {0}, tmp[4][4] = {0};
unsigned int seed = 0;
unsigned int steps = 0;
char append = 0;
bool cheque = true;
bool quit = false;

inline unsigned int randnum(int start = 0, int end = 3) {
    seed = (seed * 97597 + 63143) % 308397181;
    return (start + (seed % (end - start + 1)));
}

void check();

void addnum();

void update();

void draw();

int main() {
    seed = time(nullptr);
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    HWND wnd = GetConsoleWindow();
    addnum();
    while (true) {
        if (quit) { break; }
        if (cheque) {
            SetWindowText(wnd, "2048");
            addnum();
        } else {
            SetWindowText(wnd, "Invalid Move !");
        }
        SetConsoleCursorPosition(console, {0, 0});
        draw();
        update();
    }
    return 0;
}

void check() {
    for (char i = 0; i < 4; i++) {
        for (char j = 0; j < 4; j++) {
            if (tmp[i][j] != grid[i][j]) {
                steps++;
                cheque = true;
                return;
            }
        }
    }
    cheque = false;
}

void addnum() {
    if (randnum(1, 100) > 90) {
        append = 2;
    } else {
        append = 1;
    }
    while (true) {
        unsigned char a = randnum(), b = randnum();
        if (grid[a][b] == 0) {
            grid[a][b] = append;
            break;
        }
    }
}

void update() {
    for (char i = 0; i < 4; i++) {
        for (char j = 0; j < 4; j++) {
            tmp[i][j] = grid[i][j];
        }
    }
    char count = 0;
    while (true) {
        if (GetAsyncKeyState(0x57) < 0) {
            for (char i = 0; i < 4; i++) {
                count = 0;
                for (char j = 0; j < 3; j++) {
                    for (char k = 0; k < 3 - j; k++) {
                        if (!grid[j][i]) {
                            for (char x = j; x < 3; x++) {
                                grid[x][i] = grid[x + 1][i];
                            }
                            grid[3][i] = 0;
                        } else { break; }
                    }
                }
                for (char t = 0; t < 4; t++) {
                    if (grid[t][i]) {
                        count++;
                    }
                }
                for (char j = 1; j < count; j++) {
                    if ((grid[j - 1][i] == grid[j][i]) && grid[j - 1][i]) {
                        grid[j - 1][i]++;
                        grid[j][i] = 0;
                        j++;
                    }
                }
                for (char j = 0; j < 3; j++) {
                    if (!grid[j][i]) {
                        grid[j][i] = grid[j + 1][i];
                        grid[j + 1][i] = 0;
                    }
                }
            }
            while (GetAsyncKeyState(0x57) < 0) {
                Sleep(26);
            }
            break;
        }
        if (GetAsyncKeyState(0x53) < 0) {
            for (char i = 0; i < 4; i++) {
                count = 0;
                for (char j = 3; j > 0; j--) {
                    for (char k = 0; k < j; k++) {
                        if (!grid[j][i]) {
                            for (char x = j; x > 0; x--) {
                                grid[x][i] = grid[x - 1][i];
                            }
                            grid[0][i] = 0;
                        } else { break; }
                    }
                }
                for (char t = 0; t < 4; t++) {
                    if (grid[t][i]) {
                        count++;
                    }
                }
                for (char j = 1; j < count; j++) {
                    if ((grid[4 - j][i] == grid[3 - j][i]) && grid[4 - j][i]) {
                        grid[4 - j][i]++;
                        grid[3 - j][i] = 0;
                        j++;
                    }
                }
                for (char j = 3; j > 0; j--) {
                    if (!grid[j][i]) {
                        grid[j][i] = grid[j - 1][i];
                        grid[j - 1][i] = 0;
                    }
                }
            }
            while (GetAsyncKeyState(0x53) < 0) {
                Sleep(26);
            }
            break;
        }
        if (GetAsyncKeyState(0x41) < 0) {
            for (char i = 0; i < 4; i++) {
                count = 0;
                for (char j = 0; j < 3; j++) {
                    for (char k = 0; k < 3 - j; k++) {
                        if (!grid[i][j]) {
                            for (char x = j; x < 3; x++) {
                                grid[i][x] = grid[i][x + 1];
                            }
                            grid[i][3] = 0;
                        } else { break; }
                    }
                }
                for (char t = 0; t < 4; t++) {
                    if (grid[i][t]) {
                        count++;
                    }
                }
                for (char j = 1; j < count; j++) {
                    if ((grid[i][j - 1] == grid[i][j]) && grid[i][j - 1]) {
                        grid[i][j - 1]++;
                        grid[i][j] = 0;
                        j++;
                    }
                }
                for (char j = 0; j < 3; j++) {
                    if (!grid[i][j]) {
                        grid[i][j] = grid[i][j + 1];
                        grid[i][j + 1] = 0;
                    }
                }
            }
            while (GetAsyncKeyState(0x41) < 0) {
                Sleep(26);
            }
            break;
        }
        if (GetAsyncKeyState(0x44) < 0) {
            for (char i = 0; i < 4; i++) {
                count = 0;
                for (char j = 3; j > 0; j--) {
                    for (char k = 0; k < j; k++) {
                        if (!grid[i][j]) {
                            for (char x = j; x > 0; x--) {
                                grid[i][x] = grid[i][x - 1];
                            }
                            grid[i][0] = 0;
                        } else { break; }
                    }
                }
                for (char t = 0; t < 4; t++) {
                    if (grid[i][t]) {
                        count++;
                    }
                }
                for (char j = 1; j < count; j++) {
                    if ((grid[i][4 - j] == grid[i][3 - j]) && grid[i][4 - j]) {
                        grid[i][4 - j]++;
                        grid[i][3 - j] = 0;
                        j++;
                    }
                }
                for (char j = 3; j > 0; j--) {
                    if (!grid[i][j]) {
                        grid[i][j] = grid[i][j - 1];
                        grid[i][j - 1] = 0;
                    }
                }
            }
            while (GetAsyncKeyState(0x44) < 0) {
                Sleep(26);
            }
            break;
        }
        if (GetAsyncKeyState(0x51) < 0) {
            quit = true;
            while (GetAsyncKeyState(0x51) < 0) {
                Sleep(26);
            }
            break;
        }
        if (GetAsyncKeyState(0x52) < 0) {
            for (char j = 0; j < 4; j++) {
                for (char i = 0; i < 4; i++) {
                    grid[j][i] = 0;
                }
            }
            addnum();
            steps = -1;
            while (GetAsyncKeyState(0x52) < 0) {
                Sleep(26);
            }
            break;
        }
        Sleep(26);
    }
    check();
}


void draw() {
    cout << "**** 2048 Game Console Version~ ****" << endl;
    cout << "**                                **" << endl;
    cout << "*   Press WASD to move!            *" << endl;
    cout << "*   Press R to restart game!       *" << endl;
    cout << "*   Press Q to quit at any time.   *" << endl;
    cout << "**                                **" << endl;
    cout << "************************************" << " Steps: " << steps << "\t\t" << endl;
    for (char i = 0; i < 4; i++) {
        for (char j = 0; j < 4; j++) {
            switch (grid[i][j]) {
                case 0:
                    cout << "         ";
                    break;
                case 1:
                    cout << "    2    ";
                    break;
                case 2:
                    cout << "    4    ";
                    break;
                case 3:
                    cout << "    8    ";
                    break;
                case 4:
                    cout << "   1 6   ";
                    break;
                case 5:
                    cout << "   3 2   ";
                    break;
                case 6:
                    cout << "   6 4   ";
                    break;
                case 7:
                    cout << "   128   ";
                    break;
                case 8:
                    cout << "   256   ";
                    break;
                case 9:
                    cout << "   512   ";
                    break;
                case 10:
                    cout << "  10 24  ";
                    break;
                case 11:
                    cout << "  20 48  ";
                    break;
                case 12:
                    cout << "  40 96  ";
                    break;
                case 13:
                    cout << "  81 92  ";
                    break;
                case 14:
                    cout << "  16384  ";
                    break;
                case 15:
                    cout << "  32768  ";
                    break;
                case 16:
                    cout << "  65536  ";
                    break;
                default:
                    cout << "You are an ALIEN! Please Quit.";
            }
        }
        cout << endl << endl << endl << endl;
    }
}
