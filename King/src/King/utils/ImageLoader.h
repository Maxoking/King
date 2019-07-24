#pragma once
#define STB_IMAGE_IMPLEMENTATION
#include "../stb_image/stb_image.h"

namespace King {
  static unsigned char* loadImage(const char* path, int* width, int* height, int* nrChannels) {
    return stbi_load(path, width, height, nrChannels, 0);
  };
}

