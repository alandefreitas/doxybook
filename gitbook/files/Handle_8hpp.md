---
title: src/Graphics/Handle.hpp

---

# src/Graphics/Handle.hpp



## Namespaces

| Name           |
| -------------- |
| **[Engine](/namespaces/namespaceEngine.md)** <br>This namespace contains all of the necessary engine components.  |
| **[Engine::Graphics](/namespaces/namespaceEngine_1_1Graphics.md)**  |

## Classes

|                | Name           |
| -------------- | -------------- |
| class | **[Engine::Graphics::Handle](/classes/classEngine_1_1Graphics_1_1Handle.md)**  |




## Source code

```cpp
#pragma once

namespace Engine {
    namespace Graphics {
        class Handle {
          public:
            Handle() = default;
            virtual ~Handle() = default;

            int getHandle() const {
                return handle;
            }

          protected:
            // OpenGL handle
            int handle;
        };

        inline int getHandle(Handle& handle) {
            return handle.getHandle();
        }
    } // namespace Graphics
} // namespace Engine
```


-------------------------------

Updated on 2022-11-15 at 00:30:33 +0000
