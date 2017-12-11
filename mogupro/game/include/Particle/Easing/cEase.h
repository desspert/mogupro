#pragma once
#include <cinder/app/App.h>
#include <unordered_map>
#include <deque>
#include "EaseType.h"
#include "Utility/cSingletonAble.h"

#define Easing cEase::getInstance()

// �C�[�W���O�̌�
class EaseOrigin
{
public:
    EaseOrigin() {}
    EaseOrigin( float begin, float end, float end_frame, EaseType type );

    void setup( float begin, float end, float end_frame, EaseType type );

    void update( const float& delta_time );

    float currentTargetValue();

    // �I�������true
    bool isDone();

    void countReset() { count_ = 0.0f; }

    float getBegin() { return begin_; }
    void setBegin( float begin ) { begin_ = begin; }

private:

    float begin_;
    float end_;
    float end_frame_;
    std::function<float( float, float, float )> easefunc_;
    float count_;
};


// �^�[�Q�b�g�ɒǉ�����Ă���C�[�W���O�����s����N���X
class RunEase
{
public:
    RunEase();

    // �l�̍X�V
    void update( const float& delta_time );

    // �C�[�W���O�����ׂďI����Ă��邩�ǂ���
    bool isEaseEnd() { return ease_accum.empty(); }

    // float�̃C�[�W���O�X�^�b�N��ǉ�����֐�
    void add( float& target, float end, float end_frame, EaseType ease_type );

    // wait��ǉ�����֐�
    void addWait( float& target, int wait );

    void setIsStop( const bool& value ) { is_stop = value; }
    void setIsLoop( const bool& value ) { is_loop = value; }

    // �X�^�b�N�̒��g������
    void clear();

private:

    // �C�[�W���O�̍X�V
    void action( const float& delta_time );

    // �X�^�b�N��pop_front����֐�
    void pop();

    // �擪�X�^�b�N�����ɒǉ�
    void loop();

    std::deque<EaseOrigin> ease_accum;
    float* target_;
    bool is_stop;
    bool is_loop;
};

/*  �g����

    if( Easing.isEaseEnd( ������float�̒l ) )
    {
        Easing.add( ������float�̒l,
                    �I����float�̒l,
                    ���t���[�������邩,
                    �C�[�W���O�̎�� enum EaseType );
        
        Easing.wait( ������float�̒l,
                     �~�߂Ă���t���[������ );
    }

*/

// �C�[�W���O���Ǘ�����N���X
class cEase : public Utility::cSingletonAble<cEase>
{
public:
 
    // �C�[�W���O�̍X�V
    void update( const float& delta_time );

    // �C�[�W���O��ǉ�����֐�
    // target       �C�[�W���O���� float �̒l
    // end          �C�[�W���O���I�������Ƃ��ɂȂ�l
    // end_frame    ���t���[���ŏI��邩
    // ease_type    �ǂ̃C�[�W���O�֐����g����
    void add( float& target, const float& end, float end_frame, EaseType ease_type );

    // �C�[�W���O��ǉ�����֐�
    // target       �C�[�W���O���� vec3 �̒l
    // end          �C�[�W���O���I�������Ƃ��ɂȂ�l
    // end_frame    ���t���[���ŏI��邩
    // ease_type    �ǂ̃C�[�W���O�֐����g����
    void add( ci::vec3 & target, const ci::vec3& end, float end_frame, EaseType ease_type );

    // �C�[�W���O��ǉ�����֐�
    // target       �C�[�W���O���� vec2 �̒l
    // end          �C�[�W���O���I�������Ƃ��ɂȂ�l
    // end_frame    ���t���[���ŏI��邩
    // ease_type    �ǂ̃C�[�W���O�֐����g����
    void add( ci::vec2 & target, const ci::vec2& end, float end_frame, EaseType ease_type );

    // �C�[�W���O���~�߂鏈����ǉ�����֐�
    // target       �C�[�W���O���~�߂�float�̒l
    // wait_count   �~�߂鎞��
    void wait( float& target, int wait_count );
    // �C�[�W���O���~�߂鏈����ǉ�����֐�
    // target       �C�[�W���O���~�߂�vec3�̒l
    // wait_count   �~�߂鎞��
    void wait( ci::vec3 & target, int wait_count );
    // �C�[�W���O���~�߂鏈����ǉ�����֐�
    // target       �C�[�W���O���~�߂�vec3�̒l
    // wait_count   �~�߂鎞��
    void wait( ci::vec2 & target, int wait_count );

    // �C�[�W���O�̍X�V���~�߂�֐�
    void stop( float& target, const bool& is_enable = true );

    // �C�[�W���O�̍X�V���~�߂�֐�
    void stop( ci::vec3& target, const bool& is_enable = true );

    // �C�[�W���O�̍X�V���~�߂�֐�
    void stop( ci::vec2& target, const bool& is_enable = true );

    // �C�[�W���O�X�^�b�N�����[�v������
    void loop( float& target, const bool& is_enable = true );

    // �C�[�W���O�X�^�b�N�����[�v������
    void loop( ci::vec3& target, const bool& is_enable = true );

    // �C�[�W���O�X�^�b�N�����[�v������
    void loop( ci::vec2& target, const bool& is_enable = true );

    // �����̒l�̃C�[�W���O�̃X�^�b�N�����ׂď�������֐�
    void kill( float& target );

    // �����̒l�̃C�[�W���O�̃X�^�b�N�����ׂď�������֐�
    void kill( ci::vec3 & target );

    // �����̒l�̃C�[�W���O�̃X�^�b�N�����ׂď�������֐�
    void kill( ci::vec2 & target );

    // �����̒l�̃C�[�W���O���I����Ă��邩�ǂ�����Ԃ��֐�
    // target       �I����������ׂ�float�̒l
    bool isEaseEnd( float& target );

    // �����̒l�̃C�[�W���O���I����Ă��邩�ǂ�����Ԃ��֐�
    // target       �I����������ׂ�float�̒l
    bool isEaseEnd( ci::vec3& target );


    // �S�ẴC�[�W���O���I��������֐�
    void allClear();

private:
    std::unordered_map<float*, RunEase> ease;
};

