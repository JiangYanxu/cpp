## IO库
### 基础章已用到的:
1. istream输入流类型; ostream输出流类型
2. cin标准输入的istream; cout标准输出ostream; cerr标准错误ostream
3. `>>`/`<<`输入(空白/换行/制表符分割)/输出运算符
4. `getline(cin, string)`函数, 从istream中读取一行(包括换行)到string(去除换行)中.

1. IO类
    * iostream 头文件
        * istream, wistream 读取流
        * ostream, wostream 写入流
        * iostream, wiostream 读写流
    * fstream 头文件
        * ifstream, wifstream 文件读取流
        * ofstream, wofstream 文件写入流
        * fstream, wfstream 文件读写流
    * sstream 头文件
        * istringstream, wistringstream 字符串读取流
        * ostringstream, wostringstream 字符串写入流
        * stringstream, wstringstream 读写字符串流
    * w开头为wchar_t宽字符版本的类型的函数.
    * ifstream/istringstream继承于istream等
2. IO对象不能拷贝(即无法作为形参和返回值)或赋值
3. 读写IO对象会改变其状态, 传递和返回的引用不能是const的.
4. IO条件状态: 流的状态.
    * `IO类::iostate`机器相关的类型, 条件状态的位集合.
    * iostate类型的静态常量对象(相当于掩码):
        * `IO类::badbit`流的崩溃状态(0x1)
            * 通常其置位, 代表流无法再使用了
        * `IO类::failbit`流的操作失败(0x2)
            * 发生可恢复错误时(流还可以在使用), 该位被置位
        * `IO类::eofbit`流到达了文件结束(0x4)
            * 如果文件结束, eofbit与failbit都被置位
        * `IO类::goodbit`流未处于错误状态(0x0)
    * `s.eof();s.fail();s.bad();s.good();`分别获取对应状态; 当badbit被置位时, s.fail()也返回true.
    * `!s.fail()` 等价于 `s.good()`;因为到达结束eofbit与failbit同时置位, bedbit置位时s.fail()仍然是true.
    * s.clear()清除全部状态; s.clear(flags)清除(置0)flags位置(使用按位反的常量对象)的状态, 例: `cin.clear(cin.rdstate() & ~cin.failbit & ~cin.badbit)`
    * s.setstate(flags)根据给定的flags(iostate类型)设置对象的状态.
    * s.rdstate()返回流的当前条件状态, 返回值类型iostate
    * 只有流s.good()==goodbit时, 才可以读或写.
    * if(cin) 应该等价于 if(cin.good())
5. 每个输出流都管理一个缓存区, 用来保存程序读写的数据.
    * 在缓冲机制中, 输出操作可能不会立即显示, 发生缓冲刷新才会显示; 目的是减少io次数提升性能.
    * 导致缓冲刷新的原因:
        * main函数返回会刷新
        * 缓冲区满会刷新.
        * std::endl显式刷新
        * 缓冲区大小为空(无缓冲区,立即刷新); cerr默认是立即刷新的
        * 流A关联流B, 读或写流A会刷新流B的缓冲区; 保证对流A的读写时,流B是最新的;
    * endl输出`换行`并刷新;ends输出`\0`并刷新;flush直接刷新
    * `cout << unitbuf`设置无缓冲区立即刷新; nounitbuf回到默认.
    * 程序崩溃时, 输出缓冲区中可能有数据未被刷新;
6. 流的关联
    * A.tie()返回A关联的输出流的指针
    * A.tie(&B)将A关联到输出流B; B必须是输出流
    * 当A关联B时, 对A操作之前会先刷新B.
    * 每个流最多关联到一个流; 多个流可以关联到同一个ostream
    * 关联和什么的流/谁的流无关; A关联B, 只是在操作A之前刷新B, 和操作内容操作对象无关(不是A关联B,写A同时写B).
7. fstream特有的操作
    * `fstream fstrm;`创建未绑定的文件流
    * `fstream fstrm(s);`创建绑定到名为s(字符串或string)的文件的文件流, 该构造是explicit的
    * `fstream fstrm(s, mode);`按指定mode打开文件
    * `fstrm.open(s[, mode]);` 调用失败failbit会被置位, open后检查是个好习惯; open已打开的文件流会导致failbit置位, 之后使用文件流都会失败;
    * `fstrm.close();` 已打开的文件流, 先close才能再open; 当fstream对象被销毁时(生命周期结束自动析构), close会自动调用
    * `fstrm.is_open();`
8. 文件流的文件模式
    * 文件模式类型为openmode; 位的集合
    * 静态常量:
        * `in`读, ofstream不可;
        * `out`写, ifstream不可, 默认trunc;
        * `app`每次写定位到文件末尾, trunc与app互斥, 只置位app时隐式以out打开;
        * `ate`打开文件后定义到文件末尾, 可以组合任意模式;
        * `trunc`截断文件;
        * `binary`以二进制方式进行IO, 可以组合任意模式;
    * 每个文件流都有缺省的文件模式; 
9. string流特有操作
    * `sstream strm;` 创建未绑定的stringstream对象
    * `sstream strm(s);` 创建sstream对象, 保存string s的一个拷贝
    * `strm.str()` 返回strm所保存的string的拷贝
    * `strm.str(s)` 将string s拷贝到strm中, 返回void
10. ostringstream有点类似于字符串构建者, 持续的写入string, 然后返回拼接的string


    
## 没学明白的点
1. 8.1.3p307关联流
2. p314 info的声明周期

## 概念
* 继承机制: 一个类继承自另一个类, 可以将派生类(继承类)对象当作其基类(被继承的类)对象来使用