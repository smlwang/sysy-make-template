#ifndef _KOOPA_FMT_PRINT_HPP
#define _KOOPA_FMT_PRINT_HPP
#include <iostream>
#include <memory>
template <typename T> void Out(T &&arg) { std::cout << arg; }
template <typename T> void Out(std::unique_ptr<std::string> &&arg) {
    std::cout << *arg;
}
template <typename T, typename... Arg> void Out(T &&arg, Arg &&...args) {
    Out(arg);
    Out(std::forward<Arg>(args)...);
}
template <typename T> void LabelOut(T &&arg) { std::cout << arg << ":\n"; }

template <typename T> void BinaryOut(T &&arg) { std::cout << arg << '\n'; }
template <typename T, typename... Arg> void BinaryOut(T &&arg, Arg &&...args) {
    std::cout << arg << ", ";
    BinaryOut(std::forward<Arg>(args)...);
}
template <typename T = const char *, typename... Arg>
void BinaryOut(const char *op, Arg &&...args) {
    std::cout << "    " << op << ' ';
    BinaryOut(std::forward<Arg>(args)...);
}

template <typename... Arg> void Line(Arg &&...args) {
    Out(std::forward<Arg>(args)...);
    Out('\n');
}

// 程序正文
template <typename... Arg> void TextLine(Arg &&...args) {
    std::cout << "    ";
    Out(std::forward<Arg>(args)...);
    std::cout << std::endl;
}

template <typename... Arg> void TextOut(Arg &&...args) {
    std::cout << "    ";
    Out(std::forward<Arg>(args)...);
}
#endif