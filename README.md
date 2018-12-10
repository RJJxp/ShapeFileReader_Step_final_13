# 2018年12月10日11:51:09

今天按照之前的规范把这个项目的代码重新梳理一遍

其实是纠一遍错

---

#### 命名问题

位于 `rjp_Shape` 

-  `rjp_Shape` 命名
- `int temSHPtype`



#### 格式问题

位于 `rjp_Shape`

- `rjp_Shape * clone();`

- ```c++
   y = y - (picHeight/2 - 1.1*(displayBox[3]-displayBox[1])/(2*finalScale));
   ```



#### 代码的低效

- 循环体内定义每次都需要使用的变量, 每次定义销毁定义销毁, 稍不留神还有内存泄漏的麻烦



---

数据的封装

shapes->shape->datasetptr->dataset->

datasetptr是智能指针

本应还有shadow设计模式, 但我嫌麻烦就给去掉了



工厂(单例)设计模式

工厂基类->ESRI工厂

在ESRI工厂中调用静态工厂来创建