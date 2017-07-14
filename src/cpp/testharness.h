// Copyright
#ifndef SRC_CPP_TESTHARNESS_H_
#define SRC_CPP_TESTHARNESS_H_

#include <sstream>

namespace experi {
namespace test {
extern int RunAllTests();
class Tester {
 protected:
     int a;

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
        BINARY_OP(IsNe, !=)
        BINARY_OP(IsGe, >=)
        BINARY_OP(IsGt, >)
        BINARY_OP(IsLe, <=)
        BINARY_OP(IsLt, <)
#undef BINARY_OP

        template <class V>
        Tester& operator<<(const V& value) {
            if (!ok_) {
                ss_ << " " << value;
            }

            return *this;
        }
};

#define PREFIX_OBJ(e) ::experi::test::Tester(__FILE__, __LINE__)##e
#define ASSERT_TRUE(c) PREFIX_OBJ(.Is((c), #c))
#define ASSERT_EQ(a, b) PREFIX_OBJ(.IsEq((a), (b)))
#define ASSERT_NE(a, b) PREFIX_OBJ(.IsNe((a), (b)))
#define ASSERT_GE(a, b) PREFIX_OBJ(.IsGe((a), (b)))
#define ASSERT_GT(a, b) PREFIX_OBJ(.IsGt((a), (b)))
#define ASSERT_LE(a, b) PREFIX_OBJ(.IsLe((a), (b)))
#define ASSERT_LT(a, b) PREFIX_OBJ(.IsLt((a), (b)))

#define TCONCAT(a, b) TCONCAT1(a, b)
#define TCONCAT1(a, b) a##b

#define TEST(base, name)                                                 \
    class TCONCAT(_Test_, name): public base {                           \
     public:                                                             \
         void _Run();                                                    \
         static void _RunIt() {                                          \
             TCONCAT(_Test_, name) t;                                    \
             t._Run();                                                   \
         }                                                               \
    };                                                                   \
bool TCONCAT(_Test_ignored_, name) =                                     \
::experi::test::RegisterTest(#b, #name, &TCONCAT(_Test_, name)::_RunIt); \
void TCONCAT(_Test_, name)::_Run();

extern bool RegisterTest(const char* base, const char* name, void (*func)());
}  // namespace test
}  // namespace experi


#endif  // SRC_CPP_TESTHARNESS_H_
