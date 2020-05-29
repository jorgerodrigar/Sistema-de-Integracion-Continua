#pragma once
#include <string>
#include "Resources.h"

// Archivo solo con el enum de mensajes posibles entre observer/observable
enum Messages {
	Ch_Left,
	Ch_Right,
	Ch_TakeObj,
	StopRight,
	StopLeft,
	Moving,
	MouseStop,
	MouseMoving,
	CambioEscena,
	LuzInvertida,
	WinPuzzle,
	ChangeScene,
	MensajeVacio,
	DialogoAcabado,
	Stop,
	SetZBufferPlayState,
	AbreInventario,
	Pausa,
	CambioEstado,
	AddItemDialog,
	PLAY_MUSIC,
	STOP_MUSIC,
	PAUSE_MUSIC,
	RESUME_MUSIC,
	PLAY_SOUNDEFFECT,
	STOP_ALL_SOUNDEFFECT,
	MUSIC_VOLUME,
	SOUNDEFFECT_VOLUME,
	ANIM_DONE,
	STOP_SOUND_EFFECT,
	CAN_CONTINUE,
	STOP_ACTUAL_MUSIC,
	CHANGE_TO_CREDITS
};

struct Mensaje{
	Mensaje(Messages id) : id_(id) {};
	Mensaje(): id_(MensajeVacio){};
	Messages id_;
};

struct MensajePosicionMatriz: Mensaje //mensaje que devuelve la posicion de la matriz (puzzles)
{
	MensajePosicionMatriz(Messages id, std::pair<const int, const int> pos) : Mensaje(id), pos_(pos) {}
	std::pair<const int, const int> pos_;
};

struct MensajeCambioEscenaDialogos : Mensaje 
{
	MensajeCambioEscenaDialogos(Messages id, int numScene) : Mensaje(id), numScene_(numScene) {}
	int numScene_;
};

struct  MensajeAddItem : Mensaje
{
	int txt_;
	std::string tag_;
	std::string desc_;
	bool perm_;

	MensajeAddItem(Messages id, int txt, std::string tag, std::string desc, bool permanente) : Mensaje(id), txt_(txt), tag_(tag),
		desc_(desc), perm_(permanente) {}
};

struct PlayMusic : Mensaje {
	PlayMusic(Resources::MusicId idMusic) :
		Mensaje(PLAY_MUSIC), idMusic_(idMusic) {
	}
	Resources::MusicId idMusic_;
};

struct StopMusic : Mensaje {
	StopMusic(Resources::MusicId idMusic) :
		Mensaje(STOP_MUSIC), idMusic_(idMusic) {
	}
	Resources::MusicId idMusic_;
};

struct PauseMusic : Mensaje {
	PauseMusic(Resources::MusicId idMusic) :
		Mensaje(PAUSE_MUSIC), idMusic_(idMusic) {
	}
	Resources::MusicId idMusic_;
};

struct ResumeMusic : Mensaje {
	ResumeMusic(Resources::MusicId idMusic) :
		Mensaje(RESUME_MUSIC), idMusic_(idMusic) {
	}
	Resources::MusicId idMusic_;
};

struct MusicVolume : Mensaje {
	MusicVolume(Resources::MusicId idMusic, int volume) :
		Mensaje(MUSIC_VOLUME), idMusic_(idMusic), volume_(volume) {
	}
	Resources::MusicId idMusic_;
	int volume_;
};

struct SoundEffectVolume : Mensaje {
	SoundEffectVolume(Resources::SoundEffectId idSound, int volume) :
		Mensaje(SOUNDEFFECT_VOLUME), idSound_(idSound), volume_(volume) {
	}
	Resources::SoundEffectId idSound_;
	int volume_;
};

struct PlaySoundE : Mensaje {
	PlaySoundE(Resources::SoundEffectId idSoundE, int numReps) :
		Mensaje(PLAY_SOUNDEFFECT), idSoundE_(idSoundE), numReps_(numReps) {
	}
	Resources::SoundEffectId idSoundE_;
	int numReps_;
};

struct StopSoundEffect : Mensaje {
	StopSoundEffect(Resources::SoundEffectId idSound) :
		Mensaje(STOP_SOUND_EFFECT), idSound_(idSound) {
	}
	Resources::SoundEffectId idSound_;
};

struct SwapScenePuzzle : Mensaje {
	SwapScenePuzzle(bool swap) :
		Mensaje(WinPuzzle), swapScene(swap) {
	}
	bool swapScene;
};


