#include "tgaimage.h"
#include <cstdlib>
#include <ctime>
#include <cmath>

constexpr TGAColor white = { 255, 255, 255, 255 }; // attention, BGRA order
constexpr TGAColor green = { 0, 255,   0, 255 };
constexpr TGAColor red = { 0,   0, 255, 255 };
constexpr TGAColor blue = { 255, 128,  64, 255 };
constexpr TGAColor yellow = { 0, 200, 255, 255 };


void line(int ax, int ay, int bx, int by, TGAImage& framebuffer, TGAColor color)
{
    bool steep = std::abs(ax - bx) < std::abs(ay - by); //dx보다 dy가 클 때 기울기가 높음
    
    if (steep)//transpose image
    {
        std::swap(ax, ay);
        std::swap(bx, by);
    }

    if (ax > bx) //시작 점이 끝점 보다 클 경우
    {
        std::swap(ax, bx);
        std::swap(ay, by);
    }
    
    int y = ay;
    int ierror = 0;

    for (float x = ax; x <= bx; x++)//x는 1씩 전진
    {
        if(steep)
            framebuffer.set(y, x, color); //역 전치해서 출력
        else
            framebuffer.set(x, y, color); //set은 해당 point에 점 찍기

        ierror += 2 * std::abs(by - ay);
        
        if (ierror > bx - ax)
        {
            y += by > ay ? 1 : -1; //1 상승
            ierror -= 2 * (bx - ax);
        }
    }
}

int main(int argc, char** argv) {
    constexpr int width = 64;
    constexpr int height = 64;
    TGAImage framebuffer(width, height, TGAImage::RGB);

    std::srand(std::time(nullptr));
    for (int i = 0; i < (1 << 24); i++)
    {
        //width,height의 범위 안으로 설정
        int ax = rand() % width, ay = rand() % height;
        int bx = rand() % width, by = rand() % height;

        //rand % 256은 int 4bytes다, color는 uint8_t이기에 축소 변환 불가능. 명시적으로 변환한다.
        line(ax, ay, bx, by, framebuffer, { static_cast<uint8_t>(std::rand() % 256),
                                            static_cast<uint8_t>(std::rand() % 256),
                                            static_cast<uint8_t>(std::rand() % 256),
                                            static_cast<uint8_t>(std::rand() % 256) });
    }

    framebuffer.write_tga_file("framebuffer.tga");
    return 0;
}