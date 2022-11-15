---
title: src/Audio/AudioManager.hpp

---

# src/Audio/AudioManager.hpp



## Namespaces

| Name           |
| -------------- |
| **[Engine](/namespaces/namespaceEngine.md)** <br>This namespace contains all of the necessary engine components.  |
| **[Engine::Audio](/namespaces/namespaceEngine_1_1Audio.md)**  |

## Classes

|                | Name           |
| -------------- | -------------- |
| class | **[Engine::Audio::AudioManager](/classes/classEngine_1_1Audio_1_1AudioManager.md)** <br>An audio manager that _accepts_ multiple **[Audio::AudioBuffer](/classes/classEngine_1_1Audio_1_1AudioBuffer.md)** instances.  |




## Source code

```cpp
#pragma once

#include "AudioBuffer.hpp"

namespace Engine {
    namespace Audio {
        class AudioManager final {
          public:
            AudioManager(int numOfChannels = 128);
            ~AudioManager();

            void enque(const AudioBuffer& buffer);
        };
    } // namespace Audio
} // namespace Engine
```


-------------------------------

Updated on 2022-11-15 at 00:06:22 +0000
