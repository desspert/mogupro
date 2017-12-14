#pragma once
#ifdef _MSC_VER
// TIPS:FBX SDK��DLL���g��
#define FBXSDK_SHARED
#endif
#include <cinder/app/App.h>
#include <cinder/Camera.h>
#include <cinder/Arcball.h>
#include <cinder/TriMesh.h>
#include <cinder/gl/gl.h>
#include <cinder/gl/Texture.h>
#include <cinder/ip/Flip.h>
#include <boost/optional.hpp>
#include <boost/filesystem.hpp>
#include <fbxsdk.h>                // FBX SDK
#include <cinder/ImageIo.h>
#include <Utility/cSingletonAble.h>
namespace Resource
{
#ifdef _MSC_VER
// cp932 �� UTF-8
std::string getUTF8Path( const std::string& path );
#endif

// FBX SDK�T���v������q��
// Get the geometry offset to a node. It is never inherited by the children.
FbxAMatrix GetGeometry( FbxNode* pNode );

// FbxAMatrix �� Matrix44
glm::mat4 getMatrix44( const FbxAMatrix& matrix );

// �X�P���^���A�j���[�V�����p�̏��
struct Skin
{
    bool has_skins;
    std::vector<std::vector<float>> weights;
    std::vector<FbxAMatrix> base_inv;
};


// �\���p�̃��b�V��
struct Mesh
{
    ci::TriMesh tri_mesh;

    Skin skin;
    ci::TriMesh deformed_mesh;
};

// FBX������o��������ێ����Ă������߂̒�`
// �}�e���A��
struct Material
{
    //ci::gl::Material material;
    boost::optional<ci::gl::Texture> texture;
};

class cFbxManager : public Utility::cSingletonAble<cFbxManager>
{
public:

    cFbxManager();
    ~cFbxManager();

    void setup();
    void update();
    void draw();

    void drawFbx( FbxNode *node, FbxTime &time );
    Mesh createMesh( FbxMesh *mesh );
    Skin createSkin( FbxMesh *mesh );
    ci::TriMesh getDeformedTriMesh( FbxMesh *mesh,
                                    const Mesh& src_mesh,
                                    FbxAMatrix& parent_matrix,
                                    FbxTime& time );
    const ci::TriMesh& getTriMesh( FbxMesh *mesh,
                                   Mesh& src_mesh,
                                   FbxAMatrix &parent_matrix,
                                   FbxTime& time );

    void setAnimation( const int index );

public:

    // FBX���
    FbxManager* manager;
    FbxScene* scene;
    FbxNode* root_node;

    // �\�����̏��𖼑O�ŊǗ�
    std::map<std::string, Mesh> meshes;
    std::map<std::string, Material> materials;

    // �A�j���[�V�����̌o�ߎ���
    double animation_time = 0.0;
    double animation_start;
    double animation_stop;

    // �V�[�����̃A�j���[�V������
    int animation_stack_count;
    int current_animation_stack = 0;

};
}