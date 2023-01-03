---
title: Engine::Assets::Asset

---

# Engine::Assets::Asset

**[An example game engine](/libraries/group__Engine.md)** **/** **[Generic assets](/libraries/group__Assets.md)** **/** 
**[Asset](/classes/classEngine_1_1Assets_1_1Asset.md)**

<sup>Defined in header [`<src/Assets/Asset.hpp>`](/files/Asset_8hpp.md#file-asset.hpp)</sup>



```cpp

class Asset;
```



## Public Classes

|                | Name           |
| -------------- | -------------- |
| union | **[Event](/classes/unionEngine_1_1Assets_1_1Asset_1_1Event.md)**  |

## Public Functions
| Member Functions | Description |
| -------------- | -------------- |
| **[(constructor)](/classes/classEngine_1_1Assets_1_1Asset.md#function-asset)** |  <sup><span style="color:green">(function)</span></sup> |
| **[(destructor)](/classes/classEngine_1_1Assets_1_1Asset.md#function-~asset)**  = 0|  <sup><span style="color:green">(virtual function)</span></sup> |
| **[load](/classes/classEngine_1_1Assets_1_1Asset.md#function-load)** | Call this method to load the asset. <br> <sup><span style="color:green">(virtual function)</span></sup> |
| **[unload](/classes/classEngine_1_1Assets_1_1Asset.md#function-unload)** | Call this method to unload the asset. <br> <sup><span style="color:green">(virtual function)</span></sup> |
| **[getEvent](/classes/classEngine_1_1Assets_1_1Asset.md#function-getevent)** <span style="color:green">const</span>| Returns the current status of the asset. <br> <sup><span style="color:green">(function)</span></sup> |


## Public Functions

### function Asset


<sup>Defined in header [`<src/Assets/Asset.hpp>`](/files/Asset_8hpp.md#file-asset.hpp)</sup>

```cpp 
explicit Asset(const std::string & name);
```



















**Exception Safety**

Basic exception guarantee.




### function ~Asset


<sup>Defined in header [`<src/Assets/Asset.hpp>`](/files/Asset_8hpp.md#file-asset.hpp)</sup>

```cpp 
virtual ~Asset() = 0;
```



















**Exception Safety**

Basic exception guarantee.




### function load


<sup>Defined in header [`<src/Assets/Asset.hpp>`](/files/Asset_8hpp.md#file-asset.hpp)</sup>

```cpp 
virtual void
load();
```





Call this method to load the asset. 

















**Exception Safety**

Basic exception guarantee.




### function unload


<sup>Defined in header [`<src/Assets/Asset.hpp>`](/files/Asset_8hpp.md#file-asset.hpp)</sup>

```cpp 
virtual void
unload();
```





Call this method to unload the asset. 

















**Exception Safety**

Basic exception guarantee.




### function getEvent


<sup>Defined in header [`<src/Assets/Asset.hpp>`](/files/Asset_8hpp.md#file-asset.hpp)</sup>

```cpp 
const Event &
getEvent() const;
```





Returns the current status of the asset. 







**Description**

Use this to determine the state, for example if the assets is being loaded or unloaded. 










**Exception Safety**

Basic exception guarantee.








-------------------------------

<sub>Updated on 2023-01-03</sub>