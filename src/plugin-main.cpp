/*
Plugin Name
Copyright (C) <Year> <Developer> <Email Address>

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program. If not, see <https://www.gnu.org/licenses/>
*/

#include <obs-module.h>
#include <obs-frontend-api.h>

#include "plugin-macros.generated.h"

OBS_DECLARE_MODULE()
OBS_MODULE_AUTHOR("Elliot Murphy");
OBS_MODULE_USE_DEFAULT_LOCALE(PLUGIN_NAME, "en-US")

MODULE_EXPORT const char *obs_module_description(void)
{
	return obs_module_text("media playback for live events");
}

MODULE_EXPORT const char *obs_module_name(void)
{
	return obs_module_text("Shadowplayer");
}

MODULE_EXPORT void obs_module_post_load(void)
{
	blog(LOG_INFO, "plugin post load completed (version %s)",
	     PLUGIN_VERSION);
}

MODULE_EXPORT void obs_module_unload()
{
	blog(LOG_INFO, "shadowplayer plugin unloaded");
}
