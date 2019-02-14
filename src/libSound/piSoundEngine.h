#pragma once

namespace piLibs {


class piSoundEngine
{
public:
	virtual int   AddSound(const wchar_t *filename) = 0; // wav/mp3 file
	virtual int   AddSound(const int frequency, int precision, int length, void *buffer) = 0;
	virtual void  DelSound(int id) = 0;

	virtual bool  Play(int id, bool loop, float volume, int offset) = 0;
	virtual bool  Stop(int id) = 0;

	virtual void  PauseAllSounds(void) = 0;
	virtual void  ResumeAllSounds(void) = 0;
	virtual void  SetListener(const double * lst2world) = 0;

	virtual void  SetPosition(int id, const double * pos) = 0;
	virtual void  SetOrientation(int id, const double * dir, const double * up) = 0;
	virtual void  SetPositionOrientation(int id, const double * pos, const double * dir, const double * up) = 0;
	virtual bool  GetIsPlaying(int id) = 0;
	virtual float GetVolume(int id) const = 0;
	virtual bool  SetVolume(int id, float volume) = 0;
	virtual bool  GetSpatialize(int id) const = 0;
	virtual bool  SetSpatialize(int id, bool spatialize) = 0;
	virtual bool  CanChangeSpatialize(int id) const = 0;
	virtual bool  GetLooping(int id) const = 0;
	virtual void  SetLooping(int id, bool looping) = 0;
	virtual bool  GetPaused(int id) const = 0;
	virtual void  SetPaused(int id, bool paused) = 0;
	virtual int   GetAttenMode(int id) const = 0;
	virtual void  SetAttenMode(int id, int attenMode) = 0;
	virtual float GetAttenRadius(int id) const = 0;
	virtual void  SetAttenRadius(int id, float attenRadius) = 0;
	virtual float GetAttenMin(int id) const = 0;
	virtual void  SetAttenMin(int id, float attenMin) = 0;
	virtual float GetAttenMax(int id) const = 0;
	virtual void  SetAttenMax(int id, float attenMax) = 0;
};

} // namespace piLibs
