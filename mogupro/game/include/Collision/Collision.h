#pragma once
#include <cinder/Vector.h>
#include <Collision/cAABBCollider.h>
#include <Collision/cRigidBody.h>
namespace Collision
{
// ���I��Cube�ƐÓI��Cube�̓����蔻����s���܂��B
// �Ԃ�l: �����蔻����N�������ꍇ true
// result: �����蔻����N���������ɓ����Ă���Cube�̈ʒu������܂��B
// aPos: �����Ă���Cube�̌��݈ʒu
// aSpeed: �����Ă���Cube�ړ���
// aSize: �����Ă���Cube�̑傫��
// bPos: �~�܂��Ă���Cube�̈ʒu
// bSize: �~�܂��Ă���Cube�̑傫��
bool hitCubeToCube( cinder::vec3* const result, cinder::vec3 aPos, cinder::vec3 aSpeed, cinder::vec3 aSize,
                    cinder::vec3 bPos, cinder::vec3 bSize );
void hitCubeToCube( cColliderBase * aCollider, cRigidBody * aRigidBody, cColliderBase * bCollider, float& min, cinder::Ray& ray, cinder::AxisAlignedBox& boundingBox, cColliderBase** targetCollider );
void hitCubeToCube( cAABBCollider * aAABB, cRigidBody * aRigidBody, cAABBCollider * bAABB, float& min, cinder::Ray& ray, cinder::AxisAlignedBox& boundingBox, cColliderBase** targetCollider );
}
