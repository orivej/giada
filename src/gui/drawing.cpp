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

#include "drawing.h"
#include "utils/gui.h"
#include <FL/Fl.H>
#include <FL/Fl_Image_Surface.H>
#include <cassert>

namespace giada::v
{
void drawRectf(geompp::Rect<int> r, Fl_Color c)
{
	fl_rectf(r.x, r.y, r.w, r.h, c);
}

/* -------------------------------------------------------------------------- */

void drawRect(geompp::Rect<int> r, Fl_Color c)
{
	fl_rect(r.x, r.y, r.w, r.h, c);
}

/* -------------------------------------------------------------------------- */

void drawLine(geompp::Line<int> l, Fl_Color c)
{
	fl_color(c);
	fl_line(l.x1, l.y1, l.x2, l.y2);
}

/* -------------------------------------------------------------------------- */

void drawText(const std::string& s, geompp::Rect<int> b, Fl_Color c, int alignment)
{
	assert(!s.empty());

	fl_color(c);
	fl_draw(s.c_str(), b.x, b.y, b.w, b.h, alignment);
}

/* -------------------------------------------------------------------------- */

Fl_RGB_Image* toImage(const Fl_Widget& widget)
{
	Fl_Image_Surface surf(widget.w(), widget.h());
	surf.set_current();                                 // Direct graphics requests to the image
	surf.draw(&const_cast<Fl_Widget&>(widget));         // Draw the widget in the image
	Fl_RGB_Image* image = surf.image();                 // Get the resulting image
	Fl_Display_Device::display_device()->set_current(); // Direct graphics requests back to the display
	return image;
}
} // namespace giada::v
