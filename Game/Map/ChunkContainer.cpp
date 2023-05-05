//
// Created by Flo on 02/05/2023.
//

#include "ChunkContainer.hpp"

Chunk& ChunkContainer::operator()(int32_t x, int32_t z)
{
    auto index = std::make_pair(x, z);
    return m_data[index];
}

const Chunk& ChunkContainer::operator()(int32_t x, int32_t z) const
{
    auto index = std::make_pair(x, z);
    return m_data.at(index);
}

void ChunkContainer::FreeChunks()
{
    m_activeChunks.clear();
    m_data.clear();
}

void ChunkContainer::FreeChunk(int32_t x, int32_t z)
{
    auto index = std::make_pair(x, z);
    m_data.erase(index);
}

Chunk &ChunkContainer::GetPlayerChunk(float playerX, float playerZ)
{
    auto chunkX = static_cast<int32_t>(playerX / Chunk::SIZE);
    auto chunkZ = static_cast<int32_t>(playerZ / Chunk::SIZE);

    return (*this)(chunkX, chunkZ);
}

ChunkContainer::ChunkContainerIndex ChunkContainer::GetChunkIndex(float playerX, float playerZ)
{
    return {
        static_cast<int32_t>(std::floor((playerX + Chunk::SIZE / 2) / (float)Chunk::SIZE)),
        static_cast<int32_t>(std::floor((playerZ + Chunk::SIZE / 2) / (float)Chunk::SIZE))
    };
}
