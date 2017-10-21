#pragma once
#include <Utility/cSingletonAble.h>
#include <stack>
#include <Network/Packet/Request.hpp>
#include <boost/optional.hpp>
namespace Network
{
class cRequestManager : public Utility::cSingletonAble<cRequestManager>
{
    // P=====BEGIN=====P
public:
    boost::optional<Packet::Request::cReqString> getReqString( );
    void ungetReqString( Packet::Request::cReqString&& data );
public:
    std::stack<Packet::Request::cReqString> mReqString;
public:
    boost::optional<Packet::Request::cReqPlayer> getReqPlayer( );
    void ungetReqPlayer( Packet::Request::cReqPlayer&& data );
public:
    std::stack<Packet::Request::cReqPlayer> mReqPlayer;
public:
    boost::optional<Packet::Request::cReqGetJemSeed> getReqGetJemSeed( );
    void ungetReqGetJemSeed( Packet::Request::cReqGetJemSeed&& data );
public:
    std::stack<Packet::Request::cReqGetJemSeed> mReqGetJemSeed;
public:
    boost::optional<Packet::Request::cReqGetJemPoint> getReqGetJemPoint( );
    void ungetReqGetJemPoint( Packet::Request::cReqGetJemPoint&& data );
public:
    std::stack<Packet::Request::cReqGetJemPoint> mReqGetJemPoint;
public:
    boost::optional<Packet::Request::cReqCheckGetJem> getReqCheckGetJem( );
    void ungetReqCheckGetJem( Packet::Request::cReqCheckGetJem&& data );
public:
    std::stack<Packet::Request::cReqCheckGetJem> mReqCheckGetJem;
public:
    boost::optional<Packet::Request::cReqCheckPlayerRobJem> getReqCheckPlayerRobJem( );
    void ungetReqCheckPlayerRobJem( Packet::Request::cReqCheckPlayerRobJem&& data );
public:
    std::stack<Packet::Request::cReqCheckPlayerRobJem> mReqCheckPlayerRobJem;
public:
    boost::optional<Packet::Request::cReqBreakBlocks> getReqBreakBlocks( );
    void ungetReqBreakBlocks( Packet::Request::cReqBreakBlocks&& data );
public:
    std::stack<Packet::Request::cReqBreakBlocks> mReqBreakBlocks;
public:
    boost::optional<Packet::Request::cReqCheckSetQuarry> getReqCheckSetQuarry( );
    void ungetReqCheckSetQuarry( Packet::Request::cReqCheckSetQuarry&& data );
public:
    std::stack<Packet::Request::cReqCheckSetQuarry> mReqCheckSetQuarry;
public:
    boost::optional<Packet::Request::cReqCheckPlayerDeath> getReqCheckPlayerDeath( );
    void ungetReqCheckPlayerDeath( Packet::Request::cReqCheckPlayerDeath&& data );
public:
    std::stack<Packet::Request::cReqCheckPlayerDeath> mReqCheckPlayerDeath;
public:
    boost::optional<Packet::Request::cReqMakeRoom> getReqMakeRoom( );
    void ungetReqMakeRoom( Packet::Request::cReqMakeRoom&& data );
public:
    std::stack<Packet::Request::cReqMakeRoom> mReqMakeRoom;
public:
    boost::optional<Packet::Request::cReqInRoom> getReqInRoom( );
    void ungetReqInRoom( Packet::Request::cReqInRoom&& data );
public:
    std::stack<Packet::Request::cReqInRoom> mReqInRoom;
public:
    boost::optional<Packet::Request::cReqWantTeamIn> getReqWantTeamIn( );
    void ungetReqWantTeamIn( Packet::Request::cReqWantTeamIn&& data );
public:
    std::stack<Packet::Request::cReqWantTeamIn> mReqWantTeamIn;
public:
    boost::optional<Packet::Request::cReqCheckBeginGame> getReqCheckBeginGame( );
    void ungetReqCheckBeginGame( Packet::Request::cReqCheckBeginGame&& data );
public:
    std::stack<Packet::Request::cReqCheckBeginGame> mReqCheckBeginGame;
public:
    boost::optional<Packet::Request::cReqCheckMember> getReqCheckMember( );
    void ungetReqCheckMember( Packet::Request::cReqCheckMember&& data );
public:
    std::stack<Packet::Request::cReqCheckMember> mReqCheckMember;
    // P=====END=====P
};
}
