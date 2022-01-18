1. 文件结束符
    * UNIX文件结束符 ctrl+D
    * Windows文件结束符 ctrl+Z
2. 前缀
    * 字符串前缀
        |前缀|编码|类型|
        |--|--|--|
        |u|utf-16|`char16_t`|
        |U|utf-32|`char32_t`|
        |L|宽字符|`wchar_t`|
        |u8|utf-8|char|
    * 数字字面值
        |前缀|类型|说明|
        |--|--|--|
        |u/U|unsigned|无符号|
        |l/L|long||
        |ll/LL|long long||
        |f/F|float||
        |l/L|long double||
3. 空指针字面量
    ```c++
    int *p1 = nullptr;   //内置的空指针字面量
    int *p2 = 0;         //合法, 但不建议使用
    int *p3 = NULL;      //预处理, 需#include <cstdlib>  即#define NULL 0
    ```
4. 列表初始化:用花括号括起, 严格检查初始化数据与被初始化类型的一致性.
5. 标识符
    * 不能出现连续两个下划线
    * 不能以下划线紧跟大写字母开头
6. 当域操作符左侧为空时, 指代全局作用域.
7. 引用`reference`
    * 引用必须初始化(绑定bind到左值上); 引用相当于别名, 声明引用必须告诉是谁的别名.
        ```c++
        int * point = (int *)malloc(sizeof(int));
        int & ref = * point; //is ok!
        ```
    * 引用的类型要与之绑定的对象严格匹配.
8. `void *` 是一个任意类型的指针, 该类型对象是非左值.
9. const
    * `const`对象仅在文件内有效(在文件作用域的`const`对象不在全局作用域)
        ```c++
        int &i = 10;       //这是错误的.
        const int &ci = 10; //这是正确的. 等价于 const int temp = 10; const int &ci = temp; temp是临时无名的.

        const int ci = 10;
        int i = ci;
        //该代码片被编译器优化成:
        const int ci = 10;
        int i = 10;
        //实际上ci还是有自己的内存空间, 且可以通过指针强转改变其中的值.
        ```
    * const修饰的标识符只是不可写标识符, 获取其内存还是可以更改标识符对应对象的值.
10. constexpr
    * constexpr关键字就是显式要求(**对象**或**如果满足两个条件的constexpr函数<sub>详见42</sub>**)编译期求值.
    * 常量表达式(const expression)是编译过程中即可得到结果的表达式. 字面量就是一种常量表达式
    * 可以用constexpr声明变量为常量表达式, 初始值可以由常量表达式或constexpr函数来指定.
    * constexpr指针只能指向某个固定地址中的对象(静态存储期)
    * `constexpr int *q=nullptr;`等价于`int * const p = nullptr;`
11. 类型别名
    * using 别名 = 类型;
    * typedef 类型 别名;
        ```c++
        typedef char *pstr;
        const pstr a = 0;
        const char * b = 0;
        //a与b不同, a中const作用在a上(a本身对象); b中const作用在*b上(b指向的对象).
        ```
12. auto类型说明符
    * auto是让编译器执行表达式(常量表达式)得到的结果的类型定义对象
    * auto定义的对象会忽略**顶层const**
        * 要定义顶层const对象, 使用`const auto 标识符=表达式`
    * auto定义的的引用不忽略**顶层const**
13. decltype类型指示符
    * decltype是让编译器分析**如果运行表达式**得到的类型.
    * decltype(表达式/函数) 标识符 = 值.
        ```c++
        int i = 1, *p = &i, &r = i;
        decltype(i) a;       //a是int
        decltype(*p) b;      //b是int &
        decltype(r) c;       //c是int, 和a一样.
        decltype((i)) d;     //d是int &
        //decltype((?))的类型永远是引用, decltype(?)只有?是引用,类型才是引用.
        //?在使用*(解引用符)的结果(如*p), ?是引用.
        int a=0;
        decltype(a = 1) b = a;
        //a=0,b=0; 1.赋值的结果的类型是引用; 2.a=1只是用于判断b的类型, 运行阶段没有a=1;
        ```
