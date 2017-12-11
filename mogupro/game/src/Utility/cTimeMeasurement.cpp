#include <Utility/cTimeMeasurement.h>

cTimeMeasurement::cTimeMeasurement() 
	: mNow(std::chrono::steady_clock::now()), mPrev(mNow), mDeltaTime(0.0f), mTotalTime(0.0f)
{

}

void cTimeMeasurement::make()
{
	using namespace std::chrono;
	//���ݎ�����_now�ɑ��
	mNow = steady_clock::now();
	//_now����_prev�ŁA�����1�t���[���Ɋ|���������Ԃ��v�Z���A���
	mDeltaTime = static_cast<float>(duration_cast<microseconds>(mNow - mPrev).count() * 0.000001f);
	mTotalTime += mDeltaTime;
	//_prev��_now�����Ď��Ԃ𓯂��ɂ���
	mPrev = mNow;
	return;
}

float cTimeMeasurement::deltaTime()
{
	return mDeltaTime;
}

float cTimeMeasurement::totalTime()
{
	return mTotalTime;
}