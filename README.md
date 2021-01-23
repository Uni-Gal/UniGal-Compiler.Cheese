# UniGal-Complier

本仓库为UniGal-Script的编译器

Official Complier of UniGal-Script

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

## 原生支持不需要编译器的列表

暂无语言能原生支持导入UniGal，故所有语言都需要两次编译
