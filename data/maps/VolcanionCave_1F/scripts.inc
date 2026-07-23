VolcanionCave_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, VolcanionCave_1F_OnTransition
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, VolcanionCave_1F_OnWarp
	map_script MAP_SCRIPT_ON_FRAME_TABLE, VolcanionCave_1F_OnFrame
	.byte 0

VolcanionCave_1F_OnTransition:
	call_if_set FLAG_VOLCANION_CAVE_1F_DIGLETT_LEFT_SPOT, VolcanionCave_1F_EventScript_MoveBadge
	end

VolcanionCave_1F_EventScript_MoveBadge::
	setobjectxyperm LOCALID_DIGLETT, 34, 17
	return

VolcanionCave_1F_OnWarp:
	map_script_2 VAR_TEMP_1, 0, VolcanionCave_1F_EventScript_TrySpawnPlayer2
	.2byte 0

VolcanionCave_1F_EventScript_TrySpawnPlayer2::
	callnative TrySpawnPlayer2
	setvar VAR_TEMP_1, 1
	call_if_eq VAR_VOLCANION_CAVE_1F_STATE, 0, VolcanionCave_1F_EventScript_HidePlayers
	end

VolcanionCave_1F_EventScript_HidePlayers::
	hideobjectat LOCALID_PLAYER_2, MAP_VOLCANION_CAVE_1F
	hideplayer
	return

VolcanionCave_1F_OnFrame:
	map_script_2 VAR_VOLCANION_CAVE_1F_STATE, 0, VolcanionCave_1F_EventScript_EnterCave
	.2byte 0

VolcanionCave_1F_EventScript_EnterCave::
	lock
	applymovement LOCALID_PLAYER_2, VolcanionCave_1F_Movement_Player2EnterCave
	waitmovement 0
	applymovement LOCALID_PLAYER, VolcanionCave_1F_Movement_PlayerEnterCave
	waitmovement 0
	delay 30
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	applymovement LOCALID_PLAYER_2, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	delay 30
	setvar VAR_VOLCANION_CAVE_1F_STATE, 1
	applymovement LOCALID_PLAYER_2, Common_Movement_WalkInPlaceRight
	waitmovement 0
	message ViridianForest_Text_ExploringQuestion
	waitmessage
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceLeft
	waitmovement 0
	message ViridianForest_Text_ExploringConfirmation
	waitmessage
	release
	end

VolcanionCave_1F_Movement_Player2EnterCave::
	set_visible
	walk_up
	walk_left
	walk_up
	step_end

VolcanionCave_1F_Movement_PlayerEnterCave::
	set_visible
	walk_up
	walk_right
	walk_up
	step_end

ViridianForest_Text_ExploringQuestion::
	.string "{RIVAL}: Exploring?\p$"

ViridianForest_Text_ExploringConfirmation::
	.string "{PLAYER}: Exploring.\p$"

VolcanionCave_1F_EventScript_MagmaGruntF::
	random 3
	goto_if_eq VAR_RESULT, 1, VolcanionCave_1F_EventScript_MagmaGruntFMsg1
	goto_if_eq VAR_RESULT, 2, VolcanionCave_1F_EventScript_MagmaGruntFMsg2
	msgbox ViridianForest_Text_HowDidIGetHere, MSGBOX_NPC
	end

VolcanionCave_1F_EventScript_MagmaGruntFMsg1::
	msgbox ViridianForest_Text_Help, MSGBOX_NPC
	end

VolcanionCave_1F_EventScript_MagmaGruntFMsg2::
	msgbox ViridianForest_Text_HELP, MSGBOX_NPC
	end

ViridianForest_Text_HowDidIGetHere::
	.string "How did I get here…$"

ViridianForest_Text_Help::
	.string "… … …\p"
	.string "Help.$"

ViridianForest_Text_HELP::
	.string "HELP$"

