---
title: Engine::Audio

---

# Engine::Audio



## Classes

| Classes        | Description    |
| -------------- | -------------- |
| **[AudioBuffer](/classes/classEngine_1_1Audio_1_1AudioBuffer.md)** | _A simple audio buffer to hold PCM samples_<br> <sup><span style="color:green">(class)</span></sup> |
| **[AudioManager](/classes/classEngine_1_1Audio_1_1AudioManager.md)** | An audio manager that _accepts_ multiple **[Audio::AudioBuffer](/classes/classEngine_1_1Audio_1_1AudioBuffer.md)** instances. <br> <sup><span style="color:green">(class)</span></sup> |

## Types

| Member Types | Definition           |
| -------------- | -------------- |
| **[Callback](/namespaces/namespaceEngine_1_1Audio.md#typedef-callback)**| Some callback function pointer type definition. <br> <sup><span style="color:green">(typedef)</span></sup>|
| **[Callback2](/namespaces/namespaceEngine_1_1Audio.md#using-callback2)**| Some callback function pointer type definition. <br> <sup><span style="color:green">(using)</span></sup>|

## Functions
| Member Functions | Description |
| -------------- | -------------- |
| **[doSomething](/namespaces/namespaceEngine_1_1Audio.md#function-dosomething)** | Do something with the buffer. <br> <sup><span style="color:green">(function)</span></sup> |


## Types

### typedef Callback

<sup>Defined in header [`<src/Audio/AudioBuffer.hpp>`](/files/AudioBuffer_8hpp.md#file-audiobuffer.hpp)</sup>
```cpp
typedef int(* Engine::Audio::Callback) (AudioBuffer &buffer, size_t offset);
```

Some callback function pointer type definition. 

**Parameters**: 

  * **buffer** The buffer this callback is called from 
  * **offset** The offset of the buffer currently playing 


**Deprecated**:

Use the [Audio::Callback2](/namespaces/namespaceEngine_1_1Audio.md#using-callback2) instead 

### using Callback2

<sup>Defined in header [`<src/Audio/AudioBuffer.hpp>`](/files/AudioBuffer_8hpp.md#file-audiobuffer.hpp)</sup>
```cpp
using Callback2 = 
    int(*)(AudioBuffer &buffer, size_t offset, void *user);
```

Some callback function pointer type definition. 

**Parameters**: 

  * **buffer** The buffer this callback is called from 
  * **offset** The offset of the buffer currently playing 
  * **user** User specific data 




## Functions

### function doSomething


<sup>Defined in header [`<src/Audio/AudioBuffer.hpp>`](/files/AudioBuffer_8hpp.md#file-audiobuffer.hpp)</sup>

```cpp 
void
doSomething(AudioBuffer & buffer);
```





Do something with the buffer. 

















**Exception Safety**

Basic exception guarantee.









-------------------------------

<sub>Updated on 2023-01-02</sub>