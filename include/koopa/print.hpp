#ifndef _KOOPA_PRINT_HPP
#define _KOOPA_PRINT_HPP
template <typename T>
void Out(T&& arg) {
    std::cout << arg; 
}
template <typename T, typename ...Arg>
void Out(T&& arg,  Arg&& ...args) {
    std::cout << arg; 
    Out(std::forward<Arg>(args)...);
}
template <typename T>
void OutSpace(T&& arg) {
    std::cout << arg << '\n';
}
template <typename T, typename ...Arg>
void OutSpace(T&& arg,  Arg&& ...args) {
    std::cout << arg << ", "; 
    OutSpace(std::forward<Arg>(args)...);
}
template <typename T = const char*, typename ...Arg>
void OutSpace(const char* op, Arg&& ...args) {
    std::cout << "    " << op << ' ';
    OutSpace(std::forward<Arg>(args)...);
}
template <typename ...Arg>
void Line(Arg&& ...args) {
    Out("    ", std::forward<Arg>(args)...);
    Out('\n');
}

template <typename ...Arg>
void FrontLine(Arg&& ...args) {
    Out(std::forward<Arg>(args)...);
    Out('\n');
}

#endif