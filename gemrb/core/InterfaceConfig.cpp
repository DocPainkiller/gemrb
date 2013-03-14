/* GemRB - Infinity Engine Emulator
 * Copyright (C) 2013 The GemRB Project
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 *
 */

#include "globals.h"

#include "InterfaceConfig.h"

#include "System/FileStream.h"

namespace GemRB {

InterfaceConfig::InterfaceConfig(int /*argc*/, char** /**argv[]*/)
{
	// currently the base class has no CLI options.
	configVars = new StringMap();
	configVars->init(50, 10);

	// default to the correct endianswitch
	ieWord endiantest = 1;
	if (((char *)&endiantest)[1] == 1) {
		// big-endian
		DataStream::SetEndianSwitch(true);
	}
}

InterfaceConfig::~InterfaceConfig()
{
	delete configVars;
}
	
void InterfaceConfig::SetKeyValuePair(const char* key, const char* value)
{
	configVars->set(key, value);
}

const char* InterfaceConfig::GetValueForKey(const char* key) const
{
	const char* value = NULL;
	if (key && configVars->get(key)) {
		value = configVars->get(key)->c_str();
	}
	return value;
}

const std::string* InterfaceConfig::GetKeyValuePair(std::string* key) const
{
	if (key) {
		return configVars->get(key->c_str());
	}
	return NULL;
}
	
CFGConfig::CFGConfig(int argc, char *argv[])
	: InterfaceConfig(argc, argv)
{
	isValid = false;
	FileStream* config = new FileStream();
	// skip arg0 (it is just gemrb)
	for (int i=1; i < argc; i++) {
		if (stricmp(argv[i], "-c") == 0) {
			const char* filename = argv[++i];

			if (!config->Open(filename)) {
				// Explicitly specified cfg file HAS to be present
				Log(FATAL, "Config", "Failed to open config file \"%s\".", filename);
			}
			isValid = InitWithINIData(config);
		}
	}
	if (!isValid) {
		// nothing passed in on CLI, so search for gemrb.cfg
		char datadir[_MAX_PATH];
		char path[_MAX_PATH];
		char name[_MAX_PATH];

		// Find basename of this program. It does the same as basename (3),
		// but that's probably missing on some archs
		char* appName = strrchr( argv[0], PathDelimiter );
		if (appName) {
			appName++;
		} else {
			appName = argv[0];
		}

		strcpy( name, appName );
		assert(name[0]);

#if TARGET_OS_MAC
		// CopyGemDataPath would give us bundle resources dir
		CopyHomePath(datadir, _MAX_PATH);
		PathAppend(datadir, PACKAGE);
#else
		CopyGemDataPath(datadir, _MAX_PATH);
#endif
		PathJoinExt( path, datadir, name, "cfg" );

#define ATTEMPT_INIT \
if (config->Open(path) \
	&& InitWithINIData(config)) { \
		goto done; \
	}

		ATTEMPT_INIT;

#ifdef SYSCONFDIR
		PathJoinExt( path, SYSCONFDIR, name, "cfg" );
		ATTEMPT_INIT
#endif

		// Don't try with default binary name if we have tried it already
		if (!strcmp( name, PACKAGE )) {
			goto done;
		}

		PathJoinExt( path, datadir, PACKAGE, "cfg" );

		ATTEMPT_INIT;

#ifdef SYSCONFDIR
		PathJoinExt( path, SYSCONFDIR, PACKAGE, "cfg" );
		ATTEMPT_INIT;
#endif
	}
#undef ATTEMPT_INIT
done:
	delete config;
}

CFGConfig::~CFGConfig()
{}
	
bool CFGConfig::InitWithINIData(DataStream* const cfgStream)
{
	if (cfgStream == NULL) {
		return false;
	}

	if (isValid) {
		Log(WARNING, "Config", "attempting to replace config values with contents of %s", cfgStream->filename);
	} else {
		Log(MESSAGE, "Config", "attempting to initialize config with %s", cfgStream->filename);
	}

	isValid = false;
	int lineno = 0;
	char line[1024];
	while (cfgStream->Remains()) {
		char *key, *keyend, *value, *valueend;

		if (cfgStream->ReadLine(line, _MAX_PATH) == -1) {
			break;
		}
		lineno++;

		// skip leading blanks from name
		key = line;
		key += strspn( line, " \t\r\n" );

		// ignore empty or comment lines
		if (*key == '\0' || *key == '#') {
			continue;
		}

		value = strchr( key, '=' );
		if (!value || value == key) {
			Log(WARNING, "Config", "Invalid line %d", lineno);
			continue;
		}

		// trim trailing blanks from name
		keyend = value;
		while (keyend > key && strchr( "= \t", *keyend )) {
			*keyend-- = '\0';
		}

		value++;
		// skip leading blanks
		value += strspn( value, " \t");

		// trim trailing blanks from value
		valueend = value + strlen( value ) - 1;
		while (valueend >= value && strchr( " \t\r\n", *valueend )) {
			*valueend-- = '\0';
		}
		SetKeyValuePair(key, value);
	}
	isValid = true;
	return true;
}

}