14. `using namespace::name;`从命名空间引入name, 可直接使用name, 每个名字都需要独立的using声明
15. string 标准库类型
    1. `#include <string> \n using std::string;`
    2. string无结尾的`'\0'`
        ```c++
        string s = "value";            //拷贝初始化, s无'\0'
        string s1("value");            //直接初始化, 等价于s
        string s2(3, 'c');             //直接初始化, s2="ccc"
        string s3 = string(3, 'c');    //拷贝初始化, 等价于s2; 相当于string temp(3, "c"); string s3=temp;
        ```
    3. string操作
        * `cin>>s`从cin读字符串到s, 空白(空格/换行/制表)分割, 返回cin
        * `getline(cin, s)`从cin读取一行(包括换行)到s(不包括换行), 返回cin; 
        * `s.empty(); s.size(); s[n];`
        * `s1+s2`返回s1连接s2的结果. `+`的两侧保证有一个是string, 另一个可以是字符或字符串.
        * `s1=s2;`用s2的**副本**替换s1.
        * `==;!=;<;<=;>;>=;`如预期
    4. string 和 字符串不是一个类型!!!
    5. `#include <cctype>` 包含字符相关的函数
        ```c++
        string s = "abcd";
        for (auto &c : s)        //c是char &, c引用s的成员
          c = toupper(c);
        cout << s << endl;       //输出ABCD
        for (auto c : s)         //c是char, s的成员赋值给c, 所以s没被改变.
          c = tolower(c);  
        cout << s << endl;       //输出ABCD
        ```
    6. 下标运算符`str[string::size_type]`也可读写str的成员.返回位置上的字符的**引用**
16. c语言标准库name.h的c++版本是cname, cname中的名字从属于std命名空间
17. vector 标准库类型
    1. `#include <vector> \n using std::vector;`
    2. `vector<T>`是一个类模板.
        ```c++
        vector<T> v1               v1是空向量,元素类型是T
        vector<T> v2(v1)           v2包含v1的所有副本
        vector<T> v2 = v1          同上
        vector<T> v3(n, val)       v3包含n个元素, 元素值是val
        vector<T> v4(n)            v4包含n个元素, 元素值是初始化值
        vector<T> v5{a,b,c...}     v5包含列表中的元素.
        vector<T> v5 = {a,b,c...}  同上
        vector<int> v1(10);        v1有10个元素,值都是0
        vector<int> v2{10};        v2有一个元素,值是10
        vector<int> v3(10, 1);     v3有10个元素,值都是1
        vector<int> v4{10, 1};     v4有两个元素,值分别是10和1
        vector<string> s1{10};     s1有10个空string
        vector<string> s2{10,"hi"} s2有10个值为"hi"的string
        ```
    3. 确认无法执行列表初始化(花括号)后,编译器会尝试用默认值初始化(圆括号)
    4. vector操作
        * `v.empty(); v.size(); v.push_back(t); v[n]; v1=v2;(v2的拷贝) v1={a,b,c..};(列表拷贝)`
        * `==;!=;<......`如预期.
    5. `v.size()`返回`vector<T>::size_type`类型, 不能用`vector::size_type`.
18. 范围for语句体内不应该该表所遍历序列的大小!
19. 标准容器迭代器
    1. v.begin(); 返回指向首元素的迭代器, 根据容器对象决定是否返回只读迭代器
    2. v.end(); 返回**尾后迭代器**, 指向最后一个元素的下一个位置, 根据容器对象决定是否返回只读迭代器
        * v.cbegin(); v.cend();返回只读迭代器.
    3. 标准容器迭代器的运算符.
        * `*iter` 所指元素的**引用**
        * `iter->mem` 所指元素的mem成员, 等价于`(*iter).mem`
        * `++iter / --iter` 指向下一个 / 上一个元素
        * `it1==it2 / it1!=it2` 
    4. 迭代器类型, 如果容器对象是一个常量, 只能使用只读迭代器
        * `vector<T>::iterator`; `string::iterator`
        * 只读迭代器: `vector<T>::const_iterator`; `string::const_iterator`
    5. 改变容器数量, 会使迭代器失效! 比如`push_back`.
    6. 迭代器加减整数(`difference_type`,带符号整型), 向前后移动; 同一容器的迭代器可以比大小.
    7. 迭代器不是指针!!!
