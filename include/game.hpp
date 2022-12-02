#define GAME_H
#include <vector>
#include <iostream>
#include "windows.h"
#include <bits/stdc++.h>

using namespace std;
class Game {
public:
    Game(int, int, int);
    void draw();
    void inp();
    bool checkWin();
    bool win, loose, games;
private:
    void drawLoose();
    int min_count(int, int);
    void open(int, int);
    vector<vector<int>> arena;
    vector<vector<bool>> isOpen;
};
vector<int> simple_tokenizer(string s);