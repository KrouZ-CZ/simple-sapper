#include "game.hpp"

void start_game(int x, int y, int m) {
    Game game(x, y, m);
    while (game.games) {
        game.inp();
        if (game.checkWin()) {
            game.draw();
            cout << "You win!" << endl;
        }
    }
    Sleep(5000);
}
void logo() {
    system("cls");
    cout << "  _____  "   << endl                
         << " / ____|     "  << endl                
         << "| (___   __ _ _ __  _ __   ___ _ __ " << endl
         << " \\___ \\ / _` | '_ \\| '_ \\ / _ \\ '__|" << endl
         << " ____) | (_| | |_) | |_) |  __/ |   " << endl
         << "|_____/ \\__,_| .__/| .__/ \\___|_|   " << endl
         << "             | |   | |          " << endl
         << "             |_|   |_|              " << endl;
}
void settings(int &x, int &y, int &m) {
    system("cls");
    cout << "Enter x" << endl
    << "> ";
    cin >> x;
    cout << "Enter y" << endl
    << "> ";
    cin >> y;
    cout << "Enter mins" << endl
    << "> ";
    cin >> m;
}
int main() {
    system("title Sapper");
    string tmp;
    bool end = false;
    int x, y, m;
    x = 10;
    y = 10;
    m = 10;
    while (!end) {
        logo();
        cout << "Select:" << endl
        << "1. Start game" << endl
        << "2. Settings" << endl
        << "3. Exit" << endl
        << "> ";
        switch (getchar())
        {
        case '1':
            getline(cin, tmp);
            start_game(x, y, m);
            break;
        case '2':
            settings(x, y, m);
            break;
        case '3':
            end = true;
            break;
        default:
            break;
        }
    }
    return 0;
}