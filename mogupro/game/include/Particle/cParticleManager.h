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
};

enum class ParticleTextureType
{
    NONE,
    SAND,
    SPARK,
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

    cParticleHolder( const ci::vec3& position,
                     const ParticleType& type,
                     const ParticleTextureType& texture_type,
                     const ci::vec3& scale,
                     const float& time,
                     const int& count,
                     const float& speed,
                     const bool& lighting);
    ~cParticleHolder();

    void update( const float& delta_time );
    void draw( const glm::quat& rotation );

    bool isActive();

private:

    void sort();
    void create( const ci::vec3& position,
                 const float& time );

public:

    ci::vec3 mPosition;
    ci::vec3 mScale;
    ParticleType mType;
    std::string mTextureName;
    float mTime;
    float mSpeed;
    bool mLighting;
    Utility::softptr<Game::Light::cPointLightParam> mHandle;
    std::vector<std::shared_ptr<cParticle>> mParticles;
};

// /*�g����*/
// Particle::cParticleManager::getInstance()->
//     create( vec3( 0, get_map_top_pos, 0 ),         // �����ʒu�̒��S
//             Particle::ParticleType::SCATTER,       // ��΂���
//             Particle::ParticleTextureType::SPARK,  // �摜�̎��
//             100.0f,                                // ��������
//             10,                                    // ������
//             0.1f,                                  // �ʂ̑��x (������random�����Ă���
//             false);                                // ���C�g��enable

class cParticleManager : public Utility::cSingletonAble<cParticleManager>
{
public:

    cParticleManager();
    ~cParticleManager();

    void setup();
    void update( const float& delta_time );
    void draw();

    // �p�[�e�B�N������
    // position     : �����ʒu 
    // type         : ��΂����
    // texture_type : �摜�̎��
    // time         : ��������
    void create( const ci::vec3& position,
                 const ParticleType& type,
                 const ParticleTextureType& texture_type,
                 const ci::vec3& scale,
                 const float& time,
                 const float& speed = 0.1f );

    // �p�[�e�B�N����������
    // position     : �����ʒu 
    // type         : ��΂����
    // texture_type : �摜�̎��
    // scale        : �X�P�[��
    // count        : ������
    // speed        : �p�[�e�B�N���̑���
    void create( const ci::vec3& position,
                 const ParticleType& type = ParticleType::EXPROTION,
                 const ParticleTextureType& texture_type = ParticleTextureType::SPARK,
                 const ci::vec3& scale = ci::vec3( 0.3f ),
                 const float& time = 5.0f,
                 const int& count = 10,
                 const float& speed = 0.1f,
                 const bool& lighting = false);

private:

    void builbordUpdate();

private:

    std::vector<std::shared_ptr<cParticleHolder>> mParticleHolders;
    glm::quat mBuilbordRotate;

};
}
