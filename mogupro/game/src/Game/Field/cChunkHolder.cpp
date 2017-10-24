#include <Game/Field/cChunkHolder.h>
#include <Game/Field/cUnderGround.h>
#include <Game/Field/cChunkMeshBuilder.h>
#include <Utility/cString.h>

using namespace ci;
namespace Game
{
namespace Field
{
cChunkHolder::cChunkHolder( cUnderGround* under_ground ) :
    mUnderGround( under_ground )
{
}

cChunkHolder::~cChunkHolder()
{

}

cChunk & cChunkHolder::getChunk( const int& x, const int& z )
{
    return getChunk( ci::ivec3( x, 0, z ) );
}

cChunk & cChunkHolder::getChunk( const ci::ivec3& c )
{
    return mChunks.at( c );
}

ChunkMap& cChunkHolder::getChunks()
{
    return mChunks;
}

void cChunkHolder::setChunk( cChunk&  chunk )
{
    auto cell = chunk.getCell();
    mChunks[cell] = chunk;
}

void cChunkHolder::setChunk( const int& x, const int& y, const int& z )
{
    if ( isExistsChunk( x, y, z ) == false )
        return;
    auto chunk = cChunk( x, z, mUnderGround );
    mChunks[ivec3( x, y, z )] = chunk;
}

bool cChunkHolder::createChunk( cChunk& chunk )
{
    if ( chunk.mIsLoaded )
        return false;
    chunk.mIsLoaded = true;

    chunk.createBlocks();
    chunk.buildMesh();
    return chunk.mIsDone = true;
}

bool cChunkHolder::isExistsChunk( const int& x, const int& y, const int& z )
{
    return mChunks.find( ivec3( x, y, z ) ) == mChunks.end();
}
bool cChunkHolder::cellIsOutOfBounds( const int & x, const int & y, const int & z )
{
    if ( x >= CHUNK_SIZE || y >= CHUNK_SIZE || z >= CHUNK_SIZE )
        return true;
    if ( x < 0 || y < 0 || z < 0 )
        return true;
    return false;
}
void cChunkHolder::clear()
{
    mChunks.clear();
}
}
}
