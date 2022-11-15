---
title: example-1.cpp
summary: This is an example. 

---

# example-1.cpp



This is an example This is detailed docummentation ```cpp

#include <iostream>
#include <memory>
#include "Engine.hpp"

// A dummy example 
int main() {
    // Create pixels buffer
    const auto pixels = std::make_unique<uint8_t[]>(new uint8_t[1024*1024*3]);
    fillData(*pixels, "path/to/texture.png");

    // Create a texture out of the pixels
    Engine::Graphics::Texture2D texture(1024, 1024, *data);

    // Done
    return 0;
}
```

_Filename: example-1.cpp_

-------------------------------

Updated on 2022-11-15 at 02:37:49 +0000