20. 数组
    * 数组下标类型通常定义为`size_t`;位于`cstddef`中
    * `iterator`中`std::begin`和`std::end`用于获取头指针和尾指针(**数组类型** 不是 **指针类型**)
    * 两指针差类型为`ptrdiff_t`;位于`cstddef`中
    * C语言风格字符串以`\0`结尾, 操作函数多封装于`cstring`中
    * string类型提供了c_str函数用以返回字符数组指针, 返回数组可能跟随string对象改变
    * `int a[] = {1,2,3};vector<int> vi(begin(a),end(a));`用数组头尾指针初始化容器
    * 多维数组使用范围for循环时,除了最内层的循坏外,其余所有循环的控制变量都应该是引用(如果非引用, 数组类型将转换成指针类型, 从而失去维度的量)
21. 表达式
    * 当对象作为右值,使用对象的内容;当对象为左值,使用对象的身份(对象的空间)
    * 算数运算符的运算对象与求值结果都是右值
    * m,n为整数且n非零; m = (m/n)*n + m%n;
    * 自增自减运算符的后置版本除非必须,否则不用
22. sizeof运算符
    * sizeof 右结合; 返回值为size_t类型
        ```c++
        sizeof (type);
        sizeof expr;
        //expr并不计算表达式;所以在expr中解引用一个无效指针让然是一种安全的行为.
        ```
    * 对解引用指针执行sizeof运算得到指针指向的对象所占空间的大小, 指针无需有效.
    * 对数组执行sizeof运算得到整个数组所占空间的大小, 不会把数组转换成指针来处理.
    * string对象或vector对象的sizeof结果返回类型固定部分的大小, 不计算容器内元素占用的空间.
23. 类型转换
    * 隐式类型转换时机
        1. 表达式中, 小类型提升到较大类型
        2. 条件中, 非布尔转换布尔
        3. 赋值中, 右侧运算对象(也可能是初始化值)转换左值运算对象的类型
        4. 函数调用时, 也发生类型转换
    * 数组转换成指针, 当作为decltype的参数/取地址符(&)/sizeof/typeid时.数组不转换成指针.
        * 常量整数0或nullptr可以转换成任意指针类型.
        * 指向任意对象的指针能转换成const void *.
        * 指向T的指针或引用能转换成指向const T的指针或引用.
        * IO库定义了从istream向布尔值转换的规则, 即 cin 自动转换成布尔值.
    * 显式转换
        * `cast-name<type>(expression)`;type是目标类型,type是引用类型,则结果是左值;expression是被转换的值;
        * static_cast: 无法丢弃底层const (顶层const不用强转, 如数组赋值指针)
        * const_cast: 只能改变对象底层const; 不能改变对象的类型. (相当于static_cast补集)
        * reinterpret_cast: 为运算对象的位模式提供重新的解释.
        * type (expr); or (type) expr; 以上三种是这种的细化.
24. 运算符优先级表p173页
25. switch语句中case标签必须是**整型常量表达式**
26. `throw runtime_error("抛出(引发)异常");`
    * 抛出异常将种植当前的函数, 并把控制权转移给能处理该异常的代码.
    * 类型`runtime_error`是标准库异常类型; 定义在`stdexcept`头文件中.
    * 可以通过string对象或C风格字符串初始化`runtime_error`对象.
    * catch的括号内包含一个对象的声明(称作异常声明).
    * 每一个标准异常类都定义了名为what的成员函数, 无参, 返回值是`const char *`
    * 如果catch未能捕获异常, 将沿着调用顺序逆向查找.
    * 如果最终未能找到任何匹配的catch, 程序转到`terminate`的标准库函数. 该函数行为与系统有关, 一般执行该函数将导致程序非正常退出.
    * 在异常发生期间正确执行了**清理**工作的程序被称为**异常安全**(exception safe)的代码.
    * 标准库定义了一组类, 用于报告标准库函数遇到的问题. 分别定义在4个头文件中:
        * exception头文件, 最通用的异常类exception(只能默认初始化). 他只报告异常的发生
        * stdexcept头文件, 定义了几种常用的异常类(不允许用默认初始化). 详见p202
        * new头文件定义了bad_alloc(只能默认初始化)异常类型
        * type_info头文件定义了bad_cast(只能默认初始化)异常类型
