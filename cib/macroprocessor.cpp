/******************************************************************************
 * Icinga 2                                                                   *
 * Copyright (C) 2012 Icinga Development Team (http://www.icinga.org/)        *
 *                                                                            *
 * This program is free software; you can redistribute it and/or              *
 * modify it under the terms of the GNU General Public License                *
 * as published by the Free Software Foundation; either version 2             *
 * of the License, or (at your option) any later version.                     *
 *                                                                            *
 * This program is distributed in the hope that it will be useful,            *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of             *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              *
 * GNU General Public License for more details.                               *
 *                                                                            *
 * You should have received a copy of the GNU General Public License          *
 * along with this program; if not, write to the Free Software Foundation     *
 * Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA.             *
 ******************************************************************************/

#include "i2-cib.h"

using namespace icinga;

string MacroProcessor::ResolveMacros(const string& str, const Dictionary::Ptr& macros)
{
	string::size_type offset, pos_first, pos_second;

	offset = 0;

	string result = str;
	while ((pos_first = result.find_first_of('$', offset)) != string::npos) {
		pos_second = result.find_first_of('$', pos_first + 1);

		if (pos_second == string::npos)
			throw runtime_error("Closing $ not found in macro format string.");

		string name = result.substr(pos_first + 1, pos_second - pos_first - 1);
		string value;
		if (!macros || !macros->Get(name, &value))
			throw runtime_error("Macro '" + name + "' is not defined.");

		result.replace(pos_first, pos_second - pos_first + 1, value);

		offset = pos_first + value.size();
	}

	return result;
}
