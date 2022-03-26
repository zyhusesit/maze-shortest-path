#include <iostream>

using namespace std;

struct Point {
    int x, y;
    int prev_point_index;
    Point *next;
};

struct PointQueue {
    Point *front;
    Point *rear;
};

void checkAllDirections(PointQueue *points_queue);

bool checkPoint(int x, int y);

int getPointIndex(Point *&ptr_current_point);

void moveUp(PointQueue *&points_queue);

void moveRight(PointQueue *&points_queue);

void moveDown(PointQueue *&points_queue);

void moveLeft(PointQueue *&points_queue);

void searchForPath(Point *&points_list, Point end_point);

void displayPath(Point *list_tail);

void displayPoint(Point *point);

Point *getPoint(int index);

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

auto start_point = new Point;

int main() {
    start_point->prev_point_index = 0;
    Point end_point{};

    cout << "Please enter the X direction of your start point:" << endl;
    cin >> start_point->x;
    cout << "Please enter the Y direction of your start point:" << endl;
    cin >> start_point->y;
    cout << "Please enter the X direction of your end point:" << endl;
    cin >> end_point.x;
    cout << "Please enter the Y direction of your end point:" << endl;
    cin >> end_point.y;
    searchForPath(start_point, end_point);
}

void checkAllDirections(PointQueue *points_queue) {
    if (points_queue->front->x > 1 && !checkPoint(points_queue->front->x - 1, points_queue->front->y)) {
        moveUp(points_queue);
        points_queue->rear->prev_point_index = getPointIndex(points_queue->front);
    }
    if (points_queue->front->y < 8 && !checkPoint(points_queue->front->x, points_queue->front->y + 1)) {
        moveRight(points_queue);
        points_queue->rear->prev_point_index = getPointIndex(points_queue->front);
    }
    if (points_queue->front->x < 8 && !checkPoint(points_queue->front->x + 1, points_queue->front->y)) {
        moveDown(points_queue);
        points_queue->rear->prev_point_index = getPointIndex(points_queue->front);
    }
    if (points_queue->front->y > 1 && !checkPoint(points_queue->front->x, points_queue->front->y - 1)) {
        moveLeft(points_queue);
        points_queue->rear->prev_point_index = getPointIndex(points_queue->front);
    }
    maze[points_queue->front->x][points_queue->front->y] = 1;
}


bool checkPoint(int x, int y) {
    if (maze[x][y] == 1)
        return true;
    else
        return false;
}

int getPointIndex(Point *&ptr_current_point) {
    int i = 0;
    Point *ptr = start_point;
    while (ptr != ptr_current_point) {
        ptr = ptr->next;
        i++;
    }
    return i;
}

void moveUp(PointQueue *&points_queue) {
    auto *new_point = new Point;
    new_point->x = points_queue->front->x - 1;
    new_point->y = points_queue->front->y;
    points_queue->rear->next = new_point;
    points_queue->rear = new_point;
}

void moveRight(PointQueue *&points_queue) {
    auto *new_point = new Point;
    new_point->x = points_queue->front->x;
    new_point->y = points_queue->front->y + 1;
    points_queue->rear->next = new_point;
    points_queue->rear = new_point;
}

void moveDown(PointQueue *&points_queue) {
    auto *new_point = new Point;
    new_point->x = points_queue->front->x + 1;
    new_point->y = points_queue->front->y;
    points_queue->rear->next = new_point;
    points_queue->rear = new_point;
}

void moveLeft(PointQueue *&points_queue) {
    auto *new_point = new Point;
    new_point->x = points_queue->front->x;
    new_point->y = points_queue->front->y - 1;
    points_queue->rear->next = new_point;
    points_queue->rear = new_point;
}

void searchForPath(Point *&points_list, Point end_point) {
    auto *points_queue = new PointQueue;
    points_queue->front = points_list;
    points_queue->rear = points_list;

    do {
        if (points_queue->front->x != end_point.x || points_queue->front->y != end_point.y)
            checkAllDirections(points_queue);
        else {
            cout << "#####Final path: ";
            displayPath(points_queue->front);
            cout << "\n";
        }
        points_queue->front = points_queue->front->next;
    } while (points_queue->front != points_queue->rear->next);


}

void displayPath(Point *list_tail) {
    Point *ptr = list_tail;
    while (ptr != start_point) {
        displayPoint(ptr);
        ptr = getPoint(ptr->prev_point_index);
    }
    cout << "(" << start_point->x << "," << start_point->y << ")";

}

void displayPoint(Point *point) {
    cout << "(" << point->x << "," << point->y << ")<--";
}

Point *getPoint(int index) {
    Point *ptr = start_point;
    while (index--) {
        ptr = ptr->next;
    }
    return ptr;
}


