#pragma once
#include <Network/NetworkDefines.h>
namespace Network
{
namespace Packet
{
enum class PacketId : ubyte1
{
    // 初期化用です。
    // 0で埋めているので、間違って呼ばれないように保険を掛けておきます。
    INVALID_NUMBER = 0U,

    //=========================================================//
    //                         Event                           //
    //=========================================================//
    // クライアント目線で書かれています。

    // <std::string>が送られてきました。
    EVE_STRING,
    // 他のプレイヤーや掘削機がフィールドのジェムを採ったと通知されました。
    EVE_GET_JEM,
    // 他のプレイヤーに奪われたと通知されました。
    // ※この瞬間にプレイヤーはステータスを変えてください。
    EVE_PLAYER_ROB_JEM,
    // 他のプレイヤーに倒されたと通知されました。
    // ※この瞬間にプレイヤーはステータスを変えてください。
    EVE_PLAYER_DEATH,

    //=========================================================//
    //                        Request                          //
    //=========================================================//
    // クライアント目線で書かれています。

    // <std::string>を送ります。
    REQ_STRING,
    // 他のプレイヤーの情報の更新を要求します。この時に自分のデータをパケットに乗せてください。
    REQ_PLAYER,
    // ワールドを生成するためのシード値を要求します。
    REQ_GET_JEM_SEED,
    // 現在持っているジェムの数をサーバーから取り寄せます。
    REQ_GET_JEM_POINT,
    // ジェムを取得したことを知らせます。プレイヤーと掘削機の両方、このパケットを使ってください。
    // ※このタイミングでは取得できません。サーバーからのレスポンスを待ってください。
    REQ_CHECK_GET_JEM,
    // プレイヤーが他のプレイヤーのジェムを奪ったことを通知します。
    // ※このタイミングでは奪取できません。サーバーからのレスポンスを待ってください。
    REQ_CHECK_PLAYER_ROB_JEM,
    // ブロックを破壊したと知らせます。
    // ※このタイミングでは破壊できません。サーバーからのレスポンスを待ってください。
    REQ_CHECK_BRAKE_BLOCKS,
    // 掘削機を設置したと知らせます。
    // ※このタイミングでは設置できません。サーバーからのレスポンスを待ってください。
    REQ_CHECK_SET_QUARRY,
    // 他のプレイヤーを倒した情報をサーバーに送る。
    // ※このタイミングでは倒せません。サーバーからのレスポンスを待ってください。
    REQ_CHECK_PLAYER_DEATH,

    //=========================================================//
    //                        Response                         //
    //=========================================================//
    // サーバー目線で書かれています。

    // <std::string>を送ります。
    RES_STRING,
    // 他のプレイヤーの情報を渡します。
    RES_PLAYER,
    // ワールドを生成するためのシード値を渡します。
    RES_GET_JEM_SEED,
    // プレイヤーが持っているジェムの数を渡します。
    RES_GET_JEM_POINT,
    // ジェムの取得に成功したか失敗したか、について通知します。
    RES_CHECK_GET_JEM,
    // ジェムの奪取に成功したか失敗したか、について通知します。
    RES_CHECK_PLAYER_ROB_JEM,
    // ブロック破壊に成功したか失敗したか、について通知します。
    RES_CHECK_BRAKE_BLOCKS,
    // 掘削機の設置に成功したか失敗したか、について通知します。
    RES_CHECK_SET_QUARRY,
    // 他のプレイヤーのキルに成功したか失敗したか、について通知します。
    RES_CHECK_PLAYER_DEATH,
};
}
}
