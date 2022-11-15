---
title: Engine::Audio

---

# Engine::Audio



## Classes

|                | Name           |
| -------------- | -------------- |
| class | **[Engine::Audio::AudioBuffer](/classes/classEngine_1_1Audio_1_1AudioBuffer.md)** <br>_A simple audio buffer to hold PCM samples_ |
| class | **[Engine::Audio::AudioManager](/classes/classEngine_1_1Audio_1_1AudioManager.md)** <br>An audio manager that _accepts_ multiple **[Audio::AudioBuffer](/classes/classEngine_1_1Audio_1_1AudioBuffer.md)** instances.  |

## Types

|                | Name           |
| -------------- | -------------- |
| typedef int(*)(AudioBuffer &buffer, size_t offset) | **[Callback](/namespaces/namespaceEngine_1_1Audio.md#typedef-callback)** <br>Some callback function pointer type definition.  |
| using int(*)([AudioBuffer](/classes/classEngine_1_1Audio_1_1AudioBuffer.md) &buffer, size_t offset, void *user) | **[Callback2](/namespaces/namespaceEngine_1_1Audio.md#using-callback2)** <br>Some callback function pointer type definition.  |

## Functions

|                | Name           |
| -------------- | -------------- |
| void | **[doSomething](/namespaces/namespaceEngine_1_1Audio.md#function-dosomething)**([AudioBuffer](/classes/classEngine_1_1Audio_1_1AudioBuffer.md) & buffer)<br>Do something with the buffer.  |

## Types Documentation

### typedef Callback

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

```cpp
using Engine::Audio::Callback2 = typedef int (*)(AudioBuffer& buffer, size_t offset, void* user);
```

Some callback function pointer type definition. 

**Parameters**: 

  * **buffer** The buffer this callback is called from 
  * **offset** The offset of the buffer currently playing 
  * **user** User specific data 



## Functions Documentation

### function doSomething

```cpp
void doSomething(
    AudioBuffer & buffer
)
```

Do something with the buffer. 





-------------------------------

Updated on 2022-11-15 at 01:22:50 +0000