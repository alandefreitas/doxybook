---
title: Engine::Exception

---

# Engine::Exception

**[An example game engine](/libraries/group__Engine.md)** **/** 
**[Exception](/classes/classEngine_1_1Exception.md)**

<sup>Defined in header [`<src/Exception.hpp>`](/files/Exception_8hpp.md#file-exception.hpp)</sup>



```cpp

class Exception;
```



**Inherits from** `std::exception`

## Public Functions
| Member Functions | Description |
| -------------- | -------------- |
| **[(constructor)](/classes/classEngine_1_1Exception.md#function-exception)** |  <sup><span style="color:green">(function)</span></sup> |
| **[what](/classes/classEngine_1_1Exception.md#function-what)** <span style="color:green">const</span> <span style="color:green">override</span>|  <sup><span style="color:green">(function)</span></sup> |


## Public Functions

### function Exception


<sup>Defined in header [`<src/Exception.hpp>`](/files/Exception_8hpp.md#file-exception.hpp)</sup>

```cpp  title="(1)" 
Exception() = default;
```

```cpp  title="(2)" 
explicit Exception(std::string msg);
```



















**Exception Safety**

Basic exception guarantee.




### function what


<sup>Defined in header [`<src/Exception.hpp>`](/files/Exception_8hpp.md#file-exception.hpp)</sup>

```cpp 
const char *
what() const override;
```



















**Exception Safety**

Basic exception guarantee.








-------------------------------

<sub>Updated on 2023-01-04</sub>