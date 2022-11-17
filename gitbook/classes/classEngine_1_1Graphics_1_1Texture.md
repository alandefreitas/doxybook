---
title: Engine::Graphics::Texture
summary: This is a base texture class that serves as a base class for other texture types. 

---

# Engine::Graphics::Texture

**[An example game engine](/libraries/group__Engine.md)** **/** **[Graphical related classes](/libraries/group__Graphics.md)** **/** 
**[Texture](/classes/classEngine_1_1Graphics_1_1Texture.md)**

<sup>Defined in header [`<src/Graphics/Texture.hpp>`](/files/Texture_8hpp.md#file-texture.hpp)</sup>



```cpp

class Texture;
```

This is a base texture class that serves as a base class for other texture types. 


**Description**


```cpp

#include <iostream>
#include <memory>
#include "Engine.hpp"

// A dummy example 
int main() {
    // Create pixels buffer
    const auto pixels = std::make_unique<uint8_t[]>(new uint8_t[1024*1024*3]);
    fillData(*pixels, "path/to/texture.png");

    // Create a texture out of the pixels
    Engine::Graphics::Texture2D texture(1024, 1024, *data);

    // Done
    return 0;
}
```

_Filename: example-1.cpp_


**Bug**: This has some **weird** bug too! 


**Inherits from** [Handle](/classes/classEngine_1_1Graphics_1_1Handle.md)

**Inherited by** [Framebuffer](/classes/classEngine_1_1Graphics_1_1Framebuffer.md), [Texture2D](/classes/classEngine_1_1Graphics_1_1Texture2D.md), [Texture3D](/classes/classEngine_1_1Graphics_1_1Texture3D.md)

## Public Types

| Member Types | Definition           |
| -------------- | -------------- |
| **[Type](/classes/classEngine_1_1Graphics_1_1Texture.md#enum-type)**| `Type`<br> <sup><span style="color:green">(enum)</span></sup>|

## Public Functions
| Member Functions | Description |
| -------------- | -------------- |
| **[(constructor)](/classes/classEngine_1_1Graphics_1_1Texture.md#function-texture)** |  <sup><span style="color:green">(function)</span></sup> |
| **[(destructor)](/classes/classEngine_1_1Graphics_1_1Texture.md#function-~texture)**  <span style="color:green">= default</span>|  <sup><span style="color:green">(virtual function)</span></sup> |
| **[getWidth](/classes/classEngine_1_1Graphics_1_1Texture.md#function-getwidth)** <span style="color:green">const</span> = 0| Returns the width of the texture in pixels. <br> <sup><span style="color:green">(virtual function)</span></sup> |
| **[getHeight](/classes/classEngine_1_1Graphics_1_1Texture.md#function-getheight)** <span style="color:green">const</span> = 0| Returns the height of the texture in pixels. <br> <sup><span style="color:green">(virtual function)</span></sup> |
| **[getDepth](/classes/classEngine_1_1Graphics_1_1Texture.md#function-getdepth)** <span style="color:green">const</span> = 0| Returns the depth of the texture in pixels. <br> <sup><span style="color:green">(virtual function)</span></sup> |
| **[isLoaded](/classes/classEngine_1_1Graphics_1_1Texture.md#function-isloaded)** <span style="color:green">const</span>|  <sup><span style="color:green">(function)</span></sup> |


## Protected Attributes

| Member Protected Attributes| Description    |
| -------------- | -------------- |
| **[loaded](/classes/classEngine_1_1Graphics_1_1Texture.md#variable-loaded)** | `bool`<br> <sup><span style="color:green">(protected variable)</span></sup> |
| **[type](/classes/classEngine_1_1Graphics_1_1Texture.md#variable-type)** | [Type](/classes/classEngine_1_1Graphics_1_1Texture.md#enum-type)<br> <sup><span style="color:green">(protected variable)</span></sup> |

## Additional inherited members

**Public Functions**<sup><span style="color:green">(inherited from [Engine::Graphics::Handle](/classes/classEngine_1_1Graphics_1_1Handle.md))</span></sup>

| Member Functions | Description |
| -------------- | -------------- |
| **[Handle](/classes/classEngine_1_1Graphics_1_1Handle.md#function-handle)**  <span style="color:green">= default</span>|  <sup><span style="color:green">(function)</span></sup> |
| **[~Handle](/classes/classEngine_1_1Graphics_1_1Handle.md#function-~handle)**  <span style="color:green">= default</span>|  <sup><span style="color:green">(virtual function)</span></sup> |
| **[getHandle](/classes/classEngine_1_1Graphics_1_1Handle.md#function-gethandle)** <span style="color:green">const</span>|  <sup><span style="color:green">(function)</span></sup> |


**Protected Attributes**<sup><span style="color:green">(inherited from [Engine::Graphics::Handle](/classes/classEngine_1_1Graphics_1_1Handle.md))</span></sup>


| Member Protected Attributes| Description    |
| -------------- | -------------- |
| **[handle](/classes/classEngine_1_1Graphics_1_1Handle.md#variable-handle)** | `int`<br> <sup><span style="color:green">(protected variable)</span></sup> |


## Public Types

### enum Type

<sup>Defined in header [`<src/Graphics/Texture.hpp>`](/files/Texture_8hpp.md#file-texture.hpp)</sup>
```cpp
enum class Type;
```

| Enumerator | Value | Description |
| ---------- | ----- | ----------- |
| UNKNOWN | 0|   |
| RGBA_8 | |   |
| RGB_8 | |   |
| RGBA_16 | |   |
| RGB_16 | |   |
| RGBA_32 | |   |
| RGB_32 | |   |




## Public Functions

### function Texture


<sup>Defined in header [`<src/Graphics/Texture.hpp>`](/files/Texture_8hpp.md#file-texture.hpp)</sup>

```cpp 
explicit Texture(Type type);
```



















**Exception Safety**

Basic exception guarantee.




### function ~Texture


<sup>Defined in header [`<src/Graphics/Texture.hpp>`](/files/Texture_8hpp.md#file-texture.hpp)</sup>

```cpp 
virtual ~Texture() = default;
```



















**Exception Safety**

Basic exception guarantee.




### function getWidth


<sup>Defined in header [`<src/Graphics/Texture.hpp>`](/files/Texture_8hpp.md#file-texture.hpp)</sup>

```cpp 
virtual int
getWidth() const = 0;
```





Returns the width of the texture in pixels. 






**Return value**

Width in pixels 











**Exception Safety**

Basic exception guarantee.




### function getHeight


<sup>Defined in header [`<src/Graphics/Texture.hpp>`](/files/Texture_8hpp.md#file-texture.hpp)</sup>

```cpp 
virtual int
getHeight() const = 0;
```





Returns the height of the texture in pixels. 






**Return value**

Height in pixels 











**Exception Safety**

Basic exception guarantee.




### function getDepth


<sup>Defined in header [`<src/Graphics/Texture.hpp>`](/files/Texture_8hpp.md#file-texture.hpp)</sup>

```cpp 
virtual int
getDepth() const = 0;
```





Returns the depth of the texture in pixels. 






**Return value**

Depth in pixels 


**Notes**

If this texture is 2D the depth is always 1 pixels 









**Exception Safety**

Basic exception guarantee.




### function isLoaded


<sup>Defined in header [`<src/Graphics/Texture.hpp>`](/files/Texture_8hpp.md#file-texture.hpp)</sup>

```cpp 
bool
isLoaded() const;
```



















**Exception Safety**

Basic exception guarantee.








## Protected Attributes

### variable loaded

<sup>Defined in header [`<src/Graphics/Texture.hpp>`](/files/Texture_8hpp.md#file-texture.hpp)</sup>
```cpp
bool loaded {false};
```


### variable type

<sup>Defined in header [`<src/Graphics/Texture.hpp>`](/files/Texture_8hpp.md#file-texture.hpp)</sup>
```cpp
Type type;
```


-------------------------------

<sub>Updated on 2022-11-17</sub>