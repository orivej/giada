/* -----------------------------------------------------------------------------
 *
 * Giada - Your Hardcore Loopmachine
 *
 * -----------------------------------------------------------------------------
 *
 * Copyright (C) 2010-2022 Giovanni A. Zuliani | Monocasual Laboratories
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
 * -------------------------------------------------------------------------- */

#ifndef G_MODEL_SEQUENCER_H
#define G_MODEL_SEQUENCER_H

#include "core/const.h"
#include "core/types.h"
#include "core/weakAtomic.h"
#include "deps/mcl-audio-buffer/src/audioBuffer.hpp"

namespace giada::m::model
{
class Sequencer
{
	friend class Model;

public:
	/* isRunning
    When sequencer is actually moving forward, i.e. SeqStatus == RUNNING. */

	bool isRunning() const;

	/* isActive
    Sequencer is enabled, but might be in wait mode, i.e. SeqStatus == RUNNING or
    SeqStatus == WAITING. */

	bool isActive() const;

	/* canQuantize
	Sequencer can quantize only if it's running and quantizer is enabled. */

	bool canQuantize() const;

	bool a_isOnBar() const;
	bool a_isOnBeat() const;
	bool a_isOnFirstBeat() const;

	Frame a_getCurrentFrame() const;
	Frame a_getCurrentBeat() const;

	void a_setCurrentFrame(Frame f, int sampleRate) const;
	void a_setCurrentBeat(int b, int sampleRate) const;

	SeqStatus status       = SeqStatus::STOPPED;
	int       framesInLoop = 0;
	int       framesInBar  = 0;
	int       framesInBeat = 0;
	int       framesInSeq  = 0;
	int       bars         = G_DEFAULT_BARS;
	int       beats        = G_DEFAULT_BEATS;
	float     bpm          = G_DEFAULT_BPM;
	int       quantize     = G_DEFAULT_QUANTIZE;

private:
	struct Shared
	{
		WeakAtomic<Frame> currentFrame = 0;
		WeakAtomic<int>   currentBeat  = 0;
	};

	Shared* shared = nullptr;
};
} // namespace giada::m::model

#endif
