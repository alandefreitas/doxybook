---
title: src/Exception.hpp

---

# src/Exception.hpp



## Namespaces

| Name           |
| -------------- |
| **[Engine](/namespaces/namespaceEngine.md)** <br>This namespace contains all of the necessary engine components.  |

## Classes

|                | Name           |
| -------------- | -------------- |
| class | **[Engine::Exception](/classes/classEngine_1_1Exception.md)**  |




## Source code

```cpp
#pragma once
#include <exception>
#include <string>

namespace Engine {
    class Exception: public std::exception {
    public:
        Exception() = default;

        explicit Exception(std::string msg)
            : msg(std::move(msg)) {

        }

        const char* what() const throw() override {
            return msg.c_str();
        }

    private:
        std::string msg;
    };
}
```


-------------------------------

Updated on 2022-11-15 at 01:04:15 +0000
