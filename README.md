# UniGal-Complier-Interpreter

本仓库为UniGal-Script的编译器和解释器

Complier and official Interpreter of UniGal-Script

语言标准请点击[此处](https://github.com/Uni-Gal/UniGal-Script)

流程图标准请点击[此处](https://github.com/Uni-Gal/UniGal-Diagram)

## 编译器 Complier

UniGal是作为一门中间语言出现的，用来作为交换标准

因此您需要在A语言和B语言两者之间交换的时候，我们假设是A到B，那么需要经过如下的流程

假设您现在只有A语言的脚本文件，在第一次编译之后获得了Unigal语言的中间文件

```
A---(A_2_Unigal_Complier)--->Unigal---(Unigal_2_B_Complier)--->B
```

在第二次编译后获得了目标语言B语言的脚本。之后您可以用B引擎来编译/解释B语言的脚本文件

## 解释器 Interpreter

出于更好的阐述UniGal-Script的工作原理的思想，为了让人更好的明白它对应的效果是什么，防止对同一个实验性标准的不同的非官方实现出现类似Web前端一样的混战，我们特别设计了官方的解释器，作为它的一种实现。这样至少它便不是一个死的标准。

**注意！这不意味着解释器是一个游戏引擎（或Chrome一样的垄断性行业标准），它没有游戏引擎所需要具备的诸多功能，它仅能用于正确且完整的实现标准的所有功能。**

其他引擎作者对Unigal的原生支持，也相当于是Unigal的解释器，但是是根据引擎特色定制的解释器。

## 原生支持不需要编译器的列表

暂无语言能原生支持导入UniGal，故所有语言都需要两次编译