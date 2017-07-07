// Copyright
#ifndef SRC_CPP_TESTHARNESS_H_
#define SRC_CPP_TESTHARNESS_H_

#include <sstream>

namespace experi {
namespace test {
extern int RunAllTests();
class Tester {
 private:
        bool ok_;
        const char* fname_;
        int line_;
        std::stringstream ss_;

 public:
        Tester(const char* f, int l)
            : ok_(true), fname_(f), line_(l) {
            }

        ~Tester() {
            if (!ok_) {
                fprintf(stderr, "%s:%d:%s\n", fname_, line_, ss_.str().c_str());
            }
        }

        Tester& Is(bool b, const char* msg) {
            if (!b) {
                ss_ << " Assertion failure " << msg;
                ok_ = false;
            }

            return *this;
        }

#define BINARY_OP(name, op)                                      \
        template <class X, class Y>                              \
        Tester& name(const X& x, const Y& y) {                   \
            if (!(x op y)) {                                     \
                ss_ << " failed: " << x << (" " #op " ") << y;   \
                ok_ = false;                                     \
            }                                                    \
            return *this;                                        \
        }

        BINARY_OP(IsEq, ==)
        BINARY_OP(isNe, !=)
        BINARY_OP(isGe, >=)
        BINARY_OP(isGt, >)
        BINARY_OP(isLe, <=)
        BINARY_OP(isLt, <)
#undef BINARY_OP

        template <class V>
        Tester& operator<<(const V& value) {
            if (!ok_) {
                ss_ << " " << value;
            }

            return *this;
        }
};
}  // namespace test
}  // namespace experi


#endif  // SRC_CPP_TESTHARNESS_H_
