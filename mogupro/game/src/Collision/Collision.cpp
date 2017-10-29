#include <Collision/Collision.h>
#include <cinder/AxisAlignedBox.h>
#include <cinder/Ray.h>
using namespace cinder;
namespace Collision
{
void hitRayToCube( cinder::Ray const & ray, unsigned int layer, cColliderBase * bCollider, float & calcMin, cinder::Ray & calcRay, cinder::AxisAlignedBox & calcBoundingBox, cColliderBase ** targetCollider )
{
    if ( ( bCollider->getLayer( ) & layer ) != layer ) 
        return;

    if ( bCollider->getType( ) == cColliderBase::Type::AABB )
    {
        hitRayToCube( ray,
                      dynamic_cast<cAABBCollider*>( bCollider ),
                      calcMin, calcRay, calcBoundingBox, targetCollider );
    }
}
void hitRayToCube( cinder::Ray const & ray, cAABBCollider * bCollider, float & calcMin, cinder::Ray & calcRay, cinder::AxisAlignedBox & calcBoundingBox, cColliderBase ** targetCollider )
{
    AxisAlignedBox boundingBox( cinder::vec3( 0.0F ) + -bCollider->getSize( ) * bCollider->getAnchor( ),
                                cinder::vec3( 0.0F ) + bCollider->getSize( ) * ( 1.0F - bCollider->getAnchor( ) ) );
    boundingBox.transform( translate( mat4( ), bCollider->getPosition( ) ) );

    float min = 0.0F, max = 0.0F;
    if ( boundingBox.intersect( ray, &min, &max ) != 0 )
    {
        if ( min >= 0.0F && min <= 1.0F )
        {
            if ( min < calcMin )
            {
                calcMin = min;
                calcRay = ray;
                calcBoundingBox = boundingBox;
                *targetCollider = bCollider;
            }
        }
    }
}
void hitCubeToCube( cColliderBase * aCollider, cRigidBody * aRigidBody, cColliderBase * bCollider, float& min, cinder::Ray& ray, cinder::AxisAlignedBox& boundingBox, cColliderBase** targetCollider )
{
    if ( ( bCollider->getLayer( ) & aCollider->getLayer( ) ) != aCollider->getLayer( ) ) return;

    if ( aCollider == bCollider ) return;
    if ( aCollider->getType( ) == cColliderBase::Type::AABB &&
         bCollider->getType( ) == cColliderBase::Type::AABB )
    {
        hitCubeToCube( dynamic_cast<cAABBCollider*>( aCollider ), aRigidBody,
                       dynamic_cast<cAABBCollider*>( bCollider ),
                       min, ray, boundingBox, targetCollider );
    }
}
void hitCubeToCube( cAABBCollider * aAABB, cRigidBody * aRigidBody, cAABBCollider * bAABB, float& min, cinder::Ray& ray, cinder::AxisAlignedBox& boundingBox, cColliderBase** targetCollider )
{
    auto aPrevPos = aAABB->getPosition( ) - aRigidBody->getSpeed( );
    auto direction = aAABB->getPosition( ) - aPrevPos;
    //�@ �Q�^�P�P�P�P�_�Q
    //�@(���@ �L�ցM�@ ��)
    //�@/�@ �^�P�P�P�_�@��
    //`/�@�^/�u| �m�u|�_ ��
    //�b /�u �_�R| �^�R�� �b
    //�b�b�b(��). (��)| �b�b
    //�b�b�l��(�P�P)��| �b�b
    //�b(ڂu������_��|/� �b
    //�b �_�__�Q(o_�Q�m��D�b
    //�b�@/�V�@�@�@�@�R �@�b
    //�b / �b�@�^�@�@ |�� �b
    //�l(�| L_�Q�Q�Q�Q|�m)�
    //�@�_�R|-/�u)�|-|�m�^
    //�@�@�P(/�P�P �R)�P

    Ray calcRay( aPrevPos, direction );

    AxisAlignedBox calcBoundingBox( -aAABB->getSize( ) * aAABB->getAnchor( ) + -bAABB->getSize( ) * bAABB->getAnchor( ),
                                    aAABB->getSize( ) * ( 1.0F - aAABB->getAnchor( ) ) + bAABB->getSize( ) * ( 1.0F - bAABB->getAnchor( ) ) );
    calcBoundingBox.transform( translate( mat4( ), bAABB->getPosition( ) ) );

    float calcMin = 0.0F, calcMax = 0.0F;
    if ( calcBoundingBox.intersect( calcRay, &calcMin, &calcMax ) != 0 )
    {
        if ( calcMin >= 0.0F && calcMin <= 1.0F )
        {
            if ( calcMin < min )
            {
                min = calcMin;
                ray = calcRay;
                boundingBox = calcBoundingBox;
                *targetCollider = bAABB;
            }
        }
    }
}
}
