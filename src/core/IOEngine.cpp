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

#include "core/IOEngine.h"
#include "core/midiDispatcher.h"
#include "core/model/model.h"

namespace giada::m
{
IOEngine::IOEngine(model::Model& m, MidiDispatcher& md, Conf::Data& c)
: m_model(m)
, m_midiDispatcher(md)
, m_conf(c)
{
}

/* -------------------------------------------------------------------------- */

const model::MidiIn& IOEngine::getModelMidiIn() const
{
	return m_model.get().midiIn;
}

/* -------------------------------------------------------------------------- */

void IOEngine::channel_enableMidiLearn(ID channelId, bool v)
{
	m_model.get().getChannel(channelId).midiLearner.enabled = v;
	m_model.swap(m::model::SwapType::NONE);
}

/* -------------------------------------------------------------------------- */

void IOEngine::channel_enableMidiLightning(ID channelId, bool v)
{
	m_model.get().getChannel(channelId).midiLighter.enabled = v;
	m_model.swap(m::model::SwapType::NONE);
}

/* -------------------------------------------------------------------------- */

void IOEngine::channel_enableMidiOutput(ID channelId, bool v)
{
	m_model.get().getChannel(channelId).midiSender->enabled = v;
	m_model.swap(m::model::SwapType::NONE);
}

/* -------------------------------------------------------------------------- */

void IOEngine::channel_enableVelocityAsVol(ID channelId, bool v)
{
	m_model.get().getChannel(channelId).samplePlayer->velocityAsVol = v;
	m_model.swap(m::model::SwapType::NONE);
}

/* -------------------------------------------------------------------------- */

void IOEngine::channel_setMidiInputFilter(ID channelId, int ch)
{
	m_model.get().getChannel(channelId).midiLearner.filter = ch;
	m_model.swap(m::model::SwapType::NONE);
}

void IOEngine::channel_setMidiOutputFilter(ID channelId, int ch)
{
	m_model.get().getChannel(channelId).midiSender->filter = ch;
	m_model.swap(m::model::SwapType::NONE);
}

/* -------------------------------------------------------------------------- */

bool IOEngine::channel_setKey(ID channelId, int k)
{
	if (!isValidKey(k))
		return false;
	m_model.get().getChannel(channelId).key = k;
	m_model.swap(m::model::SwapType::HARD);
	return true;
}

/* -------------------------------------------------------------------------- */

void IOEngine::channel_startMidiLearn(int param, ID channelId, std::function<void()> doneCb)
{
	m_midiDispatcher.startChannelLearn(param, channelId, doneCb);
}

void IOEngine::master_startMidiLearn(int param, std::function<void()> doneCb)
{
	m_midiDispatcher.startMasterLearn(param, doneCb);
}

void IOEngine::plugin_startMidiLearn(int paramIndex, ID pluginId, std::function<void()> doneCb)
{
	m_midiDispatcher.startPluginLearn(paramIndex, pluginId, doneCb);
}

/* -------------------------------------------------------------------------- */

void IOEngine::stopMidiLearn()
{
	m_midiDispatcher.stopLearn();
}

/* -------------------------------------------------------------------------- */

void IOEngine::channel_clearMidiLearn(int param, ID channelId, std::function<void()> doneCb)
{
	m_midiDispatcher.clearChannelLearn(param, channelId, doneCb);
}

void IOEngine::master_clearMidiLearn(int param, std::function<void()> doneCb)
{
	m_midiDispatcher.clearMasterLearn(param, doneCb);
}

void IOEngine::plugin_clearMidiLearn(int param, ID pluginId, std::function<void()> doneCb)
{
	m_midiDispatcher.clearPluginLearn(param, pluginId, doneCb);
}

/* -------------------------------------------------------------------------- */

void IOEngine::master_enableMidiLearn(bool v)
{
	m_model.get().midiIn.enabled = v;
	m_model.swap(m::model::SwapType::NONE);
}

/* -------------------------------------------------------------------------- */

void IOEngine::master_setMidiFilter(int c)
{
	m_model.get().midiIn.filter = c;
	m_model.swap(m::model::SwapType::NONE);
}

/* -------------------------------------------------------------------------- */

bool IOEngine::isValidKey(int key) const
{
	for (const int& bind : m_conf.keyBindings)
		if (key == bind)
			return false;
	return true;
}
} // namespace giada::m
