#ifndef _KOOPA_REGISTER_HPP
#define _KOOPA_REGISTER_HPP
#include <string>
#include <vector>
class TempRegister
{
private:
    const std::vector<std::string> _t_register = {
        "t0", "t1",
        "t2", "t3",
        "t4", "t5",
        "t6", "a0",
        "a1", "a2",
        "a3", "a4",
        "a5", "a6",
    };

    size_t _index = -1;

public:
    const std::string apply()
    {
        _index += 1;
        if (_index == _t_register.size())
            _index = 0;
        return _t_register[_index];
    }
};
#endif