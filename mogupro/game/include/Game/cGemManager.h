#pragma once
#include "cinder/Rand.h"
#include "cinder/gl/Fbo.h"
#include "Game/Gem/cGem.h"
#include "Utility/cSingletonAble.h"
#include <vector>
#include <map>

#define GemManager Game::cGemManager::getInstance()

namespace Game
{
class cGemManager : public Utility::cSingletonAble<cGemManager>
{
public:

    cGemManager() {}
    ~cGemManager() {}
    // position           ���S���W(��l)   x,y,z�S��+�����Ƀ}�b�v�`�b�v�Ő������܂��B
    // randomRange        �����_���̐����͈�(�Е��w�n�̃}�b�v�T�C�Y)
    // mapChipSize        �}�b�v�`�b�v��}�X�̑傫��
    // gemMaxNum          gem�̐�����
    // seed               �V�[�h�l(���݂͓��͂��Ă��ϓ��Ȃ�)
    void setUp( ci::vec3 position, ci::vec3 randomRange, float mapChipSize, float gemScale, int gemMaxNum, unsigned long seed );
    void draw();
    void update();

    void create();
    // team     0��first,1��second
    void gemCountUp( int team, int it );
    void gemDelete( int it );

    std::vector<Gem::cGem> getGems() { return mGems; }

private:

    std::vector<Gem::cGem> mGems;
    std::map<Gem::GemType, int> mTeamGems[2];
    vec3 mPosition;
    vec3 mRandomRange;
    float mMapChipSize;
    float mGemScale;
    int mGemMaxNum;
    gl::FboRef mGemBuffer;
    unsigned long mSeed;
};
}