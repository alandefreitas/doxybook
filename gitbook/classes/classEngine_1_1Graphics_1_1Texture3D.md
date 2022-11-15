---
title: Engine::Graphics::Texture3D
summary: Some deprecated class. 

---

# Engine::Graphics::Texture3D

**Module:** **[An example game engine](/modules/group__Engine.md)** **/** **[Graphical related classes](/modules/group__Graphics.md)**



Some deprecated class.  [More...](#detailed-description)


`#include <Texture3D.hpp>`

Inherits from [Engine::Graphics::Texture](/classes/classEngine_1_1Graphics_1_1Texture.md), [Engine::Graphics::Handle](/classes/classEngine_1_1Graphics_1_1Handle.md)

## Public Functions

|                | Name           |
| -------------- | -------------- |
| | **[Texture3D](/classes/classEngine_1_1Graphics_1_1Texture3D.md#function-texture3d)**(int width, int height, int depth, uint8_t * data, [Texture::Type](/classes/classEngine_1_1Graphics_1_1Texture.md#enum-type) type =Texture::Type::RGBA8) |
| virtual | **[~Texture3D](/classes/classEngine_1_1Graphics_1_1Texture3D.md#function-~texture3d)**() |
| virtual int | **[getWidth](/classes/classEngine_1_1Graphics_1_1Texture3D.md#function-getwidth)**() const override<br>Returns the width of the texture in pixels.  |
| virtual int | **[getHeight](/classes/classEngine_1_1Graphics_1_1Texture3D.md#function-getheight)**() const override<br>Returns the height of the texture in pixels.  |
| virtual int | **[getDepth](/classes/classEngine_1_1Graphics_1_1Texture3D.md#function-getdepth)**() const override<br>Returns the depth of the texture in pixels.  |

## Additional inherited members

**Public Types inherited from [Engine::Graphics::Texture](/classes/classEngine_1_1Graphics_1_1Texture.md)**

|                | Name           |
| -------------- | -------------- |
| enum class| **[Type](/classes/classEngine_1_1Graphics_1_1Texture.md#enum-type)** { UNKNOWN, RGBA_8, RGB_8, RGBA_16, RGB_16, RGBA_32, RGB_32} |

**Public Functions inherited from [Engine::Graphics::Texture](/classes/classEngine_1_1Graphics_1_1Texture.md)**

|                | Name           |
| -------------- | -------------- |
| | **[Texture](/classes/classEngine_1_1Graphics_1_1Texture.md#function-texture)**([Type](/classes/classEngine_1_1Graphics_1_1Texture.md#enum-type) type) |
| virtual | **[~Texture](/classes/classEngine_1_1Graphics_1_1Texture.md#function-~texture)**() =default |
| bool | **[isLoaded](/classes/classEngine_1_1Graphics_1_1Texture.md#function-isloaded)**() const |

**Protected Attributes inherited from [Engine::Graphics::Texture](/classes/classEngine_1_1Graphics_1_1Texture.md)**

|                | Name           |
| -------------- | -------------- |
| bool | **[loaded](/classes/classEngine_1_1Graphics_1_1Texture.md#variable-loaded)**  |
| [Type](/classes/classEngine_1_1Graphics_1_1Texture.md#enum-type) | **[type](/classes/classEngine_1_1Graphics_1_1Texture.md#variable-type)**  |

**Public Functions inherited from [Engine::Graphics::Handle](/classes/classEngine_1_1Graphics_1_1Handle.md)**

|                | Name           |
| -------------- | -------------- |
| | **[Handle](/classes/classEngine_1_1Graphics_1_1Handle.md#function-handle)**() =default |
| virtual | **[~Handle](/classes/classEngine_1_1Graphics_1_1Handle.md#function-~handle)**() =default |
| int | **[getHandle](/classes/classEngine_1_1Graphics_1_1Handle.md#function-gethandle)**() const |

**Protected Attributes inherited from [Engine::Graphics::Handle](/classes/classEngine_1_1Graphics_1_1Handle.md)**

|                | Name           |
| -------------- | -------------- |
| int | **[handle](/classes/classEngine_1_1Graphics_1_1Handle.md#variable-handle)**  |


## Detailed Description

```cpp
class Engine::Graphics::Texture3D;
```

Some deprecated class. 

**Deprecated**: 

Don't use this texture type 
## Public Functions Documentation

### function Texture3D

```cpp
Texture3D(
    int width,
    int height,
    int depth,
    uint8_t * data,
    Texture::Type type =Texture::Type::RGBA8
)
```


### function ~Texture3D

```cpp
virtual ~Texture3D()
```


### function getWidth

```cpp
virtual int getWidth() const override
```

Returns the width of the texture in pixels. 

**Return**: Width in pixels 

**Reimplements**: [Engine::Graphics::Texture::getWidth](/classes/classEngine_1_1Graphics_1_1Texture.md#function-getwidth)


### function getHeight

```cpp
virtual int getHeight() const override
```

Returns the height of the texture in pixels. 

**Return**: Height in pixels 

**Reimplements**: [Engine::Graphics::Texture::getHeight](/classes/classEngine_1_1Graphics_1_1Texture.md#function-getheight)


### function getDepth

```cpp
virtual int getDepth() const override
```

Returns the depth of the texture in pixels. 

**Return**: Depth in pixels 

**Note**: If this texture is 2D the depth is always 1 pixels 

**Reimplements**: [Engine::Graphics::Texture::getDepth](/classes/classEngine_1_1Graphics_1_1Texture.md#function-getdepth)


-------------------------------

Updated on 2022-11-15 at 02:37:49 +0000