VolcanionCave_1F_EventScript_MagmaGruntM::
	lock
	goto_if_set FLAG_VOLCANION_CAVE_1F_GRUNT_DROPPED_BADGE, VolcanionCave_1F_EventScript_MagmaGruntMDroppedBadge
	setflag FLAG_VOLCANION_CAVE_1F_GRUNT_DROPPED_BADGE
	setflag FLAG_VOLCANION_CAVE_1F_DIGLETT_LEFT_SPOT
	message VolcanionCave_1F_Text_MagmaGruntMElipsis
	waitmessage
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_WalkInPlaceRight
	waitmovement 0
	applymovement LOCALID_DIGLETT, VolcanionCave_1F_Movement_DiglettDigDown
	waitmovement 0
	applymovement VAR_LAST_TALKED, VolcanionCave_1F_Movement_MagmaGruntMConfused
	waitmovement 0
	delay 20
	applymovement LOCALID_DIGLETT, VolcanionCave_1F_Movement_DiglettDigUp
	waitmovement 0
	applymovement VAR_LAST_TALKED, VolcanionCave_1F_Movement_MagmaGruntMSurprised
	waitmovement 0
	delay 20
	setobjectxyperm LOCALID_HEAT_BADGE, 33, 17
	addobject LOCALID_HEAT_BADGE
	clearflag FLAG_HIDE_VOLCANION_CAVE_1F_HEAT_BADGE
	applymovement VAR_LAST_TALKED, VolcanionCave_1F_Movement_MagmaGruntMWatchBadgeFallDown
	applymovement LOCALID_HEAT_BADGE, VolcanionCave_1F_Movement_BadgeFallDown
	waitmovement 0
	delay 20
	msgbox VolcanionCave_1F_Text_MagmaGruntMDroppedBadge
	closemessage
	release
	end

VolcanionCave_1F_EventScript_MagmaGruntMDroppedBadge::
	goto_if_set FLAG_HIDE_VOLCANION_CAVE_1F_HEAT_BADGE, VolcanionCave_1F_EventScript_MagmaGruntMBadgeStolen
	faceplayer
	msgbox VolcanionCave_1F_Text_MagmaGruntMDroppedBadge
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

VolcanionCave_1F_EventScript_MagmaGruntMBadgeStolen::
	faceplayer
	msgbox VolcanionCave_1F_Text_MagmaGruntMBadgeStolen
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

VolcanionCave_1F_Movement_DiglettDigDown::
	walk_in_place_fast_left
	walk_in_place_fast_left
	walk_in_place_fast_left
	set_invisible
	walk_faster_left
	walk_faster_left
	face_left
	step_end

VolcanionCave_1F_Movement_DiglettDigUp::
	face_left
	set_visible
	walk_in_place_fast_left
	step_end

VolcanionCave_1F_Movement_MagmaGruntMConfused::
	emote_question_mark
	walk_in_place_left
	delay_16
	walk_in_place_down
	delay_16
	walk_in_place_right
	delay_16
	step_end

VolcanionCave_1F_Movement_MagmaGruntMSurprised::
	emote_exclamation_mark
	jump_in_place_right
	step_end

VolcanionCave_1F_Movement_MagmaGruntMWatchBadgeFallDown::
	delay_16
	emote_exclamation_mark
	walk_in_place_down
	step_end

VolcanionCave_1F_Movement_BadgeFallDown::
	set_visible
	slide_down
	jump_down
	jump_left
	jump_down
	step_end

VolcanionCave_1F_Text_MagmaGruntMElipsis::
	.string "...\p$"

VolcanionCave_1F_Text_MagmaGruntMDroppedBadge::
	.string "I dropped my HEAT BADGE and\n"
	.string "it fell down there…\p"
	.string "I sure hope no TEAM AQUA GRUNT\n"
	.string "ends up stealing it!$"

VolcanionCave_1F_Text_MagmaGruntMBadgeStolen::
	.string "My HEAT BADGE!\p"
	.string "It's gone!!$"

VolcanionCave_1F_EventScript_HeatBadge::
	removeobject VAR_LAST_TALKED
	msgbox VolcanionCave_1F_Text_ObtainedHeatBadge
	closemessage
	setflag FLAG_BADGE04_GET
	end

VolcanionCave_1F_Text_ObtainedHeatBadge::
	.string "{PLAYER} obtained the HEAT BADGE!$"

VolcanionCave_1F_EventScript_Diglett::
	lock
	faceplayer
	clearflag FLAG_VOLCANION_CAVE_1F_DIGLETT_LEFT_SPOT
	applymovement LOCALID_DIGLETT, VolcanionCave_1F_Movement_DiglettDigDown2
	waitmovement 0
	delay 20
	applymovement LOCALID_DIGLETT, VolcanionCave_1F_Movement_DiglettDigUp2
	waitmovement 0
	release
	end

VolcanionCave_1F_Movement_DiglettDigDown2::
	walk_in_place_fast_up
	walk_in_place_fast_up
	walk_in_place_fast_up
	set_invisible
	walk_faster_right
	walk_faster_right
	face_left
	step_end

VolcanionCave_1F_Movement_DiglettDigUp2::
	face_left
	set_visible
	walk_in_place_fast_left
	step_end

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
	setflag WE_FLAG_WILD_BOSS
	dowildbattle
	clearflag WE_FLAG_WILD_BOSS
	specialvar VAR_RESULT, GetBattleOutcome
	call_if_eq VAR_RESULT, B_OUTCOME_WON, VolcanionCave_1F_EventScript_RemoveLastTalked
	release
	end