27. 函数返回值不可以是数组类型或函数类型;可以是数组指针或函数指针
28. 名字有作用域(在作用域内可见);对象有声明周期(在周期内可以读写).
29. 如果形参(函数内部的)是引用, 绑定到实参(函数外部的;传递给函数的)上(引用传递,传引用调用);否则实参的值拷贝后赋值给形参(值传递,传值调用).
30. c语言中常通过指针形参访问函数外部对象;c++中建议使用引用的形参代替指针.
31. 数组不能拷贝, 数组通常会转换成指针.
    * 数组会转换成指针, 所以数组的大小对函数的调用没有影响.
    * 管理指针形参的三种方式:
        * (长度自解释)使用标记指定数组长度; c字符串就是这种方式结尾有'\0',遇到0标志着结尾.
        * (告诉开头与结尾)使用迭标注库规范(迭代器); 传递begin和end迭代器
        * (告诉数组长度)显式传递一个数组长度的形参; size_t
33. 数组引用: `f(int (&arr)[10])`; `f(int &arr[10])`意为引用的数组(10)
34. main函数
    ```c++
    int main(){;}
    int main(int argc, char* argv[]){;}
    int main(int argc, char ** argv){;}
    /*
     * ./a.out 1 2
     * argc = 3;
     * argv[0] = "./a.out";
     * argv[1] = "1";
     * argv[2] = "2";
     * argv[3] = 0;  注意! argv[3]这个指针为0;
     */
    ```
35. 含有可变参数的函数
    * 所有实参类型相同, 传递一个名为initializer_list的标准库类型.
        * initializer_list标准库类型定义在同名头文件中.
        * initializer_list对象中的元素永远是常量值, 无法改变对象中元素的值.
        ```c++
        #include <initializer_list>
        using std::initializer_list;
        initializer_list<T> lst; //默认初始化; T类型元素的空列表
        initializer_list<T> lst{a,b,c...};
        lst2(lst);lst2 = lst; //拷贝或赋值对象不会拷贝列表中元素; 拷贝后原始和副本共享元素
        lst.size();lst.begin();lst.end();
        ```
    * 实参类型不同, 可以编写特殊的函数(可变参数模板)
    * 省略符形参, 一般只用于与C函数交互的接口程序.
        * 大多数类类型对象传递给省略符形参时无法正确拷贝.
        ```c++
        #include <cstdarg>                  //头文件!
        int sum_list (int num, ...)
        {
            int sum = 0;
            va_list list;                   //头文件中定义的类型.
            va_start(list, num);            //初始化, void va_start(va_list类型变量, last_arg最后一个已知类型的固定参数)
            for (int i=0;i<num;i++) 
                sum += va_arg(list, int);   //取值, type va_arg(va_list变量, type)
            va_end(list);                   //释放.
            return sum;
        }
        ```
36. 不能返回局部变量的引用或指针; 函数返回值可以是引用值, 即函数结果是左值.
37. main函数返回值: cstdlib头文件中EXIT_FAILURE和EXIT_SUCCESS; 该值与机器无关, 且为预处理变量, 不能前加std::, 也不能在using中出现.
38. `int (*func(int i))[10];`
    1. `func(int i)`表明func是一个参数为int的函数
    2. `(* func(int i))`表明可以对函数的结果解引用
    3. `(* func(int i))[10]`表明解引用的结果是一个大小为10的数组
    4. `int (*func(int i))[10]`表明数组是int型.
    5. func的返回值是一个二级指针, 指向长度为10的数组(一级指针)
    6. 技巧就是`func(int i)`看成一个变量(调用的结果)
    * 等价于`auto func(int i) -> int(*)[10];`
    * 如果存在一个对象与函数结果一致, 可以用`int (*p)[10]; decltype(p) func(int i);`
