#include <stdio.h>

#define TEST 1

typedef struct RGB {
    short red;
    short green;
    short blue;
} RGB;

typedef struct Point {
    short x;
    short y;
} Point;

double find_slope(Point *first, Point *second) {
    // find Δy / Δx for two points
    return (second->y - first->y) / (second->x - first->x);
}

int trunc_x(double x) { return x /= 1; }

double fract(double x) {
    // Get fractional part of double
    double new = (double)trunc_x(x);
    return x - new;
}

double find_y(double x, int *known_x) {
    if (fract(x) == 0) {
        return (double)known_x[(int)x];
    }

    int left_x = trunc_x(x);
    int right_x = left_x + 1;

    int left_y = known_x[left_x];
    int right_y = known_x[right_x];

    Point left_point = {left_x, left_y};
    Point right_point = {right_x, right_y};

    double slope = find_slope(&left_point, &right_point);

    return (double)left_y + (slope * (x - left_x));
}

int test_trunc() {
    int num = trunc_x(3.141);
    return num == 3;
}

int test_fract() {
    double num = fract(3.141);
	printf("%d", num);
    return num == 0.141000;
}

int test_find_slope() {
    Point p1_1 = {2, 3};
    Point p2_1 = {5, 6};
    double slope_1 = find_slope(&p1_1, &p2_1);

    Point p1_2 = {8, 6};
    Point p2_2 = {4, 3};
    double slope_2 = find_slope(&p1_2, &p2_2);

    return slope_1 == 1 && slope_2 == 2;
}

void test(char *name, int (*func)()) {
    printf("Testing %s...", name);

    int len = *(&name + 1) - name;
    int off = 40 - len;

    if ((*func)()) {
        printf("\e[0;92mPassed\e[0m\n");
    } else {
        printf("\e[0;91mFailed\e[0m\n");
    }
}

void tests() {
    test("test_trunc", test_trunc);
    test("test_fract", test_fract);
    test("test_find_slope", test_find_slope);
}

int main() {
#if TEST
    tests();
#endif

    return 0;
}
