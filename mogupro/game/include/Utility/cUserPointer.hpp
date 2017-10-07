#pragma once
#include <memory>
namespace Utility
{
template<class type>
using cHardPointer = std::shared_ptr<type>;
template<class type>
using hardptr = cHardPointer<type>;
// weak_ptr���g�p����Ƃ��ɁA�������� lock �Ƃ� expired ���g���̂����邢�̂Ń��b�s���O���܂��B
template<class type>
class cSoftPointer : public std::weak_ptr<type>
{
public:
    cSoftPointer( ) = default;
    cSoftPointer( cHardPointer<type> const& right ) noexcept
        : std::weak_ptr<type>( right )
    {
    }
    cSoftPointer( cHardPointer<type>&& right ) noexcept
        : std::weak_ptr<type>( std::move( right ) )
    {
    }
    template<class type2>
    cSoftPointer( cSoftPointer<type2> const& _Other ) noexcept
        : std::weak_ptr<type>( std::dynamic_pointer_cast<type>( _Other.lock( ) ) )
    {
    }
    template<class type2>
    cSoftPointer( cSoftPointer<type2>&& _Other ) noexcept
        : std::weak_ptr<type>( std::dynamic_pointer_cast<type>( _Other.lock( ) ) )
    {
    }
    template<class type2>
    cSoftPointer( cHardPointer<type2> const& _Other ) noexcept
        : std::weak_ptr<type>( _Other )
    {
    }
    template<class type2>
    cSoftPointer( cHardPointer<type2>&& _Other ) noexcept
        : std::weak_ptr<type>( std::move( _Other ) )
    {
    }
    template<class type2>
    cSoftPointer& operator=( cSoftPointer<type2> const& right ) noexcept
    {
        this->_Resetw( std::dynamic_pointer_cast<type>( right.lock( ) ) );
        return ( *this );
    }
    template<class type2>
    cSoftPointer& operator=( cHardPointer<type2> const& right ) noexcept
    {
        this->_Resetw( std::dynamic_pointer_cast<type>( right ) );
        return ( *this );
    }
    // �|�C���^�̎��Ԃ�Ԃ��܂��B
    type& operator*( ) const noexcept
    {
        return *this->lock( );
    }
    // �|�C���^�̎��Ԃ�Ԃ��܂��B
    cHardPointer<type> operator->( ) const noexcept
    {
        return this->lock( );
    }
    // �|�C���^��null������؂�𔻒f���܂��B
    operator bool( ) const noexcept
    {
        return this->lock( ) && ( !this->expired( ) );
    }
    // �|�C���^��null������؂�̔��f��"not"��^���܂��B
    bool operator!( ) const noexcept
    {
        return !( this->lock( ) && ( !this->expired( ) ) );
    }
    // �|�C���^���m�̔�r�����܂��B
    bool operator==( cSoftPointer<type> const& right ) const noexcept
    {
        return this->get( ) == right.get( );
    }
    // �|�C���^���m�̔�r�����܂��B
    bool operator==( cHardPointer<type> const& right ) const noexcept
    {
        return this->get( ) == right.get( );
    }
    // �|�C���^���m�̔�r�����܂��B
    bool operator!=( cSoftPointer<type> const& right ) const noexcept
    {
        return this->get( ) != right.get( );
    }
    // �|�C���^���m�̔�r�����܂��B
    bool operator!=( cHardPointer<type> const& right ) const noexcept
    {
        return this->get( ) != right.get( );
    }
    // �|�C���^���m�̔�r�����܂��B
    bool operator<( cSoftPointer<type> const& right ) const noexcept
    {
        return this->get( ) < right.get( );
    }
    // �|�C���^���m�̔�r�����܂��B
    bool operator<( cHardPointer<type> const& right ) const noexcept
    {
        return this->get( ) < right.get( );
    }
    // �����I�Ƀ|�C���^�̎��Ԃ�Ԃ��܂��B
    operator type&( ) const noexcept
    {
        return *this->lock( );
    }
    // �����I�Ƀ|�C���^�̎��Ԃ�Ԃ��܂��B
    operator type const&( ) const noexcept
    {
        return *this->lock( );
    }
    // �����I�Ƀn�[�h�|�C���^�ɃL���X�g���܂��B
    operator cHardPointer<type>( ) const noexcept
    {
        return std::move( this->lock( ) );
    }
    // static_cast�����܂��B
    template<class type2>
    cHardPointer<type2> staticptr( ) const
    {
        return std::move( std::static_pointer_cast<type2>( this->lock( ) ) );
    }
    // dynamic_cast�����܂��B
    template<class type2>
    cHardPointer<type2> dynamicptr( ) const
    {
        return std::move( std::dynamic_pointer_cast<type2>( this->lock( ) ) );
    }
    // ���̃|�C���^�[��Ԃ��܂��B
    type* get( ) const noexcept
    {
        return this->lock( ).get( );
    }
};
// �|�C���^���m�̔�r�����܂��B
template<class type>
bool operator==( cHardPointer<type> const& left, cSoftPointer<type> const& right ) noexcept
{
    return left.get( ) == right.get( );
}
// �|�C���^���m�̔�r�����܂��B
template<class type>
bool operator!=( cHardPointer<type> const& left, cSoftPointer<type> const& right ) noexcept
{
    return left.get( ) != right.get( );
}
// �|�C���^���m�̔�r�����܂��B
template<class type>
bool operator<( cHardPointer<type> const& left, cSoftPointer<type> const& right ) noexcept
{
    return left.get( ) < right.get( );
}
template<class type>
using softptr = cSoftPointer<type>;
}