39. 函数重载
    * 函数名相同, 形参不同. 不按返回值区分重载
    * 重载确定, 又叫函数匹配; 是编译器过程.
    * 一旦在当前作用域找到了所需名字, 就进行下一步了(就与外层作用域无关了).
40. 默认实参
    * `char * screen(size_t ht = 24, size_t wid = 80, char backgrnd = ' ');`
    * 一旦形参有默认值,其后形参必须均有. 
    * 若想使用默认实参,调用时省略就可以了. 只能按顺序省略.
    * 指定作用域下(不同作下就隐藏了外层作)一个形参只能被赋予一次默认实参. 且可以补充.
    ```c++
    int i(int a, int b, int c){return a+b+c;}
    void printi0(){cout<<i(1,2,3)<<endl;}   //输出6
    int i(int a, int b, int c=3);           //正确,添加了形参c的默认实参
    void printi1(){cout<<i(1,2)<<endl;}     //输出6
    //int i(int a=0, int, int);               //错误,形参b没有默认实参
    //int i(int, int b=2, int c=4);           //错误,不可更改形参c的默认实参
    int i(int, int b=2, int);               //正确,添加形参b的默认实参
    void printi2(){cout<<i(1)<<endl;}       //输出6
    int i(int a=1, int, int);               //正确,此时bc都有了默认实参
    void printi3(){cout<<i()<<endl;}        //输出6
    ```
    * 局部变量不能做默认实参
    * 默认实参的名字在函数声明的作用域内解析, 名字的求值发生在函数调用时.
    ```c++
    int i(int a, int b){return a+b;}
    int ib=0;
    int i(int, int b = ib);
    void f1(){
        cout<<i(1)<<endl;       //输出1
        ib=1;
        cout<<i(1)<<endl;       //输出2
        int ib = 2;
        cout<<i(1)<<endl;       //输出2, 形参b还是解析全局变量
    }
    ```
41. 内联函数关键字`inline`: 在每个调用点上内联地展开, 避免函数调用的开销.
    * 对于编译器来说内联说明只是一种建议.
42. constexpr函数指能用于常量表达式的函数,目的是: 扩展编译期间的运算能力.
    * constexpr函数**不等于**编译时求值, 只是提示编译器函数具备这样的能力.
    * constexpr关键字就是显式要求(**对象**或**如果满足两个条件的constexpr函数**)编译期求值.
    * constexpr函数默认是内联的
    * 当constexpr函数同时满足两点,才能触发编译期求值. 否则就是普通的内联函数
        * 所有参数都是常量表达式
        * 函数运算结果被用于常量表达式(比如初始化constexpr对象)
    * constexpr只可以包含运行时不执行任何操作的语句(如空语句/类型别名/using声明),否则constexpr函数就没有意义, 因为他不能用到常量表达式中(用到常量表达式中时不能编译通过).
43. 内联函数和constexpr函数通常定义于头文件中.因为编译器仅知道声明是不够的.
44. assert于NDEBUG
    * `assert(expr);`定义于cassert头文件中
    * 是预处理宏, 由预处理器管理. 因而不能使用std::assert, 也不能用using声明.
    * 当没定义NDEBUG时:expr为假时, 输出信息并终止程序;expr为真时, 什么也不做.
    * 当定义了NDEBUG时, 什么也不做.
    * `-D NDEBUG` 等价于在文件中添加 `#define NDEBUG`
    * 定义NDEBUG时不会执行检查, 也就无开销. 所以assert应用于验证确实不可能发生的事情, 不能代替真正的运行时逻辑检查, 也不能代替程序本身应该包含的错误检查.
        * 正常情况下程序不会到达的地方防止`assert(false);`
        * 可以检查私有方法的参数. (公有方法因是提供给外部使用, 所以应该由相应的参数校验才是健壮的)
        * 使用断言检查类的不变状态, 确保任何情况下某个变量的状态必须满足(如年龄的范围等,内联的getset方法?)
    * `#ifndef NDEBUG \*代码*\ #endif`
