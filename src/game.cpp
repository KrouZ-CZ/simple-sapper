#include "game.hpp"
#include <ctime>
#include <random>

Game::Game(int width, int height, int count) {
    srand(time(nullptr));
    loose = false;
    win = false;
    games = true;
    // Инициализирую массивы
    for (int i = 0; i < width; i++) {
        arena.push_back(vector<int> {});
        isOpen.push_back(vector<bool> {});
        for (int j = 0; j < height; j++) {
            arena[i].push_back(0);
            isOpen[i].push_back(false);
        }
    }
    // Генерация мин
    int x, y;
    for (int i = 0; i < count; i++) {
        while (true) {
            x = rand() % height;
            y = rand() % width;
            if (arena[y][x] == 0) {
                arena[y][x] = -1;
                break; 
            }
        }
    }
    // Генерация номеров
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            if (arena[i][j] == -1) {
                continue;
            }
            arena[i][j] = min_count(j, i);
        }
    }
}

void Game::draw() {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    system("cls");
    cout << "  ";
    for (int i = 0; i < arena[0].size(); i++) {
        cout << "| " << i << " ";
    }
    cout << "|" << endl;
    for (int i = 0; i < arena[0].size(); i++) {
        cout << "----";
    }
    cout << "---" << endl;

    for (int i = 0; i < arena.size(); i++) {
        cout << i << " ";
        for (int j = 0; j < arena[0].size(); j++) {
            if (isOpen[i][j]) {
                cout << "| ";
                switch (arena[i][j])
                {
                case -1:
                    SetConsoleTextAttribute(h, 2);
                    cout << "M ";
                    break;
                case 0:
                    cout << "  ";
                    break;
                case 1:
                    SetConsoleTextAttribute(h, 11);
                    cout << arena[i][j] << " ";
                    break;
                case 2:
                    SetConsoleTextAttribute(h, 9);
                    cout << arena[i][j] << " ";
                    break;
                case 3:
                    SetConsoleTextAttribute(h, 6);
                    cout << arena[i][j] << " ";
                    break;
                default:
                    SetConsoleTextAttribute(h, 4);
                    cout << arena[i][j] << " ";
                    break;
                }
                SetConsoleTextAttribute(h, 15);
            } else {
                cout << "| X ";
            }
        }
        cout << "|" << endl;
        for (int i = 0; i < arena[0].size(); i++) {
            cout << "----";
        }
        cout << "---" << endl;
    }
}

void Game::inp() {
    string select;
    while (true) {
        draw();
        cout << "Select (x y): ";
        getline(cin, select);
        if (select == (string)"e"){
            games = false;
            return;
        }
        vector<int> map = simple_tokenizer(select);
        int x = map[0];
        int y = map[1];
        if (x >= arena[0].size() || y >= arena.size()) {
            cout << "Error scope" << endl;
            Sleep(2000);
        } else {
            if (arena[y][x] == -1) {
                games = false;
                loose = true;
                drawLoose();
                cout << "you loose";
                return;
            }
            open(x, y);
            break;
        }
    }
}

void Game::open(int x, int y) {
    isOpen[y][x] = true;
    if (arena[y][x] == 0) {
        if (y != 0 && !isOpen[y-1][x]) {
            open(x, y-1);
        }
        if (x != arena[0].size()-1 && !isOpen[y][x+1]) {
            open(x+1, y);
        }
        if (y != arena.size()-1 && !isOpen[y+1][x]) {
            open(x, y+1);
        }
        if (x != 0 && !isOpen[y][x-1]) {
            open(x-1, y);
        }
    }
}

bool Game::checkWin() {
    for (int i = 0; i < arena.size(); i++) {
        for (int j = 0; j < arena[0].size(); j++) {
            if (arena[i][j] != -1 && !isOpen[i][j]) {
                return false;
            }
        }
    }
    win = true;
    games = false;
    return true;
}

