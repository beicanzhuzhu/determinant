# Determinant 行列式计算器

这个仓库实现了一个类 `Determinant` 用于表示行列式

可以使用 `get_sum()` 获取行列式的值

## get_sum()

因为作者水平有限，没能编译出适用于msvc的gmp库，故msvc编译器只能使用`int64_t` 存储行列式
，并且因为精度原因，使用的是效率低下的递归展开。而gmp版本是使用了`mpq_class`，高斯消元方法来计算值
