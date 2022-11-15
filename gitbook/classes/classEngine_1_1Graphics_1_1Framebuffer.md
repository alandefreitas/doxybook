---
title: Engine::Graphics::Framebuffer

---

# Engine::Graphics::Framebuffer

**Module:** **[An example game engine](/modules/group__Engine.md)** **/** **[Graphical related classes](/modules/group__Graphics.md)**






`#include <Framebuffer.hpp>`

Inherits from [Engine::Graphics::Texture](/classes/classEngine_1_1Graphics_1_1Texture.md), [Engine::Graphics::Handle](/classes/classEngine_1_1Graphics_1_1Handle.md)

## Public Functions

|                | Name           |
| -------------- | -------------- |
| | **[Framebuffer](/classes/classEngine_1_1Graphics_1_1Framebuffer.md#function-framebuffer)**(int width, int height) |
| virtual | **[~Framebuffer](/classes/classEngine_1_1Graphics_1_1Framebuffer.md#function-~framebuffer)**() |
| virtual int | **[getWidth](/classes/classEngine_1_1Graphics_1_1Framebuffer.md#function-getwidth)**() const override<br>Returns the width of the texture in pixels.  |
| virtual int | **[getHeight](/classes/classEngine_1_1Graphics_1_1Framebuffer.md#function-getheight)**() const override<br>Returns the height of the texture in pixels.  |
| virtual int | **[getDepth](/classes/classEngine_1_1Graphics_1_1Framebuffer.md#function-getdepth)**() const override<br>Returns the depth of the texture in pixels.  |

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


## Public Functions Documentation

### function Framebuffer

```cpp
Framebuffer(
    int width,
    int height
)
```


### function ~Framebuffer

```cpp
virtual ~Framebuffer()
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

Updated on 2022-11-15 at 04:12:34 +0000