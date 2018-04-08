# 手敲游戏引擎

## 文件目录结构

- 1.Assert

  目录,用于存放shader、贴图、模型、场景、动画、音频等游戏资源文件

  - 1.1. Shaders

- 2.External

  目录, 用于存放项目依赖的第三方库或者源码

  - 2.1. GL

    OpenGL Loader（加载器）的自动生成脚本。可以根据最新的OpenGL规格文件（xml，脚本会自动从互联网下载）自动生成OpenGL的函数签名（申明）以及运行时加载并绑定这些API的C/C++源码。通过执行glad_generate.bat就可以生或者更新GL目录当中的文件。注意需要python2.7（在本系列开头编译clang的时候已经安装)。

    - 2.1.1. include

      - 2.1.1.1. glad

      - 2.1.1.2. KHR

    - 2.1.2. src

- 3.Framework

  用于存放框架

  - 3.1. Common

    用于存放各平台通用代码

  - 3.2. Interface

    用于存放模块间接口代码

- 4.Platform

   目录下的项目按平台分类，Linux平台的代码在Windows下是不能编译的，反之亦然。因此我们需要在CMakeLists.txt当中作平台的检测，进行条件编译。

  - 4.1. Empty

  - 4.2. Windows

  - 4.3. Linux

- 5.RHI

  表示空（无）图形API。这是用来验证我们的代码（除了特定的RHI模块之外）与任何图形API都没有绑定关系，可以在空API的情况下完成编译。也就是图形API无关性。（平台无关性通过platform目录下的empty确保）

  - 5.1. Empty

    表示空（无）图形API

  - 5.2. D3d

  - 5.3. OpenGL

## 文件类型说明

- `*.ps`
- `*.hs`
- `*.dds`: 一种图片格式，广泛应用于3D游戏贴图，它是DirectX纹理压缩(DirectX Texture Compression,简称DXTC)的产物，简称"贴图"。
- `*.gxt`
- `*.gnf`
- `*.ppm`: (Portable PixMap)是portable像素图片，没有经过压缩，相对比较大，但是由于图片格式简单，一般做为图片处理的中间件。或者做为单间的图片格式保持。
- `*.tga`
- `*.raw`: 文件几乎未经处理而直接从CCD或CMOS上得到的信息。
- `*.tga`:

## 工具链

### CMAKE

[Reference Maunual](https://cmake.org/cmake/help/latest/index.html)

- CMAKE-buildsystem

- CMAKE-commands
  - Scripting Commands

  - Project Command
    - `add_library(<name> [STATIC | SHARED | MODULE] [EXCLUDE_FROM_ALL] [source1] [source2] [...])`
       其中\<name\>表示库文件的名字，该库文件会根据命令里列出的源文件来创建。而STATIC、SHARED和MODULE的作用是指定生成的库文件的类型。STATIC库是目标文件的归档文件，在链接其它目标的时候使用。SHARED库会被动态链接（动态链接库），在运行时会被加载。MODULE库是一种不会被链接到其它目标中的插件，但是可能会在运行时使用dlopen-系列的函数。默认状态下，库文件将会在于源文件目录树的构建目录树的位置被创建，该命令也会在这里被调用。而语法中的source1 source2分别表示各个源文件
    - `add_subdirectory(src_dir [binary_dir] [EXCLUDE_FROM_ALL])`
       向当前工程添加存放源文件的子目录,并可以指定中间二进制和目标二进制的存放位置EXCLUDE_FROM_ALL含义：将这个目录从编译过程中排除
    - `include_directories([AFTER | BEFORE] [SYSTEM] dir1 dir2 … )` 
       向工程添加多个特定的头文件搜索路径,路径之间用空格分隔,如果路径包含空格,可以使用双引号将它括起来,默认的行为为追加到当前头文件搜索路径的后面。有如下两种方式可以控制搜索路径添加的位置

    - `target_include_directories(<target> [SYSTEM] [BEFORE] <INTERFACE|PUBLIC|PRIVATE> [items1...][<INTERFACE|PUBLIC|PRIVATE> [items2...] ...])` 
    作用：编译给定目标文件时，指定要包含的文件（一般为头文件）以及目标文件所在目录路径。  
    参数
    1.target目标文件必须已经存在（由命令add_executable()或add_library()所创建)，并且不能被IMPORTED修饰.  
    2.若使用BEFORE，则它修饰的内容会被添加到属性前面。     
    3.关键字INTERFACE，PUBLIC和PRIVATE指定它后面参数的作用域。PRIVATE和PUBLIC项会填充targe目标文件的INCLUDE_DIRECTORIES属性。PUBLIC和INTERFACE项会填充target目标文件的INTERFACE_INCLUDE_DIRECTORIES属性。随后的参数指定包含目录。
    指定的包含目录可能是绝对路径也可能是相对路径。对同一个target目标文件的重复调用会按命令的调用顺序进行。如果指定标志为SYSTEM，则是告诉编译器在一些平台上该目录表示系统包含目录(表示这个设置可能取得效果比如跳过警告，或者这些固定的安装系统文件在依赖计算中不被考虑-参考编译文档)。如果SYSTEM和PUBLIC和INTERFACE同时使用，则目标文件属性INTERFACE_SYSTEM_INCLUDE_DIRECTORIES会被填充到指定目录。

    - `file(STRINGS filename variable [LIMIT_COUNT num] [LIMIT_INPUT numBytes] [LIMIT_OUTPUTnumBytes] [LENGTH_MINIMUM numBytes][LENGTH_MAXIMUMnumBytes] [NEWLINE_CONSUME] [REGEX regex][NO_HEX_CONVERSIO])`
    :TRINGS 从文件中解析出ASCII字符串列表并存储在变量中。文件中的二进制数据将被忽略。回车符(CR)也会被忽略。也能解析Intel Hex和Motorola S-record文件，这两种文件在读取是会自动转换为二进制格式，可以使用参数NO_HEX_CONVERSION 禁用这种自动转换。LIMIT_COUNT设置可返回的最大数量的字符串。LIMIT_INPUT 设置从输入文件中可读取的最大字节数。LIMIT_OUTPUT设置了存储在输出变量中最大的字节数。 LENGTH_MINIMUM设置了返回的字符串的最小长度。小于这个长度的字符串将被忽略。 LENGTH_MAXIMUM 设置返回的字符串的最大长度。大于这个长度的字符串将被切分为长度不大于于最大长度值的子字符串。NEWLINE_CONSUME 允许换行符包含进字符串中而不是截断它们。REGEX 指定了返回的字符串必须匹配的正则表达式的模式。典型用法 
    file(STRINGS myfile.txt myfile)， 将输入文件的每行内容存储在变量"myfile"中  

    - `cmake_policy`

