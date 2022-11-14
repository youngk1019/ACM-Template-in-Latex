# ACM-Template-in-Latex

本项目是基于cpp自动生成Latex文档，用于自动整理生成ACM（算法）模板

## 文件结构：

1. 主文件中的 `config`文件为控制一级目录的配置文件，主要用来控制Section的输出，内部填写的名字代表着一个一级目录，需使用者自行进行更改
2. 主文件中的 `head.tex`、`main.cpp`文件，可以根据需要进行修改（如更改组织和作者姓名，或者更改`Latex`格式）
3. 一级目录中的`config`文件为当前目录的配置文件，主要用来控制Subsection的输出及判定是否存在Subsubsection。该文件存在四个参数：
<节名称> <代码文件> <tex文件> <二级目录名称>
   - <节名称>：在<>内部填写当前你需要最终渲染出来的节（即Subsection）的名称
   - <代码文件>：在<>内部填写在当前节中，所需要插入的代码(支持`.cpp`/`.java`/`.py`等文件)。**如果当前状态下无需代码文件，则在<>中间留空，如果没有后面两个参数，则可以直接省略<>**，
   - <tex文件>：在<>内部填写在当前节中，你所需要插入的说明文件`.tex`.**如果当前状态下无需代码，则在<>中间留空（如果没有最后一个参数，则可以直接省略<>）**
   - <二级目录名称>：如果你需要生成一个二级目录，则你只需要在次项中填写于<节名称>相同的信息。**注意：此时填写的名字代表的是一个二级目录（是一个文件夹），此时第二个以及第三个参数需要留空**，二级目录中的`config`文件配置跟上述相同，但暂不支持更多级的目录

## 使用：

### 准备：

`g++(MinGW,Clang等)`、`Latex(TexLive,MacTex等)`

可能会在系统中没有对应的字体，可以在文件夹`字体`中进行安装，或者在head文件中对字体进行修改

#### Linux,MacOS：

```bash
make
```

#### Windows：

**因为需要支持中文，需要将Windows系统编码改为utf-8**

```bash
 g++ main.cpp -o gen.exe
 gen.exe
 XeLatex template.tex
 XeLatex template.tex
 ```
 编译运行`main.cpp`，会生成一份`template.tex`文件，只需要用Latex使用`XeLatex`编译生成pdf文件即可，最终需要编译两次XeLatex

## 说明：

项目本体来基于[ICPC-Code-Template-in-Latex](https://github.com/Chen-Jr/ICPC-Code-Template-in-Latex)和[ACM-ICPC-CodeTemplate-Latex](https://github.com/jasison27/ACM-ICPC-CodeTemplate-Latex)，修复了其中Latex、cpp、跨平台兼容性等问题，此外主要保存自己的算法模板
