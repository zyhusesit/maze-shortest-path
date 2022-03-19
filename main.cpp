#include <iostream>

using namespace std;

struct Point {
    int x{}, y{};
};

struct Path {
    Point *node_point = nullptr;
    Path *next = nullptr;
};


bool checkPath(Path *test_path);

Point *getTop(Path *path);

void *pushStack(Path *path, Point *new_point);

Point *popStack(Path *path);

bool isEmpty(Path *path);

void displayPath(Path *path);

void moveForward(Path *path, int operator_num);

void searchForPath(Path *path, Point *start_point, Point *end_point);

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
    auto *start_point = new Point;
    auto *end_point = new Point;
    Path *test_path = new Path;

    cout << "Please enter the X direction of your start point:" << endl;
    cin >> start_x;
    cout << "Please enter the Y direction of your start point:" << endl;
    cin >> start_y;
    cout << "Please enter the X direction of your end point:" << endl;
    cin >> end_x;
    cout << "Please enter the Y direction of your end point:" << endl;
    cin >> end_y;


    start_point->x = start_x;
    start_point->y = start_y;
    end_point->x = end_x;
    end_point->y = end_y;

    searchForPath(test_path, start_point, end_point);

}

bool checkPath(Path *test_path) {
    Point *point = getTop(test_path);
    if (maze[point->y][point->x] == 0)
        return false;
    else
        return true;

}

Point *getTop(Path *path) {
    if (isEmpty(path)) {
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
    if (isEmpty(path)) {
        cout << "ERROR! The path stack is empty." << endl;
    } else {
        Path *ptr = path->next;
        Point *pop_point;
        pop_point = ptr->node_point;
        path->next = ptr->next;
        delete ptr;
        return pop_point;
    }
}

bool isEmpty(Path *path) {
    if (path->next == nullptr)
        return true;
    else
        return false;
}


void displayPath(Path *path) {
    if (isEmpty(path))
        cout << "ERROR! The path stack is empty." << endl;
    else {
        Path *ptr = path->next;
        while (ptr != nullptr) {
            cout << "(" << ptr->node_point->x << "," << ptr->node_point->y << ")<--";
            ptr = ptr->next;
        }
    }
}

void moveForward(Path *path, int operator_num) {
    auto *new_point = new Point;
    switch (operator_num) {
        case 1://up
            new_point->y = getTop(path)->y - 1;
            new_point->x = getTop(path)->x;
            break;
        case 2://right
            new_point->y = getTop(path)->y;
            new_point->x = getTop(path)->x + 1;
            break;
        case 3://down
            new_point->y = getTop(path)->y + 1;
            new_point->x = getTop(path)->x;
            break;
        case 4://left
            new_point->y = getTop(path)->y;
            new_point->x = getTop(path)->x - 1;
            break;
        default:
            break;
    }
    pushStack(path, new_point);
}

void searchForPath(Path *path, Point *start_point, Point *end_point) {
    pushStack(path, start_point);
    int i = 1;
    while (getTop(path)->x != end_point->x && getTop(path)->y != end_point->y) {

        moveForward(path, 1);
        if (!checkPath(path)) {
            i = 1;
            continue;
        } else {
            popStack(path);
            i++;
        }
        moveForward(path, 2);
        if (!checkPath(path)) {
            i = 1;
            continue;
        } else {
            popStack(path);
            i++;
        }
        moveForward(path, 3);
        if (!checkPath(path)) {
            i = 1;
            continue;
        } else {
            popStack(path);
            i++;
        }
        moveForward(path, 4);
        if (!checkPath(path)) {
            i = 1;
            continue;
        } else {
            break;
        }
    }
    displayPath(path);
}