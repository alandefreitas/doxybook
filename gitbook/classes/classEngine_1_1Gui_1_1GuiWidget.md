---
title: Engine::Gui::GuiWidget
summary: Some generic gui widget class. 

---

# Engine::Gui::GuiWidget

**[An example game engine](/libraries/group__Engine.md)** **/** **[Some gui related stuff and whatever](/libraries/group__Gui.md)** **/** 
**[GuiWidget](/classes/classEngine_1_1Gui_1_1GuiWidget.md)**

<sup>Defined in header [`<src/Gui/GuiWidget.hpp>`](/files/GuiWidget_8hpp.md#file-guiwidget.hpp)</sup>



```cpp

class GuiWidget;
```

Some generic gui widget class. 


## Public Slots
| Member Slots | Description |
| -------------- | -------------- |
| **[mySlot](/classes/classEngine_1_1Gui_1_1GuiWidget.md#slot-myslot)** |  <sup><span style="color:green">(slot)</span></sup> |


## Public Signals
| Member Signals | Description |
| -------------- | -------------- |
| **[mySignal](/classes/classEngine_1_1Gui_1_1GuiWidget.md#signal-mysignal)** |  <sup><span style="color:green">(signal)</span></sup> |


## Public Functions
| Member Functions | Description |
| -------------- | -------------- |
| **[(constructor)](/classes/classEngine_1_1Gui_1_1GuiWidget.md#function-guiwidget)** |  <sup><span style="color:green">(function)</span></sup> |
| **[(destructor)](/classes/classEngine_1_1Gui_1_1GuiWidget.md#function-~guiwidget)**  <span style="color:green">= default</span>|  <sup><span style="color:green">(virtual function)</span></sup> |


## Public Slots

### slot mySlot

<sup>Defined in header [`<src/Gui/GuiWidget.hpp>`](/files/GuiWidget_8hpp.md#file-guiwidget.hpp)</sup>
```cpp
void mySlot(
    QObject * object,
    int a,
    bool b
);
```


## Public Signals

### signal mySignal

<sup>Defined in header [`<src/Gui/GuiWidget.hpp>`](/files/GuiWidget_8hpp.md#file-guiwidget.hpp)</sup>
```cpp
void mySignal(
    QObject * object,
    int a,
    bool b
);
```


## Public Functions

### function GuiWidget


<sup>Defined in header [`<src/Gui/GuiWidget.hpp>`](/files/GuiWidget_8hpp.md#file-guiwidget.hpp)</sup>

```cpp 
explicit GuiWidget(QObject * parent);
```



















**Exception Safety**

Basic exception guarantee.




### function ~GuiWidget


<sup>Defined in header [`<src/Gui/GuiWidget.hpp>`](/files/GuiWidget_8hpp.md#file-guiwidget.hpp)</sup>

```cpp 
virtual ~GuiWidget() = default;
```



















**Exception Safety**

Basic exception guarantee.








-------------------------------

<sub>Updated on 2022-11-17</sub>