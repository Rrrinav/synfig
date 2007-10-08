/* === S Y N F I G ========================================================= */
/*!	\file translate.cpp
**	\brief Template File
**
**	$Id$
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
**
** === N O T E S ===========================================================
**
** ========================================================================= */

/* === H E A D E R S ======================================================= */

#ifdef USING_PCH
#	include "pch.h"
#else
#ifdef HAVE_CONFIG_H
#	include <config.h>
#endif

#include "translate.h"
#include <synfig/string.h>
#include <synfig/time.h>
#include <synfig/context.h>
#include <synfig/paramdesc.h>
#include <synfig/renddesc.h>
#include <synfig/surface.h>
#include <synfig/value.h>
#include <synfig/valuenode.h>
#include <synfig/canvas.h>
#include <synfig/transform.h>

#endif

/* === M A C R O S ========================================================= */

/* === G L O B A L S ======================================================= */

SYNFIG_LAYER_INIT(Translate);
SYNFIG_LAYER_SET_NAME(Translate,"translate");
SYNFIG_LAYER_SET_LOCAL_NAME(Translate,_("Translate"));
SYNFIG_LAYER_SET_CATEGORY(Translate,_("Transform"));
SYNFIG_LAYER_SET_VERSION(Translate,"0.1");
SYNFIG_LAYER_SET_CVS_ID(Translate,"$Id$");

/* === P R O C E D U R E S ================================================= */

/* === M E T H O D S ======================================================= */

/* === E N T R Y P O I N T ================================================= */

Translate::Translate():origin(0,0)
{
}

Translate::~Translate()
{
}

bool
Translate::set_param(const String & param, const ValueBase &value)
{
	IMPORT(origin);

	return false;
}

ValueBase
Translate::get_param(const String& param)const
{
	EXPORT(origin);
	EXPORT_NAME();
	EXPORT_VERSION();

	return ValueBase();
}

Layer::Vocab
Translate::get_param_vocab()const
{
	Layer::Vocab ret;

	ret.push_back(ParamDesc("origin")
		.set_local_name(_("Origin"))
		.set_description(_("Point where you want the origin to be"))
	);

	return ret;
}

synfig::Layer::Handle
Translate::hit_check(synfig::Context context, const synfig::Point &pos)const
{
	return context.hit_check(pos-origin);
}

Color
Translate::get_color(Context context, const Point &pos)const
{
	return context.get_color(pos-origin);
}

class Translate_Trans : public Transform
{
	etl::handle<const Translate> layer;
public:
	Translate_Trans(const Translate* x):Transform(x->get_guid()),layer(x) { }

	synfig::Vector perform(const synfig::Vector& x)const
	{
		return x+layer->origin;
	}

	synfig::Vector unperform(const synfig::Vector& x)const
	{
		return x-layer->origin;
	}
};
etl::handle<Transform>
Translate::get_transform()const
{
	return new Translate_Trans(this);
}

bool
Translate::accelerated_render(Context context,Surface *surface,int quality, const RendDesc &renddesc, ProgressCallback *cb)const
{
	RendDesc desc(renddesc);

	desc.clear_flags();
	desc.set_tl(desc.get_tl()-origin);
	desc.set_br(desc.get_br()-origin);

	// Render the scene
	if(!context.accelerated_render(surface,quality,desc,cb))
	{
		if(cb)cb->error(strprintf(__FILE__"%d: Accelerated Renderer Failure",__LINE__));
		return false;
	}

	return true;
}

Rect
Translate::get_full_bounding_rect(Context context)const
{
	return context.get_full_bounding_rect() + origin;
}
