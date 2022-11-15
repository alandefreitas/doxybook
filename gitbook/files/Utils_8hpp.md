---
title: src/Utils/Utils.hpp

---

# src/Utils/Utils.hpp



## Namespaces

| Name           |
| -------------- |
| **[Engine](/namespaces/namespaceEngine.md)** <br>This namespace contains all of the necessary engine components.  |
| **[Engine::Utils](/namespaces/namespaceEngine_1_1Utils.md)**  |




## Source code

```cpp
#pragma once

#include "Path.hpp"
#include "ArrayView.hpp"
#include "Config.hpp"
#include "Log.hpp"

namespace Engine {
    namespace Utils {
        inline void name_with_underscores(const std::string& arg) {
            (void)arg;
        }
    }
}
```


-------------------------------

Updated on 2022-11-15 at 02:37:49 +0000
