#include <Network/cConnectionInfo.h>
#include <Utility/MessageBox.h>
#include <cinder/app/App.h>
namespace Network
{
cConnectionInfo::cConnectionInfo( ubyte1 idCount )
	: closeSecond( cinder::app::getElapsedSeconds( ) + HOLD_SECOND )
{
	if ( idCount == 255 )
	{
		MES_ERR( "�ڑ�����̐�������ɒB���܂����B",
				 [ ] { exit( 0 ); } );
	}
	else
	{
		id = idCount;
	}
}
}
