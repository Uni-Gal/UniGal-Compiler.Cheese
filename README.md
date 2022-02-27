# UniGal-Compiler.Cheese

本仓库为UniGal-Script的一个停止维护的编译器。

本项目支持v0.0.2版本UniGal-Script

## 编译器 Complier

UniGal是作为一门中间语言出现的，用来作为交换标准

因此您需要在A语言和B语言两者之间交换的时候，我们假设是A到B，那么需要经过如下的流程

假设您现在只有A语言的脚本文件，在第一次编译之后获得了Unigal语言的中间文件

```
A---(A_2_Unigal_Complier)--->Unigal---(Unigal_2_B_Complier)--->B
```

在第二次编译后获得了目标语言B语言的脚本。之后您可以用B引擎来编译/解释B语言的脚本文件

## 原生支持不需要编译器的列表

暂无语言能原生支持导入UniGal，故所有语言都需要两次编译

## 语言兼容方式

设计一个NxM的矩阵，N为特性数目，M为语言，然后对应的点存储支持程度信息，是按照定义写出，还是按照UEP给警告，还是报错。

## 本工程

在这里躺着的是```Unigal_2_BKE_Complier```和```Unigal_2_librian_Complier```的代码

我们可能会在同一个程序里面提供多个编译器合并在一起。

这样未来就只有两个程序了，```A_2_U_Complier```和```U_2_B_Complier```

之后引入一个编译控制器，来无缝衔接两个程序。

（好家伙，这是IDE啊）
