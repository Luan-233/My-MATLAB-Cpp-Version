# My-MATLAB-Cpp-Version

**这个作者他XCPC被暴打然后写不完作业然后咕了。**

​		之前闲的没事写了几个矩阵运算，后来发现每一次都是在交互端复制粘贴太麻烦了，于是模仿MATLAB自己实现了一个简易的矩阵计算器。只适用于小规模矩阵运算如写线性代数作业。我一天没挂就可能更一天。

声明：

+ 这个程序中，除了生成矩阵可以不用预先定义以外，其他矩阵使用时必须提前定义
+ 一定要严格按照这个输入进行操作，区分大小写
+ 此程序不具有记忆化功能。也就是说关了数据就没了（这个坑我打算以后补上
+ 建议先拿一个记事本写好输入内容！！！（不然你会绝望的

具体操作：

+ 定义新矩阵 - Define  矩阵名字  矩阵行数  矩阵列数
  （支持重新定义已有矩阵大小，新矩阵为空；单个矩阵大小不得超过30万）
+ 输出矩阵所有元素 - Show  矩阵名字
  （按照行列输出，每个元素之间空一格）
+ 矩阵单点修改 - Modify 矩阵名字  行数  列数  值
+ 输入矩阵元素 - Init  矩阵名字 矩阵值
  （请严格按照矩阵大小将所有元素输入）
+ 矩阵求逆 - Inverse  矩阵名字  生成矩阵名字
  （若矩阵不可逆则会有提示）
+ 矩阵的秩 - Rank  矩阵名字
+ 求行列式 - Det  矩阵名字
+ 加减乘法 - Calculate  矩阵名字1  算数符号（英文的+ - *）  矩阵名字2  生成矩阵名字
  （若矩阵行列数值不对应则会有提示）
+ 矩阵转置 - T  矩阵名字  生成矩阵名字
+ 查看当前所有矩阵信息 - Who
+ 程序结束 - Quit

打算以后吃饱了撑的加进去的内容：

+ 虚数以及复数运算
+ 超高精度运算
+ 模意义下的运算
+ 文件（.txt 格式）导入 - DataInput
+ 多项式乘法 - PloyMul
+ 矩阵幂 - Pow
+ N元一次方程组求解 - MatSolve
+ 一元N次方程求解 - PloySolve
+ 定积分求值 - Sum
+ 清屏 - CleanScreen
+ 删除所有矩阵 - Clean

这个例子会教给你如何使用这个程序。

```
Define A 3 3
Init A
1 1 1
1 1 2
1 2 3
Det A
Rank A
Inverse A B
Show B
Calculate  A + B C
Show C
Calculate  A * B C
Y
Show C
Who
Quit
```
