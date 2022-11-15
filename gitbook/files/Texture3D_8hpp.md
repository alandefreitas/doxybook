---
title: src/Graphics/Texture3D.hpp

---

# src/Graphics/Texture3D.hpp



## Namespaces

| Name           |
| -------------- |
| **[Engine](/namespaces/namespaceEngine.md)** <br>This namespace contains all of the necessary engine components.  |
| **[Engine::Graphics](/namespaces/namespaceEngine_1_1Graphics.md)**  |

## Classes

|                | Name           |
| -------------- | -------------- |
| class | **[Engine::Graphics::Texture3D](/classes/classEngine_1_1Graphics_1_1Texture3D.md)** <br>Some deprecated class.  |




## Source code

```cpp
#pragma once
#pragma once

#include "Texture.hpp"

namespace Engine {
    namespace Graphics {
        class Texture3D : public Texture {
          public:
            Texture3D(int width, int height, int depth, uint8_t* data, Texture::Type type = Texture::Type::RGBA8);
            virtual ~Texture3D();

            int getWidth() const override;
            int getHeight() const override;
            int getDepth() const override;
        };
    } // namespace Graphics
} // namespace Engine
```


-------------------------------

Updated on 2022-11-15 at 02:20:56 +0000
