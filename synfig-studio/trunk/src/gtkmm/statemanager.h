/* === S Y N F I G ========================================================= */
/*!	\file statemanager.h
**	\brief Template Header
**
**	$Id: statemanager.h,v 1.1.1.1 2005/01/07 03:34:36 darco Exp $
**
**	\legal
**	Copyright (c) 2002-2005 Robert B. Quattlebaum Jr., Adrian Bentley
**
**	This package is free software; you can redistribute it and/or
**	modify it under the terms of the GNU General Public License as
**	published by the Free Software Foundation; either version 2 of
**	the License, or (at your option) any later version.
**
**	This package is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
**	General Public License for more details.
**	\endlegal
*/
/* ========================================================================= */

/* === S T A R T =========================================================== */

#ifndef __SYNFIG_STATEMANAGER_H
#define __SYNFIG_STATEMANAGER_H

/* === H E A D E R S ======================================================= */

#include <glibmm/refptr.h>
#include <vector>
#include "smach.h"

/* === M A C R O S ========================================================= */

/* === T Y P E D E F S ===================================================== */

/* === C L A S S E S & S T R U C T S ======================================= */

namespace Gtk { class ActionGroup; }

typedef unsigned int guint;

namespace studio {
	class StateManager
{
private:
	Glib::RefPtr<Gtk::ActionGroup> state_group;

	guint merge_id;
	std::vector<guint> merge_id_list;

	void change_state_(const Smach::state_base *state);

public:
	StateManager();

	~StateManager();

	void add_state(const Smach::state_base *state);

	Glib::RefPtr<Gtk::ActionGroup> get_action_group();
};

}; // END of namespace studio

/* === E N D =============================================================== */

#endif