void Game::drawLoose() {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    system("cls");
    cout << "  ";
    for (int i = 0; i < arena[0].size(); i++) {
        cout << "| " << i << " ";
    }
    cout << "|" << endl;
    for (int i = 0; i < arena[0].size(); i++) {
        cout << "----";
    }
    cout << "---" << endl;

    for (int i = 0; i < arena.size(); i++) {
        cout << i << " ";
        for (int j = 0; j < arena[0].size(); j++) {
            cout << "| ";
            switch (arena[i][j])
            {
            case -1:
                SetConsoleTextAttribute(h, 2);
                cout << "M ";
                break;
            case 0:
                cout << "  ";
                break;
            case 1:
                SetConsoleTextAttribute(h, 11);
                cout << arena[i][j] << " ";
                break;
            case 2:
                SetConsoleTextAttribute(h, 9);
                cout << arena[i][j] << " ";
                break;
            case 3:
                SetConsoleTextAttribute(h, 6);
                cout << arena[i][j] << " ";
                break;
            default:
                SetConsoleTextAttribute(h, 4);
                cout << arena[i][j] << " ";
                break;
            }
            SetConsoleTextAttribute(h, 15);
        }
        cout << "|" << endl;
        for (int i = 0; i < arena[0].size(); i++) {
            cout << "----";
        }
        cout << "---" << endl;
    }
}

int Game::min_count(int x, int y) {
    int mins = 0;
    if (x == 0 && y == 0) {
        if (arena[y+1][x] == -1) { mins++; }
        if (arena[y+1][x+1] == -1) { mins++; }
        if (arena[y][x+1] == -1) { mins++; }
    } else if (y == 0 && x == arena[0].size() - 1) {
        if (arena[y][x-1] == -1) { mins++; }
        if (arena[y+1][x-1] == -1) { mins++; }
        if (arena[y+1][x] == -1) { mins++; }
    } else if (x == arena[0].size() - 1 && y == arena.size() - 1) {
        if (arena[y-1][x] == -1) { mins++; }
        if (arena[y-1][x-1] == -1) { mins++; }
        if (arena[y][x-1] == -1) { mins++; }
    } else if (y == arena.size() - 1 && x == 0) {
        if (arena[y-1][x] == -1) { mins++; }
        if (arena[y-1][x+1] == -1) { mins++; }
        if (arena[y][x+1] == -1) { mins++; }
    } else if (y == 0) {
        if (arena[y][x-1] == -1) { mins++; }
        if (arena[y+1][x-1] == -1) { mins++; }
        if (arena[y+1][x] == -1) { mins++; }
        if (arena[y+1][x+1] == -1) { mins++; }
        if (arena[y][x+1] == -1) { mins++; }
    } else if (x == arena[0].size() - 1) {
        if (arena[y-1][x] == -1) { mins++; }
        if (arena[y-1][x-1] == -1) { mins++; }
        if (arena[y][x-1] == -1) { mins++; }
        if (arena[y+1][x-1] == -1) { mins++; }
        if (arena[y+1][x] == -1) { mins++; }
    } else if (y == arena.size()-1) {
        if (arena[y][x+1] == -1) { mins++; }
        if (arena[y-1][x+1] == -1) { mins++; }
        if (arena[y-1][x] == -1) { mins++; }
        if (arena[y-1][x-1] == -1) { mins++; }
        if (arena[y][x-1] == -1) { mins++; }
    } else if (x == 0) {
        if (arena[y-1][x] == -1) { mins++; }
        if (arena[y-1][x+1] == -1) { mins++; }
        if (arena[y][x+1] == -1) { mins++; }
        if (arena[y+1][x+1] == -1) { mins++; }
        if (arena[y+1][x] == -1) { mins++; }
    } else {
        if (arena[y-1][x] == -1) { mins++; }
        if (arena[y-1][x+1] == -1) { mins++; }
        if (arena[y][x+1] == -1) { mins++; }
        if (arena[y+1][x+1] == -1) { mins++; }
        if (arena[y+1][x] == -1) { mins++; }
        if (arena[y+1][x-1] == -1) { mins++; }
        if (arena[y][x-1] == -1) { mins++; }
        if (arena[y-1][x-1] == -1) { mins++; }
    }
    return mins;
}

vector<int> simple_tokenizer(string s)
{
    vector<int> map;
    stringstream ss(s);
    string word;
    while (!ss.eof()) {
        getline(ss, word, ' ');
        map.push_back(atoi(word.c_str()));
    }
    return map;
}