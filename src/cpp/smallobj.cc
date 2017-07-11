#include "smallobj.h"

namespace experi {

void Chunk::Init(std::size_t block_size, unsigned char block_count) {
    data_ = new unsigned char[block_count * block_size];
    first_available_block_ = 0;
    blocks_available_ = block_count;

    auto p = static_cast<unsigned char *>(data_);
    unsigned char i = 0;
    for (; i < block_count; p += block_size) {
        *p = ++i;
    }
}

void* Chunk::Allocate(std::size_t block_size) {
    if (blocks_available_ == 0) {
        return NULL;
    }

    --blocks_available_;

    auto ret = static_cast<unsigned char *>(data_) + first_available_block_ * block_size;
    first_available_block_ = *ret;

    return ret;
}

void Chunk::Deallocate(void *p, std::size_t block_size) {
    auto d = static_cast<unsigned char *>(p);
    *d = first_available_block_;

    first_available_block_ = static_cast<unsigned char>(
            static_cast<std::size_t>(d - static_cast<unsigned char *>(data_)) / block_size);
    ++blocks_available_;
}

} // namespace experi
