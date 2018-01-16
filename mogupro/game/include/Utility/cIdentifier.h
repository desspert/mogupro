#pragma once
#include <unordered_set>
namespace Utility
{
class cIdentifier
{
public:
	class IDNotCreate : public std::runtime_error
	{
	public:
		IDNotCreate( )
			: std::runtime_error( "����ȏ�ID���쐬�ł��܂���B" )
		{

		}
	};
public:
    cIdentifier( );
	cIdentifier( const int min, const int max );
	const int createId( );
	void removeId( const int id );
    ~cIdentifier( );
private:
	const int min;
	const int max;
	std::unordered_set<int> handles;
};
}
