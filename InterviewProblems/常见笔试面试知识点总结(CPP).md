
## (一) C/C++结构体内存对齐

遵循两条重要的原则:

1. **大小为size的数据成员的align必须满足 align % size = 0**
2. **整个结构体的size必须为最大数据成员size的整数倍**

例如,

```c
struct pad {
    char ch;
    short s;
    int i;
    char ch2;
};
```

- 首先ch的size为1，align为0满足0%1=0的要求，不需要修改；
- 然后看s的size为2，如果不加padding的话其align=1，1%2=1不满足要求，所以需要在前面增加大小为1的padding，使其align为2；
- 然后是i，size=4，当前align=4，符合1的要求，不需要pading；
- 最后ch2的size=1，不加padding，其align=9，符合1的要求；
- 这样当前整个结构体大小为9，再看原则2，最大成员(此时为int)的size=4,9不是4的整数倍，所以需要在结构体末尾再padding 3个字节，所以最终的结构体大小为12

此外，需要特别注意的是，在32位机器上，指针的大小为4字节；而在64位机器上指针的大小为8字节，例如

```c
struct ss {
    int* p;
    int i;
    char ch;
};
```

在32位机器上，通过上面两个原则不难分析该结构体大小为12个字节（只需要在结构末尾padding 3个字节即可）；而在64位机器上，该结构体的大小为16个字节，因为int*占8个字节，整个结构体大小需要是8的整数倍，因此需要在结构padding 3个字节。

## (二) C/C++中的static关键字
因为static关键字在C语言和C++语言中都有出现，因此下面分开讨论

### 1. C语言(面向过程)中的static关键字

在C语言中，static关键字可以修饰变量和函数，其主要的作用是**隐藏**。

#### 1.1 static修饰全局变量，限制该全局变量仅在当前文件可见，例如

```c
// file1.c
static int global_a = 10; // 定义静态全局变量
int global_b = 20; // 定义全局变量
```

在file1中声明的全局变量在其他文件中是不可见的

```c
// file2.c
extern int global_a; // 声明外部变量
global_a = 100; // ERROR:不可访问
extern int global_b;
global_b = 200; // OK:可以访问普通的全局变量
```

file2访问不能访问file1中静态全局变量

#### 1.2 static修饰局部变量，对变量进行**持久化**。

```c
void fun() {
    static int call_count = 0; // 记录fun()函数被调用次数
    call_count += 1;
    printf("fun() is called %d times\n", call_count);
}
```

static局部变量在函数声明处被*初始化一次*，以后的调用不再*初始化*,这样static局部变量就有了记忆函数状态的功能，同时由于其在函数内部声明，对函数外部是不可见的。

static变量（包括static全局变量和static局部变量）在全局数据区，其生存周期为整个程序从开始到结束。但是static局部变量的作用域与普通的局部变量相同，函数退出即不可访问。注意：此时static变量仍然存在只是不可访问；而普通局部变量函数退出内存已被回收，当然不可访问。

#### 1.3 static修饰函数

与static全局变量作用类似，限制函数仅在当前文件可见

### 2. C++语言(面向对象)中的static关键字

#### 2.1 static数据成员

类中的static数据成员，是属于整个类，所有的对象没有static成员的私有拷贝，**共享static数据成员**。

static数据成员的初始化与一般数据成员的不同

    <类型> <类名>::<static数据成员名> = value
例如:

```c
struct Test {
    static int count;
    int a;
    int b;

    static void GetCount() {
		cout << count << endl;
	}
};
int Test::count = 0; // static成员变量初始化
```

对static成员的访问方式可以有两种形式:

- 通过类访问
- 通过对象访问

还以上面Test类为例:

```c
Test t; // 定义一个对象
Test::count = 10; // OK,通过类名访问
t.count = 20; // OK,通过对象访问
```

#### 2.2 static成员函数

与static数据成员类似，static成员函数也属于整个类，为整个类而非个别对象服务。因此，static成员函数只能访问static数据成员和其他static成员函数，不能访问非static数据成员和非static成员函数。

其访问方式也为两种，仍以Test类为例:

```c
Test::GetCount(); // OK, 通过类名访问
t.GetCount();  // OK, 通过对象访问
```

## (三) C++中extern关键字

C语言中extern关键字用于变量或者函数前，表示“**该变量或者函数在别处定义，要在此处引用**”

### 3.1 extern 修饰变量

最佳实践，将所有的全局变量放在一个头文件 `global.h`中并用extern关键字修饰，将变量的定义放在 `global.c`文件中，所有用到全局变量的文件只需要包含该头文件即可

```
/* global.h */
extern int g_a;
extern int g_b;
```
```
/* global.c */
#incude "global.h"
int g_a = 10;
int g_b = 20;
```
```
/* A.cpp, B.cpp, C.cpp */
#include "global.h"
```
### 3.2 extern 修饰函数

作用于extern变量相似，仅仅表示函数在其他的源文件中定义

### 3.3 extern "C" 链接指示

在C++调用C函数时，需要在C++程序中用extern "C"声明要引用的函数，这告诉编译器，用C函数规范进行编译和链接，不要进行命名修饰。

#### 注：有关命名修饰的解释
由于C++语言支持函数重载，而C语言不支持，函数被C++编译后在符号库中的名字与C语言编译的不同，例如，
```
void foo(int x, int y)
```

该函数被C编译后在符号库中的名字为__foo，而C++编译器则会产生类似于__foo_int_int之类的名字（不同的编译器生成的名字略有不同，但是采用相同的机制，即将参数类型作为名字的一部分），这样生成的名字称为**mangled name**.

__foo_int_int这样的名字包含了函数名、参数数量以及参数类型，C++靠这样的方式才区别重载函数。例如，在C++中，`void foo(int x, double y)`生成的符号名称为__foo_int_double

## C++中的虚函数机制

## C++中构造函数和析构函数机制

## C++对象的内存布局



## C++中的static_cast和dynamic_cast区别
