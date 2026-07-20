VolcanionCave_1F_MapScripts::
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, VolcanionCave_1F_OnWarp
	.byte 0

VolcanionCave_1F_OnWarp:
	map_script_2 VAR_TEMP_1, 0, VolcanionCave_1F_EventScript_TrySpawnPlayer2
	.2byte 0

VolcanionCave_1F_EventScript_TrySpawnPlayer2::
	callnative TrySpawnPlayer2
	setvar VAR_TEMP_1, 1
	end

VolcanionCave_1F_EventScript_RemoveLastTalked::
	removeobject VAR_LAST_TALKED
	return

VolcanionCave_1F_EventScript_Tirtouga::
	lock
	faceplayer
	playmoncry SPECIES_TIRTOUGA, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setwildbattle SPECIES_TIRTOUGA, 20
	dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	call_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, VolcanionCave_1F_EventScript_RemoveLastTalked
	release
	end

VolcanionCave_1F_EventScript_Cubone::
	lock
	faceplayer
	playmoncry SPECIES_CUBONE, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setwildbattle SPECIES_CUBONE, 20
	dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	call_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, VolcanionCave_1F_EventScript_RemoveLastTalked
	release
	end

VolcanionCave_1F_EventScript_Golem::
	lock
	faceplayer
	playmoncry SPECIES_GOLEM_ALOLA, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setwildbattle SPECIES_GOLEM_ALOLA, 50
	setflag FLAG_DO_WILD_BOSS_BATTLE
	dowildbattle
	clearflag FLAG_DO_WILD_BOSS_BATTLE
	specialvar VAR_RESULT, GetBattleOutcome
	call_if_eq VAR_RESULT, B_OUTCOME_WON, VolcanionCave_1F_EventScript_RemoveLastTalked
	release
	end
