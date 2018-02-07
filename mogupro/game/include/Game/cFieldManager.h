#pragma once
#include <cinder/app/App.h>
#include <Utility/cSingletonAble.h>
#include <Game/Field/cUnderGround.h>
#include <Game/Field/cBreakBlockType.h>

namespace Game
{
class cFieldManager : public ::Utility::cSingletonAble<cFieldManager>
{
public:

    cFieldManager();
    ~cFieldManager();

    void setup();
    void update( const float& delta_time );
    void draw();

public: //Player, Strategy ���g���֐�

    // �u���b�N��j�󂷂�
    // position : �ʒu
    // radius   : �͈͂̔��a
    bool blockBreak( const ci::vec3& position, const float& radius, const Field::cBreakBlockType& type = Field::BlockType::NORMAL );

    // �u���b�N��j�󂷂�(�l�b�g���[�N�p)
    // position : �ʒu
    // radius   : �͈͂̔��a
    bool blockBreakNetwork( const ci::vec3& position, const float& radius, const Field::cBreakBlockType& type = Field::BlockType::NORMAL );

    // �u���b�N��j��ł��邩�m�F����
    // position : �ʒu
    // radius   : �͈͂̔��a
    bool isBreakBlock( const ci::vec3& position, const float& radius );

    // ����(vec3)�ŋ߂��̃u���b�N�̏㕔���S�ʒu��Ԃ�
    // target_position : �Ώۂ̈ʒu
    ci::vec3 getBlockHighestPosition( const ci::vec3& target_position );

    // x,z�ŋ߂��̃u���b�N�̈ʒu���Ay�̓u���b�N�̈�ԍ����Œ�l��Ԃ�
    // target_position : �Ώۂ̈ʒu
    ci::vec3 getBlockTopPosition( const ci::vec3& target_position );

    // ���W����`�����N�� id ��Ԃ�
    // position : ���W
    // radius   : �͈͂̔��a
    std::vector<int> getChunkId( const ci::vec3& position, const float& radius );

    bool isUnderCannon( const int& chunk_x, const int& chunk_y, const int& chunk_z );

    // �u���b�N�̃��Z�b�g
    void blockAllReset();

    // �V���b�g�_�E��
    void shutdown();

public:

    void addToBreakType( const Field::BlockType& type );
    void clearToBreakType();

public:

    void playBreakBlockSounds( const ci::vec3& position, const std::string& key );

private: // Member
    std::shared_ptr<Field::cUnderGround> mUnderGround;
    std::set<Field::BlockType> mToBreakBlocksType;
};
}