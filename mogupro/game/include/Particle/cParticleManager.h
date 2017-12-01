#pragma once
#include <cinder/app/App.h>
#include <cinder/gl/gl.h>
#include <Utility/cUserPointer.hpp>
#include <Game/Light/cPointLightParam.h>
#include <Utility/cSingletonAble.h>

namespace Particle
{
enum class ParticleType
{
    NONE,
    SCATTER,    // ��юU��
    EXPROTION,  // ����
    GLITTER,    // �L���L��
    CONVERGE,   // ����
};

enum class ParticleTextureType
{
    NONE,
    SAND,
    SPARK,
};

class ParticleParam
{
public:
    friend class cParticleHolder;

    // �f�t�H���g�̐ݒ�
    ParticleParam();

    // �����̒��S�ʒu
    ParticleParam& position( const ci::vec3& position );
    // �p�[�e�B�N���̃X�P�[��
    ParticleParam& scale( const float& scale );
    // �p�[�e�B�N���̈ړ��̎d��
    ParticleParam& moveType( const ParticleType& move_type );
    // �p�[�e�B�N���̉摜�̎��
    ParticleParam& textureType( const ParticleTextureType& texture_type );
    // �F
    ParticleParam& color( const ci::ColorA& color );
    // ��t���[���Ńp�[�e�B�N������������鐔
    ParticleParam& count( const int& count );
    // ���Ŏ���
    ParticleParam& vanishTime( const float& vanish_time );
    // ���Ŏ��Ԃ̃����_���͈̔�
    ParticleParam& vanishTimeRange( const float& vanish_time_range );
    // ���ł��n�߂鎞��
    ParticleParam& vanishBeginTime( const float& vanish_begin_time );
    // �������� ( time < 0 �ɂȂ�Ɛ����I�� )
    ParticleParam& effectTime( const float& effect_time );
    // �p�[�e�B�N���̈ړ����x
    ParticleParam& speed( const float& speed );
    // �x�N�g���̒ǉ��� ( �x�N�g���ɕ΂���������� )
    ParticleParam& addVec( const ci::vec3& add_vec );
    // �d�͂̋��� ( vec.y - gravity )
    ParticleParam& gravity( const float& gravity );
    // �p�[�e�B�N���̌��ʔ͈́@( moveType == GLITTER or CONVERGE )
    ParticleParam& effectRange( const float& effect_range );
    // �����̒��S�ʒu�Ƀ��C�g�𐶐����邩�ǂ���
    ParticleParam& isLighting( const bool& is_lighting = true );
    // �p�[�e�B�N���̋O�Ղ𐶐����邩�ǂ���
    ParticleParam& isTrajectory( const bool& is_trajectory = true );
    // �p�[�e�B�N����Cube�ɂ��邩�ǂ���
    ParticleParam& isCube( const bool& is_cube = true );

private:

    ci::vec3 mPosition;
    float mScale;
    ParticleType mMoveType;
    ParticleTextureType mTextureType;
    ci::ColorA mColor;
    int mCount;
    float mVanishTime;
    float mVanishTimeRange;
    float mVainshBeginTime;
    float mEffectTime;
    float mSpeed;
    ci::vec3 mAddVec;
    float mGravity;
    float mEffectRange;
    float mEaseTime;
    bool mIsLighting;
    bool mIsTrajectory;
    bool mIsCube;

};

class cParticle
{
public:

    cParticle( const ci::vec3& position,
               const ci::vec3& vec,
               const float& time,
               const float& vanish_begin_time );
    ~cParticle();

    void update( const float& delta_time, const float& gravity );
    void draw( const glm::quat& rotation, const ci::ColorA& color );
    void cubeDraw( const ci::ColorA& color );
    bool isActive();

private:

    void alphaUpdate(const float& delta_time);
    float getAlpha();

public:

    ci::vec3 mPosition;
    ci::vec3 mPrevPosition;
    ci::vec3 mVec;
    float mTime;
    float mVanishBeginTime;
    float mAlpha;
    int mTrajectoryCount;
};

class cParticleHolder
{
public:

    cParticleHolder( const ParticleParam& param );
    cParticleHolder( const ci::vec3& position,
                     const ParticleType& type,
                     const ParticleTextureType& texture_type,
                     const float& scale,
                     const float& time,
                     const int& count,
                     const float& speed,
                     const bool& lighting,
                     const ci::ColorA& color );
    ~cParticleHolder();

    void update( const float& delta_time );
    void draw( const glm::quat& rotation );

    bool isActive();

private:

    void createParticle();
    ci::vec3 createPosition();
    ci::vec3 createVec( const ci::vec3& particle_position );
    float createVanishTime();
    void createTrajectory( const ci::vec3& position, const float& vanish_time, const float& delta_time );
    void particleDraw( const glm::quat& rotation );
    void setTexture( const ParticleTextureType& texture_type );
    void setLight( bool is_lighting );

public:

    ParticleParam mParam;
    std::string mTextureName;
    Utility::softptr<Game::Light::cPointLightParam> mHandle;
    std::vector<std::shared_ptr<cParticle>> mParticles;
    std::deque<std::shared_ptr<cParticle>> mTrajectoryParticles;

    ci::TriMeshRef mMesh;
    ci::gl::VboMeshRef mVbo;

};

// /* �g���� */
// /* �R���X�g���N�^�@ */
//
// Particle::cParticleManager::getInstance()->
//     create( vec3( 0, get_map_top_pos, 0 ),         // �����ʒu�̒��S
//             Particle::ParticleType::SCATTER,       // ��΂���
//             Particle::ParticleTextureType::SPARK,  // �摜�̎��
//             100.0f,                                // ��������
//             10,                                    // ������
//             0.1f,                                  // �ʂ̑��x (������random�����Ă���
//             false,                                 // ���C�g��enable
//             color);                                // �J���[
//

// /* �ύX�������p�����[�^�[�����ύX���Ă����`�F�[���L�@ */
//
// Particle::cParticleManager::getInstance()->
//     create( Particle::ParticleParam()
//             .position( mCollider.getPosition()
//             .scale( vec3( 0.5f ) ) );    // �����ʒu�̒��S
//

class cParticleManager : public Utility::cSingletonAble<cParticleManager>
{
public:

    cParticleManager();
    ~cParticleManager();

    void setup();
    void update( const float& delta_time );
    void draw();

    // �p�[�e�B�N����������
    // param : ParticleParam
    void create( const ParticleParam& param );

    void create( const ci::vec3& position,
                 const ParticleType& type = ParticleType::EXPROTION,
                 const ParticleTextureType& texture_type = ParticleTextureType::SPARK,
                 const float& scale = 0.3f,
                 const float& time = 5.0f,
                 const int& count = 10,
                 const float& speed = 0.1f,
                 const bool& lighting = false,
                 const ci::ColorA& color = ci::ColorA( 1, 1, 1, 1 ) );

    void create( const ci::vec3& position,
                 const ParticleType& type = ParticleType::EXPROTION,
                 const ParticleTextureType& texture_type = ParticleTextureType::SPARK,
                 const ci::vec3& scale = ci::vec3( 0.3f ),
                 const float& time = 5.0f,
                 const int& count = 10,
                 const float& speed = 0.1f,
                 const bool& lighting = false,
                 const ci::ColorA& color = ci::ColorA( 1, 1, 1, 1 ) );

private:

    void builbordUpdate();

private:

    std::vector<std::shared_ptr<cParticleHolder>> mParticleHolders;
    glm::quat mBuilbordRotate;

};
}
