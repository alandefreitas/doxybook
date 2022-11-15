---
title: src/Graphics/Texture2D.hpp

---

# src/Graphics/Texture2D.hpp



## Namespaces

| Name           |
| -------------- |
| **[Engine](/namespaces/namespaceEngine.md)** <br>This namespace contains all of the necessary engine components.  |
| **[Engine::Graphics](/namespaces/namespaceEngine_1_1Graphics.md)**  |

## Classes

|                | Name           |
| -------------- | -------------- |
| class | **[Engine::Graphics::Texture2D](/classes/classEngine_1_1Graphics_1_1Texture2D.md)**  |




## Source code

```cpp
#pragma once

#include "Texture.hpp"

namespace Engine {
    namespace Graphics {
        class Texture2D : public Texture {
          public:
            Texture2D(int width, int height, uint8_t* data, Texture::Type type = Texture::Type::RGBA8);
            virtual ~Texture2D();

            int getWidth() const override;
            int getHeight() const override;
            int getDepth() const override;
        };
    } // namespace Graphics
} // namespace Engine
```


-------------------------------

Updated on 2022-11-15 at 03:20:41 +0000
