---
title: Engine::Audio::AudioManager
summary: An audio manager that accepts multiple Audio::AudioBuffer instances. 

---

# Engine::Audio::AudioManager

**[An example game engine](/libraries/group__Engine.md)** **/** **[Audio buffers and devices](/libraries/group__Audio.md)** **/** 
**[AudioManager](/classes/classEngine_1_1Audio_1_1AudioManager.md)**

<sup>Defined in header [`<src/Audio/AudioManager.hpp>`](/files/AudioManager_8hpp.md#file-audiomanager.hpp)</sup>



```cpp

class AudioManager;
```

An audio manager that _accepts_ multiple **[Audio::AudioBuffer](/classes/classEngine_1_1Audio_1_1AudioBuffer.md)** instances. 


**Description**


Lorem Ipsum Donor. Some [Random link with **bold** and _italics_](http://github.com) And the following is a `typewritter` font. And here is some list items:

* First item
* Second item
* Third item **with bold text**

Followed by some more text and another list:

* First item
* Second item


**See Also**: [Audio::AudioBuffer](/classes/classEngine_1_1Audio_1_1AudioBuffer.md)


## Public Functions
| Member Functions | Description |
| -------------- | -------------- |
| **[(constructor)](/classes/classEngine_1_1Audio_1_1AudioManager.md#function-audiomanager)** |  <sup><span style="color:green">(function)</span></sup> |
| **[(destructor)](/classes/classEngine_1_1Audio_1_1AudioManager.md#function-~audiomanager)** |  <sup><span style="color:green">(function)</span></sup> |
| **[enque](/classes/classEngine_1_1Audio_1_1AudioManager.md#function-enque)** |  <sup><span style="color:green">(function)</span></sup> |


## Public Functions

### function AudioManager


<sup>Defined in header [`<src/Audio/AudioManager.hpp>`](/files/AudioManager_8hpp.md#file-audiomanager.hpp)</sup>

```cpp 
AudioManager(int numOfChannels =128);
```



















**Exception Safety**

Basic exception guarantee.




### function ~AudioManager


<sup>Defined in header [`<src/Audio/AudioManager.hpp>`](/files/AudioManager_8hpp.md#file-audiomanager.hpp)</sup>

```cpp 
~AudioManager();
```



















**Exception Safety**

Basic exception guarantee.




### function enque


<sup>Defined in header [`<src/Audio/AudioManager.hpp>`](/files/AudioManager_8hpp.md#file-audiomanager.hpp)</sup>

```cpp 
void
enque(const AudioBuffer & buffer);
```



















**Exception Safety**

Basic exception guarantee.








-------------------------------

<sub>Updated on 2023-01-04</sub>