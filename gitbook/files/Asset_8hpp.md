---
title: src/Assets/Asset.hpp

---

# src/Assets/Asset.hpp



## Namespaces

| Name           |
| -------------- |
| **[Engine](/namespaces/namespaceEngine.md)** <br>This namespace contains all of the necessary engine components.  |
| **[Engine::Assets](/namespaces/namespaceEngine_1_1Assets.md)**  |

## Classes

|                | Name           |
| -------------- | -------------- |
| class | **[Engine::Assets::Asset](/classes/classEngine_1_1Assets_1_1Asset.md)**  |
| union | **[Engine::Assets::Asset::Event](/classes/unionEngine_1_1Assets_1_1Asset_1_1Event.md)**  |
| struct | **[Engine::Assets::Asset::Event::Loaded](/classes/structEngine_1_1Assets_1_1Asset_1_1Event_1_1Loaded.md)**  |
| struct | **[Engine::Assets::Asset::Event::Unloaded](/classes/structEngine_1_1Assets_1_1Asset_1_1Event_1_1Unloaded.md)**  |
| struct | **[Engine::Assets::Asset::Event::Waiting](/classes/structEngine_1_1Assets_1_1Asset_1_1Event_1_1Waiting.md)**  |




## Source code

```cpp
#pragma once
#include <queue>
#include <string>

namespace Engine {
    namespace Assets {
        class Asset {
        public:
            union Event {
                struct Loaded {
                    bool success;
                    int usage;
                } loaded;
                struct Unloaded {
                    bool success;
                } unloaded;
                struct Waiting {
                    Asset* other;
                } waiting;
            };

            explicit Asset(const std::string& name);
            virtual ~Asset() = 0;

            virtual void load();
            virtual void unload();
            const Event& getEvent() const {
                return event;
            }
        private:
            Event event;
        };
    }
}
```


-------------------------------

Updated on 2022-11-15 at 04:12:35 +0000
