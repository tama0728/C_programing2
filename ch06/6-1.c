#include <stdio.h>
#include <math.h>   // sqrt(), pow(), fabs()

int main(void) {

    struct point {
        int x;
        int y;
    };
    struct point p1 = {10, 20};
    struct point p2 = {30, 40};

    double dist;
    dist = sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));     //피타고라스 정리
    printf("%f\n", dist);
    int area = fabs((p1.x - p2.x) * (p1.y - p2.y));     //절대값 사용
    printf("%d\n", area);
    return 0;
}
