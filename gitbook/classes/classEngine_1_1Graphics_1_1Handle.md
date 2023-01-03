---
title: Engine::Graphics::Handle

---

# Engine::Graphics::Handle

**[An example game engine](/libraries/group__Engine.md)** **/** **[Graphical related classes](/libraries/group__Graphics.md)** **/** 
**[Handle](/classes/classEngine_1_1Graphics_1_1Handle.md)**

<sup>Defined in header [`<src/Graphics/Handle.hpp>`](/files/Handle_8hpp.md#file-handle.hpp)</sup>



```cpp

class Handle;
```



**Inherited by**: `Handle` is a base class for
[Texture](/classes/classEngine_1_1Graphics_1_1Texture.md)

## Public Functions
| Member Functions | Description |
| -------------- | -------------- |
| **[(constructor)](/classes/classEngine_1_1Graphics_1_1Handle.md#function-handle)**  <span style="color:green">= default</span>|  <sup><span style="color:green">(function)</span></sup> |
| **[(destructor)](/classes/classEngine_1_1Graphics_1_1Handle.md#function-~handle)**  <span style="color:green">= default</span>|  <sup><span style="color:green">(virtual function)</span></sup> |
| **[getHandle](/classes/classEngine_1_1Graphics_1_1Handle.md#function-gethandle)** <span style="color:green">const</span>|  <sup><span style="color:green">(function)</span></sup> |


## Protected Attributes

| Member Protected Attributes| Description    |
| -------------- | -------------- |
| **[handle](/classes/classEngine_1_1Graphics_1_1Handle.md#variable-handle)** | `int`<br> <sup><span style="color:green">(protected variable)</span></sup> |

## Public Functions

### function Handle


<sup>Defined in header [`<src/Graphics/Handle.hpp>`](/files/Handle_8hpp.md#file-handle.hpp)</sup>

```cpp 
Handle() = default;
```



















**Exception Safety**

Basic exception guarantee.




### function ~Handle


<sup>Defined in header [`<src/Graphics/Handle.hpp>`](/files/Handle_8hpp.md#file-handle.hpp)</sup>

```cpp 
virtual ~Handle() = default;
```



















**Exception Safety**

Basic exception guarantee.




### function getHandle


<sup>Defined in header [`<src/Graphics/Handle.hpp>`](/files/Handle_8hpp.md#file-handle.hpp)</sup>

```cpp 
int
getHandle() const;
```



















**Exception Safety**

Basic exception guarantee.








## Protected Attributes

### variable handle

<sup>Defined in header [`<src/Graphics/Handle.hpp>`](/files/Handle_8hpp.md#file-handle.hpp)</sup>
```cpp
int handle;
```


-------------------------------

<sub>Updated on 2023-01-03</sub>