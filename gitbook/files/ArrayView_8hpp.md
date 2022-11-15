---
title: src/Utils/ArrayView.hpp

---

# src/Utils/ArrayView.hpp



## Namespaces

| Name           |
| -------------- |
| **[Engine](/namespaces/namespaceEngine.md)** <br>This namespace contains all of the necessary engine components.  |
| **[Engine::Utils](/namespaces/namespaceEngine_1_1Utils.md)**  |

## Classes

|                | Name           |
| -------------- | -------------- |
| class | **[Engine::Utils::ArrayView](/classes/classEngine_1_1Utils_1_1ArrayView.md)** <br>Filesystem path utility functions.  |




## Source code

```cpp
#pragma once

namespace Engine {
    namespace Utils {
        template<typename T = uint8_t>
        class ArrayView {
        public:
            ArrayView(const T* src, size_t len);
            virtual ~ArrayView() = default;

            virtual const T* data() const;
            virtual size_t size() const;
        };
    }
}
```


-------------------------------

Updated on 2022-11-15 at 02:37:49 +0000
