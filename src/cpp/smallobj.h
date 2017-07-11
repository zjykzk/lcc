#ifndef CPP_SMALL_OBJ_H_
#define CPP_SMALL_OBJ_H_

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
} // experi

#endif /* ifndef CPP_SMALL_OBJ_H_ */
