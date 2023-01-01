---
title: Engine::Graphics::Texture2D

---

# Engine::Graphics::Texture2D

**[An example game engine](/libraries/group__Engine.md)** **/** **[Graphical related classes](/libraries/group__Graphics.md)** **/** 
**[Texture2D](/classes/classEngine_1_1Graphics_1_1Texture2D.md)**

<sup>Defined in header [`<src/Graphics/Texture2D.hpp>`](/files/Texture2D_8hpp.md#file-texture2d.hpp)</sup>



```cpp

class Texture2D;
```



**Inherits from** [Texture](/classes/classEngine_1_1Graphics_1_1Texture.md), [Handle](/classes/classEngine_1_1Graphics_1_1Handle.md)

## Public Functions
| Member Functions | Description |
| -------------- | -------------- |
| **[(constructor)](/classes/classEngine_1_1Graphics_1_1Texture2D.md#function-texture2d)** |  <sup><span style="color:green">(function)</span></sup> |
| **[(destructor)](/classes/classEngine_1_1Graphics_1_1Texture2D.md#function-~texture2d)** |  <sup><span style="color:green">(virtual function)</span></sup> |
| **[getWidth](/classes/classEngine_1_1Graphics_1_1Texture2D.md#function-getwidth)** <span style="color:green">const</span> <span style="color:green">override</span>| Returns the width of the texture in pixels. <br> <sup><span style="color:green">(virtual function)</span></sup> |
| **[getHeight](/classes/classEngine_1_1Graphics_1_1Texture2D.md#function-getheight)** <span style="color:green">const</span> <span style="color:green">override</span>| Returns the height of the texture in pixels. <br> <sup><span style="color:green">(virtual function)</span></sup> |
| **[getDepth](/classes/classEngine_1_1Graphics_1_1Texture2D.md#function-getdepth)** <span style="color:green">const</span> <span style="color:green">override</span>| Returns the depth of the texture in pixels. <br> <sup><span style="color:green">(virtual function)</span></sup> |


## Additional inherited members

**Public Types**<sup><span style="color:green">(inherited from [Engine::Graphics::Texture](/classes/classEngine_1_1Graphics_1_1Texture.md))</span></sup>


| Member Types | Definition           |
| -------------- | -------------- |
| **[Type](/classes/classEngine_1_1Graphics_1_1Texture.md#enum-type)**| `Type`<br> <sup><span style="color:green">(enum)</span></sup>|

**Public Functions**<sup><span style="color:green">(inherited from [Engine::Graphics::Texture](/classes/classEngine_1_1Graphics_1_1Texture.md))</span></sup>

| Member Functions | Description |
| -------------- | -------------- |
| **[Texture](/classes/classEngine_1_1Graphics_1_1Texture.md#function-texture)** |  <sup><span style="color:green">(function)</span></sup> |
| **[~Texture](/classes/classEngine_1_1Graphics_1_1Texture.md#function-~texture)**  <span style="color:green">= default</span>|  <sup><span style="color:green">(virtual function)</span></sup> |
| **[isLoaded](/classes/classEngine_1_1Graphics_1_1Texture.md#function-isloaded)** <span style="color:green">const</span>|  <sup><span style="color:green">(function)</span></sup> |


**Protected Attributes**<sup><span style="color:green">(inherited from [Engine::Graphics::Texture](/classes/classEngine_1_1Graphics_1_1Texture.md))</span></sup>


| Member Protected Attributes| Description    |
| -------------- | -------------- |
| **[loaded](/classes/classEngine_1_1Graphics_1_1Texture.md#variable-loaded)** | `bool`<br> <sup><span style="color:green">(protected variable)</span></sup> |
| **[type](/classes/classEngine_1_1Graphics_1_1Texture.md#variable-type)** | [Type](/classes/classEngine_1_1Graphics_1_1Texture.md#enum-type)<br> <sup><span style="color:green">(protected variable)</span></sup> |

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


## Public Functions

### function Texture2D


<sup>Defined in header [`<src/Graphics/Texture2D.hpp>`](/files/Texture2D_8hpp.md#file-texture2d.hpp)</sup>

```cpp 
Texture2D(
    int width, 
    int height, 
    uint8_t * data, 
    Texture::Type type =Texture::Type::RGBA8);
```







**Parameters**

- **data** - The pointer to the raw pixels data 
- **height** - The height of the image held by the data pointer 
- **type** - What is the type of this pixels array? 
- **width** - The width of the image held by the data pointer 













**Exception Safety**

Basic exception guarantee.




### function ~Texture2D


<sup>Defined in header [`<src/Graphics/Texture2D.hpp>`](/files/Texture2D_8hpp.md#file-texture2d.hpp)</sup>

```cpp 
virtual ~Texture2D();
```



















**Exception Safety**

Basic exception guarantee.




### function getWidth


<sup>Defined in header [`<src/Graphics/Texture2D.hpp>`](/files/Texture2D_8hpp.md#file-texture2d.hpp)</sup>

```cpp 
virtual int
getWidth() const override;
```





Returns the width of the texture in pixels. 






**Return value**

Width in pixels 











**Exception Safety**

Basic exception guarantee.




### function getHeight


<sup>Defined in header [`<src/Graphics/Texture2D.hpp>`](/files/Texture2D_8hpp.md#file-texture2d.hpp)</sup>

```cpp 
virtual int
getHeight() const override;
```





Returns the height of the texture in pixels. 






**Return value**

Height in pixels 











**Exception Safety**

Basic exception guarantee.




### function getDepth


<sup>Defined in header [`<src/Graphics/Texture2D.hpp>`](/files/Texture2D_8hpp.md#file-texture2d.hpp)</sup>

```cpp 
virtual int
getDepth() const override;
```





Returns the depth of the texture in pixels. 






**Return value**

Depth in pixels 


**Notes**

If this texture is 2D the depth is always 1 pixels 









**Exception Safety**

Basic exception guarantee.








-------------------------------

<sub>Updated on 2023-01-01</sub>