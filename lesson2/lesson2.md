- [OpenBLAS库及其安装](#openblas库及其安装)
  - [BLAS](#blas)
  - [OpenBLAS](#openblas)
  - [安装OpenBLAS](#安装openblas)
    - [包管理](#包管理)
    - [在仓库下编译](#在仓库下编译)

# OpenBLAS库及其安装

## BLAS

> 基本线性代数子程序，Basic Linear Algebra Subprograms，是一个API标淮，用以规范发布基础线性代数操作的数值库（如矢量或矩阵乘法）。  
> Netlib用Fortran实现了BLAS的这些API接口，得到的库也叫做BLAS。

由此，BLAS指代两个有关联但性质完全不同的东西：API标准和Fortran库。

## OpenBLAS

OpenBLAS是一个BLAS(API标准)的开源实现，OpenBLAS的整体性能不够稳定，但是平均性能是所有库里面最好的。它的开发者是中国人，中科院研究所的张先义([xianyi](https://github.com/xianyi))，github仓库为[OpenBLAS](https://github.com/xianyi/OpenBLAS)

## 安装OpenBLAS

在仓库的[wiki](https://github.com/xianyi/OpenBLAS/wiki)上给出了详细的安装教程。

### 包管理

在[Precompiled-installation-packages](https://github.com/xianyi/OpenBLAS/wiki/Precompiled-installation-packages#linux)中作者给出了安装已编译版本的方法。
```bash
sudo apt install libopenblas-dev
```
编译测试文件。
```bash
gcc test.c -o test -lopenblas
./test
```

### 在仓库下编译

clone仓库，使用gitee上的镜像。
```bash
git clone https://gitee.com/mirrors/OpenBLAS.git
```
接着进仓库进行编译
```bash
cd OpenBLAS
make
```
编译结束会提示，此时用
```bash
make PREFIX=/root/codefield/hpc/lesson2 install
```
将依赖项装进lesson2文件夹。

编译测试文件。
```bash
# -I 头文件文件夹  -L lib文件夹
gcc test.c  -I ./include/ -L ./lib -lopenblas -o test
./test
```
输出
```
0.000000 1.000000 2.000000 3.000000 4.000000 5.000000 6.000000 7.000000 8.000000 9.000000 
90.000000 81.000000 72.000000 63.000000 54.000000 45.000000 36.000000 27.000000 18.000000 9.000000
```