45. 编译器的魔法常量
    |变量名|内容|
    |--|--|
    |`__FILE__`|文件名-字符串字面量|
    |`__LINE__`|行号-整型字面量|
    |`__TIME__`|文件编译时间-字符串字面量|
    |`__DATE__`|文件编译日期-字符串字面量|

46. 函数匹配
    1. 选定重载函数集(候选函数);函数名相同且调用点可见
    2. 考察实参,筛选出可行函数;形参数=实参数且类型能通过转换而匹配
    3. 找出最佳匹配;最佳匹配的函数的所有参数不劣于其他可行函数且至少有一个参数优于其他可行函数(实参好于其他函数,才能匹配;否则报错)
    * 调用重载函数时不应由强制类型转换, 否则说明设计的重载函数形参不合理.
    * 最佳匹配中类型转换类型的优劣
        1. 精确匹配;类型相同/数组或函数转换成相应指针/增加或删除顶层const
        2. 通过const转换实现的匹配
        3. 通过类型提升实现的匹配
        4. 通过算数类型转换或指针转换实现的匹配
        5. 通过类类型转换实现的匹配
47. 当函数名后没括号时, 函数自动转换成指针
    * `bool func(int, double);`
    * `pf = func;`等价于`pf = &func;`/`pf(1, 3.14);`等价于`(*pf)(1, 3.14);`
    * 不能定义函数类型的形参, 但是可以定义函数类型的指针的形参
    * `void f(bool func(int, double));`等价于`void func(bool (*func)(int, double));`
    * f是函数类型`typedef bool f(int, double);`等价于`typedef decltype(func) f;`
    * f是函数指针`typedef bool (*f)(int, double);`等价于`typedef decltype(func) *f;`
    * 函数返回值是函数指针.
        ```c++
        using F=int(int*, int);
        using PF=int (*)(int*,int); //注意括号, 必须要加否则*就与前面的int结合了.
        PF f1(int);                 //正确
        F f1(int);                  //错误, 返回值不能是函数
        F *f1(int);                 //正确
        int (*f1(int))(int*,int);   //首先写函数定义, 后把函数名替换成函数
        auto f1(int) -> int(*)(int*,int);
        decltype(F) *f1(int);
        decltype(PF) f1(int);
        //使用decltype(fun)时要注意返回值时函数类型, 并非函数指针
        int f(int*, int);
        decltype(f) *f1(int);       //正确
        decltype(f) f1(int);        //错误, 返回值不能是函数
        decltype(F) *f1(int);       //错误, 不能使用类型名
        decltype(PF) f1(int);       //错误, 不能使用类型名
        ```
### 类
> 杂想: 类如果是结构体, 那么对象就是结构体变量, 成员函数就是函数指针, 构造函数就是为结构体申请内存并初始化的过程, 静态成员变量就是静态变量, 静态成员函数就是静态函数指针, 静态函数指针只能调用静态变量.

```c++
Sales_data item("100-1000-11-1");   //const char *实参的构造函数定义对象
Sales_data item();                  //声明函数
Sales_data item;                    //默认构造定义对象
```

1. 成员函数声明于类内部, 定义可以在内部(定义在内部的函数时隐式inline函数), 也可以在外部.
2. `total.isbn()`;点运算符访问成员(类似结构体访问成员);括号运算符调用函数.
3. 编译器负责把total地址传递给isbn的隐式形参this.
    * this的类型为`T * const`(常量指针/顶层const);
    * 常量对象`const T`无法传递给this, 即常量对象无法调用普通成员函数(this不具有底层const)
    * `string isbn() const {return this->bookNo};`该函数叫常量成员函数, 可被常量对象调用; 这个const可以作为重载依据
    * const标识this的类型是`const T * const`(指向常量对象的常量指针/顶层+底层const);顶层const是this本身的, 底层const是参数列表后的const带来的.
    * 重申:常量对象以及常量对象的引用或常量对象的指针, 只能调用常量成员函数!
