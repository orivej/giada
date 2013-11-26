/* ---------------------------------------------------------------------
 *
 * Giada - Your Hardcore Loopmachine
 *
 * sampleChannel
 *
 * ---------------------------------------------------------------------
 *
 * Copyright (C) 2010-2013 Giovanni A. Zuliani | Monocasual
 *
 * This file is part of Giada - Your Hardcore Loopmachine.
 *
 * Giada - Your Hardcore Loopmachine is free software: you can
 * redistribute it and/or modify it under the terms of the GNU General
 * Public License as published by the Free Software Foundation, either
 * version 3 of the License, or (at your option) any later version.
 *
 * Giada - Your Hardcore Loopmachine is distributed in the hope that it
 * will be useful, but WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Giada - Your Hardcore Loopmachine. If not, see
 * <http://www.gnu.org/licenses/>.
 *
 * ------------------------------------------------------------------ */


#ifndef SAMPLE_CHANNEL_H
#define SAMPLE_CHANNEL_H


#include <samplerate.h>
#include "channel.h"


class SampleChannel : public Channel {

private:

	SRC_STATE *converter;
	SRC_DATA data;
	float *_procChan_;

	/* calcFadeoutStep
	 * how many frames are left before the end of the sample? Is there
	 * enough room for a complete fadeout? Should we shorten it? */

	void calcFadeoutStep();

	/* calcVolumeEnv
	 * compute any changes in volume done via envelope tool */

	void calcVolumeEnv(int frame);

public:

	SampleChannel(char side);
	~SampleChannel();

	void  clear      (int bufSize);
	void  process    (float *buffer, int size);
	void  start      (bool doQuantize);
	void  kill       ();
	void  empty      ();
	void  stopBySeq  ();
	void  stop       ();
	void  rewind     ();
	void  setMute    (bool internal);
	void  unsetMute  (bool internal);
	void  reset      ();
	int   load       (const char *file);
	int   loadByPatch(const char *file, int i);
	void  writePatch (FILE *fp, int i, bool isProject);
	void  quantize   (int index, int frame);
	void  onZero     ();
	void  onBar      ();
	void  parseAction(recorder::action *a, int frame);

	/* fade methods
	 * prepare channel for fade, mixer will take care of the process
	 * during master play. */

	void  setFadeIn  (bool internal);
	void  setFadeOut (int actionPostFadeout);
	void  setXFade   ();

	/* pushWave
	 * add a new wave to an existing channel. */

	void pushWave(class Wave *w);

	/* getPosition
	 * returns the position of an active sample. If EMPTY o MISSING
	 * returns -1. */

	int getPosition();

	/* sum
	 * add sample frames to virtual channel. Frame = processed frame in
	 * Mixer. Running = is Mixer in play? */

	void sum(int frame, bool running);

	/* setPitch
	 * updates the pitch value and chanStart+chanEnd accordingly. */

	void setPitch(float v);

	/* processPitch
	 * resample the internal virtual channel. */

	void processPitch();

	/* setStart/end
	 * change begin/end read points in sample. */

	void setBegin(unsigned v);
	void setEnd  (unsigned v);

	/* save
	 * save sample to file. */

	int save(const char *path);

	/* hardStop
	 * stop the channel immediately, no further checks. */

	void hardStop();

	/* allocEmpty
	 * alloc an empty wave used in input recordings. */

	bool allocEmpty(int frames, int takeId);

	/* canInputRec
	 * true if channel can host a new wave from input recording. */

	bool  canInputRec();

	/* ---------------------------------------------------------------- */

	class  Wave *wave;
	int    tracker;         // chan position
	int    begin;
	int    end;
  float  pitch;
	float  boost;
	int    mode;            // mode: see const.h
	bool   qWait;           // quantizer wait
	float  fadein;
	bool   fadeoutOn;
	float  fadeoutVol;      // fadeout volume
	int    fadeoutTracker;  // tracker fadeout, xfade only
	float  fadeoutStep;     // fadeout decrease
  int    fadeoutType;     // xfade or fadeout
  int		 fadeoutEnd;      // what to do when fadeout ends
  int    key;

	/* recorder:: stuff */

  bool   readActions;     // read actions or not

	/* midi stuff */

  uint32_t midiInReadActions;

	/* const - what to do when a fadeout ends */

	enum {
		DO_STOP   = 0x01,
		DO_MUTE   = 0x02,
		DO_MUTE_I = 0x04
	};

	/*  const - fade types */

	enum {
		FADEOUT = 0x01,
		XFADE   = 0x02
	};
};

#endif
