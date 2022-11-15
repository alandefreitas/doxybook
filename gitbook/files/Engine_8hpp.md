---
title: src/Engine.hpp

---

# src/Engine.hpp



## Namespaces

| Name           |
| -------------- |
| **[Engine](/namespaces/namespaceEngine.md)** <br>This namespace contains all of the necessary engine components.  |

## Functions

|                | Name           |
| -------------- | -------------- |
| std::string | **[someGlobalFunc](/files/Engine_8hpp.md#function-someglobalfunc)**()<br>Some global extern function.  |


## Functions Documentation

### function someGlobalFunc

```cpp
std::string someGlobalFunc()
```

Some global extern function. 



## Source code

```cpp

#include "Assets/Assets.hpp"
#include "Audio/Audio.hpp"
#include "Exception.hpp"
#include "Graphics/Graphics.hpp"
#include "Gui/Gui.hpp"
#include "Utils/Utils.hpp"

extern std::string someGlobalFunc();

namespace Engine {
    extern std::string getVersion();
} // namespace Engine

//-----------------------------------------------------------

//-----------------------------------------------------------
```


-------------------------------

Updated on 2022-11-15 at 01:04:15 +0000
