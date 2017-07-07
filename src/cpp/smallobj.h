// Copyright
#ifndef SRC_CPP_SMALLOBJ_H_
#define SRC_CPP_SMALLOBJ_H_

#include<cstddef>

namespace experi {
struct Chunk {
    void Init(std::size_t block_size, unsigned char block_count);
    void Release();
    void *Allocate(std::size_t block_size);
    void Deallocate(void *p, std::size_t block_size);
    unsigned char first_available_block_, blocks_available_;
    void *data_;
};
class SmallObject {
 public:
        virtual ~SmallObject(){}
};
}  // namespace experi

#endif  // SRC_CPP_SMALLOBJ_H_
