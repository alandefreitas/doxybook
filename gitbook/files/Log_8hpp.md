---
title: src/Utils/Log.hpp

---

# src/Utils/Log.hpp



## Defines

|                | Name           |
| -------------- | -------------- |
|  | **[LOG_DEBUG](/modules/group__Utils.md#define-log-debug)**(MSG, ...)  |




## Macros Documentation

### define LOG_DEBUG

```cpp
#define LOG_DEBUG(
    MSG,
    ...
)
printf(MSG, ##__VA_ARGS__)
```


## Source code

```cpp
#pragma once
#include <stdio.h>

#define LOG_DEBUG(MSG, ...) printf(MSG, ##__VA_ARGS__)
```


-------------------------------

Updated on 2022-11-15 at 03:20:41 +0000
