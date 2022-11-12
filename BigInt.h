#ifndef BIGINT_BIGINT_H
#define BIGINT_BIGINT_H

#include <deque>
#include <string>
#include <cstdint>
#include <algorithm>
#include <iostream>

using namespace std;

class BigInt {
    typedef deque<uint8_t> BigInt_t;
public:
    BigInt() {}

    BigInt(const string &src) { init(src); }

    BigInt(const char *src) { init(string(src)); }

    template<typename Tp>
    BigInt(const Tp &src) { init(std::to_string(src)); }

    template<typename Tp>
    BigInt operator+(const Tp &src) { return this->template add(src); };

    template<typename Tp>
    BigInt add(const Tp &src);

    template<typename Tp>
    bool operator==(const Tp &src) { return this->equal(src); };

    template<typename Tp>
    bool equal(const Tp &src);

    string to_string() const;

    ~BigInt() = default;

private:
    BigInt_t value;

    void init(const string &src);

};

void BigInt::init(const string &src) {
    string _ = src;
    size_t len = 0;

    for (size_t i = 0; i < _.size(); i++, len++)
        if (isdigit(_[i]) and _[i] > '0') {
            len = _.size() - len;
            break;
        }

    if (len % 2 == 1)
        _.insert(0, "0");

    for (size_t i = _.size(); i != 0; i -= 2) {
        this->value.emplace_front((uint8_t) ((_[i - 2] - '0') * 10 + (_[i - 1] - '0')));
    }
}

template<typename Tp>
BigInt BigInt::add(const Tp &src) {
    BigInt tp = src, out;

    BigInt_t *big, *little;
    if (this->value.size() > tp.value.size())
        big = &this->value, little = &tp.value;
    else
        big = &tp.value, little = &this->value;

    for (int i = 0; i < big->size() - little->size(); ++i)
        little->template emplace_front(0);

    uint8_t _carry = 0;

    for (auto _1 = this->value.rbegin(), _2 = tp.value.rbegin();
         _1 != this->value.rend() or _2 != tp.value.rend();
         _1++, _2++) {
        uint8_t _ = *_1 + *_2 + _carry;
        _carry = _ / 100;
        out.value.template emplace_front(_ % 100);

    }
    if (_carry > 0)out.value.template emplace_front(_carry);

    return out;
}

string BigInt::to_string() const {
    string out;
    for (auto &i: this->value) {
        string _(2, ' ');
        sprintf((char *) _.c_str(), "%02d", i);
        out += _;
    }
    if (out[0] == '0')out.erase(0, 1);
    return out;
}

template<typename Tp>
bool BigInt::equal(const Tp &src) {
    BigInt _ = src;
    return std::equal(_.value.cbegin(), _.value.cend(), this->value.begin(), this->value.end());
}


#endif //BIGINT_BIGINT_H
