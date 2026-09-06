VolcanionCave_Outside_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, VolcanionCave_Outside_OnFrame
	.byte 0

VolcanionCave_Outside_OnFrame:
	map_script_2 VAR_TEMP_2, 0, VolcanionCave_Outside_EventScript_GetSentBackInside
	.2byte 0

VolcanionCave_Outside_EventScript_GetSentBackInside::
	lock
	special SpawnCameraObject
	delay 30
	applymovement LOCALID_CAMERA, VolcanionCave_Outside_Movement_CameraMoveDown
	waitmovement 0
	applymovement LOCALID_OUTSIDE_SHELLY, Common_Movement_WalkInPlaceUp
	message VolcanionCave_Outside_Text_ShellyEllipsis
	waitmovement 0
	waitmessage
	applymovement LOCALID_OUTSIDE_COURTNEY, Common_Movement_WalkInPlaceUp
	message VolcanionCave_Outside_Text_CourtneyEllipsis
	waitmovement 0
	waitmessage
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceDown
	callnative IsPlayerOne
	call_if_eq VAR_RESULT, TRUE, VolcanionCave_Outside_EventScript_PlayerAquaEllipsis
	call_if_eq VAR_RESULT, FALSE, VolcanionCave_Outside_EventScript_PlayerMagmaEllipsis
	waitmovement 0
	waitmessage
	closemessage
	playmoncry SPECIES_SHARPEDO, CRY_MODE_NORMAL
	applymovement LOCALID_OUTSIDE_SHARPEDO, VolcanionCave_Outside_Movement_JumpInPlaceUp
	waitmovement 0
	waitmoncry
	playmoncry SPECIES_NUMEL, CRY_MODE_NORMAL
	applymovement LOCALID_OUTSIDE_NUMEL_3, VolcanionCave_Outside_Movement_JumpInPlaceUp
	delay 2
	playmoncry SPECIES_NUMEL, CRY_MODE_NORMAL
	applymovement LOCALID_OUTSIDE_NUMEL_5, VolcanionCave_Outside_Movement_JumpInPlaceUp
	delay 2
	playmoncry SPECIES_NUMEL, CRY_MODE_NORMAL
	applymovement LOCALID_OUTSIDE_NUMEL_2, VolcanionCave_Outside_Movement_JumpInPlaceUp
	delay 2
	playmoncry SPECIES_NUMEL, CRY_MODE_NORMAL
	applymovement LOCALID_OUTSIDE_NUMEL_4, VolcanionCave_Outside_Movement_JumpInPlaceUp
	delay 2
	playmoncry SPECIES_NUMEL, CRY_MODE_NORMAL
	applymovement LOCALID_OUTSIDE_NUMEL_1, VolcanionCave_Outside_Movement_JumpInPlaceUp
	waitmovement 0
	waitmoncry
	applymovement LOCALID_CAMERA, VolcanionCave_Outside_Movement_CameraMoveUp
	waitmovement 0
	special RemoveCameraObject
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceDown
	callnative IsPlayerOne
	call_if_eq VAR_RESULT, TRUE, VolcanionCave_Outside_EventScript_PlayerAquaIllGoBack
	call_if_eq VAR_RESULT, FALSE, VolcanionCave_Outside_EventScript_PlayerMagmaIllGoBack
	waitmovement 0
	waitmessage
	closemessage
	applymovement LOCALID_PLAYER, Common_Movement_WalkUp
	waitmovement 0
	warp MAP_VOLCANION_CAVE_1F, 19, 21
	waitstate
	release
	end

VolcanionCave_Outside_EventScript_PlayerAquaEllipsis::
	message VolcanionCave_Outside_Text_PlayerAquaEllipsis
	return

VolcanionCave_Outside_EventScript_PlayerMagmaEllipsis::
	message VolcanionCave_Outside_Text_PlayerMagmaEllipsis
	return

VolcanionCave_Outside_EventScript_PlayerAquaIllGoBack::
	message VolcanionCave_Outside_Text_PlayerAquaIllGoBack
	return

VolcanionCave_Outside_EventScript_PlayerMagmaIllGoBack::
	message VolcanionCave_Outside_Text_PlayerMagmaIllGoBack
	return

VolcanionCave_Outside_Text_ShellyEllipsis::
	.string "{SPEAKER NAME_SHELLY COLOR_AQUA}…\p$"

VolcanionCave_Outside_Text_CourtneyEllipsis::
	.string "{SPEAKER NAME_COURTNEY COLOR_MAGMA}…\p$"

VolcanionCave_Outside_Text_PlayerAquaEllipsis::
	.string "{SPEAKER NAME_PLAYER COLOR_AQUA}Hey SHELLY! How's it…\p$"

VolcanionCave_Outside_Text_PlayerMagmaEllipsis::
	.string "{SPEAKER NAME_PLAYER COLOR_MAGMA}…\p$"

VolcanionCave_Outside_Text_PlayerAquaIllGoBack::
	.string "{SPEAKER NAME_PLAYER COLOR_AQUA}HOLD ON, I FORGOT MY… {PAUSE 40}KEYS!!!\n"
	.string "I'LL BE RIGHT BACK!!!!!\p$"

VolcanionCave_Outside_Text_PlayerMagmaIllGoBack::
	.string "{SPEAKER NAME_PLAYER COLOR_MAGMA}…\p"
	.string "…point taken.\p$"

VolcanionCave_Outside_Movement_CameraMoveDown::
	walk_down
	walk_down
	step_end

VolcanionCave_Outside_Movement_CameraMoveUp::
	walk_up
	walk_up
	step_end

VolcanionCave_Outside_Movement_JumpInPlaceUp::
	jump_in_place_up
	step_end
