#include <Node/Action/action_manager.h>
#include <algorithm>
#include <Node/node.h>
namespace Node
{
namespace Action
{
void action_manager::add_action( hardptr<action> act, hardptr<node> target )
{
    act->set_target( target );
    _actions.emplace_back( act );
}
softptr<action> action_manager::get_action_by_name( std::string const & name ) const
{
    // assert_log( !name.empty( ), "[action]�����Ȗ��O�ł��B", return nullptr );

    std::hash<std::string> h;
    size_t hash = h( name );

    auto itr = std::find_if( std::cbegin( _actions ), std::cend( _actions ), [ this, hash, name ] ( hardptr<action> const& act )
    {
        return act->_hash == hash && act->_name.compare( name ) == 0;
    } );

    if ( itr != std::cend( _actions ) )
    {
        return *itr;
    }
    return nullptr;
}
softptr<action> action_manager::get_action_by_tag( int tag ) const
{
    // assert_log( tag == node::INVALID_TAG, "[action]�����ȃ^�O�ł��B", return nullptr );

    auto itr = std::find_if( std::cbegin( _actions ), std::cend( _actions ), [ this, tag ] ( hardptr<action> const& act )
    {
        return act->_tag == tag;
    } );

    if ( itr != std::cend( _actions ) )
    {
        return *itr;
    }
    return nullptr;
}
void action_manager::remove_all_actions( )
{
    _actions.clear( );
}
void action_manager::remove_action( softptr<action> remove_act )
{
    if ( _actions.empty( ) ) return;
    auto erase_itr = std::remove_if( std::begin( _actions ), std::end( _actions ), [ this, remove_act ] ( hardptr<action>& act )
    {
        return act == remove_act;
    } );
    // action_manager��erase��for���̒��ŌĂ΂�Ȃ����Ƃ��ۏ؂���Ă��܂��B
    _actions.erase( erase_itr, std::end( _actions ) );
}
void action_manager::remove_action_by_tag( int tag )
{
    // assert_log( tag == node::INVALID_TAG, "[action]�����ȃ^�O�ł��B", return );
    if ( auto act = this->get_action_by_tag( tag ) )
    {
        remove_action( act );
    }
    else
    {
        // log( "[action]remove_action_by_tag( \"%d\" ): �q����������܂���ł����B", tag );
    }
}
void action_manager::remove_action_by_name( std::string const & name )
{
    // assert_log( !name.empty( ), "[action]�����Ȗ��O�ł��B", return );
    if ( auto act = this->get_action_by_name( name ) )
    {
        remove_action( act );
    }
    else
    {
        // log( "[action]remove_action_by_name( \"%s\" ): �q����������܂���ł����B", name.c_str( ) );
    }
}
bool action_manager::is_running( ) const
{
    return !_actions.empty( );
}
void action_manager::update( float delta )
{
    for ( auto& act : _actions )
    {
        // manager�܂ň��Ă���l�͖������܂��Bdelay::create(0.0F)�Ƃ��������疳�����[�v�ɓ���̂ŁB
        act->update( delta );
    }
    auto erase = std::remove_if( std::begin( _actions ), std::end( _actions ), [ ] ( hardptr<action>& act )
    {
        return act->is_done( );
    } );
    _actions.erase( erase, std::end( _actions ) );
}
}
}