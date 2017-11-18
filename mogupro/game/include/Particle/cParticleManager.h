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
    SCATTER,    // �d�͖����̔�юU��
    SPLASH,     // �d�͂���̔�юU��
    EXPROTION,  // ����
    GLITTER,    // �����Ȃ��L���L��
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
    ci::vec3 mPosition;
    ci::vec3 mScale;
    ParticleType mMoveType;
    ParticleTextureType mTextureType;
    ci::ColorA mColor;
    int mCount;
    float mVanishTime;
    float mEffectTime;
    float mSpeed;
    bool mIsLighting;
    bool mIsTrajectory;

    ParticleParam();

    ParticleParam& position( const ci::vec3& position );
    ParticleParam& scale( const ci::vec3& scale );
    ParticleParam& moveType( const ParticleType& move_type );
    ParticleParam& textureType( const ParticleTextureType& texture_type );
    ParticleParam& color( const ci::ColorA& color );
    ParticleParam& count( const int& count );
    ParticleParam& vanishTime( const float& vanish_time );
    ParticleParam& effectTime( const float& effect_time );
    ParticleParam& speed( const float& speed );
    ParticleParam& isLighting( const bool& is_lighting );
    ParticleParam& isTrajectory( const bool& is_trajectory );

};

class cParticle
{
public:

    cParticle() {}
    cParticle( const ci::vec3& vec,
               const ci::vec3& position,
               const float& time );

    void update( const float& delta_time );
    bool isActive();

public:
    ci::vec3 mPosition;
    ci::vec3 mVec;
    float mTime;
};

class cParticleHolder
{
public:

    cParticleHolder( const ParticleParam& param );
    cParticleHolder( const ci::vec3& position,
                     const ParticleType& type,
                     const ParticleTextureType& texture_type,
                     const ci::vec3& scale,
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

    void sort();
    void create( const ci::vec3& position,
                 const float& time );
    void particleDraw( const glm::quat& rotation );
    void setTexture( const ParticleTextureType& texture_type );
    void setLight( bool is_lighting );

public:

    ParticleParam mParam;
    std::string mTextureName;
    Utility::softptr<Game::Light::cPointLightParam> mHandle;
    std::vector<std::shared_ptr<cParticle>> mParticles;
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
