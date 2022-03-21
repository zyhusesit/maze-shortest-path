#include <iostream>

using namespace std;


struct Point {
    int x{}, y{};
};

typedef Point *(*fptr_moveForward)(Point *);

struct FptrLink {
    fptr_moveForward function_pointer;
    FptrLink *next;
};

auto *moveForwardLink = new FptrLink;

struct Path {
    Point *node_point = nullptr;
    Path *next = nullptr;
    FptrLink *fptr_operations_front = moveForwardLink;
    FptrLink *fptr_operations_rear = moveForwardLink->next;
};

bool checkPath(Path *path);

Path *getTop(Path *path);

void *pushStack(Path *path, Point *new_point);

Point *popStack(Path *path);

bool isEmpty(Path *path);

void displayPath(Path *path);

void searchForPath(Path *path, Point *start_point, Point *end_point);

Point *moveUp(Point *point);

Point *moveRight(Point *point);

Point *moveDown(Point *point);

Point *moveLeft(Point *point);

void initializeMoveForwardLink();

void moveForward(Path *path);

void safeMoveForward(Path *path);


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
    initializeMoveForwardLink();

    int start_x, start_y, end_x, end_y;
    auto *start_point = new Point;
    auto *end_point = new Point;

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

    Path *test_path = new Path;
    searchForPath(test_path, start_point, end_point);

    delete test_path;
    delete start_point;
    delete end_point;
}


Path *getTop(Path *path) {
    if (isEmpty(path)) {
        cout << "ERROR! The path stack is empty." << endl;
    } else
        return path->next;
}

void *pushStack(Path *path, Point *new_point) {
    Path *new_node = new Path;
    new_node->node_point = new_point;
    if (!isEmpty(path))
        new_node->next = getTop(path);
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
        Path *ptr = getTop(path);
        while (ptr != nullptr) {
            cout << "(" << ptr->node_point->x << "," << ptr->node_point->y << ")<--";
            ptr = ptr->next;
        }
    }
}

Point *moveUp(Point *point) {
    auto *new_point = new Point;
    new_point->x = point->x - 1;
    new_point->y = point->y;
    return new_point;
}

Point *moveRight(Point *point) {
    auto *new_point = new Point;
    new_point->x = point->x;
    new_point->y = point->y + 1;
    return new_point;
}

Point *moveDown(Point *point) {
    auto *new_point = new Point;
    new_point->x = point->x + 1;
    new_point->y = point->y;
    return new_point;
}

Point *moveLeft(Point *point) {
    auto *new_point = new Point;
    new_point->x = point->x;
    new_point->y = point->y - 1;
    return new_point;
}

void initializeMoveForwardLink() {
    FptrLink *ptr = moveForwardLink;
    ptr->function_pointer = moveUp;

    ptr->next = new FptrLink;
    ptr = ptr->next;
    ptr->function_pointer = moveRight;

    ptr->next = new FptrLink;
    ptr = ptr->next;
    ptr->function_pointer = moveDown;

    ptr->next = new FptrLink;
    ptr = ptr->next;
    ptr->function_pointer = moveLeft;

    ptr->next = moveForwardLink;
}

bool checkPath(Path *path) {
    if (isEmpty(path))
        cout << "ERROR! The path stack is empty." << endl;
    else {
        Path *ptr = getTop(path);
        if (ptr->fptr_operations_rear == ptr->fptr_operations_front) {
            cout << "(" << ptr->node_point->x << "," << ptr->node_point->y << ")<--";
            cout << " has benn tried out! " << endl;
            return true;
        } else {
            cout << "(" << ptr->node_point->x << "," << ptr->node_point->y << ")<--";
            cout << " still can try! " << endl;
            return false;
        }
    }
}

void moveForward(Path *path) {
    Path *ptr = getTop(path);
    Point *new_point = ptr->fptr_operations_rear->function_pointer(ptr->node_point);
    ptr->fptr_operations_rear = ptr->fptr_operations_rear->next;
    pushStack(path, new_point);
    getTop(path)->fptr_operations_front = ptr->fptr_operations_rear->next;
    getTop(path)->fptr_operations_rear = getTop(path)->fptr_operations_front->next;
}

void safeMoveForward(Path *path) {
    Path *ptr = getTop(path);
    if (!checkPath(path)) {
        if (maze[ptr->node_point->x][ptr->node_point->y] == 1) {

            cout << "(" << ptr->node_point->x << "," << ptr->node_point->y << ")<--";
            cout << " is wrong! " << endl;
            popStack(path);

        }
        moveForward(path);
    } else {
        maze[ptr->node_point->x][ptr->node_point->y] = 1;
        popStack(path);
    }
}

void searchForPath(Path *path, Point *start_point, Point *end_point) {
    pushStack(path, start_point);

    while (getTop(path)->node_point->x != end_point->x && getTop(path)->node_point->y != end_point->y) {
        safeMoveForward(path);
        if (getTop(path)->node_point->x == start_point->x && getTop(path)->node_point->y == start_point->y) {
            cout << "No path found!" << endl;
            break;
        }
    }
    displayPath(path);
}