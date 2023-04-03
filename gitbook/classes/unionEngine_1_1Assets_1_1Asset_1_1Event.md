---
title: Engine::Assets::Asset::Event

---

# Engine::Assets::Asset::Event

**[An example game engine](/libraries/group__Engine.md)** **/** **[Generic assets](/libraries/group__Assets.md)** **/** 
**[Event](/classes/unionEngine_1_1Assets_1_1Asset_1_1Event.md)**

<sup>Defined in header [`<src/Assets/Asset.hpp>`](/files/Asset_8hpp.md#file-asset.hpp)</sup>



```cpp

union Event;
```



## Public Classes

|                | Name           |
| -------------- | -------------- |
| struct | **[Loaded](/classes/structEngine_1_1Assets_1_1Asset_1_1Event_1_1Loaded.md)**  |
| struct | **[Unloaded](/classes/structEngine_1_1Assets_1_1Asset_1_1Event_1_1Unloaded.md)**  |
| struct | **[Waiting](/classes/structEngine_1_1Assets_1_1Asset_1_1Event_1_1Waiting.md)**  |

## Public Attributes

| Member Public Attributes| Description    |
| -------------- | -------------- |
| **[loaded](/classes/unionEngine_1_1Assets_1_1Asset_1_1Event.md#variable-loaded)** | struct [Engine::Assets::Asset::Event::Loaded](/classes/structEngine_1_1Assets_1_1Asset_1_1Event_1_1Loaded.md)<br> <sup><span style="color:green">(public variable)</span></sup> |
| **[unloaded](/classes/unionEngine_1_1Assets_1_1Asset_1_1Event.md#variable-unloaded)** | struct [Engine::Assets::Asset::Event::Unloaded](/classes/structEngine_1_1Assets_1_1Asset_1_1Event_1_1Unloaded.md)<br> <sup><span style="color:green">(public variable)</span></sup> |
| **[waiting](/classes/unionEngine_1_1Assets_1_1Asset_1_1Event.md#variable-waiting)** | struct [Engine::Assets::Asset::Event::Waiting](/classes/structEngine_1_1Assets_1_1Asset_1_1Event_1_1Waiting.md)<br> <sup><span style="color:green">(public variable)</span></sup> |





## Public Attributes

### variable loaded

<sup>Defined in header [`<src/Assets/Asset.hpp>`](/files/Asset_8hpp.md#file-asset.hpp)</sup>
```cpp
struct Engine::Assets::Asset::Event::Loaded loaded;
```


### variable unloaded

<sup>Defined in header [`<src/Assets/Asset.hpp>`](/files/Asset_8hpp.md#file-asset.hpp)</sup>
```cpp
struct Engine::Assets::Asset::Event::Unloaded unloaded;
```


### variable waiting

<sup>Defined in header [`<src/Assets/Asset.hpp>`](/files/Asset_8hpp.md#file-asset.hpp)</sup>
```cpp
struct Engine::Assets::Asset::Event::Waiting waiting;
```


-------------------------------

<sub>Updated on 2023-04-03</sub>