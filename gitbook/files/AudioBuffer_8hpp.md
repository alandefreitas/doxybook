---
title: src/Audio/AudioBuffer.hpp

---

# src/Audio/AudioBuffer.hpp



## Namespaces

| Name           |
| -------------- |
| **[Engine](/namespaces/namespaceEngine.md)** <br>This namespace contains all of the necessary engine components.  |
| **[Engine::Audio](/namespaces/namespaceEngine_1_1Audio.md)**  |

## Classes

|                | Name           |
| -------------- | -------------- |
| class | **[Engine::Audio::AudioBuffer](/classes/classEngine_1_1Audio_1_1AudioBuffer.md)** <br>_A simple audio buffer to hold PCM samples_ |
| struct | **[Engine::Audio::AudioBuffer::TypedAudioData](/classes/structEngine_1_1Audio_1_1AudioBuffer_1_1TypedAudioData.md)** <br>Use this to populate the buffer.  |




## Source code

```cpp
#pragma once
#include "../Utils/ArrayView.hpp"

namespace Engine {
    namespace Audio {
        class AudioManager;
        class AudioBuffer;

        typedef int (*Callback)(AudioBuffer& buffer, size_t offset);

        using Callback2 = int (*)(AudioBuffer& buffer, size_t offset, void* user);

        extern void doSomething(AudioBuffer& buffer);

        class AudioBuffer {
        public:
            enum class Type {
                UNKNOWN = 0,
                INT_8 = 1 << 1,
                INT_16 = 1 << 2,
                INT_24 = 1 << 3,
                INT_32 = 1 << 4,
                FLOAT_32 = 1 << 5
            };
            template <typename T> using AudioData = Utils::ArrayView<T>;
            typedef AudioData<uint8_t> AudioData8U;
            struct TypedAudioData {
                AudioData8U buffer;
                Type type;
            };
            explicit AudioBuffer(const std::string& filename);
            virtual ~AudioBuffer() = default;
            void play(AudioManager& manager) const;
            void stop(AudioManager& manager) const;
            void loop(AudioManager& manager) const;
            void setData(const TypedAudioData& data);

            template <size_t Size> void setDataMultiple(const TypedAudioData data[Size]) {
            }

            void setData(const TypedAudioData data[], size_t size);

            friend class AudioManager;
            friend void Audio::doSomething(AudioBuffer& buffer);

            void setCallback(Callback callback);

            void setCallback2(Callback2 callback, void* user);

        protected:
            float* getData();
            bool playing{false};
        };
    } // namespace Audio
} // namespace Engine
```


-------------------------------

Updated on 2022-11-15 at 01:22:50 +0000
