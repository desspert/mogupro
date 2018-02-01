#include <Resource/cFbxManager.h>
#include <Utility/cSearchSystem.h>
#include <Utility/cString.h>
#include <Resource/TextureManager.h>
using namespace ci;
using namespace ci::app;

namespace Resource
{
std::string getUTF8Path( const std::string & path )
{
    // ���΃p�X �� ��΃p�X
    char fullPath[512];
    _fullpath( fullPath, path.c_str(), 512 );

    // cp932 �� UTF8
    char* path_utf8;
    FbxAnsiToUTF8( fullPath, path_utf8 );

    // char* �� std::string
    std::string coverted_path( path_utf8 );
    // FBX SDK�����Ŋm�ۂ��ꂽ�������͐�p�̊֐��ŉ��
    FbxFree( path_utf8 );

    return coverted_path;
}

FbxAMatrix GetGeometry( FbxNode * pNode )
{
    const FbxVector4 lT = pNode->GetGeometricTranslation( FbxNode::eSourcePivot );
    const FbxVector4 lR = pNode->GetGeometricRotation( FbxNode::eSourcePivot );
    const FbxVector4 lS = pNode->GetGeometricScaling( FbxNode::eSourcePivot );

    return FbxAMatrix( lT, lR, lS );
}

glm::mat4 getMatrix44( const FbxAMatrix & matrix )
{
    const double* p = (const double*) matrix;

    glm::mat4 m( p[0], p[1], p[2], p[3],
                 p[4], p[5], p[6], p[7],
                 p[8], p[9], p[10], p[11],
                 p[12], p[13], p[14], p[15] );

    return m;
}

cFbx::cFbx()
{

}
cFbx::~cFbx()
{

}

void cFbx::setup( FbxManager *manager, const std::string& fullpath )
{
    // �ǂݍ��݋@�\�𐶐�
    auto* importer = FbxImporter::Create( manager, "" );
    assert( importer );

    // FBX�t�@�C����ǂݍ���
    // assets���̃t�@�C����T���āA�t���p�X���擾����
//  std::string path = getAssetPath( "Fbx/" + filename + ".fbx" ).string();
    std::string path = fullpath;
#ifdef _MSC_VER
    path = getUTF8Path( path );
#endif

    // std::string �� char*
    if ( !importer->Initialize( path.c_str() ) )
        console() << "FBX:can't open " << path << std::endl;

    // �ǂݍ��ݗp�̃V�[���𐶐�
    scene = FbxScene::Create( manager, "" );
    assert( scene );

    // �t�@�C������V�[���֓ǂݍ���
    importer->Import( scene );
    console() << "Imported." << std::endl;

    // FbxImporter�͂����g��Ȃ��̂ł����Ŕj��
    importer->Destroy();

    FbxGeometryConverter geometryConverter( manager );
    // TIPS:���炩���߃|���S����S�ĎO�p�`�����Ă���
    geometryConverter.Triangulate( scene, true );
    geometryConverter.RemoveBadPolygonsFromMeshes( scene );

    // TIPS:�}�e���A�����ƂɃ��b�V���𕪗�
    geometryConverter.SplitMeshesPerMaterial( scene, true );
    console() << "Converted." << std::endl;

    // FBX���̍\�����擾���Ă���
    root_node = scene->GetRootNode();
    assert( root_node );

    root_node->GetChild( 0 );
    {
        // �V�[���Ɋ܂܂�郁�b�V���̉��
        auto meshCount = scene->GetSrcObjectCount<FbxMesh>();
        console() << "meshCount:" << meshCount << std::endl;

        for ( int i = 0; i < meshCount; ++i )
        {
            auto* mesh = scene->GetSrcObject<FbxMesh>( i );
            std::string name = mesh->GetName();

            if ( meshes.count( name ) )
                continue;

            Mesh mesh_info = createMesh( mesh );
            meshes.insert( { name, mesh_info } );
        }
    }

    //{
    //    // �V�[���Ɋ܂܂��}�e���A���̉��
    //    auto materialCount = scene->GetMaterialCount();
    //    console() << "material:" << materialCount << std::endl;
    //    for ( int i = 0; i < materialCount; ++i )
    //    {
    //        FbxSurfaceMaterial* material = scene->GetMaterial( i );
    //        std::string name = material->GetName();
    //        if ( materials.count( name ) ) continue;
    //        Material mat = createMaterial( material );
    //        materials.insert( { name, mat } );
    //    }
    //}


    // FBS SDK��j��
    // manager->Destroy();
}
void cFbx::update()
{

}
void cFbx::draw()
{
    draw( 0.0 );
}

void cFbx::draw( const double & animation_time )
{
    gl::pushModelView();
    float scale_ = 0.013f;
    gl::scale( scale_, scale_, scale_ );

    // �`��
    FbxTime time;
    time.SetSecondDouble( animation_time );
    drawFbx( root_node, time );

    gl::popModelView();
}

void cFbx::createAnimation( Anim & anim )
{
    anim.animation_stack_count = 0;

    // �A�j���[�V�����ɕK�v�ȏ������W
    anim.animation_stack_count = scene->GetSrcObjectCount<FbxAnimStack>();
    console() << "Anim:" << anim.animation_stack_count << std::endl;
    setAnimation( anim.current_animation_stack, anim );

    console() << "Pose:" << scene->GetPoseCount() << std::endl;

}

void cFbx::drawFbx( FbxNode * node, FbxTime & time )
{
    // TIPS:�����Ă���m�[�h�̂ݕ`��(�������Z�p�̕`����X�L�b�v)
    if ( node->GetVisibility() )
    {
        // �s��
        FbxAMatrix matrix;// = node->EvaluateGlobalTransform( time );
        matrix.SetIdentity();
        // �P�̃m�[�h�ɕ����̑������֘A�Â�����
        int attr_count = node->GetNodeAttributeCount();
        for ( int i = 0; i < attr_count; ++i )
        {
            FbxNodeAttribute* attr = node->GetNodeAttributeByIndex( i );
            auto type = attr->GetAttributeType();
            switch ( attr->GetAttributeType() )
            {
                case FbxNodeAttribute::eMesh:
                {
                    gl::pushModelView();

                    //glMatrixMode( GL_MODELVIEW );
                    //glMultMatrixd( matrix );

                    // �`��Ɏg�����b�V���ƃ}�e���A�������
                    FbxMesh* mesh = static_cast<FbxMesh*>( attr );
                    auto& mesh_info = meshes.at( mesh->GetName() );

                    // �X�P���^���A�j���[�V������K�p
                    const auto& tri_mesh = getTriMesh( mesh, mesh_info, matrix, time );

                    gl::draw( tri_mesh );

                    gl::popModelView();
                }
                break;

                default:
                    break;
            }
        }
    }

    // �q���̃m�[�h���ċA�ŕ`��
    int childCount = node->GetChildCount();
    for ( int i = 0; i < childCount; ++i )
    {
        FbxNode* child = node->GetChild( i );
        drawFbx( child, time );
    }
}

Mesh cFbx::createMesh( FbxMesh * mesh )
{
    Mesh mesh_info;

    {
        // ���_���W
        int indexCount = mesh->GetPolygonVertexCount();
        console() << "index:" << indexCount << std::endl;

        // TIPS:���_�z�񂩂�W�J����TriMesh�Ɋi�[���Ă���(T^T)
        int* index = mesh->GetPolygonVertices();
        for ( int i = 0; i < indexCount; ++i )
        {
            auto controlPoint = mesh->GetControlPointAt( index[i] );
            mesh_info.tri_mesh.appendPosition( vec3( controlPoint[0], controlPoint[1], controlPoint[2] ) );
        }

        for ( int i = 0; i < indexCount; i += 3 )
        {
            mesh_info.tri_mesh.appendTriangle( i, i + 1, i + 2 );
        }
    }

    {
        // ���_�@��
        FbxArray<FbxVector4> normals;
        mesh->GetPolygonVertexNormals( normals );

        console() << "normals:" << normals.Size() << std::endl;

        for ( int i = 0; i < normals.Size(); ++i )
        {
            const FbxVector4& n = normals[i];
            mesh_info.tri_mesh.appendNormal( vec3( n[0], n[1], n[2] ) );
        }
    }

    {
        // UV
        FbxStringList uvsetName;
        mesh->GetUVSetNames( uvsetName );

        if ( uvsetName.GetCount() > 0 )
        {
            // �ŏ���UV�Z�b�g�����o��
            console() << "UV SET:" << uvsetName.GetStringAt( 0 ) << std::endl;

            FbxArray<FbxVector2> uvsets;
            mesh->GetPolygonVertexUVs( uvsetName.GetStringAt( 0 ), uvsets );

            console() << "UV:" << uvsets.Size() << std::endl;

            for ( int i = 0; i < uvsets.Size(); ++i )
            {
                const FbxVector2& uv = uvsets[i];
                mesh_info.tri_mesh.appendTexCoord( vec2( uv[0], uv[1] ) );
            }
        }
    }

    //{
    //    // Material
    //    FbxGeometryElementMaterial* lMaterialElement = mesh->CreateElementMaterial();
    //    lMaterialElement->SetMappingMode( FbxGeometryElement::eByPolygon );
    //    lMaterialElement->SetReferenceMode( FbxGeometryElement::eIndexToDirect );

    //    int poly_count = mesh->GetPolygonCount();
    //    std::vector<FbxSurfacePhong*> lMaterial = std::vector<FbxSurfacePhong*>( poly_count );

    //    for ( int i = 0; i < poly_count; i++ )
    //    {
    //        FbxString lMaterialName = "material";
    //        lMaterialName += i;

    //        lMaterial[i] = FbxSurfacePhong::Create( scene, lMaterialName.Buffer() );

    //        // Generate primary and secondary colors.
    //        lMaterial[i]->Emissive.Set( FbxDouble3( 0.0, 0.0, 0.0 ) );
    //        lMaterial[i]->Ambient.Set( FbxDouble3( 1, 1, 1 ) );
    //        lMaterial[i]->Diffuse.Set( FbxDouble3( 1.0, 1.0, 1.0 ) );
    //        lMaterial[i]->Specular.Set( FbxDouble3( 0.0, 0.0, 0.0 ) );
    //        lMaterial[i]->TransparencyFactor.Set( 0.0 );
    //        lMaterial[i]->Shininess.Set( 0.5 );
    //        lMaterial[i]->ShadingModel.Set( FbxString( "phong" ) );

    //        // add materials to the node
    //        root_node->AddMaterial( lMaterial[i] );
    //    }
    //}

    // �X�P���^���A�j���[�V���������擾
    mesh_info.skin = createSkin( mesh );

    return mesh_info;
}

Skin cFbx::createSkin( FbxMesh * mesh )
{
    Skin skin_info;
    skin_info.has_skins = false;

    auto skinCount = mesh->GetDeformerCount( FbxDeformer::eSkin );
    if ( skinCount == 0 )
    {
        // �X�P���^���A�j���[�V�����Ȃ�
        console() << "No skeltal animation." << std::endl;
        return skin_info;
    }

    // eSkin�`���̃f�t�H�[�}�[���Q�ȏ㑶�݂���ꍇ������
    console() << "deformer:" << skinCount << std::endl;

    // �O�Ԗڂ�eSkin�`���̃f�t�H�[�}�[�����o��
    FbxSkin* skin = static_cast<FbxSkin*>( mesh->GetDeformer( 0, FbxDeformer::eSkin ) );
    int clusterCount = skin->GetClusterCount();

    console() << "cluster:" << clusterCount << std::endl;

    if ( clusterCount == 0 )
    {
        // FIXME:�e����^����N���X�^������??
        console() << "No cluster." << std::endl;
        return skin_info;
    }

    skin_info.has_skins = true;
    skin_info.weights.resize( mesh->GetPolygonVertexCount() );

    for ( auto& weights : skin_info.weights )
    {
        weights.resize( clusterCount );
        std::fill( std::begin( weights ), std::end( weights ), 0.0 );
    }

    // �����s��̋t�s��
    skin_info.base_inv.resize( clusterCount );

    int vtx_indexCount = mesh->GetPolygonVertexCount();
    int* vtx_index = mesh->GetPolygonVertices();

    for ( int i = 0; i < clusterCount; ++i )
    {
        FbxCluster* cluster = skin->GetCluster( i );

        // eNormalize�����Ή����Ȃ�
        assert( cluster->GetLinkMode() == FbxCluster::eNormalize );

        int indexCount = cluster->GetControlPointIndicesCount();
        int* indices = cluster->GetControlPointIndices();
        double* weights = cluster->GetControlPointWeights();

        // �E�F�C�g�����o��
        for ( int j = 0; j < indexCount; ++j )
        {
            double w = weights[j];

            // �R���g���[���|�C���g�����_�z��ʒu
            for ( int k = 0; k < vtx_indexCount; ++k )
            {
                if ( vtx_index[k] == indices[j] )
                {
                    skin_info.weights[k][i] = w;
                }
            }
        }

        // ������Ԃ̋t�s����v�Z���Ă���
        // FbxAMatrix m;
        // cluster->GetTransformLinkMatrix(m);
        // skin_info.base_inv[i] = m.Inverse();
    }

    return skin_info;
}

vec3 transformPoint( const mat4& m, const vec3& rhs )
{
    float x = m[0].x*rhs.x + m[0].y*rhs.y + m[0].z*rhs.z + m[0].w;
    float y = m[1].x*rhs.x + m[1].y*rhs.y + m[1].z*rhs.z + m[1].w;
    float z = m[2].x*rhs.x + m[2].y*rhs.y + m[2].z*rhs.z + m[2].w;
    float w = m[3].x*rhs.x + m[3].y*rhs.y + m[3].z*rhs.z + m[3].w;

    return vec3( x / w, y / w, z / w );
}
vec3 transformVec( const mat4& m, const vec3& rhs )
{
    float x = m[0].x*rhs.x + m[0].y*rhs.y + m[0].z*rhs.z;
    float y = m[1].x*rhs.x + m[1].y*rhs.y + m[1].z*rhs.z;
    float z = m[2].x*rhs.x + m[2].y*rhs.y + m[2].z*rhs.z;

    return vec3( x, y, z );
}

ci::TriMesh cFbx::getDeformedTriMesh( FbxMesh * mesh, const Mesh & src_mesh, FbxAMatrix & parent_matrix, FbxTime & time )
{
    TriMesh dst_mesh( src_mesh.tri_mesh );

    FbxSkin* skin = static_cast<FbxSkin*>( mesh->GetDeformer( 0, FbxDeformer::eSkin ) );
    int clusterCount = skin->GetClusterCount();

    std::vector<mat4> matricies( clusterCount );

    // �t�s����擾
    FbxAMatrix inv = parent_matrix.Inverse();

    for ( int i = 0; i < clusterCount; ++i )
    {
        // �e�����󂯂�s������o��
        // FIXME:FBX SDK�T���v���R�[�h���̂܂܁B���������̂ŗv�C��
        FbxCluster* cluster = skin->GetCluster( i );

        FbxAMatrix lReferenceGlobalInitPosition;
        cluster->GetTransformMatrix( lReferenceGlobalInitPosition );

        FbxAMatrix lReferenceGeometry = GetGeometry( mesh->GetNode() );
        lReferenceGlobalInitPosition *= lReferenceGeometry;

        FbxAMatrix lClusterGlobalInitPosition;
        cluster->GetTransformLinkMatrix( lClusterGlobalInitPosition );

        FbxNode* node = cluster->GetLink();
        FbxAMatrix lClusterGlobalCurrentPosition = node->EvaluateGlobalTransform( time );

        FbxAMatrix lClusterRelativeInitPosition = lClusterGlobalInitPosition.Inverse() * lReferenceGlobalInitPosition;
        FbxAMatrix lClusterRelativeCurrentPositionInverse = inv * lClusterGlobalCurrentPosition;

        matricies[i] = getMatrix44( lClusterRelativeCurrentPositionInverse * lClusterRelativeInitPosition );
    }


    // ���_���W��ϊ�
    const auto& src_vtx = src_mesh.tri_mesh.getBufferPositions();
    auto& dst_vtx = dst_mesh.getBufferPositions();
    const auto& src_norm = src_mesh.tri_mesh.getNormals();
    auto& dst_norm = dst_mesh.getNormals();

    for ( size_t i = 0; i < src_mesh.skin.weights.size(); ++i )
    {
        mat4 m = matricies[0] * src_mesh.skin.weights[i][0];
        for ( int j = 1; j < clusterCount; ++j )
        {
            if ( src_mesh.skin.weights[i][j] == 0.0 ) continue;

            m += matricies[j] * src_mesh.skin.weights[i][j];
        }

        vec3 src = vec3( src_vtx[i * 3 + 0],
                         src_vtx[i * 3 + 1],
                         src_vtx[i * 3 + 2] );

        vec4 temp = vec4( vec3( 0.0f ), 1.0f );
        // ���_���W�Ɩ@����ϊ�
        vec4 dst = translate( m, src ) * temp;
        //vec3 dst = transformPoint( m, src );
        dst_vtx[i * 3 + 0] = dst.x;
        dst_vtx[i * 3 + 1] = dst.y;
        dst_vtx[i * 3 + 2] = dst.z;

        if ( src_mesh.tri_mesh.hasNormals() )
            dst_norm[i] = transformVec( m, src_norm[i] );
    }

    return dst_mesh;
}

std::vector<ci::TriMesh> cFbx::getModelTriMesh()
{
    std::vector<ci::TriMesh> trimesh;
    FbxTime time;
    time.SetSecondDouble( 0 );

    // ���f����TriMesh�����ׂĎ擾
    triMeshConstruction( root_node, time, trimesh );

    return trimesh;
}

const ci::TriMesh & cFbx::getTriMesh( FbxMesh * mesh, Mesh & src_mesh, FbxAMatrix & parent_matrix, FbxTime & time )
{
    if ( src_mesh.skin.has_skins )
    {
        src_mesh.deformed_mesh = getDeformedTriMesh( mesh, src_mesh, parent_matrix, time );
        return src_mesh.deformed_mesh;
    }
    else
    {
        return src_mesh.tri_mesh;
    }
}

void cFbx::triMeshConstruction( FbxNode * node,
                                FbxTime & time,
                                std::vector<ci::TriMesh>& mesh_constr )
{
    // TIPS:�����Ă���m�[�h�̂ݕ`��(�������Z�p�̕`����X�L�b�v)
    if ( node->GetVisibility() )
    {
        // �s��
        FbxAMatrix matrix;// = node->EvaluateGlobalTransform( time );
        matrix.SetIdentity();

        // �P�̃m�[�h�ɕ����̑������֘A�Â�����
        int attr_count = node->GetNodeAttributeCount();
        for ( int i = 0; i < attr_count; ++i )
        {
            FbxNodeAttribute* attr = node->GetNodeAttributeByIndex( i );
            switch ( attr->GetAttributeType() )
            {
                case FbxNodeAttribute::eMesh:
                {
                    // �`��Ɏg�����b�V���ƃ}�e���A�������
                    FbxMesh* mesh = static_cast<FbxMesh*>( attr );
                    auto& mesh_info = meshes.at( mesh->GetName() );

                    // �X�P���^���A�j���[�V������K�p
                    const auto& tri_mesh = getTriMesh( mesh, mesh_info, matrix, time );
                    mesh_constr.push_back( tri_mesh );
                }
                break;

                default:
                    break;
            }
        }
    }

    // �q���̃m�[�h���ċA�ŕ`��
    int childCount = node->GetChildCount();
    for ( int i = 0; i < childCount; ++i )
    {
        FbxNode* child = node->GetChild( i );
        triMeshConstruction( node, time, mesh_constr );
    }
}

void cFbx::setAnimation( const int index, Anim &anim )
{
    auto* stack = scene->GetSrcObject<FbxAnimStack>( index );
    // assert(stack);
    if ( !stack )
        return;

    anim.animation_start = stack->LocalStart.Get().GetSecondDouble();
    anim.animation_stop = stack->LocalStop.Get().GetSecondDouble();
    console() << "Duration:" << anim.animation_start << "-" << anim.animation_stop << std::endl;

    anim.animation_time = anim.animation_start;

    scene->SetCurrentAnimationStack( stack );
}

//-------------------------------------------------------------------------------------------------------------------
//
// cFbxManager
//
//-------------------------------------------------------------------------------------------------------------------

cFbxManager::cFbxManager()
{
    // FBXSDK����
    manager = FbxManager::Create();
    assert( manager );

    Utility::cSearchSystem search;
    search.search( Utility::cString::getAssetPath() + "FBX\\" );
    mFilePaths = search.unixNotationFullPaths();
    TEX->set( "Gemstone", "Fbx/UV_Gemstone.jpg" );
}

cFbxManager::~cFbxManager()
{
}

void cFbxManager::setup()
{
}

void cFbxManager::testUpdate( const float& delta_time )
{
}

void cFbxManager::testDraw()
{
    gl::ScopedColor scoped_color( 1, 1, 1, 1 );
    gl::pushModelView();
    gl::translate( vec3( 5, 17, 2 ) );
    Resource::cFbxManager::getInstance()->draw( "Gemstone" );

    gl::translate( vec3( 0, 0, 1 ) );
    Resource::cFbxManager::getInstance()->draw( "Gemstone2" );

    gl::ScopedTextureBind tex( TEX->get( "Gemstone" ) );
    gl::translate( vec3( 0, 0, 1 ) );
    Resource::cFbxManager::getInstance()->draw( "Gemstone3" );


    gl::popModelView();
}

void cFbxManager::draw( const std::string & name )
{
    if ( models.find( name ) == models.end() )
    {
        assert( !"Model not found" );
        return;
    }
    models[name]->draw( 0.0 );
}

void cFbxManager::draw( const std::string & name, const double &animation_time )
{
    if ( models.find( name ) == models.end() )
        return;
    models[name]->draw( animation_time );
}
void cFbxManager::create( std::string const& name, const std::string & fullpath )
{
    if ( models.find( name ) != models.end() )
        return;
    std::shared_ptr<cFbx> model = std::make_shared<cFbx>();
    model->setup( manager, fullpath );
    models.insert( std::make_pair( name, std::move( model ) ) );
}
void cFbxManager::createAnimation( const std::string & name, Anim & anim )
{
    if ( models.find( name ) == models.end() )
        return;
    models[name]->createAnimation( anim );
}
void cFbxManager::loadOne()
{
    if ( isFinished() ) return;

    auto const& fullpath = mFilePaths[mCurrentLoadIndex];
    mCurrentLoadIndex = std::min( mCurrentLoadIndex + 1, (int) mFilePaths.size() );
    auto extension = Utility::cString::getExtensionName( fullpath );
    extension = Utility::cString::toUpper( extension );
    if ( extension == "FBX" )
    {
        auto underImagePos = fullpath.find( "FBX/" ) + sizeof( "FBX/" ) - sizeof( '\0' );
        auto unferImageName = fullpath.substr( underImagePos );
        Resource::cFbxManager::getInstance()->create( Utility::cString::getFileNameWithoutExtension( unferImageName ), fullpath );
    }
}
bool cFbxManager::isFinished()
{
    return mCurrentLoadIndex == mFilePaths.size();
}
int cFbxManager::maxNum()
{
    return mFilePaths.size();
}
int cFbxManager::currentNum()
{
    return mCurrentLoadIndex;
}
std::vector<ci::TriMesh> cFbxManager::getTriMesh( const std::string & name )
{
    if ( models.find( name ) == models.end() )
    {
        assert(!"Not find name ,getTriMesh");
    }
    return models[name]->getModelTriMesh();
}
}
