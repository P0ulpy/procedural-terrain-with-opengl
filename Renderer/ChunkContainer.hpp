//
// Created by Flo on 29/04/2023.
//

#pragma once

#include <map>
#include "Chunk.hpp"
#include "Math/Point.hpp"

struct ChunkContainer
{
    using ChunkContainerIndex = std::pair<int32_t, int32_t>;

    static ChunkContainerIndex GetChunkIndex(float playerX, float playerZ);

    Chunk& GetPlayerChunk(float playerX, float playerZ);

    void FreeChunk(int32_t x, int32_t z);
    void FreeChunks();
    Chunk& operator()(int32_t x, int32_t z);
    const Chunk& operator()(int32_t x, int32_t z) const;

    [[nodiscard]] std::vector<Chunk*>& GetActiveChunks() { return m_activeChunks; }
    [[nodiscard]] std::map<ChunkContainerIndex, Chunk>& GetData() { return m_data; }

    std::vector<Chunk*> m_activeChunks;
private:
    
    std::map<ChunkContainerIndex, Chunk> m_data;
};
