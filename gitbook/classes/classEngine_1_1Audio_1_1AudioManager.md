---
title: Engine::Audio::AudioManager
summary: An audio manager that accepts multiple Audio::AudioBuffer instances. 

---

# Engine::Audio::AudioManager

**Module:** **[An example game engine](/modules/group__Engine.md)** **/** **[Audio buffers and devices](/modules/group__Audio.md)**



An audio manager that _accepts_ multiple **[Audio::AudioBuffer](/classes/classEngine_1_1Audio_1_1AudioBuffer.md)** instances.  [More...](#detailed-description)


`#include <AudioManager.hpp>`

## Public Functions

|                | Name           |
| -------------- | -------------- |
| | **[AudioManager](/classes/classEngine_1_1Audio_1_1AudioManager.md#function-audiomanager)**(int numOfChannels =128) |
| | **[~AudioManager](/classes/classEngine_1_1Audio_1_1AudioManager.md#function-~audiomanager)**() |
| void | **[enque](/classes/classEngine_1_1Audio_1_1AudioManager.md#function-enque)**(const [AudioBuffer](/classes/classEngine_1_1Audio_1_1AudioBuffer.md) & buffer) |

## Detailed Description

```cpp
class Engine::Audio::AudioManager;
```

An audio manager that _accepts_ multiple **[Audio::AudioBuffer](/classes/classEngine_1_1Audio_1_1AudioBuffer.md)** instances. 

**See**: [Audio::AudioBuffer](/classes/classEngine_1_1Audio_1_1AudioBuffer.md)

Lorem Ipsum Donor. Some [Random link with **bold** and _italics_](http://github.com) And the following is a `typewritter` font. And here is some list items:

* First item
* Second item
* Third item **with bold text**

Followed by some more text and another list:

* First item
* Second item

## Public Functions Documentation

### function AudioManager

```cpp
AudioManager(
    int numOfChannels =128
)
```


### function ~AudioManager

```cpp
~AudioManager()
```


### function enque

```cpp
void enque(
    const AudioBuffer & buffer
)
```


-------------------------------

Updated on 2022-11-15 at 02:37:49 +0000