#include <Game/Field/cBreakBlockType.h>
namespace Game
{
namespace Field
{
cBreakBlockType::cBreakBlockType( const Network::ubyte1 & type )
{
    for ( int i = 0; i < 8; i++ )
    {
        auto k = 1 << i;
        if ( type & k == 1 )
        {
            add( (BlockType) k );
        }
    }
}
cBreakBlockType::cBreakBlockType( const BlockType & type )
{
    add( type );
}
cBreakBlockType::cBreakBlockType()
{
    add( BlockType::NORMAL );
}
cBreakBlockType::~cBreakBlockType()
{

}
void cBreakBlockType::add( const BlockType & type )
{
    mType.emplace( type );
}
bool cBreakBlockType::find( const BlockType & type ) const
{
    return mType.find( type ) != mType.end();
}
void cBreakBlockType::erase( const BlockType & type )
{
    if ( find( type ) )
        mType.erase( type );
}
}
}
