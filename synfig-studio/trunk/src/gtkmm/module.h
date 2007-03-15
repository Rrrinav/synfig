/* === S Y N F I G ========================================================= */
/*!	\file gtkmm/module.h
**	\brief Template Header
**
**	$Id: module.h,v 1.1.1.1 2005/01/07 03:34:36 darco Exp $
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

#ifndef __SYNFIG_MODULE_H
#define __SYNFIG_MODULE_H

/* === H E A D E R S ======================================================= */

#include <ETL/handle>

/* === M A C R O S ========================================================= */

/* === T Y P E D E F S ===================================================== */

/* === C L A S S E S & S T R U C T S ======================================= */

namespace studio {

class Module : public etl::shared_object
{
	bool status_;

protected:
	Module();

public:
	virtual ~Module();

	bool start();

	bool stop();

	bool get_status()const;

protected:

	virtual bool start_vfunc()=0;
	virtual bool stop_vfunc()=0;
};


}; // END of namespace studio

/* === E N D =============================================================== */

#endif
