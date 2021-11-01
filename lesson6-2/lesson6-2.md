<center>苏亦凡&emsp;&emsp;计算机科学与技术学院&emsp;&emsp;200111229</center>

# 实验内容

使用mpich实现双机多进程的矩阵乘法,测量分析加速比。

# 环境搭建

在环境搭建这一步尝试了很多方法，最终跑通的方案如下。

准备两台全新的x86_64的server，linux发行版为Ububtu 20.04LTS，主机名分别为worker和manager。

## 修改Host文件

两机都进行修改。
```bash
$ sudo vim /etc/hosts
```

```
xxx.xxx.xxx.xxx    manager
xxx.xxx.xxx.xxx    worker
```

## 创建用于mpich通信的用户

```bash
$ adduser mpiuser
```

并修改`/etc/sudoers`，使mpiuser能进行sudo提权。

## 配置ssh免密登陆

两机执行：

```bash
$ ssh-keygen -t rsa -C "mpiuser"
$ ssh-copy-id mpiuser@someip
```
然后为了安全起见，关闭密码登陆。

## NFS安装

manager端：
```bash
$ sudo apt-get install nfs-kernel-server
$ mkdir cloud
```

编辑`/etc/exports`为：
```
/home/mpiuser/cloud *(rw,sync,no_root_squash,no_subtree_check)
```
```bash
$ exportfs -a
$ sudo service nfs-kernel-server restart
```

worker端：

```bash
$ sudo apt-get install nfs-common
$ mkdir cloud
$ sudo mount -t nfs manager:/home/mpiuser/cloud ~/cloud
```

## 运行MPI程序

在manager下执行：

```bash
mpirun -np 5 -hosts worker,manager ./a.out
```

## 总结

在两台实机组成的集群中总是产生奇奇怪怪的错误。而且教程并不详细，还有些需要注意的地方需要注意，如manager和worker同时是两台机子的主机名，若不是这样，将会在双方那里寻找主机名对应的host，结果自然是找不到。

非新机情况下产生的问题我无法自行解决，两台新机确实可以跑通。

# 实验结果

> 删机跑路了，详细数据忘记记录，只讲结果

在矩阵规模较大时，双机的mpi计算速度大致为单机的两倍。这也符合直观认知：双机性能翻倍。在矩阵规模较小时应该是由于双机通信比单机的进程通信耗时长，而此时用时受通信影响较大。