#include <Game/Field/cBlock.h>
#include <cinder/gl/gl.h>

using namespace ci;
using namespace ci::app;

namespace Game
{
namespace Field
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

    // �E
    0.5f,  0.5f,  0.5f,
    0.5f, -0.5f, -0.5f,
    0.5f,  0.5f, -0.5f,
    0.5f,  0.5f,  0.5f,
    0.5f, -0.5f,  0.5f,
    0.5f, -0.5f, -0.5f,

    // ��
    -0.5f, -0.5f,  0.5f,
    -0.5f,  0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f, -0.5f,

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

    // �E
    1.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,

    // ��
    -1.0f, 0.0f, 0.0f,
    -1.0f, 0.0f, 0.0f,
    -1.0f, 0.0f, 0.0f,
    -1.0f, 0.0f, 0.0f,
    -1.0f, 0.0f, 0.0f,
    -1.0f, 0.0f, 0.0f,

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

std::vector<vec2> getUv( int side_num )
{
    std::vector<vec2> uv = std::vector<vec2>( side_num * 4 );
    int c = 0;
    for (int i = 0; i < side_num; i++)
    {
        uv[c++] = vec2( 0.00000, 1.00000 );
        uv[c++] = vec2( 1.00000, 0.00000 );
        uv[c++] = vec2( 0.00000, 0.00000 );
        uv[c++] = vec2( 1.00000, 1.00000 );
    }
    return uv;
}

int getIndex( const vec3 & vtx, const vec3 & normal,
              const std::vector<vec3>& vertices,
              const std::vector<vec3>& normals )
{
    for (uint i = 0; i < (vertices.size()); ++i)
    {
        if (vertices[i] == vtx
             && normals[i] == normal)
        {
            // �S����v
            return i;
        }
    }
    return -1;
}

cBlock::cBlock( const ci::vec3& position, const float& scale, const uint& num ) :
    mPosition( position ),
    mScale( scale ),
    mIsActive( true ),
    mNum( num ),
    mCollider( mPosition, vec3( scale ), vec3( 0.5f ) )
{
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
void cBlock::createSide( std::vector<ci::vec3>& vertices,
                         std::vector<uint>& indices,
                         std::vector<ci::vec2>& uvs,
                         std::vector<ci::vec3>& normals )
{
    if (mIsActive == false)
        return;
    if (mDrawSide.size() <= 0)
        return;

    // UV
    auto uv = getUv( mDrawSide.size() );
    for (size_t i = uvs.size(); i < uvs.size() + uv.size(); i++)
        mUvNum.emplace_back( i );
    std::copy( uv.begin(), uv.end(), std::back_inserter( uvs ) );

    // Indices�̍ő�l�����߂�
    uint offset = 0;
    if (indices.size() > 0)
        offset = *std::max_element( indices.begin(), indices.end() ) + 1;

    // DrawElements�p�̃f�[�^���쐬
    std::vector<ci::vec3> temp_vertices;
    std::vector<uint> temp_indices;
    std::vector<ci::vec3> temp_normals;

    for (int i = 0; i < 36; ++i)
    {
        vec3 vertex = vec3( cube_vtx[i * 3 + 0],
                            cube_vtx[i * 3 + 1],
                            cube_vtx[i * 3 + 2] ) + mPosition;
        vec3 normal = vec3( cube_normal[i * 3 + 0],
                            cube_normal[i * 3 + 1],
                            cube_normal[i * 3 + 2] );

        int id = getIndex( vertex, normal,
                           temp_vertices, temp_normals );

        mIndicesNum.emplace_back( indices.size() + i );

        if (id < 0)
        {
            // �������W�Ɩ@���������_�͌����炸
            temp_indices.emplace_back( temp_vertices.size() + offset );

            mVerticesNum.emplace_back( temp_vertices.size() );
            temp_vertices.emplace_back( vertex );

            mNormalsNum.emplace_back( normal.size() );
            temp_normals.emplace_back( normal );
        }
        else
        {
            // ��������
            temp_indices.emplace_back( id + offset );
        }
    }

    std::copy( temp_vertices.begin(), temp_vertices.end(), std::back_inserter( vertices ) );
    std::copy( temp_indices.begin(), temp_indices.end(), std::back_inserter( indices ) );
    std::copy( temp_normals.begin(), temp_normals.end(), std::back_inserter( normals ) );
}
void cBlock::clear()
{
}
void cBlock::toBreak()
{
    mIsActive = false;
    clear();
}
}
}