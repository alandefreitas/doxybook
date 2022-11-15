---
title: src/Gui/GuiWidget.hpp

---

# src/Gui/GuiWidget.hpp



## Namespaces

| Name           |
| -------------- |
| **[Engine](/namespaces/namespaceEngine.md)** <br>This namespace contains all of the necessary engine components.  |
| **[Engine::Gui](/namespaces/namespaceEngine_1_1Gui.md)**  |

## Classes

|                | Name           |
| -------------- | -------------- |
| class | **[Engine::Gui::GuiWidget](/classes/classEngine_1_1Gui_1_1GuiWidget.md)** <br>Some generic gui widget class.  |




## Source code

```cpp
#pragma once

class QObject; // Forward definition

namespace Engine {
    namespace Gui {
        class GuiWidget {
        public:
            explicit GuiWidget(QObject* parent);
            virtual ~GuiWidget() = default;

        signals:
            void mySignal(QObject* object, int a, bool b);

        public slots:
            void mySlot(QObject* object, int a, bool b);

        private:
            QObject* parent;
        };
    } // namespace Gui
} // namespace Engine
```


-------------------------------

Updated on 2022-11-15 at 04:12:35 +0000