4. 默认下, 拷贝对象其实是拷贝对象的数据成员
5. 构造函数的名与类一致, 没有返回值, 有参数列表和函数体
    * 编译器提供的合成的默认构造函数按照如下规则: 如果存在类内初始值, 则用其初始化成员; 否则, 默认初始化成员
    * 不能依赖于合成的默认构造函数:
        1. 类没有构造时, 编译器才创建合成的默认构造; 依据: 如果一个类在某种情况下需要控制对象初始化, 那么该类很可能在所有情况下都需要控制
        2. 如果类包含有**内置类型**或**复合类型**的成员, 只有当这些成员全部都被赋予了类内初始值时, 这个类才适合于使用合成的默认构造函数. 比如指针: 初值为0, 数组元素未定义等
        3. 有时编译器不能为某些类合成默认的构造函数. 比如, 类中成员的类型是无默认构造函数的类类型.
    * `T() = default;` 要求编译器生成合成默认构造函数, 可以声明于类内部(内联)或外部(非内联);
    * 构造函数初始值列表 `T(形参1, 形参2:成员1(形参1), 成员2(形参2), 成员3(常量值){}`
6. 类还有拷贝(返回值)/赋值(赋值运算)/析构(生命周期结束)等操作
7. 访问说明符; 一个类可以包含0-n个访问说明符.
    * public说明符:整个程序内可被访问
    * private说明符:
    * struct定义的类默认public; class定义的类默认private.这是他俩唯一的区别
8. frinde 友元: 可以访问类的private成员
    ```c++
    class T{
        friend void func();     //func函数可以访问T的私有部分
        friend class U;         //U的成员可以访问T的私有部分
        friend void U::funcU(); //U的funcU函数可以访问T的私有部分
    };
    ```
    * 可以把非成员函数/其他类/其他类的成员函数定义成友元
    * 友元声明的作用是影响访问权限, 其本身并非普通意义上的声明.
    * 友元函数能定义在类的内部, 该函数将是隐式内联的.
    * 友元不具有传递性, U的友元不可以访问T的私有部分. 每个类负责控制自己的友元类或友元函数.
    * U的FuncU作为T的友元需如下顺序:
        1. 定义U类, 声明FuncU函数(不能定义).
        2. 定义T类, 声明U::FuncU作为友元.
        3. 最后定义FuncU函数.
9. 类中还可以自定义某种类型再类中的别名, 同样具有访问限制`public: typedef int new_int;` 别名需先定义后使用(与普通成员不同).
10. mutalbe可以修饰类中的数据成员, 使其成为可变数据成员, 该成员永远不会成为const(不会被const保护), 即在const成员函数中也是可变的(const对象的该成员也是可变的).
11. `return * this;`将this作为左值返回(对象的引用); 可实现`对象.方法().方法()`; 一个const成员函数如果返回*this, 返回类型为常量引用(常量对象引用).
12. 类类型
    ```c++
    Sales_data item1;
    class Sales_data item1;
    struct Sales_data item1;    //三个语句等价
    ```
    * `class Screen;`类的声明(称作前置声明); 在声明之后到定义之前是一个**不完全类型**, 不完全类型只能在有限的情境下使用:
        1. 定义指向这种类型的指针或引用.
        2. 声明(非定义!)以不完全类型作为参数或者返回类型的函数
13. 类具有作用域, 在类作用域外, 成员变量和成员方法只能由对象/引用/指针来访问; 类类型成员使用作用域运算符访问.
    * 编译器处理完类中所有声明后才会处理成员函数的定义.
    * 成员函数中名字的查找:1.临时变量;2.类成员;3.从函数定义开始往前找
    * 类的成员可能被隐藏, 但是可以通过`类名::名`或`this->名`来访问.
    * 类外作用域名字可能被类成员或类函数的临时变量隐藏, 可以通过`::名`来访问
