#pragma once

#include <map>

#include <Renderer/Renderable/Terrain/Chunk.hpp>
#include <Renderer/Math/Point.hpp>

struct ChunkContainer
{
    using Index = std::pair<int32_t, int32_t>;

    static Index GetChunkIndex(float playerX, float playerZ);

    Chunk& GetPlayerChunk(float playerX, float playerZ);

    void FreeChunk(int32_t x, int32_t z);
    void FreeChunks();

    Chunk& operator()(int32_t x, int32_t z);
    const Chunk& operator()(int32_t x, int32_t z) const;

    [[nodiscard]] std::vector<Chunk*>& GetActiveChunks() { return m_activeChunks; }
    [[nodiscard]] const std::vector<Chunk*>& GetActiveChunks() const { return m_activeChunks; }
    [[nodiscard]] std::map<Index, Chunk>& GetData() { return m_data; }

private:
    std::map<Index, Chunk> m_data;
    std::vector<Chunk*> m_activeChunks;
};
