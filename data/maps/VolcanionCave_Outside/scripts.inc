VolcanionCave_Outside_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, VolcanionCave_Outside_OnFrame
	.byte 0

VolcanionCave_Outside_OnFrame:
	map_script_2 VAR_TEMP_2, 0, VolcanionCave_Outside_EventScript_GetSentBackInside
	.2byte 0

VolcanionCave_Outside_EventScript_GetSentBackInside::
	lock
	setvar VAR_TEMP_2, 1
	release
	end
