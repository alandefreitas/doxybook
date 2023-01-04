---
title: Engine::Audio::AudioBuffer
summary: A simple audio buffer to hold PCM samples

---

# Engine::Audio::AudioBuffer

**[An example game engine](/libraries/group__Engine.md)** **/** **[Audio buffers and devices](/libraries/group__Audio.md)** **/** 
**[AudioBuffer](/classes/classEngine_1_1Audio_1_1AudioBuffer.md)**

<sup>Defined in header [`<src/Audio/AudioBuffer.hpp>`](/files/AudioBuffer_8hpp.md#file-audiobuffer.hpp)</sup>



```cpp

class AudioBuffer;
```

_A simple audio buffer to hold PCM samples_


**Description**




Lorem ipsum donor 

```cpp
// Some random code
using namespace Engine;

Audio::AudioBuffer buffer("path/to/file.wav");
buffer.play(audioManager);
```

 More detailed description! 

```cpp
// Another code sample
#include <iostream>
using namespace Engine;
Audio::AudioBuffer buffer("path/to/file.wav");
std::cout << buffer.play(...) << std::endl;
```


**Author**: Matus Novak 

**Date**: 2017-2019 

**Note**: 

  * Some random note 
  * Some second random note 


**Bug**: Some random bug 

Some other random bug 

**Test**: Some random test description 

**Todo**: Some random todo 

**Warning**: Some random warning 

**Precondition**: First initialize the system. 


## Public Classes

|                | Name           |
| -------------- | -------------- |
| struct | **[TypedAudioData](/classes/structEngine_1_1Audio_1_1AudioBuffer_1_1TypedAudioData.md)** <br>Use this to populate the buffer.  |

## Public Types

| Member Types | Definition           |
| -------------- | -------------- |
| **[Type](/classes/classEngine_1_1Audio_1_1AudioBuffer.md#enum-type)**| Different type of audio formats. <br> <sup><span style="color:green">(enum)</span></sup>|
| **[AudioData](/classes/classEngine_1_1Audio_1_1AudioBuffer.md#using-audiodata)**| `[Utils::ArrayView](/classes/classEngine_1_1Utils_1_1ArrayView.md)< T >`<br> <sup><span style="color:green">(using)</span></sup>|
| **[AudioData8U](/classes/classEngine_1_1Audio_1_1AudioBuffer.md#typedef-audiodata8u)**| `[AudioData](/classes/classEngine_1_1Audio_1_1AudioBuffer.md#using-audiodata)< uint8_t >`<br> <sup><span style="color:green">(typedef)</span></sup>|

## Public Functions
| Member Functions | Description |
| -------------- | -------------- |
| **[(constructor)](/classes/classEngine_1_1Audio_1_1AudioBuffer.md#function-audiobuffer)** | Constructor for [Audio::AudioBuffer](/classes/classEngine_1_1Audio_1_1AudioBuffer.md). <br> <sup><span style="color:green">(function)</span></sup> |
| **[(destructor)](/classes/classEngine_1_1Audio_1_1AudioBuffer.md#function-~audiobuffer)**  <span style="color:green">= default</span>| [Audio::AudioBuffer](/classes/classEngine_1_1Audio_1_1AudioBuffer.md) destructor. <br> <sup><span style="color:green">(virtual function)</span></sup> |
| **[play](/classes/classEngine_1_1Audio_1_1AudioBuffer.md#function-play)** <span style="color:green">const</span>| Play this buffer. <br> <sup><span style="color:green">(function)</span></sup> |
| **[stop](/classes/classEngine_1_1Audio_1_1AudioBuffer.md#function-stop)** <span style="color:green">const</span>| Stop this buffer playing. <br> <sup><span style="color:green">(function)</span></sup> |
| **[loop](/classes/classEngine_1_1Audio_1_1AudioBuffer.md#function-loop)** <span style="color:green">const</span>| Loop this buffer forever. <br> <sup><span style="color:green">(function)</span></sup> |
| **[setData](/classes/classEngine_1_1Audio_1_1AudioBuffer.md#function-setdata)** |  <sup><span style="color:green">(function)</span></sup> |
| **[setDataMultiple](/classes/classEngine_1_1Audio_1_1AudioBuffer.md#function-setdatamultiple)** |  <sup><span style="color:green">(function template)</span></sup> |
| **[setCallback](/classes/classEngine_1_1Audio_1_1AudioBuffer.md#function-setcallback)** | Set the callback function. <br> <sup><span style="color:green">(function)</span></sup> |
| **[setCallback2](/classes/classEngine_1_1Audio_1_1AudioBuffer.md#function-setcallback2)** | Set the callback function. <br> <sup><span style="color:green">(function)</span></sup> |


## Protected Functions
| Member Protected Functions | Description |
| -------------- | -------------- |
| **[getData](/classes/classEngine_1_1Audio_1_1AudioBuffer.md#function-getdata)** |  <sup><span style="color:green">(function)</span></sup> |


## Protected Attributes

| Member Protected Attributes| Description    |
| -------------- | -------------- |
| **[playing](/classes/classEngine_1_1Audio_1_1AudioBuffer.md#variable-playing)** | `bool`<br> <sup><span style="color:green">(protected variable)</span></sup> |

## Friends

| Friends | Description     |
| --------------   | -------------- |
| **[AudioManager](/classes/classEngine_1_1Audio_1_1AudioBuffer.md#friend-audiomanager)**| <br><sup><span style="color:green">(public friend class)</span></sup>  |
| **[Audio::doSomething](/classes/classEngine_1_1Audio_1_1AudioBuffer.md#friend-audiodosomething)**| <br><sup><span style="color:green">(public friend void)</span></sup>  |

## Public Types

### enum Type

<sup>Defined in header [`<src/Audio/AudioBuffer.hpp>`](/files/AudioBuffer_8hpp.md#file-audiobuffer.hpp)</sup>
```cpp
enum class Type;
```

| Enumerator | Value | Description |
| ---------- | ----- | ----------- |
| UNKNOWN | 0|  Dont use this  |
| INT_8 | 1 << 1|  8-bit signed integer  |
| INT_16 | 1 << 2|  16-bit signed integer  |
| INT_24 | 1 << 3|  24-bit signed integer  |
| INT_32 | 1 << 4|  32-bit signed integer  |
| FLOAT_32 | 1 << 5|  32-bit float  |



Different type of audio formats. 

### using AudioData

<sup>Defined in header [`<src/Audio/AudioBuffer.hpp>`](/files/AudioBuffer_8hpp.md#file-audiobuffer.hpp)</sup>
```cpp
template <typename T>
using AudioData = Utils::ArrayView< T >;
```


### typedef AudioData8U

<sup>Defined in header [`<src/Audio/AudioBuffer.hpp>`](/files/AudioBuffer_8hpp.md#file-audiobuffer.hpp)</sup>
```cpp
typedef AudioData<uint8_t> Engine::Audio::AudioBuffer::AudioData8U;
```


## Public Functions

### function AudioBuffer


<sup>Defined in header [`<src/Audio/AudioBuffer.hpp>`](/files/AudioBuffer_8hpp.md#file-audiobuffer.hpp)</sup>

```cpp 
explicit AudioBuffer(const std::string & filename);
```





Constructor for [Audio::AudioBuffer](/classes/classEngine_1_1Audio_1_1AudioBuffer.md). 

















**Exception Safety**

Basic exception guarantee.




### function ~AudioBuffer


<sup>Defined in header [`<src/Audio/AudioBuffer.hpp>`](/files/AudioBuffer_8hpp.md#file-audiobuffer.hpp)</sup>

```cpp 
virtual ~AudioBuffer() = default;
```





[Audio::AudioBuffer](/classes/classEngine_1_1Audio_1_1AudioBuffer.md) destructor. 

















**Exception Safety**

Basic exception guarantee.




### function play


<sup>Defined in header [`<src/Audio/AudioBuffer.hpp>`](/files/AudioBuffer_8hpp.md#file-audiobuffer.hpp)</sup>

```cpp 
void
play(AudioManager & manager) const;
```





Play this buffer. 





**Parameters**

- **manager** - Which manager to play the sound with 













**Exception Safety**

Basic exception guarantee.




### function stop


<sup>Defined in header [`<src/Audio/AudioBuffer.hpp>`](/files/AudioBuffer_8hpp.md#file-audiobuffer.hpp)</sup>

```cpp 
void
stop(AudioManager & manager) const;
```





Stop this buffer playing. 





**Parameters**

- **manager** - Which manager to stop the sound with 













**Exception Safety**

Basic exception guarantee.




### function loop


<sup>Defined in header [`<src/Audio/AudioBuffer.hpp>`](/files/AudioBuffer_8hpp.md#file-audiobuffer.hpp)</sup>

```cpp 
void
loop(AudioManager & manager) const;
```





Loop this buffer forever. 





**Parameters**

- **manager** - Which manager to loop the sound with 




**Notes**

This will loop forever until you call stop 









**Exception Safety**

Basic exception guarantee.




### function setData


<sup>Defined in header [`<src/Audio/AudioBuffer.hpp>`](/files/AudioBuffer_8hpp.md#file-audiobuffer.hpp)</sup>

```cpp  title="(1)" 
void
setData(const TypedAudioData & data);
```

```cpp  title="(2)" 
void
setData(const TypedAudioData data[], size_t size);
```





Some deprecated function. 

















**Exception Safety**

Basic exception guarantee.




### function setDataMultiple


<sup>Defined in header [`<src/Audio/AudioBuffer.hpp>`](/files/AudioBuffer_8hpp.md#file-audiobuffer.hpp)</sup>

```cpp 
template <size_t Size>
void
setDataMultiple(const TypedAudioData data[Size]);
```



















**Exception Safety**

Basic exception guarantee.




### function setCallback


<sup>Defined in header [`<src/Audio/AudioBuffer.hpp>`](/files/AudioBuffer_8hpp.md#file-audiobuffer.hpp)</sup>

```cpp 
void
setCallback(Callback callback);
```





Set the callback function. 





**Parameters**

- **callback** - The callback function pointer 













**Exception Safety**

Basic exception guarantee.


**See Also**

- [Audio::Callback](/namespaces/namespaceEngine_1_1Audio.md#typedef-callback)




### function setCallback2


<sup>Defined in header [`<src/Audio/AudioBuffer.hpp>`](/files/AudioBuffer_8hpp.md#file-audiobuffer.hpp)</sup>

```cpp 
void
setCallback2(Callback2 callback, void * user);
```





Set the callback function. 





**Parameters**

- **callback** - The callback function pointer 













**Exception Safety**

Basic exception guarantee.


**See Also**

- [Audio::Callback](/namespaces/namespaceEngine_1_1Audio.md#typedef-callback)






## Protected Functions

### function getData


<sup>Defined in header [`<src/Audio/AudioBuffer.hpp>`](/files/AudioBuffer_8hpp.md#file-audiobuffer.hpp)</sup>

```cpp 
float *
getData();
```



















**Exception Safety**

Basic exception guarantee.






## Protected Attributes

### variable playing

<sup>Defined in header [`<src/Audio/AudioBuffer.hpp>`](/files/AudioBuffer_8hpp.md#file-audiobuffer.hpp)</sup>
```cpp
bool playing {false};
```


## Friends

### friend AudioManager

<sup>Defined in header [`<src/Audio/AudioBuffer.hpp>`](/files/AudioBuffer_8hpp.md#file-audiobuffer.hpp)</sup>
```cpp
friend
class AudioManager(AudioManager);
```


### friend Audio::doSomething

<sup>Defined in header [`<src/Audio/AudioBuffer.hpp>`](/files/AudioBuffer_8hpp.md#file-audiobuffer.hpp)</sup>
```cpp
friend
void Audio::doSomething(AudioBuffer & buffer);
```


-------------------------------

<sub>Updated on 2023-01-04</sub>