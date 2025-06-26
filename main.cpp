#include <iostream>
#include <conio.h>
#include <windows.h>
#include <ctime>
#include <stack>
#include <vector>
#include <deque>
#include <fstream>

using namespace std;

const int WIDTH = 30;     // Increased size
const int HEIGHT = 20;
const int WALL = -1;
const char FOOD = 'F';

enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };

struct Node {
    int x, y;
    Node* next;
    Node(int x, int y) : x(x), y(y), next(nullptr) {}
};

class Snake {
public:
    Node* head;
    deque<pair<int, int>> body;

    Snake(int x, int y) {
        head = new Node(x, y);
        body.push_back({x, y});
    }

    void grow(int x, int y) {
        body.push_front({x, y});
        updateHead();
    }

    void move(int x, int y) {
        body.push_front({x, y});
        body.pop_back();
        updateHead();
    }

    void updateHead() {
        head->x = body.front().first;
        head->y = body.front().second;
    }

    bool isOnBody(int x, int y) {
        for (auto& seg : body)
            if (seg.first == x && seg.second == y)
                return true;
        return false;
    }
};

int grid[HEIGHT][WIDTH];
int foodX, foodY;
int score = 0;
stack<int> scoreHistory;
Direction dir = STOP;
Snake* snake;

void spawnFood() {
    srand(time(0));
    do {
        foodX = rand() % WIDTH;
        foodY = rand() % HEIGHT;
    } while (grid[foodY][foodX] != 0 || snake->isOnBody(foodX, foodY));
    grid[foodY][foodX] = 2;
}

void draw() {
    system("cls");
    for (int i = 0; i < WIDTH + 2; i++) cout << "#";
    cout << "\n";

    for (int i = 0; i < HEIGHT; i++) {
        cout << "#";
        for (int j = 0; j < WIDTH; j++) {
            if (i == snake->head->y && j == snake->head->x)
                cout << "O";
            else if (snake->isOnBody(j, i))
                cout << "o";
            else if (i == foodY && j == foodX)
                cout << FOOD;
            else if (grid[i][j] == WALL)
                cout << "#";
            else
                cout << " ";
        }
        cout << "#\n";
    }

    for (int i = 0; i < WIDTH + 2; i++) cout << "#";
    cout << "\nScore: " << score << "\n";
}

void input() {
    if (_kbhit()) {
        switch (_getch()) {
            case 'a': dir = LEFT; break;
            case 'd': dir = RIGHT; break;
            case 'w': dir = UP; break;
            case 's': dir = DOWN; break;
        }
    }
}

bool isValidMove(int x, int y) {
    return x >= 0 && y >= 0 && x < WIDTH && y < HEIGHT && grid[y][x] != WALL;
}

bool logic() {
    int x = snake->head->x;
    int y = snake->head->y;

    switch (dir) {
        case LEFT: x--; break;
        case RIGHT: x++; break;
        case UP: y--; break;
        case DOWN: y++; break;
        default: return true;
    }

    if (!isValidMove(x, y) || snake->isOnBody(x, y))
        return false;

    if (x == foodX && y == foodY) {
        snake->grow(x, y);
        score += 10;
        spawnFood();
    } else {
        snake->move(x, y);
    }

    return true;
}

void initWalls() {
    for (int i = 0; i < WIDTH; i++) {
        grid[0][i] = WALL;
        grid[HEIGHT - 1][i] = WALL;
    }
    for (int i = 0; i < HEIGHT; i++) {
        grid[i][0] = WALL;
        grid[i][WIDTH - 1] = WALL;
    }
}

void saveScoreToFile(int finalScore) {
    ofstream file("score_history.txt", ios::app);
    if (file.is_open()) {
        time_t now = time(0);
        file << "Score: " << finalScore << " at " << ctime(&now);
        file.close();
    }
}

int main() {
    snake = new Snake(WIDTH / 2, HEIGHT / 2);
    initWalls();
    spawnFood();

    while (true) {
        draw();
        input();
        if (!logic()) break;
        Sleep(120); // Control speed
    }

    cout << "\nGame Over! Final Score: " << score << "\n";
    scoreHistory.push(score);
    saveScoreToFile(score);

    cout << "Score History (Latest on top):\wsn";
    while (!scoreHistory.empty()) {
        cout << scoreHistory.top() << "\n";
        scoreHistory.pop();
    }

    cout << "\nScore saved in 'score_history.txt'\n";
    return 0;
}
