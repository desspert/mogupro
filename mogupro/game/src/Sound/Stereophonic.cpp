#include <Sound/Stereophonic.h>
namespace Sound
{
	//void Stereophonic::read(const std::string& file)
	//{
	//	wav.read(file);
	//}

	//void Stereophonic::bindWav()
	//{
	//	const char* wavData = wav.data();
	//	// �L���X�g
	//	const ALshort* sample = (const ALshort*)wavData;
	//	// �f�[�^�T�C�Y
	//	int sampleSize = wav.size() / 2;
	//	// �z��̊J�n�ʒu�ƏI���ʒu����쐬
	//	data = std::vector<ALshort>(&sample[0],&sample[sampleSize]);
	//}

	//void Stereophonic::bind()
	//{
	//	// �o�b�t�@�̐���
	//	alGenBuffers(1, &bufferId);
	//	ALenum format = (wav.channel() == 1)
	//		? AL_FORMAT_MONO16
	//		: AL_FORMAT_STEREO16;

	//	// �p�ӂ����T�C���g���o�b�t�@�ɃR�s�[
	//	alBufferData(bufferId,
	//		format,                       // ���m�����A�ʎq���r�b�g��:16
	//		wav.data(),                   // ���j�APCM�`���f�[�^���i�[����Ă���ꏊ
	//		wav.size(),                   // �T�C�Y(�o�C�g��)
	//		wav.sampleRate());            // �T���v�����O���[�g
	//									  // �\�[�X�̐���
	//	alGenSources(1, &sourceId);

	//	// �\�[�X�ɍĐ��������o�b�t�@�����蓖�Ă�
	//	alSourcei(sourceId, AL_BUFFER, bufferId);
	//}

	//void Stereophonic::setListenerPos(std::shared_ptr<ci::vec3> listenerPos)
	//{
	//	listenerPosition = listenerPos;
	//	alListenerfv(AL_POSITION, reinterpret_cast<float*>(&listenerPosition));
	//}
	//void Stereophonic::setListenerPos()
	//{
	//	float listenerP[] = { listenerPosition->x,listenerPosition->y,listenerPosition->z };
	//	alListenerfv(AL_POSITION, listenerP);
	//}

	//void Stereophonic::setListenerDirection(std::shared_ptr<ci::vec3> listerDir)
	//{
	//	listenerDirection = listerDir;
	//	// up�x�N�g��
	//	float upX = 0.0;
	//	float upY = 1.0;
	//	float upZ = 0.0;
	//	ALfloat listenerOrientation[] = { listenerDirection->x, listenerDirection->y, listenerDirection->z, upX, upY, upZ };
	//	alListenerfv(AL_ORIENTATION, listenerOrientation);
	//}
	//void Stereophonic::setListenerDirection()
	//{
	//	float upX = 0.0;
	//	float upY = 1.0;
	//	float upZ = 0.0;
	//	ALfloat listenerOrientation[] = { listenerDirection->x, listenerDirection->y, listenerDirection->z, upX, upY, upZ };
	//	alListenerfv(AL_ORIENTATION, listenerOrientation);
	//}

	//void Stereophonic::setSourcePos(std::shared_ptr<ci::vec3> sourcePos)
	//{
	//	sourcePosition = sourcePos;
	//	// �\�[�X�̈ʒu���ړ�
	//	alSourcefv(sourceId, AL_POSITION, reinterpret_cast<float*>(&sourcePosition));
	//}
	//void Stereophonic::setSourcePos()
	//{
	//	float sourceP[] = { sourcePosition->x,sourcePosition->y,sourcePosition->z };
	//	alSourcefv(sourceId, AL_POSITION, sourceP);
	//}
	//void Stereophonic::play()
	//{
	//	alSourcePlay(sourceId);
	//}

	//void Stereophonic::stop()
	//{
	//	alSourceStop(sourceId);
	//}

	//void Stereophonic::pause()
	//{
	//	alSourcePause(sourceId);
	//}

	//void Stereophonic::gain(const float value)
	//{
	//	alSourcef(sourceId, AL_GAIN, value);
	//}

	//void Stereophonic::pitch(const float value)
	//{
	//	alSourcef(sourceId, AL_PITCH, value);
	//}

	//void Stereophonic::looping(const bool value)
	//{
	//	alSourcei(sourceId, AL_LOOPING, value ? AL_TRUE : AL_FALSE);
	//}

	//bool Stereophonic::isPlaying()
	//{
	//	ALint state;
	//	alGetSourcei(sourceId, AL_SOURCE_STATE, &state);
	//	return state == AL_PLAYING;
	//}

	//float Stereophonic::currentTime()
	//{
	//	ALfloat currentTime;
	//	alGetSourcef(sourceId, AL_SEC_OFFSET, &currentTime);
	//	return currentTime;
	//}

	//void Stereophonic::update()
	//{
	//	if (!sourcePosition)
	//	{
	//		stop();
	//		return;
	//	}

	//	setListenerPos();
	//	setListenerDirection();
	//	setSourcePos();
	//	
	//}
	//void Stereophonic::clean()
	//{
	//	// �\�[�X�̔j��
	//	alDeleteSources(1, &sourceId);
	//	// �o�b�t�@�̔j��
	//	alDeleteBuffers(1, &bufferId);
	//}

	


	void StereophonicManager::open()
	{
		device = alcOpenDevice(nullptr);
		context = alcCreateContext(device, nullptr);
		alcMakeContextCurrent(context);
	}

	void StereophonicManager::close()
	{
		alcMakeContextCurrent(nullptr);
		alcDestroyContext(context);
		alcCloseDevice(device);
	}

}
