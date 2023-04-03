---
title: Engine::Utils::ArrayView
summary: Filesystem path utility functions. 

---

# Engine::Utils::ArrayView

**[An example game engine](/libraries/group__Engine.md)** **/** **[Some useful utilities](/libraries/group__Utils.md)** **/** 
**[ArrayView](/classes/classEngine_1_1Utils_1_1ArrayView.md)**

<sup>Defined in header [`<src/Utils/ArrayView.hpp>`](/files/ArrayView_8hpp.md#file-arrayview.hpp)</sup>



```cpp
template <typename T = uint8_t> 
class ArrayView;
```

Filesystem path utility functions. 

**Template Parameters**

  * **T** - The type of the data, for example uint8_t 



## Public Functions
| Member Functions | Description |
| -------------- | -------------- |
| **[(constructor)](/classes/classEngine_1_1Utils_1_1ArrayView.md#function-arrayview)** |  <sup><span style="color:green">(function)</span></sup> |
| **[(destructor)](/classes/classEngine_1_1Utils_1_1ArrayView.md#function-~arrayview)**  <span style="color:green">= default</span>|  <sup><span style="color:green">(virtual function)</span></sup> |
| **[data](/classes/classEngine_1_1Utils_1_1ArrayView.md#function-data)** <span style="color:green">const</span>|  <sup><span style="color:green">(virtual function)</span></sup> |
| **[size](/classes/classEngine_1_1Utils_1_1ArrayView.md#function-size)** <span style="color:green">const</span>|  <sup><span style="color:green">(virtual function)</span></sup> |


## Public Functions

### function ArrayView


<sup>Defined in header [`<src/Utils/ArrayView.hpp>`](/files/ArrayView_8hpp.md#file-arrayview.hpp)</sup>

```cpp 
ArrayView(const T * src, size_t len);
```




















**Exception Safety**

Basic exception guarantee.




### function ~ArrayView


<sup>Defined in header [`<src/Utils/ArrayView.hpp>`](/files/ArrayView_8hpp.md#file-arrayview.hpp)</sup>

```cpp 
virtual ~ArrayView() = default;
```




















**Exception Safety**

Basic exception guarantee.




### function data


<sup>Defined in header [`<src/Utils/ArrayView.hpp>`](/files/ArrayView_8hpp.md#file-arrayview.hpp)</sup>

```cpp 
virtual const T *
data() const;
```




















**Exception Safety**

Basic exception guarantee.




### function size


<sup>Defined in header [`<src/Utils/ArrayView.hpp>`](/files/ArrayView_8hpp.md#file-arrayview.hpp)</sup>

```cpp 
virtual size_t
size() const;
```




















**Exception Safety**

Basic exception guarantee.








-------------------------------

<sub>Updated on 2023-04-03</sub>