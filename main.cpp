#include <iostream>

using namespace std;

struct Point {
    int x, y;
    bool status = false;
};

struct Path {
    Point *node_point = nullptr;
    Path *next = nullptr;
};

bool checkPath(Path *test_path);

Point *getTop(Path *path);

void *pushStack(Path *path, Point *new_point);

Point *popStack(Path *path);

void displayPath(Path *path);

void moveForward(Path *path, int operator_num);

int maze[10][10] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 1, 0, 0, 0, 1, 0, 1},
        {1, 0, 0, 1, 0, 0, 0, 1, 0, 1},
        {1, 0, 0, 0, 0, 1, 1, 0, 0, 1},
        {1, 0, 1, 1, 1, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
        {1, 0, 1, 0, 0, 0, 1, 0, 0, 1},
        {1, 0, 1, 1, 1, 0, 1, 1, 0, 1},
        {1, 1, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},};

int main() {
    int start_x, start_y, end_x, end_y;
    cout << "Please enter the X direction of your start point:" << endl;
    cin >> start_x;
    cout << "Please enter the Y direction of your start point:" << endl;
    cin >> start_y;
    cout << "Please enter the X direction of your end point:" << endl;
    cin >> end_x;
    cout << "Please enter the Y direction of your end point:" << endl;
    cin >> end_y;

}

bool checkPath(Path *test_path) {
    if (!getTop(test_path)->status)
        return false;
    else
        return true;
}

Point *getTop(Path *path) {
    if (path->next == nullptr) {
        cout << "ERROR! The path stack is empty." << endl;
    } else
        return path->next->node_point;
}

void *pushStack(Path *path, Point *new_point) {
    Path *new_node = new Path;
    new_node->node_point = new_point;
    new_node->next = path->next;
    path->next = new_node;
}

Point *popStack(Path *path) {
    if (path->next == nullptr) {
        cout << "ERROR! The path stack is empty." << endl;
    } else {
        Path *ptr = path->next;
        auto *pop_point = new Point;
        pop_point = ptr->node_point;
        path->next = ptr->next;
        delete ptr;
        return pop_point;
    }
}

void displayPath(Path *path) {
    Path *ptr = path->next;
    while (ptr) {
        cout << "(" << ptr->node_point->x << "," << ptr->node_point->y << ")<--";
        ptr = ptr + 1;
    }
}

void moveForward(Path *path, int operator_num) {
    Point *new_point = new Point;
    switch (operator_num) {
        case 1://up
            new_point->y = getTop(path)->y - 1;
            new_point->x = getTop(path)->x;
            break;
        case 2://right
            new_point->y = getTop(path)->y;
            new_point->x = getTop(path)->x + 1;
            break;
        case 3:
            new_point->y = getTop(path)->y + 1;
            new_point->x = getTop(path)->x;
            break;
        case 4:
            new_point->y = getTop(path)->y;
            new_point->x = getTop(path)->x - 1;
            break;
        default:
            break;
    }
    pushStack(path, new_point);
}
