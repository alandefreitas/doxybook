---
title: src/Graphics/Texture.hpp

---

# src/Graphics/Texture.hpp



## Namespaces

| Name           |
| -------------- |
| **[Engine](/namespaces/namespaceEngine.md)** <br>This namespace contains all of the necessary engine components.  |
| **[Engine::Graphics](/namespaces/namespaceEngine_1_1Graphics.md)**  |

## Classes

|                | Name           |
| -------------- | -------------- |
| interface | **[Engine::Graphics::Texture](/classes/classEngine_1_1Graphics_1_1Texture.md)** <br>This is a base texture class that serves as a base class for other texture types.  |




## Source code

```cpp
#pragma once

#include "Handle.hpp"

namespace Engine {
    namespace Graphics {
        class Texture : protected Handle {
          public:
            enum class Type {
                UNKNOWN = 0,
                RGBA_8,
                RGB_8,
                RGBA_16,
                RGB_16,
                RGBA_32,
                RGB_32
            };

            explicit Texture(Type type);
            virtual ~Texture() = default;
            virtual int getWidth() const = 0;
            virtual int getHeight() const = 0;
            virtual int getDepth() const = 0;
            inline bool isLoaded() const {
                return loaded;
            }

          protected:
            bool loaded{false};
            Type type;
        };
    } // namespace Graphics
} // namespace Engine
```


-------------------------------

Updated on 2022-11-15 at 02:37:49 +0000
