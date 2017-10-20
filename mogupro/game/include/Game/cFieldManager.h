#pragma once
#include <cinder/app/App.h>
#include <Utility/cSingletonAble.h>
#include <Game/Field/cUnderGround.h>

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
    // radius    : ���̔��a
    bool blockBreak( const ci::vec3& position, const float& radius = 0 );
    // �u���b�N��j�󂷂�
    // cell_num : �Z���ԍ�
    // radius    : ���̔��a
    bool blockBreak( const ci::ivec3& cell_num, const float& radius = 0 );

    // ����(vec3)�ŋ߂��̃u���b�N�̏㕔���S�ʒu��Ԃ�
    // position : �Ώۂ̈ʒu
    ci::vec3 getBlockCenterTopPosition( const ci::vec3& target_position );

    // �u���b�N�̃Z���̍ő�l��Ԃ�
    ci::ivec3 getBlockMaxCell();

private: // Member
    Field::cUnderGround mUnderGround;
};
}