- CMAKE-compile-features

- CMAKE-developer

- CMAKE-generator-expression

- CMAKE-generators

- CMAKE-language

- CMAKE-server

- CMAKE-modules

- CMAKE-packages

- CMAKE-policies

- CMAKE-properties

- CMAKE-qt

- CMAKE-toolchains

- CMAKE-variables

  - Variables that Provide Information
    - `CMAKE_AR`
      静态库的归档工具名字

    - `CMAKE_ARGC`

    - `CMAKE_ARGV0`

    - `CMAKE_BINARY_DIR`

    - `CMAKE_BUILD_TOOL`

  - Variables that Change Behavior

    - `CMAKE_INCLUDE_DIRECTORIES_BEFORE`
    通过SET这个cmake变量为on,可以将添加的头文件搜索路径放在已有路径的前面,
通过AFTER或BEFORE参数,也可以控制是追加还是置前

  - Variables that Describle the System
    -`CMAKE_SYSTEM_NAME`
      目标机操作系统，如Android,Linux,PSP2,

    - `CMAKE_SYSTEM_VERSION`

  - Variables that Control the Build
    - `CMAKE_C_COMPILER`
    - `CMAKE_BUILD_TYPE`:
       设置Build Type(Debug Release)

  - Varialbes for Languages 

  - Variables for CTest

  - Variables for CPack

  - CMAKE-env-variables

 [CMake Useful Variable](https://cmake.org/Wiki/CMake_Useful_Variables)
- Location
- Environment Variables
- System & Compiler Information 
- Various Option
- Compilers and Tools

  - `CMAKE_C_COMPILER`

- Prefixes,Suffixes(Postfixes),and Extensions
- Variables not listed here
- Logging code

[CMakeCache.txt](https://blog.csdn.net/dbzhang800/article/details/6340102)

CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS

### CLANG-LLVM

- [Document](http://llvm.org/docs/index.html)
  - Overview
  - LLVM Design & Overview
  - User Guide
  - Programming Documentation
  - Subsystem Documentation
  - Development Process Documention 
  - Community 
  - Community wide proposals
  - Indices and tables

### 命令行

删除当前目录下所有文件：rm -rf *

#### Windows

```bash
cmake -G "NMake Makefiles" ../.. ;对应 nmake
```

#### Linux

``` bash
cmake -G "Unix Makefiles" ../.. ;对应 make
build/Release当中执行下面的命令:cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release ..\..
build/Debug当中执行下面的命令:cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug ..\..
```

#### LLVM-CLANG
cmake -G "Unix Makefiles" -DCMAKE_TOOLCHAIN_FILE=..\..\cmake\clang-cl.cmake ..\..