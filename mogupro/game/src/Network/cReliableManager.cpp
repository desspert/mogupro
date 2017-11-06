#include <Network/cReliableManager.h>
namespace Network
{
cReliableManager::cReliableManager( )
{

}
cReliableManager::~cReliableManager( )
{

}
void cReliableManager::append( std::vector<char>&& sendData )
{
	mReliables.emplace_back( std::move( sendData ) );
}
std::vector<char> cReliableManager::update( )
{
	// �K��񐔑������f�[�^�͍폜����܂��B
	auto itr = mReliables.begin( );
	while ( itr != mReliables.end( ) )
	{
		if ( !itr->isFinished( ) ) break;
		else
		{
			itr = mReliables.erase( itr );
		}
	}
	// �l�߂��ď�ʂ̃N���X�ɏo�ׂ���܂��B
	std::vector<char> sendData;
	for ( auto& o : mReliables )
	{
		auto reliableData = o.get( );
		std::copy( reliableData.begin( ), reliableData.end( ), std::back_inserter( sendData ) );
	}
	return sendData;
}
}
