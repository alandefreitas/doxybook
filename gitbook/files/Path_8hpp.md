---
title: src/Utils/Path.hpp

---

# src/Utils/Path.hpp



## Namespaces

| Name           |
| -------------- |
| **[Engine](/namespaces/namespaceEngine.md)** <br>This namespace contains all of the necessary engine components.  |
| **[Engine::Utils](/namespaces/namespaceEngine_1_1Utils.md)**  |
| **[Engine::Utils::Path](/namespaces/namespaceEngine_1_1Utils_1_1Path.md)** <br>Filesystem path utility functions.  |




## Source code

```cpp
#pragma once
#include <string>

namespace Engine {
    namespace Utils {
        namespace Path {
            std::string getFilename(const std::string& path);
            std::string getExtension(const std::string& path);
        }
    }
}
```


-------------------------------

Updated on 2022-11-15 at 04:08:15 +0000
