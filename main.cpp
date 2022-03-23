#include <iostream>

using namespace std;

struct Point {
    int x, y;
    int prev_point_index;
};

struct PointQueue {
    Point *front;
    Point *rear;
};

void checkAllDirections(Point *points, PointQueue *points_queue);

bool checkPoint(int x, int y);

int getPointIndex(Point *points, Point *ptr_current_point);

void moveUp(Point *points, PointQueue *points_queue);

void moveRight(Point *points, PointQueue *points_queue);

void moveDown(Point *points, PointQueue *points_queue);

void moveLeft(Point *points, PointQueue *points_queue);

void searchForPath(Point *points, Point *end_point);

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
    Point points[100];
    points[0].prev_point_index = 0;
    auto *end_point = new Point;

    cout << "Please enter the X direction of your start point:" << endl;
    cin >> points[0].x;
    cout << "Please enter the Y direction of your start point:" << endl;
    cin >> points[0].y;
    cout << "Please enter the X direction of your end point:" << endl;
    cin >> end_point->x;
    cout << "Please enter the Y direction of your end point:" << endl;
    cin >> end_point->y;

    searchForPath(points, end_point);
}

void checkAllDirections(Point *points, PointQueue *points_queue) {
    if (!checkPoint(points_queue->rear->x - 1, points_queue->rear->y))
        moveUp(points, points_queue);
    if (checkPoint(points_queue->rear->x, points_queue->rear->y + 1))
        moveRight(points, points_queue);
    if (checkPoint(points_queue->rear->x + 1, points_queue->rear->y))
        moveDown(points, points_queue);
    if (checkPoint(points_queue->rear->x, points_queue->rear->y - 1))
        moveLeft(points, points_queue);

    points_queue->front = points_queue->front + 1;
}

bool checkPoint(int x, int y) {
    if (maze[x][y] == 1)
        return true;
    else
        return false;
}

int getPointIndex(Point *points, Point *ptr_current_point) {
    return (int) (ptr_current_point - points);
}

void moveUp(Point *points, PointQueue *points_queue) {
    int current_point_index = getPointIndex(points, points_queue->rear) + 1;
    points[current_point_index].x = points_queue->front->x - 1;
    points[current_point_index].y = points_queue->front->y;
    points[current_point_index].prev_point_index = getPointIndex(points, points_queue->front);
    points_queue->rear = points_queue->rear + 1;
}

void moveRight(Point *points, PointQueue *points_queue) {
    int current_point_index = getPointIndex(points, points_queue->rear) + 1;
    points[current_point_index].x = points_queue->front->x - 1;
    points[current_point_index].y = points_queue->front->y;
    points[current_point_index].prev_point_index = getPointIndex(points, points_queue->front);
    points_queue->rear = points_queue->rear + 1;

}

void moveDown(Point *points, PointQueue *points_queue) {
    int current_point_index = getPointIndex(points, points_queue->rear) + 1;
    points[current_point_index].x = points_queue->front->x - 1;
    points[current_point_index].y = points_queue->front->y;
    points[current_point_index].prev_point_index = getPointIndex(points, points_queue->front);
    points_queue->rear = points_queue->rear + 1;

}

void moveLeft(Point *points, PointQueue *points_queue) {
    int current_point_index = getPointIndex(points, points_queue->rear) + 1;
    points[current_point_index].x = points_queue->front->x - 1;
    points[current_point_index].y = points_queue->front->y;
    points[current_point_index].prev_point_index = getPointIndex(points, points_queue->front);
    points_queue->rear = points_queue->rear + 1;

}

void searchForPath(Point *points, Point *end_point) {
    auto *points_queue = new PointQueue;
    points_queue->front = points;
    points_queue->rear = points;

    do {
        while (points_queue->rear->x != end_point->x && points_queue->rear->y != end_point->y) {
            checkAllDirections(points, points_queue);
        }
    } while (points_queue->front != points_queue->rear);

}

