#include <fstream>
#include <cstdint>

#pragma pack(push, 1)
struct BMPHeader {
    // BMP 파일 헤더
    uint16_t type{ 0x4D42 };
    uint32_t size{ 0 };
    uint16_t reserved1{ 0 };
    uint16_t reserved2{ 0 };
    uint32_t offset{ sizeof(BMPHeader) + sizeof(BMPInfoHeader) };
};

struct BMPInfoHeader {
    // BMP 정보 헤더
    uint32_t size{ sizeof(BMPInfoHeader) };
    int32_t width{ 0 };
    int32_t height{ 0 };
    uint16_t planes{ 1 };
    uint16_t bitCount{ 24 };
    uint32_t compression{ 0 };
    uint32_t imageSize{ 0 };
    int32_t xPelsPerMeter{ 0 };
    int32_t yPelsPerMeter{ 0 };
    uint32_t clrUsed{ 0 };
    uint32_t clrImportant{ 0 };
};
#pragma pack(pop)

int main() {
    // raw 파일 읽기
    const char* filename = "input.raw";
    std::ifstream input(filename, std::ios::binary);
    if (!input) {
        return 1;
    }

    // raw 파일의 너비, 높이 및 채널 수 지정
    const int width = 640;
    const int height = 480;
    const int channels = 3;

    // BMP 파일 헤더 설정
    BMPHeader bmpHeader;
    bmpHeader.size = sizeof(BMPHeader) + sizeof(BMPInfoHeader) + width * height * channels;
    BMPInfoHeader bmpInfoHeader;
    bmpInfoHeader.width = width;
    bmpInfoHeader.height = -height;  // 비트맵은 y축이 아래로 증가하므로 음수로 설정

    // BMP 파일 생성
    const char* outFilename = "output.bmp";
    std::ofstream output(outFilename, std::ios::binary);
    if (!output) {
        return 1;
    }

    // BMP 파일 헤더 쓰기
    output.write(reinterpret_cast<const char*>(&bmpHeader), sizeof(bmpHeader));
    output.write(reinterpret_cast<const char*>(&bmpInfoHeader), sizeof(bmpInfoHeader));

    // raw 데이터를 BMP 파일에 쓰기
    char buffer[width * channels];
    for (int y = height - 1; y >= 0; --y) {
        for (int x = 0; x < width; ++x) {
            input.read(buffer, channels);
            output.write(buffer, channels);
        }
    }

    // 파일 닫기
    input.close();
    output.close();

    return 0;
}
