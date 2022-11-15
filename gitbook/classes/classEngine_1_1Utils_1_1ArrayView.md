---
title: Engine::Utils::ArrayView
summary: Filesystem path utility functions. 

---

# Engine::Utils::ArrayView

**Module:** **[An example game engine](/modules/group__Engine.md)** **/** **[Some useful utilities](/modules/group__Utils.md)**



Filesystem path utility functions.  [More...](#detailed-description)


`#include <ArrayView.hpp>`

## Public Functions

|                | Name           |
| -------------- | -------------- |
| | **[ArrayView](/classes/classEngine_1_1Utils_1_1ArrayView.md#function-arrayview)**(const T * src, size_t len) |
| virtual | **[~ArrayView](/classes/classEngine_1_1Utils_1_1ArrayView.md#function-~arrayview)**() =default |
| virtual const T * | **[data](/classes/classEngine_1_1Utils_1_1ArrayView.md#function-data)**() const |
| virtual size_t | **[size](/classes/classEngine_1_1Utils_1_1ArrayView.md#function-size)**() const |

## Detailed Description

```cpp
template <typename T  =uint8_t>
class Engine::Utils::ArrayView;
```

Filesystem path utility functions. 

**Template Parameters**: 

  * **T** The type of the data, for example uint8_t 

## Public Functions Documentation

### function ArrayView

```cpp
ArrayView(
    const T * src,
    size_t len
)
```


### function ~ArrayView

```cpp
virtual ~ArrayView() =default
```


### function data

```cpp
virtual const T * data() const
```


### function size

```cpp
virtual size_t size() const
```


-------------------------------

Updated on 2022-11-15 at 02:20:56 +0000