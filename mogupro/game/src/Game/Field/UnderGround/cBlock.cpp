#include <Game/Field/UnderGround/cBlock.h>
#include <cinder/gl/gl.h>

using namespace ci;
using namespace ci::app;

namespace Game
{
namespace Field
{
namespace UnderGround
{
static vec3 vertex0[] = {
    vec3( -0.5f,  0.5f, 0.5f ),
    vec3( 0.5f, -0.5f, 0.5f ),
    vec3( 0.5f,  0.5f, 0.5f ),
    vec3( -0.5f,  0.5f, 0.5f ),
    vec3( -0.5f, -0.5f, 0.5f ),
    vec3( 0.5f, -0.5f, 0.5f ), };
static vec3 vertex1[] = {
    vec3( -0.5f, -0.5f, -0.5f ),
    vec3( 0.5f,  0.5f, -0.5f ),
    vec3( 0.5f, -0.5f, -0.5f ),
    vec3( -0.5f, -0.5f, -0.5f ),
    vec3( -0.5f,  0.5f, -0.5f ),
    vec3( 0.5f,  0.5f, -0.5f ), };
static vec3 vertex2[] = {
    vec3( -0.5f, -0.5f,  0.5f ),
    vec3( -0.5f,  0.5f, -0.5f ),
    vec3( -0.5f, -0.5f, -0.5f ),
    vec3( -0.5f, -0.5f,  0.5f ),
    vec3( -0.5f,  0.5f,  0.5f ),
    vec3( -0.5f,  0.5f, -0.5f ), };
static vec3 vertex3[] = {
    vec3( 0.5f,  0.5f,  0.5f ),
    vec3( 0.5f, -0.5f, -0.5f ),
    vec3( 0.5f,  0.5f, -0.5f ),
    vec3( 0.5f,  0.5f,  0.5f ),
    vec3( 0.5f, -0.5f,  0.5f ),
    vec3( 0.5f, -0.5f, -0.5f ), };
static vec3 vertex4[] = {
    vec3( -0.5f, 0.5f, -0.5f ),
    vec3( 0.5f, 0.5f,  0.5f ),
    vec3( 0.5f, 0.5f, -0.5f ),
    vec3( -0.5f, 0.5f, -0.5f ),
    vec3( -0.5f, 0.5f,  0.5f ),
    vec3( 0.5f, 0.5f,  0.5f ), };
static vec3 vertex5[] = {
    vec3( -0.5f, -0.5f,  0.5f ),
    vec3( 0.5f, -0.5f, -0.5f ),
    vec3( 0.5f, -0.5f,  0.5f ),
    vec3( -0.5f, -0.5f,  0.5f ),
    vec3( -0.5f, -0.5f, -0.5f ),
    vec3( 0.5f, -0.5f, -0.5f ), };

static vec3 normal0[] = {
    vec3( 0.0f, 0.0f, 1.0f ),
    vec3( 0.0f, 0.0f, 1.0f ),
    vec3( 0.0f, 0.0f, 1.0f ),
    vec3( 0.0f, 0.0f, 1.0f ),
    vec3( 0.0f, 0.0f, 1.0f ),
    vec3( 0.0f, 0.0f, 1.0f ), };
static vec3 normal1[] = {
    vec3( 0.0f, 0.0f, -1.0f ),
    vec3( 0.0f, 0.0f, -1.0f ),
    vec3( 0.0f, 0.0f, -1.0f ),
    vec3( 0.0f, 0.0f, -1.0f ),
    vec3( 0.0f, 0.0f, -1.0f ),
    vec3( 0.0f, 0.0f, -1.0f ), };
static vec3 normal2[] = {
    vec3( -1.0f, 0.0f, 0.0f ),
    vec3( -1.0f, 0.0f, 0.0f ),
    vec3( -1.0f, 0.0f, 0.0f ),
    vec3( -1.0f, 0.0f, 0.0f ),
    vec3( -1.0f, 0.0f, 0.0f ),
    vec3( -1.0f, 0.0f, 0.0f ), };
static vec3 normal3[] = {
    vec3( 1.0f, 0.0f, 0.0f ),
    vec3( 1.0f, 0.0f, 0.0f ),
    vec3( 1.0f, 0.0f, 0.0f ),
    vec3( 1.0f, 0.0f, 0.0f ),
    vec3( 1.0f, 0.0f, 0.0f ),
    vec3( 1.0f, 0.0f, 0.0f ), };
static vec3 normal4[] = {
    vec3( 0.0f, 1.0f, 0.0f ),
    vec3( 0.0f, 1.0f, 0.0f ),
    vec3( 0.0f, 1.0f, 0.0f ),
    vec3( 0.0f, 1.0f, 0.0f ),
    vec3( 0.0f, 1.0f, 0.0f ),
    vec3( 0.0f, 1.0f, 0.0f ), };
static vec3 normal5[] = {
    vec3( 0.0f, -1.0f, 0.0f ),
    vec3( 0.0f, -1.0f, 0.0f ),
    vec3( 0.0f, -1.0f, 0.0f ),
    vec3( 0.0f, -1.0f, 0.0f ),
    vec3( 0.0f, -1.0f, 0.0f ),
    vec3( 0.0f, -1.0f, 0.0f ), };


GLfloat cube_vtx[] = {
    // �O
    //  x,     y,    z,
    -0.5f,  0.5f, 0.5f,
    0.5f, -0.5f, 0.5f,
    0.5f,  0.5f, 0.5f,
    -0.5f,  0.5f, 0.5f,
    -0.5f, -0.5f, 0.5f,
    0.5f, -0.5f, 0.5f,

    // ��
    -0.5f, -0.5f, -0.5f,
    0.5f,  0.5f, -0.5f,
    0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f,  0.5f, -0.5f,
    0.5f,  0.5f, -0.5f,

    // ��
    -0.5f, -0.5f,  0.5f,
    -0.5f,  0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f, -0.5f,

    // �E
    0.5f,  0.5f,  0.5f,
    0.5f, -0.5f, -0.5f,
    0.5f,  0.5f, -0.5f,
    0.5f,  0.5f,  0.5f,
    0.5f, -0.5f,  0.5f,
    0.5f, -0.5f, -0.5f,

    // ��
    -0.5f, 0.5f, -0.5f,
    0.5f, 0.5f,  0.5f,
    0.5f, 0.5f, -0.5f,
    -0.5f, 0.5f, -0.5f,
    -0.5f, 0.5f,  0.5f,
    0.5f, 0.5f,  0.5f,

    // ��
    -0.5f, -0.5f,  0.5f,
    0.5f, -0.5f, -0.5f,
    0.5f, -0.5f,  0.5f,
    -0.5f, -0.5f,  0.5f,
    -0.5f, -0.5f, -0.5f,
    0.5f, -0.5f, -0.5f,
};

GLfloat cube_normal[] = {
    // �O
    // x,    y,    z,
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,

    // ��
    0.0f, 0.0f, -1.0f,
    0.0f, 0.0f, -1.0f,
    0.0f, 0.0f, -1.0f,
    0.0f, 0.0f, -1.0f,
    0.0f, 0.0f, -1.0f,
    0.0f, 0.0f, -1.0f,

    // ��
    -1.0f, 0.0f, 0.0f,
    -1.0f, 0.0f, 0.0f,
    -1.0f, 0.0f, 0.0f,
    -1.0f, 0.0f, 0.0f,
    -1.0f, 0.0f, 0.0f,
    -1.0f, 0.0f, 0.0f,

    // �E
    1.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,

    // ��
    0.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,

    // ��
    0.0f, -1.0f, 0.0f,
    0.0f, -1.0f, 0.0f,
    0.0f, -1.0f, 0.0f,
    0.0f, -1.0f, 0.0f,
    0.0f, -1.0f, 0.0f,
    0.0f, -1.0f, 0.0f,
};

std::vector<uint32_t> getIndices( int side_size, int offset = 0 )
{
    std::vector<GLuint> indices = std::vector<GLuint>( side_size * 6 );
    int c = 0;
    for (int i = 0; i < side_size * 4; i += 4)
    {
        indices[c++] = i + offset;
        indices[c++] = i + 2 + offset;
        indices[c++] = i + 1 + offset;
        indices[c++] = i + 2 + offset;
        indices[c++] = i + offset;
        indices[c++] = i + 3 + offset;
    }
    return indices;
}

std::vector<vec2> getUv( int side_num )
{
    std::vector<vec2> uv = std::vector<vec2>( side_num * 4 );
    int c = 0;
    for (int i = 0; i < side_num; i++)
    {
        uv[c++] = vec2( 0.00000, 1.00000 );
        uv[c++] = vec2( 0.00000, 0.00000 );
        uv[c++] = vec2( 1.00000, 0.00000 );
        uv[c++] = vec2( 1.00000, 1.00000 );
    }
    return uv;
}

vec3* getVertices( int side_num )
{
    switch (side_num)
    {
        case 0: return vertex0;
        case 1: return vertex1;
        case 2: return vertex3;
        case 3: return vertex2;
        case 4: return vertex4;
        case 5: return vertex5;
    }
    return new vec3();
}

vec3* getNormals( int side_num )
{
    switch (side_num)
    {
        case 0: return normal0;
        case 1: return normal1;
        case 2: return normal3;
        case 3: return normal2;
        case 4: return normal4;
        case 5: return normal5;
    }
    return new vec3();
}

int getIndex( float x, float y, float z, float nx, float ny, float nz,
              const std::vector<vec3>& vtx,
              const std::vector<vec3>& normal )
{
    for (int i = 0; i < (vtx.size()); ++i)
    {
        if (vtx[i].x == x
             && vtx[i].y == y
             && vtx[i].z == z
             && normal[i].x == nx
             && normal[i].y == ny
             && normal[i].z == nz)
        {
            // �S����v����!!
            return i;
        }
    }

    return -1;
}

cBlock::cBlock( const ci::vec3 position, const float scale )
{
    mPosition = position;
    mScale = scale;
    mIsActive = true;
}
cBlock::~cBlock()
{
}
void cBlock::update()
{
}
void cBlock::draw()
{
    if (mIsActive == false) return;
    gl::pushModelView();
    gl::translate( mPosition );
    gl::scale( vec3( mScale ) );
    gl::drawCube( vec3( 0 ), vec3( 1 ) );
    gl::popModelView();
}
void cBlock::drawMesh()
{
    if (mIsActive == false) return;
    if (mVertices.size() == 0)return;
    gl::pushModelView();
    gl::translate( mPosition );
    gl::scale( vec3( mScale ) );
    //gl::draw( mVboMesh );
    gl::draw( *mMesh );
    gl::popModelView();
}
void cBlock::setupDrawSide( const std::vector<int>& draw_side, const  int& offset_index )
{
    //for (size_t i = 0; i < draw_side.size(); i++)
    //{
    //    // ���_
    //    vec3* temp = getVertices( draw_side[i] );
    //    for (int k = 0; k < 6; k++)
    //        mVertices.emplace_back( mPosition + temp[k] );

    //    // �@��
    //    temp = getNormals( draw_side[i] );
    //    for (int k = 0; k < 6; k++)
    //        mNormals.emplace_back( temp[k] );
    //}
    //mIndices = getIndices( draw_side.size(), offset_index );
    mUv = getUv( draw_side.size() );

    // DrawElements�p�̃f�[�^���쐬
    for (int i = 0; i < 36; ++i)
    {
        float x = cube_vtx[i * 3 + 0] + mPosition.x;
        float y = cube_vtx[i * 3 + 1] + mPosition.y;
        float z = cube_vtx[i * 3 + 2] + mPosition.z;
        float nx = cube_normal[i * 3 + 0];
        float ny = cube_normal[i * 3 + 1];
        float nz = cube_normal[i * 3 + 2];

        int id = getIndex( x, y, z, nx, ny, nz,
                           mVertices, mNormals );

        if (id < 0)
        {
            // �������W�Ɩ@���������_�͌����炸
            mIndices.emplace_back( mVertices.size() + offset_index );

            mVertices.emplace_back( vec3( x, y, z ) );
            mNormals.emplace_back( vec3( nx, ny, nz ) );
        }
        else
        {
            // ��������!!
            mIndices.emplace_back( id + offset_index );
        }
    }


    // ���b�V�������
    mMesh = ci::TriMesh::create();
    if (mVertices.size() > 0)
        mMesh->appendPositions( &mVertices[0], mVertices.size() );
    if (mIndices.size() > 0)
        mMesh->appendIndices( &mIndices[0], mIndices.size() );
    if (mUv.size() > 0)
        mMesh->appendTexCoords0( &mUv[0], mUv.size() );
    if (mNormals.size() > 0)
        mMesh->appendNormals( &mNormals[0], mNormals.size() );

    // VBO�̎����͂������傢��
    //mVboMesh = gl::VboMesh::create( mMesh );
}
void cBlock::clear()
{
    mVertices.clear();
    mIndices.clear();
    mUv.clear();
    mMesh->clear();
    mMesh.reset();
    mVboMesh.reset();
}
void cBlock::toBreak()
{
    mIsActive = false;
}
}
}
}
