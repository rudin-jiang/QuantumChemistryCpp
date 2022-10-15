# nhfstr

The nhfstr is a submodule of nhf. The functions in nhfstr are in the namespace `nhfStr`.

## Functions

* `void remove_comment(std::string &line)`
在进行计算时，程序依赖一些文件，例如输入文件以及基组文件。在这些文件中，我们将 `!` 后面的内容认定为注释，程序会忽略掉后面的内容。`remove_comment` 函数的功能就是将一个 `std::string` 中，从前往后找到第一个 `!`，将 `!` 以及后面的内容丢弃掉。 

* `void remove_head_space(std::string &line)`
[whitespace](https://en.cppreference.com/w/c/comment)
这个函数删除一个字符串开头的所有白空格。

* `void remove_tail_space(std::string &line)`
[whitespace](https://en.cppreference.com/w/c/comment)
这个函数删除一个字符串末尾的所有白空格。

* `void remove_dual_space(std::string &line)`
[whitespace](https://en.cppreference.com/w/c/comment)
这个函数删除一个字符串开头和结尾的所有白空格。

* `void str_upper(std::string &line)`

* `void str_lower(std::string &line)`

* `void str_change(std::string &line, char pre, char aft)`

* `std::vector<std::string> split_string(const std::string &line, const std::string & delimitor)`


