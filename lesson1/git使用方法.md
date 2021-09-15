# git在linux下的使用方法
> 以Ubuntu20.04为例

## git安装

Ubuntu下git的安装非常轻松，直接包管理。
```bash
apt install git
```
若不是root用户前面加`sudo`即可。

## git配置

与win下git的配置几乎毫无二致。
配置全局用户名与邮箱：
```bash
# 字符串替换为对应字符串
git config --global username "Your Name"
git config --global user.email "youremail@yourdomain.com"
```

## 添加ssh密钥

生成密钥对：
```bash
ssh-keygen -t rsa -C "your_email@youremail.com"
```
可以一路回车使用默认配置。生成的`.pub`结尾的文件即为公钥，另一文件为公钥。复制公钥内容，在github--<kbd>Settings</kbd>--<kbd>SSH and GPG keys</kbd>--<kbd>New SSH key</kbd>的key栏粘贴，title自行填写。

此时进行测试：
```bash
ssh -T git@github.com
```
多半会遇到错误`Error: Permission denied (publickey)`，解决方法是配置ssh_config。
```bash
vim /etc/ssh/ssh_config
```
在结尾添加：
```
#github
    Host github.com
    HostName github.com
    User git
    IdentityFile ~/.ssh/github_rsa
```
此时再次设置，将会在终端打印出类似于`Hi SoraShu! You've successfully authenticated, but GitHub does not provide shell access.`的信息。

## 在本地建立仓库

直接对本地文件夹进行初始化。下面演示建立空仓库并添加README.md的操作过程。
```bash
mkdir hcp
cd hcp
echo "# 高性能计算应用实践" >> README.md
git init
git add .
git commit -m 'init'
```
这样一个包含了基本的README文件的仓库就建好了。

## 连接github仓库

在github上新建空仓库。

添加远程仓库：
```bash
git remote add origin git@github.com:sorashu/hcp.git
git push -u origin main
```
我们在`push`时加了`-u`参数，之后可以用`git push`替代`git push origin main`。

## 一些注意事项

### 连接问题

国内访问github有时会出现SSL错误，连接超时的问题，这在`clone`或者`push`，`pull`的时候几乎是fatal的。

解决方法是通过代理访问github。由于git不走系统代理，于是需要对git配置代理。

若使用github的https url进行clone或远程仓库的添加，需要配置https代理。
```bash
git config --global https.proxy http://127.0.0.1:11223
```
若使用ssh，则需要配置ssh代理。在[添加ssh密钥](##添加ssh密钥)中，将添加的配置修改为：
```
Host github.com
    User git
    Port 22
    Hostname %h
    IdentityFile ~/.ssh/github_rsa
    # HTTPS使用-H，SOCKS使用-S
    ProxyCommand connect -S 127.0.0.1:11223 %h %p
```
当然也可以通过路由器全局透明代理等方式解决。或者改用国内的托管平台，如gitee。

### 选择忽略文件

有时我们希望一些文件不会被git捕捉，从而精简仓库。
```bash
vim .gitignore
```
在文件中添加希望忽略的文件。语法如下：
1. 以斜杠`/`开头表示目录；
2. 以星号`*`通配多个字符；
3. 以问号`?`通配单个字符
4. 以方括号`[]`包含单个字符的匹配列表；
5. 以叹号`!`开头表示不忽略匹配到的文件或目录；

若已经提交暂存，则需要将暂存区全部清空，然后重新提交暂存。
```bash
git rm -r --cached .
git -add .
```
若之前已经commit过了，再次commit之后就会删除已忽略文件。