14. 如果成员是const/引用或者某种未提供默认构造函数的类类型, 必须通过构造函数初始值列表为这些成员提供初值.
15. 成员初始化顺序与类定义中出现顺序一致.
    ```c++
    class X {
        int i;
        int j;
        public:
            X(int val): j(val), i(j){}  //i结果未定义.
    };
    ```
    * 部分编译器具备, 构造函数初始值列表中顺序与声明顺序不一致时发出警告
    * 尽量保持顺序一致, 且尽量避免使用成员初始化其他成员.
16. 如果一个构造函数为所有参数都提供了默认实参, 则他实际上也定义了默认构造函数
17. 委托构造函数`类名(参数列表):类名(参数列表){}`
18. 如果构造函数只定义了一个实参, 则这个构造函数可以当作实参自动转换成对象的规则; 自动转换只允许一步的类类型转换;
    * 构造函数声明为`explicit`可以抑制构造函数成为自动转换规则; 
    * explicit只对一个实参的构造函数有效(多实参不能用于执行隐式转换);
    * 只能在类内声明构造函数时使用explicit, 类外不应重复.
    * explicit构造函数可以通过`static_cast<Sales_data>(实参)`来强制自动转换
19. 聚合类: 就是c中的结构体; 所有成员都是public; 无构造函数; 无类内初始值; 无基类; 无virtual函数.
    ```c++
    struct Data {
        int ival; string s;
    };
    Data val = {0, "Anna"};
    val.ival = 1; val.s = string ("啦啦啦");
    ```
20. 字面值常量类. ***7.5.6章! 没读懂***
    > 字面值常量类: 应该是用编译器已知的方式初始化类得到字面值常量类, 编译期就求得该类, 并对该类的使用均由字面值常量替换.
    * 如果聚合类的数据成员都是字面值类型, 就是字面值常量类.
    * 如果符合如下, 也是字面值常量类.
        1. 数据成员都是字面值类型; 
        2. 类至少含有一个constexpr构造函数;
        3. 如果数据成员有类内初始值, 该初始值必须是常量表达式; 如果有类成员, 初始值必须使用成员类型自己的constexpr构造函数.
        4. 类不许使用析构函数的默认定义, 该成员负责销毁类的对象
21. static修饰的成员(称为静态成员)与类关联起来, 与对象无关, 也具有访问控制.
    * 使用`T::成员`直接访问静态成员
    * static 与 explicit一样只能类内使用, 类外定义不可用.















p232

带看问题:
1. 7中2项,P72,引用的类型与绑定的对象严格匹配的两种例外情况! 2.4.1p55,15.2.3p534
2. P73,指针的类型与所指向的对象严格匹配的两种例外情况! 2.4.2p56,152.2.3p534
3. p125,19中5项,改变容器数量,迭代器失效的原因.9.3.6p315
4. p202,26项,bad_alloc异常类型12.1.2p407与bad_cast异常类型19.2p731
5. p223,35项2条, 可变参数模板16.4p618

core dump核心转储, 当程序发生异常退出时, 由操作系统保存现场到一个core文件中.
ulimit -c unlimited设置core文件大小为无限大. 默认为0即不保存现场.
g++ -O0 -g hello.cc -o hello以不优化与添加debug信息的方式编译hello.cc
gdb -tui hello以TUI模式运行GDB, 分为两个窗口(一用于令GDB,二用于观源码)

类的基本思想是数据抽象和封装
    数据抽象依赖于接口和实现分离的设计技术
        接口:用户所能执行的操作
        实现:类的数据成员/负责接口实现的函数体
    封装实现了类的接口与实现的分离, 隐藏类的实现细节, 只能通过接口操作

字符串字面量是`const char []`类型.const作用在a[]上,即底层const!