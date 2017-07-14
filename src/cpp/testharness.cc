// CopyRight
#include "cpp/testharness.h"
#include <sys/stat.h>
#include <sys/types.h>

#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <vector>

namespace experi {
namespace test {

namespace {
struct Test {
    const char* base;
    const char* name;
    void (*func)();
};
std::vector<Test>* tests;
}

bool RegisterTest(const char* base, const char* name, void (*func)()) {
    if (tests == nullptr) {
        tests = new std::vector<Test>;
    }

    Test t;
    t.base = base;
    t.name = name;
    t.func = func;
    tests->push_back(t);
    return true;
}

int RunAllTests() {
    const char* matcher = getenv("TESTS");

    int num = 0;
    if (tests != nullptr) {
        for (size_t i = 0; i < tests->size(); i++) {
            const Test& t = (*tests)[i];
            if (matcher != nullptr) {
                std::string name = t.base;
                name.push_back('.');
                name.append(t.name);
                if (std::strstr(name.c_str(), matcher) == nullptr) {
                    continue;
                }
            }

            fprintf(stderr, "=== Test %s.%s\n", t.base, t.name);
            (*t.func)();
            ++num;
        }
    }
    fprintf(stderr, "=== PASSED %d tests\n", num);
}

}  // namespace test
}  // namespace experi
