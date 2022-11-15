---
title: src/Graphics/Framebuffer.hpp

---

# src/Graphics/Framebuffer.hpp



## Namespaces

| Name           |
| -------------- |
| **[Engine](/namespaces/namespaceEngine.md)** <br>This namespace contains all of the necessary engine components.  |
| **[Engine::Graphics](/namespaces/namespaceEngine_1_1Graphics.md)**  |

## Classes

|                | Name           |
| -------------- | -------------- |
| class | **[Engine::Graphics::Framebuffer](/classes/classEngine_1_1Graphics_1_1Framebuffer.md)**  |




## Source code

```cpp
#pragma once

#include "Texture.hpp"

namespace Engine {
    namespace Graphics {
        class Framebuffer : public Texture {
          public:
            Framebuffer(int width, int height);
            virtual ~Framebuffer();

            int getWidth() const override;
            int getHeight() const override;
            int getDepth() const override;
        };
    } // namespace Graphics
} // namespace Engine
```


-------------------------------

Updated on 2022-11-15 at 03:20:41 +0000
