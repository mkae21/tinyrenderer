#include "tgaimage.h"
#include <cmath>

constexpr TGAColor white = { 255, 255, 255, 255 }; // attention, BGRA order
constexpr TGAColor green = { 0, 255,   0, 255 };
constexpr TGAColor red = { 0,   0, 255, 255 };
constexpr TGAColor blue = { 255, 128,  64, 255 };
constexpr TGAColor yellow = { 0, 200, 255, 255 };


void line(int ax, int ay, int bx, int by, TGAImage& framebuffer, TGAColor color)
{

    for (float x = ax; x <= bx; x++)
    {
        if (ax > bx) //시작 점이 끝점 보다 클 경우
        {
            std::swap(ax, bx);
            std::swap(ay, by);
        }
        float t = (x - ax) / static_cast<float>(bx - ax);
        int y = std::round(ay + t * (by - ay));

        framebuffer.set(x, y, color); //set은 해당 point에 점 찍기
    }
}

int main(int argc, char** argv) {
    constexpr int width = 64;
    constexpr int height = 64;
    TGAImage framebuffer(width, height, TGAImage::RGB);

    int ax = 7, ay = 3;
    int bx = 12, by = 37;
    int cx = 62, cy = 53;

    line(ax, ay, bx, by, framebuffer, blue);
    line(cx, cy, bx, by, framebuffer, green);
    line(cx, cy, ax, ay, framebuffer, yellow);
    line(ax, ay, cx, cy, framebuffer, red);

    framebuffer.set(ax, ay, white);
    framebuffer.set(bx, by, white);
    framebuffer.set(cx, cy, white);

    framebuffer.write_tga_file("framebuffer.tga");
    return 0;
}