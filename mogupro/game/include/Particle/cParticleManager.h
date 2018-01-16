#pragma once
#include <cinder/app/App.h>
#include <cinder/gl/gl.h>
#include <Utility/cUserPointer.hpp>
#include <Game/Light/cPointLightParam.h>
#include <Utility/cSingletonAble.h>
#include <Particle/Easing/EaseType.h>

namespace Particle
{
enum class ParticleType
{
    NONE,
    SCATTER,    // ��юU��
    EXPROTION,  // ����
    GLITTER,    // �L���L��
    CONVERGE,   // ���� ( Easing ) 
    ABSORB,     // ���K�h���C��
};

enum class ParticleTextureType
{
    NONE,
    SAND,
    SPARK,              // �Ή�
    SPARK_PURE_WHITE,   // �����Ήԁi���F�p�j
};

class ParticleParam
{
public:
    friend class cParticleHolder;
    friend class cParticleManager;

    // �f�t�H���g�̐ݒ�
    ParticleParam();

    // �����̒��S�ʒu
    ParticleParam& position( ci::vec3& position );
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

    // �C�[�W���O�ɂ����鎞�� ( frame )
    ParticleParam& easeTime( const float& ease_speed );
    // �C�[�W���O�̎�� ( EaseType:: )
    ParticleParam& easeType( const EaseType& ease_type );

    // �����̒��S�ʒu�Ƀ��C�g�𐶐����邩�ǂ���
    ParticleParam& isLighting( const bool& is_lighting = true );
    // �p�[�e�B�N���̋O�Ղ𐶐����邩�ǂ���
    ParticleParam& isTrajectory( const bool& is_trajectory = true );
    // �p�[�e�B�N����Cube�ɂ��邩�ǂ���
    ParticleParam& isCube( const bool& is_cube = true );

    // �����_���ŃC�[�W���O����ꍇ�̃C�[�W���O�̎��
    ParticleParam& randomEaseTypes( const std::vector<EaseType>& ease_types );
    // �p�[�e�B�N�����̐F
    ParticleParam& colors( const std::vector<ci::ColorA>& pop_colors );
    // �����n�_
    ParticleParam& convergePoint( ci::vec3& converge_point );
    // �p�[�e�B�N�����c��ގ���
    ParticleParam& swellEndTime( const float& swell_end_time );
    // �p�[�e�B�N�����c��񂾌�C�[�W���O�Ɉڍs����܂Œ�~���鎞��
    ParticleParam& swellWaitTime( const float& swell_wait_time );

private:

    ci::vec3* mPosition;
    ci::vec3 mCurrentPosition;
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
    EaseType mEaseType;

    bool mIsLighting;
    bool mIsTrajectory;
    bool mIsCube;

    // Absorb�p
    std::vector<EaseType> mEaseTypes;
    std::vector<ci::ColorA> mColors;
    ci::vec3* mConvergePoint;
    float mSwellEndTime;
    float mSwellWaitTime;

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
    ci::vec3 getVec();
    float getAlpha();

private:

    void alphaUpdate( const float& delta_time );

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
    cParticleHolder( ci::vec3& position,
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
    void createMesh( const glm::quat& rotation, std::vector<std::shared_ptr<cParticle>>& particles );
    void particleDraw( const glm::quat& rotation );
    void setTexture( const ParticleTextureType& texture_type );
    void setLight( bool is_lighting );
    void clearMesh();

public:

    ParticleParam mParam;
    std::string mTextureName;
    Game::Light::PointLightHandle mHandle;
    std::vector<std::shared_ptr<cParticle>> mParticles;
    std::vector<std::shared_ptr<cParticle>> mTrajectoryParticles;
    glm::quat mRotation;
    bool mIsSwellEnd;

    unsigned int mIndicesIndex;
    ci::TriMeshRef mMesh;
    ci::gl::VboMeshRef mVbo;

};

// /* �g���� */
// /* �ύX�������p�����[�^�[�����ύX���Ă����`�F�[���L�@ */
//
// Particle::cParticleManager::getInstance()->
//     create( Particle::ParticleParam()
//             .position( mCollider.getPosition()
//             .scale( vec3( 0.5f ) ) );    
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

    void create( ci::vec3& position,
                 const ParticleType& type = ParticleType::EXPROTION,
                 const ParticleTextureType& texture_type = ParticleTextureType::SPARK,
                 const float& scale = 0.3f,
                 const float& time = 5.0f,
                 const int& count = 10,
                 const float& speed = 0.1f,
                 const bool& lighting = false,
                 const ci::ColorA& color = ci::ColorA( 1, 1, 1, 1 ) );

    void create( ci::vec3& position,
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

    std::list<std::shared_ptr<cParticleHolder>> mParticleHolders;

    glm::quat mBuilbordRotate;

};
}
