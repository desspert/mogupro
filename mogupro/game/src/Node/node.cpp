#include <Node/node.h>
#include <cinder/gl/gl.h>
#include <limits>
#include <Utility/MessageBox.h>
namespace Node
{
using namespace cinder;
const int node::INVALID_TAG = -std::numeric_limits<int>::max( );
const char node::iteration::RUNNING = 1 << 1;
const char node::iteration::INCREMENT = ( node::iteration::RUNNING | 0 << 2 );
const char node::iteration::DECREMENT = ( node::iteration::RUNNING | 1 << 2 );
CREATE_CPP( node )
{
    CREATE( node );
}
node::~node( )
{
    if ( !_name.empty( ) )
    {
        if ( _tag == node::INVALID_TAG )
        {
            // log( "[node]~node: name[%s] tag[node::INVALID_TAG]", _name.c_str( ) );
        }
        else
        {
            // log( "[node]~node: name[%s] tag[%d]", _name.c_str( ), _tag );
        }
    }
}
bool node::entry_mouse_began( cinder::app::MouseEvent event )
{
    if ( !_block_schedule_event )
    {
        iteration it( *this );
		it.decrement();

        for ( _riterator = (int)_children.size( ) - 1; _riterator >= 0; --_riterator )
        {
            try
            {
                // �q�������[�_���I�u�W�F�N�g�������ꍇ
                if ( _children[_riterator]->entry_mouse_began( event ) )
                {
                    return true;
                }
            }
            catch ( exception_node_remove_self const& e )
            {
                /*MES_ERR( e.what( ),
                         [ ] { } );*/
            }
        }

		it.reset();
    }
    if ( _schedule_mouse_event )
    {
        if ( mouse_began( event ) )
        {
            _swallow = true;
            return true;
        }
    }
    return false;
}
bool node::entry_mouse_moved( cinder::app::MouseEvent event )
{
    if ( !_block_schedule_event )
    {
		iteration it(*this);
		it.decrement();

        for ( _riterator = (int)_children.size( ) - 1; _riterator >= 0; --_riterator )
        {
            try
            {
                if ( _children[_riterator]->entry_mouse_moved( event ) )
                {
                    return true;
                }
            }
            catch ( exception_node_remove_self const& e )
            {
                /*MES_ERR( e.what( ),
                         [ ] { } );*/
            }
        }

		it.reset();
    }
    if ( _schedule_mouse_event )
    {
        if ( _swallow )
        {
            mouse_moved( event );
            return true;
        }
    }
    return false;
}
bool node::entry_mouse_ended( cinder::app::MouseEvent event )
{
    if ( !_block_schedule_event )
    {
        iteration it(*this);
		it.decrement();

        for ( _riterator = (int)_children.size( ) - 1; _riterator >= 0; --_riterator )
        {
            try
            {
                if ( _children[_riterator]->entry_mouse_ended( event ) )
                {
                    return true;
                }
            }
            catch ( exception_node_remove_self const& e )
            {
               /* MES_ERR( e.what( ),
                         [ ] { } );*/
            }
        }

		it.reset();
    }
    if ( _schedule_mouse_event )
    {
        if ( _swallow )
        {
            mouse_ended( event );
            _swallow = false;
            return true;
        }
    }
    return false;
}
bool node::entry_touch_began( cinder::app::TouchEvent::Touch event )
{
    if ( !_block_schedule_event )
    {
		iteration it(*this);
		it.decrement();

        for ( _riterator = (int)_children.size( ) - 1; _riterator >= 0; --_riterator )
        {
            try
            {
                // �q�������[�_���I�u�W�F�N�g�������ꍇ
                if ( _children[_riterator]->entry_touch_began( event ) )
                {
                    return true;
                }
            }
            catch ( exception_node_remove_self const& e )
            {
                /*MES_ERR( e.what( ),
                         [ ] { } );*/
            }
        }

		it.reset();
    }
    if ( _schedule_touch_event )
    {
        if ( touch_began( event ) )
        {
            _swallow = true;
            return true;
        }
    }
    return false;
}
bool node::entry_touch_moved( cinder::app::TouchEvent::Touch event )
{
    if ( !_block_schedule_event )
    {
		iteration it(*this);
		it.decrement();

        for ( _riterator = (int)_children.size( ) - 1; _riterator >= 0; --_riterator )
        {
            try
            {
                if ( _children[_riterator]->entry_touch_moved( event ) )
                {
                    return true;
                }
            }
            catch ( exception_node_remove_self const& e )
            {
                /*MES_ERR( e.what( ),
                         [ ] { } );*/
            }
        }

		it.reset();
    }
    if ( _schedule_touch_event )
    {
        if ( _swallow )
        {
            touch_moved( event );
            return true;
        }
    }
    return false;
}
bool node::entry_touch_ended( cinder::app::TouchEvent::Touch event )
{
    if ( !_block_schedule_event )
    {
		iteration it(*this);
		it.decrement();

        for ( _riterator = (int)_children.size( ) - 1; _riterator >= 0; --_riterator )
        {
            try
            {
                if ( _children[_riterator]->entry_touch_ended( event ) )
                {
                    return true;
                }
            }
            catch ( exception_node_remove_self const& e )
            {
                /*MES_ERR( e.what( ),
                         [ ] { } );*/
            }
        }

		it.reset();
    }
    if ( _schedule_touch_event )
    {
        if ( _swallow )
        {
            touch_ended( event );
            _swallow = false;
            return true;
        }
    }
    return false;
}
void node::entry_touches_began( cinder::app::TouchEvent event )
{
    if ( !_block_schedule_event )
    {
		iteration it(*this);
		it.decrement();

        for ( _riterator = (int)_children.size( ) - 1; _riterator >= 0; --_riterator )
        {
            try
            {
                _children[_riterator]->entry_touches_began( event );
            }
            catch ( exception_node_remove_self const& e )
            {
                /*MES_ERR( e.what( ),
                         [ ] { } );*/
            }
        }

		it.reset();
    }
    if ( _schedule_touches_event )
    {
        touches_began( event );
    }
}
void node::entry_touches_moved( cinder::app::TouchEvent event )
{
    if ( !_block_schedule_event )
    {
		iteration it(*this);
		it.decrement();

        for ( _riterator = (int)_children.size( ) - 1; _riterator >= 0; --_riterator )
        {
            try
            {
                _children[_riterator]->entry_touches_moved( event );
            }
            catch ( exception_node_remove_self const& e )
            {
                /*MES_ERR( e.what( ),
                         [ ] { } );*/
            }
        }

		it.reset();
    }
    if ( _schedule_touches_event )
    {
        touches_moved( event );
    }
}
void node::entry_touches_ended( cinder::app::TouchEvent event )
{
    if ( !_block_schedule_event )
    {
		iteration it(*this);
		it.decrement();

        for ( _riterator = (int)_children.size( ) - 1; _riterator >= 0; --_riterator )
        {
            try
            {
                _children[_riterator]->entry_touches_ended( event );
            }
            catch ( exception_node_remove_self const& e )
            {
                /*MES_ERR( e.what( ),
                         [ ] { } );*/
            }
        }

		it.reset();
    }
    if ( _schedule_touches_event )
    {
        touches_ended( event );
    }
}
void node::entry_key_down( cinder::app::KeyEvent event )
{
    if ( !_block_schedule_event )
    {
		iteration it(*this);
		it.decrement();

        for ( _riterator = (int)_children.size( ) - 1; _riterator >= 0; --_riterator )
        {
            try
            {
                _children[_riterator]->entry_key_down( event );
            }
            catch ( exception_node_remove_self const& e )
            {
                /*MES_ERR( e.what( ),
                         [ ] { } );*/
            }
        }

		it.reset();
    }
    if ( _schedule_key_event )
    {
        key_down( event );
    }
}
void node::entry_key_up( cinder::app::KeyEvent event )
{
    if ( !_block_schedule_event )
    {
		iteration it(*this);
		it.decrement();

        for ( _riterator = (int)_children.size( ) - 1; _riterator >= 0; --_riterator )
        {
            _children[_riterator]->entry_key_up( event );
        }

		it.reset();
    }

    if ( _schedule_key_event )
    {
        key_up( event );
    }
}
void node::entry_update( float delta )
{
    if ( !_block_schedule_update )
    {
		iteration it(*this);
		it.increment();

        for ( _iterator = 0; _iterator < (int)_children.size( ); ++_iterator )
        {
            try
            {
                _children[_iterator]->entry_update( delta );
            }
            catch ( exception_node_remove_self const& e )
            {
                /*MES_ERR( e.what( ),
                         [ ] { } );*/
            }
        }

		it.reset();
    }
    _action_manager.update( delta );
    if ( _schedule_update ) update( delta );
}
void node::entry_render( cinder::mat4 m )
{
    if ( _block_visible ) return;
    m = translate( m, get_position_3d( ) );
    m = scale( m, get_scale_3d( ) );
    m = rotate( m, get_rotation( ), get_axis( ) );
    m = translate( m, -get_content_size_3d( ) * get_anchor_point_3d( ) );
    gl::color( _color );
    gl::setModelMatrix( m );
    if( _visible ) this->render( );
    m = translate( m, get_content_size_3d( ) * get_pivot_3d( ) );

	iteration it(*this);
	it.increment();

    for ( _iterator = 0; _iterator < (int)_children.size( ); ++_iterator )
    {
        try
        {
            _children[_iterator]->entry_render( m );
        }
        catch ( exception_node_remove_self const& e )
        {
            /*MES_ERR( e.what( ),
                     [ ] { } );*/
        }
    }

	it.reset();
}
bool node::init( )
{
    return true;
}
void node::set_schedule_all( bool value )
{
    _schedule_update = value;
    _schedule_mouse_event = value;
    _schedule_touch_event = value;
    _schedule_touches_event = value;
    _schedule_key_event = value;
}
void node::set_opacity( float alpha )
{
    _color.a = alpha;
}
float node::get_opacity( ) const
{
    return _color.a;
}
std::vector<hardptr<node>> const& node::get_children( ) const
{
    return _children;
}
void node::sort_children( std::function<bool( hardptr<node>&a, hardptr<node>&b )> const & func )
{
    if ( ( _iteration_state & iteration::RUNNING ) == iteration::RUNNING ) throw exception_node_iterator_broken( );
    std::sort( _children.begin( ), _children.end( ), func );
}
void node::set_parent( softptr<node> value )
{
    // assert_log( _parent, "�e������`�ł��B", return );
    softptr<node> prev_parent = _parent;
    value->add_child( shared_from_this( ) );
    prev_parent->remove_child( shared_from_this( ) );
}
softptr<node> const& node::get_parent( ) const
{
    return _parent;
}
void node::set_name( std::string const& value )
{
    _name = value;
    std::hash<std::string> h;
    _hash = h( value );
}
std::string const& node::get_name( ) const
{
    return _name;
}
softptr<node> node::get_child_by_name( std::string const & name ) const
{
    // assert_log( !name.empty( ), "[node]�����Ȗ��O�ł��B", return nullptr );
    std::hash<std::string> h;
    size_t hash = h( name );
    auto itr = std::find_if( std::cbegin( _children ), std::cend( _children ), [ this, hash, name ] ( hardptr<node> const& child )
    {
        return child->_hash == hash && child->_name.compare( name ) == 0;
    } );
    if ( itr != std::cend( _children ) )
    {
        return *itr;
    }
    return nullptr;
}
softptr<node> node::get_child_by_tag( int tag ) const
{
    // assert_log( tag != node::INVALID_TAG, "[node]�����ȃ^�O�ł��B", return nullptr );
    auto itr = std::find_if( std::cbegin( _children ), std::cend( _children ), [ this, tag ] ( hardptr<node> const& n )
    {
        return n->_tag == tag;
    } );

    if ( itr != std::cend( _children ) )
    {
        return *itr;
    }
    return nullptr;
}
void node::remove_child( softptr<node> child )
{
    if ( _children.empty( ) ) return;
    auto erase_itr = std::find_if( std::begin( _children ), std::end( _children ), [ this, child ] ( hardptr<node>& n )
    {
        return n == child;
    } );
    if ( erase_itr == std::end( _children ) ) return;
    auto index = std::distance( std::begin( _children ), erase_itr );
    if ( _iteration_state == ( iteration::RUNNING | iteration::INCREMENT ) ) // �R�s�y���܂����Ă�̂́A�������g���폜�������this�ɃA�N�Z�X���Ă��܂��ƁA�G���[�ɂȂ�\���������̂ŁB
    {
        if ( index == _iterator ) { _children.erase( std::begin( _children ) + index ); _iterator--; throw exception_node_remove_self( ); }
        else { _children.erase( std::begin( _children ) + index ); if ( index < _iterator ) _iterator--; }
    }
    else if ( _iteration_state == ( iteration::RUNNING | iteration::DECREMENT ) )
    {
        if ( index == _riterator ) { _children.erase( std::begin( _children ) + index ); _riterator--; throw exception_node_remove_self( ); }
        else { _children.erase( std::begin( _children ) + index ); if ( index < _riterator ) _riterator--; }
    }
    else
    {
        _children.erase( std::begin( _children ) + index );
    }
}
void node::remove_child_by_name( std::string const & name )
{
    // assert_log( !name.empty( ), "[node]�����Ȗ��O�ł��B", return );
    if ( auto child = this->get_child_by_name( name ) )
    {
        remove_child( child );
    }
    else
    {
        // log( "[node]remove_child_by_name( \"%s\" ): �q����������܂���ł����B", name.c_str( ) );
    }
}
void node::remove_child_by_tag( int tag )
{
    // assert_log( tag != node::INVALID_TAG, "�����ȃ^�O�ł��B", return );
    if ( auto child = this->get_child_by_tag( tag ) )
    {
        remove_child( child );
    }
    else
    {
        // log( "[node]remove_child_by_tag( \"%d\" ): �q����������܂���ł����B", tag );
    }
}
void node::remove_all_children( )
{
    _children.clear( );
}
void node::remove_from_parent( )
{
    // assert_log( _parent, "[node]�e������`�ł��B", return );
    _parent->remove_child( shared_from_this( ) );
}
softptr<node> node::get_root( )
{
    return _get_root( );
}
softptr<node> node::_get_root( )
{
    if ( _parent )
    {
        return _parent->_get_root( );
    }
    else
    {
        return shared_from_this( );
    }
}
softptr<Action::action> node::get_action_by_name( std::string const & name ) const
{
    return _action_manager.get_action_by_name( name );
}
softptr<Action::action> node::get_action_by_tag( int tag ) const
{
    return _action_manager.get_action_by_tag( tag );
}
void node::remove_all_actions( )
{
    _action_manager.remove_all_actions( );
}
void node::remove_action( softptr<Action::action> action )
{
    _action_manager.remove_action( action );
}
void node::remove_action_by_tag( int tag )
{
    _action_manager.remove_action_by_tag( tag );
}
void node::remove_action_by_name( std::string const & name )
{
    _action_manager.remove_action_by_name( name );
}
bool node::is_running_action( ) const
{
    return _action_manager.is_running( );
}
cinder::mat3 node::get_world_matrix( ) const
{
    std::vector<mat3> mats;
	auto p = shared_from_this( );
    while ( p )
    {
        auto m = translate( mat3( ), p->get_position( ) );
        m = scale( m, p->get_scale( ) );
        m = rotate( m, p->get_rotation( ) );
        m = translate( m, -p->get_content_size( ) * p->get_anchor_point( ) );
        m = translate( m, p->get_content_size( ) * p->get_pivot( ) );
        mats.emplace_back( m );
        p = p->_parent.lock( );
    }
    mat3 result;
    for ( auto itr = mats.rbegin( ); itr != mats.rend( ); ++itr )
    {
        result *= *itr;
    }
    return result;
}
cinder::mat4 node::get_world_matrix_3d( ) const
{
    std::vector<mat4> mats;
	auto p = shared_from_this( );
    while ( p )
    {
        mats.emplace_back( p->get_local_matrix_3d( ) );
        p = p->_parent.lock( );
    }
    mat4 result;
    for ( auto itr = mats.rbegin( ); itr != mats.rend( ); ++itr )
    {
        result *= *itr;
    }
    return result;
}
cinder::mat4 node::get_local_matrix_3d( ) const
{
	auto p = shared_from_this( );
	auto m = glm::translate( mat4( ), p->get_position_3d( ) );
	m = glm::scale( m, p->get_scale_3d( ) );
	m = glm::rotate( m, p->get_rotation( ), p->get_axis( ) );
	m = glm::translate( m, -p->get_content_size_3d( ) * p->get_anchor_point_3d( ) );
	m = glm::translate( m, p->get_content_size_3d( ) * p->get_pivot_3d( ) );
	return m;
}
void node::set_matrix_3d( cinder::mat4 const & value )
{
	auto q = glm::toQuat( value );

	float angle = glm::angle( q );

	vec3 axis = glm::axis( q );

	// https://www21.atwiki.jp/opengl/pages/138.html
	vec3 scale;
	scale.x = glm::sqrt( value[0][0] * value[0][0] + value[1][0] * value[1][0] + value[2][0] * value[2][0] );
	scale.y = glm::sqrt( value[0][1] * value[0][1] + value[1][1] * value[1][1] + value[2][1] * value[2][1] );
	scale.z = glm::sqrt( value[0][2] * value[0][2] + value[1][2] * value[1][2] + value[2][2] * value[2][2] );

	vec3 position;
	position.x = value[3][0];
	position.y = value[3][1];
	position.z = value[3][2];

	set_axis( axis );
	set_rotation( angle );
	set_scale_3d( scale );
	set_position_3d( position );
}
}