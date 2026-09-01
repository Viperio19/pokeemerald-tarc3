VolcanionCave_3F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, VolcanionCave_3F_OnTransition
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, VolcanionCave_3F_OnWarp
	map_script MAP_SCRIPT_ON_FRAME_TABLE, VolcanionCave_3F_OnFrame
	map_script MAP_SCRIPT_ON_LOAD, VolcanionCave_3F_OnLoad
	.byte 0

VolcanionCave_3F_OnTransition:
	call_if_ne VAR_VOLCANION_CAVE_3F_STATE, 0, VolcanionCave_3F_EventScript_SetWeatherFog
	end

VolcanionCave_3F_EventScript_SetWeatherFog::
	setweather WEATHER_FOG_HORIZONTAL
	return

VolcanionCave_3F_OnWarp:
	map_script_2 VAR_TEMP_1, 0, VolcanionCave_3F_EventScript_TrySpawnPlayer2
	.2byte 0

VolcanionCave_3F_EventScript_TrySpawnPlayer2::
	setvar VAR_TEMP_1, 1
	goto_if_eq VAR_VOLCANION_CAVE_3F_STATE, 0, VolcanionCave_3F_EventScript_SpawnHiddenPlayer2
	callnative TrySpawnPlayer2
	end

VolcanionCave_3F_EventScript_SpawnHiddenPlayer2::
	callnative SpawnPlayer2For3FIntro
	hideobjectat LOCALID_PLAYER_2, MAP_VOLCANION_CAVE_3F
	end

VolcanionCave_3F_OnFrame:
	map_script_2 VAR_VOLCANION_CAVE_3F_STATE, 0, VolcanionCave_3F_EventScript_EnterCave
	.2byte 0

#define LOCALID_PLAYER_AQUA  VAR_0x800A
#define LOCALID_PLAYER_MAGMA VAR_0x800B

VolcanionCave_3F_EventScript_EnterCave::
	lock
	special SpawnCameraObject
	callnative IsPlayerOne
	goto_if_eq VAR_RESULT, TRUE, VolcanionCave_3F_EventScript_PlayersEnter
	goto_if_eq VAR_RESULT, FALSE, VolcanionCave_3F_EventScript_PlayersEnter2
VolcanionCave_3F_EventScript_Intro::
	delay 10
	applymovement LOCALID_PLAYER_MAGMA, Common_Movement_WalkInPlaceFasterLeft
	applymovement LOCALID_PLAYER_AQUA, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	message VolcanionCave_3F_Text_IntroCoolRoom
	waitmessage
	closemessage
	applymovement LOCALID_PLAYER_MAGMA, Common_Movement_ExclamationMark
	delay 50
	message VolcanionCave_3F_Text_IHearSomething
	waitmessage
	closemessage
	call VolcanionCave_3F_EventScript_VolcanionCry
	applymovement LOCALID_PLAYER_AQUA, Common_Movement_WalkInPlaceUp
	applymovement LOCALID_PLAYER_MAGMA, Common_Movement_WalkInPlaceUp
	message VolcanionCave_3F_Text_IntroIsThat
	waitmovement 0
	waitmessage
	closemessage
	applymovement LOCALID_CAMERA, VolcanionCave_3F_Movement_CameraMoveUpToVolcanion
	applymovement LOCALID_PLAYER_AQUA, VolcanionCave_3F_Movement_PlayerApproachVolcanion
	applymovement LOCALID_PLAYER_MAGMA, VolcanionCave_3F_Movement_PlayerApproachVolcanion
	waitmovement 0
	delay 10
	call VolcanionCave_3F_EventScript_VolcanionCry
	closemessage
	applymovement LOCALID_CAMERA, VolcanionCave_3F_Movement_CameraMoveDown
	waitmovement 0
	message VolcanionCave_3F_Text_IntroTheLegendary
	waitmessage
	closemessage
	delay 30
	applymovement LOCALID_PLAYER_MAGMA, Common_Movement_WalkInPlaceFasterLeft
	applymovement LOCALID_PLAYER_AQUA, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	message VolcanionCave_3F_Text_IntroBothEllipsis
	waitmessage
	closemessage
	callnative IsPlayerOne
	call_if_eq VAR_RESULT, TRUE, VolcanionCave_3F_EventScript_CameraFollowAquaTryToLeave
	call_if_eq VAR_RESULT, FALSE, VolcanionCave_3F_EventScript_CameraFollowMagmaTryToStopAqua
	playse SE_PIN
	applymovement LOCALID_PLAYER_AQUA, VolcanionCave_3F_Movement_AquaTryToLeave
	applymovement LOCALID_PLAYER_MAGMA, VolcanionCave_3F_Movement_MagmaTryToStopAqua
	waitmovement 0
	message VolcanionCave_3F_Text_IntroCatchIt
	waitmessage
	closemessage
	applymovement LOCALID_CAMERA, VolcanionCave_3F_Movement_CameraMoveBackToVolcanion
	applymovement LOCALID_PLAYER_AQUA, VolcanionCave_3F_Movement_AquaWalkToVolcanion
	applymovement LOCALID_PLAYER_MAGMA, VolcanionCave_3F_Movement_MagmaWalkToVolcanion
	waitmovement 0
	delay 16
	setflag FLAG_SYS_WEATHER_CTRL
	setweather WEATHER_FOG_HORIZONTAL
	doweather
	call VolcanionCave_3F_EventScript_VolcanionCry
	closemessage
	special WaitWeather
	setwildbattle SPECIES_VOLCANION, 40, TRUE
	multi_fixed_players_vs_wild PARTNER_PLAYER_2
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, VolcanionCave_3F_EventScript_DefeatedVolcanion
	message VolcanionCave_3F_Text_IntroAwNuts
	waitmessage
	closemessage
	playbgm MUS_VS_VOLCANION, FALSE
	setvar VAR_CURRENT_HP_BAR_COLOR, 1
	call VolcanionCave_3F_EventScript_SetHPBar
	call VolcanionCave_3F_EventScript_VolcanionCry
	message VolcanionCave_3F_Text_IntroVolcanionUsedEarthPower
	waitmessage
	setvar VAR_0x8004, 0  @ Vertical pan
	setvar VAR_0x8005, 5  @ Horizontal pan
	setvar VAR_0x8006, 15  @ Num shakes
	setvar VAR_0x8007, 3  @ Shake delay
	special ShakeScreen
	playse SE_PIN
	applymovement LOCALID_PLAYER_AQUA, Common_Movement_ExclamationMark
	applymovement LOCALID_PLAYER_MAGMA, Common_Movement_ExclamationMark
	delay 50
	setvar VAR_0x8004, 0  @ Vertical pan
	setvar VAR_0x8005, 10  @ Horizontal pan
	setvar VAR_0x8006, 40  @ Num shakes
	setvar VAR_0x8007, 3  @ Shake delay
	special ShakeScreen
	applymovement LOCALID_CAMERA, VolcanionCave_3F_Movement_PlayerGetKnockedBack
	applymovement LOCALID_PLAYER_AQUA, VolcanionCave_3F_Movement_PlayerGetKnockedBack
	applymovement LOCALID_PLAYER_MAGMA, VolcanionCave_3F_Movement_PlayerGetKnockedBack
	closemessage
	waitmovement
	delay 20
	playse SE_M_ROCK_THROW
	call VolcanionCave_3F_EventScript_SetMetatilesRocksBroken
	special DrawWholeMapView
	setvar VAR_VOLCANION_CAVE_3F_STATE, 1
	fadedefaultbgm
	delay 100
	applymovement LOCALID_PLAYER_MAGMA, Common_Movement_WalkInPlaceFasterLeft
	applymovement LOCALID_PLAYER_AQUA, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	message VolcanionCave_3F_Text_IntroBattleAgainOrLookAround
	waitmessage
	closemessage
	special RemoveCameraObject
	special SpawnCameraObject
	callnative IsPlayerOne
	call_if_eq VAR_RESULT, TRUE, VolcanionCave_3F_EventScript_CameraResetToAqua
	call_if_eq VAR_RESULT, FALSE, VolcanionCave_3F_EventScript_CameraResetToMagma
	waitmovement 0
	special RemoveCameraObject
	release
	end

VolcanionCave_3F_EventScript_PlayersEnter::
	applymovement LOCALID_CAMERA, VolcanionCave_3F_Movement_CameraMoveWithPlayersEntering
	applymovement LOCALID_PLAYER, VolcanionCave_3F_Movement_PlayerAquaEnterCave
	applymovement LOCALID_PLAYER_2, VolcanionCave_3F_Movement_Player2MagmaEnterCave
	waitmovement 0
	setvar LOCALID_PLAYER_AQUA, LOCALID_PLAYER
	setvar LOCALID_PLAYER_MAGMA, LOCALID_PLAYER_2
	goto VolcanionCave_3F_EventScript_Intro
	end

VolcanionCave_3F_EventScript_PlayersEnter2::
	applymovement LOCALID_CAMERA, VolcanionCave_3F_Movement_CameraMoveWithPlayersEntering
	applymovement LOCALID_PLAYER, VolcanionCave_3F_Movement_PlayerMagmaEnterCave
	applymovement LOCALID_PLAYER_2, VolcanionCave_3F_Movement_Player2AquaEnterCave
	waitmovement 0
	setvar LOCALID_PLAYER_AQUA, LOCALID_PLAYER_2
	setvar LOCALID_PLAYER_MAGMA, LOCALID_PLAYER
	goto VolcanionCave_3F_EventScript_Intro
	end

VolcanionCave_3F_EventScript_VolcanionCry::
	setvar VAR_0x8004, 0  @ Vertical pan
	setvar VAR_0x8005, 3  @ Horizontal pan
	setvar VAR_0x8006, 10  @ Num shakes
	setvar VAR_0x8007, 4  @ Shake delay
	message VolcanionCave_3F_Text_IntroVolcanionCry
	playmoncry SPECIES_VOLCANION, CRY_MODE_NORMAL
	special ShakeScreen
	delay 30
	waitmoncry
	return

VolcanionCave_3F_EventScript_CameraFollowAquaTryToLeave::
	applymovement LOCALID_CAMERA, VolcanionCave_3F_Movement_CameraFollowAquaTryToLeave
	return

VolcanionCave_3F_EventScript_CameraFollowMagmaTryToStopAqua::
	applymovement LOCALID_CAMERA, VolcanionCave_3F_Movement_CameraFollowMagmaTryToStopAqua
	return

VolcanionCave_3F_EventScript_CameraResetToAqua::
	applymovement LOCALID_CAMERA, VolcanionCave_3F_Movement_CameraResetToAqua
	return

VolcanionCave_3F_EventScript_CameraResetToMagma::
	applymovement LOCALID_CAMERA, VolcanionCave_3F_Movement_CameraResetToMagma
	return

VolcanionCave_3F_Movement_PlayerAquaEnterCave::
	walk_up
	walk_up
	walk_left
	walk_up
	step_end

VolcanionCave_3F_Movement_PlayerMagmaEnterCave::
	walk_up
	walk_up
	walk_right
	walk_up
	step_end

VolcanionCave_3F_Movement_Player2AquaEnterCave::
	delay_16
	set_visible
	walk_up
	walk_up
	walk_up
	walk_left
	walk_up
	step_end

VolcanionCave_3F_Movement_Player2MagmaEnterCave::
	delay_16
	set_visible
	walk_up
	walk_up
	walk_up
	walk_right
	walk_up
	step_end

VolcanionCave_3F_Movement_CameraMoveWithPlayersEntering::
	walk_up
	walk_up
	walk_up
	step_end

VolcanionCave_3F_Movement_PlayerApproachVolcanion::
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

VolcanionCave_3F_Movement_CameraMoveUpToVolcanion::
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

VolcanionCave_3F_Movement_AquaTryToLeave::
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

VolcanionCave_3F_Movement_MagmaTryToStopAqua::
	emote_exclamation_mark
	delay_8
	walk_in_place_fast_down
	walk_in_place_fast_down
	delay_8
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_left
	walk_faster_left
	walk_in_place_fast_up
	step_end

VolcanionCave_3F_Movement_CameraFollowAquaTryToLeave::
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

VolcanionCave_3F_Movement_CameraFollowMagmaTryToStopAqua::
	delay_8
	walk_in_place_fast_down
	walk_in_place_fast_down
	delay_8
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	step_end

VolcanionCave_3F_Movement_CameraMoveDown::
	walk_down
	walk_down
	step_end

VolcanionCave_3F_Movement_AquaWalkToVolcanion::
	delay_16
	delay_16
	walk_right
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_left
	walk_in_place_up
	step_end

VolcanionCave_3F_Movement_MagmaWalkToVolcanion::
	walk_right
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_right
	walk_in_place_up
	step_end

VolcanionCave_3F_Movement_CameraMoveBackToVolcanion::
	delay_16
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

VolcanionCave_3F_Movement_PlayerGetKnockedBack::
	lock_facing_direction
	jump_2_down
	unlock_facing_direction
	step_end

VolcanionCave_3F_Movement_CameraResetToAqua::
	walk_left
	step_end

VolcanionCave_3F_Movement_CameraResetToMagma::
	walk_right
	step_end

VolcanionCave_3F_Text_IntroCoolRoom::
	.string "{SPEAKER NAME_PLAYER_AQUA COLOR_AQUA}Phew, it sure is warm in here!\p"
	.string "{SPEAKER NAME_PLAYER_MAGMA COLOR_MAGMA}Tch… this humidity is ruining my hair.\p"
	.string "{SPEAKER NAME_PLAYER_AQUA COLOR_AQUA}You wear a hoodie though???\p"
	.string "{SPEAKER NAME_PLAYER_MAGMA COLOR_MAGMA}Yes. {PAUSE 40}Fantastic observation.\p"
	.string "You got me real good there.\n"
	.string "Ten points to TEAM AQUA.\p"
	.string "{SPEAKER NAME_PLAYER_AQUA COLOR_AQUA}{FONT 5}yes!!! ten points!!!!\p"
	.string "{SPEAKER NAME_PLAYER_MAGMA COLOR_MAGMA}{FONT_NORMAL}That was… {FONT 5}oh forget it.\p$"

VolcanionCave_3F_Text_IHearSomething::
	.string "{SPEAKER NAME_PLAYER_MAGMA COLOR_MAGMA}{FONT_NORMAL}Wait a moment, I think I can\n"
	.string "hear something moving.\p$"

VolcanionCave_3F_Text_IntroIsThat::
	.string "{SPEAKER NAME_PLAYER_AQUA COLOR_AQUA}OVER THERE!! IS THAT-\p$"

VolcanionCave_3F_Text_IntroTheLegendary::
	.string "{SPEAKER NAME_PLAYER_MAGMA COLOR_MAGMA}It certainly matches the reports.\p"
	.string "{SPEAKER NAME_PLAYER_AQUA COLOR_AQUA}That's the LEGENDARY POKéMON\n"
	.string "I've been looking for!\p$"

VolcanionCave_3F_Text_IntroBothEllipsis::
	.string "{SPEAKER NAME_PLAYER_MAGMA COLOR_MAGMA}Interesting.\p"
	.string "{SPEAKER NAME_PLAYER_AQUA COLOR_AQUA}Thats ALL you have to say about this??\p"
	.string "{SPEAKER NAME_PLAYER_MAGMA COLOR_MAGMA}It seems your ADMINS aren't quite\n"
	.string "as incompetent as I thought.\l"
	.string "They actually got one of the\l"
	.string "LEGENDARY POKéMON's types right.\p"
	.string "{SPEAKER NAME_PLAYER_AQUA COLOR_AQUA}YOU TAKE THAT BACK!!\p"
	.string "NOT THE PART ABOUT THEM BEING RIGHT!!!\n"
	.string "THE INCOMPETENT PART!!!!!\p"
	.string "I'll have you know that SHELLY is on\n"
	.string "her way down here right now because\l"
	.string "she doesn't want us to get hurt\l"
	.string "while trying to catch this POKéMON.\p"
	.string "I bet your ADMINS don't even care\n"
	.string "enough about your well-being to\l"
	.string "help out in person, am I right?\p"
	.string "{SPEAKER NAME_PLAYER_MAGMA COLOR_MAGMA}INFURIATINGLY, yes.\p"
	.string "{SPEAKER NAME_PLAYER_AQUA COLOR_AQUA}Well, toodles! My job here is DONE!!\p"
	.string "Good luck catching a LEGENDARY\n"
	.string "with your regular POKé BALLS!!!\p$"

VolcanionCave_3F_Text_IntroCatchIt::
	.string "{SPEAKER NAME_PLAYER_MAGMA COLOR_MAGMA}Hold on, you're just leaving\n"
	.string "me to die here?\p"
	.string "{SPEAKER NAME_PLAYER_AQUA COLOR_AQUA}I mean… not exactly??\p"
	.string "{SPEAKER NAME_PLAYER_MAGMA COLOR_MAGMA}{FONT 5}(Hook.)\p"
	.string "{FONT_NORMAL}Remember, catching this LEGENDARY\n"
	.string "is also TEAM MAGMA'S goal here.\p"
	.string "And look at me, a TEAM MAGMA GRUNT\n"
	.string "ordered to put their life on the line\l"
	.string "just to catch a single POKéMON.\p"
	.string "You know me, I'm not going\n"
	.string "down without a fight.\p"
	.string "{SPEAKER NAME_PLAYER_AQUA COLOR_AQUA}Yeah, but…\p"
	.string "{SPEAKER NAME_PLAYER_MAGMA COLOR_MAGMA}{FONT 5}(Line.)\p"
	.string "{FONT_NORMAL}According to my calculations, I have a\n"
	.string "3.557% chance to catch it per ball.\p"
	.string "In the time it takes you to find SHELLY,\n"
	.string "how many POKé BALLS will I have thrown?\p"
	.string "20? {PAUSE 40}50? {PAUSE 40}100?\p"
	.string "I have a surprisingly fast\n"
	.string "throwing arm, you know.\p"
	.string "Do you really want to bet the success\n"
	.string "of your mission on a chance that isn't\l"
	.string "even in your favour?\p"
	.string "{SPEAKER NAME_PLAYER_AQUA COLOR_AQUA}Oh… {PAUSE 20}FINE!!!\p"
	.string "I'll catch this LEGENDARY and get\n"
	.string "out of here faster than the speed of\l"
	.string "SHELLY'S SHARPEDO multiplied by 5!!!\p"
	.string "{SPEAKER NAME_PLAYER_MAGMA COLOR_MAGMA}…\p"
	.string "{AUTO_SCROLL 1}{FONT 5}(Sinker.){PAUSE 80}\p"
	.string "{AUTO_SCROLL 0}wait damn it that was a fishing reference\p"
	.string "{FONT_NORMAL}Alright then, it's a challenge.\n"
	.string "Whoever knocks it out gets to catch it.\p"
	.string "{SPEAKER NAME_PLAYER_AQUA COLOR_AQUA}Fine by me! Let's go!!!\p$"

VolcanionCave_3F_Text_IntroVolcanionCry::
	.string "{SPEAKER NAME_VOLCANION COLOR_NORMAL}FWAHHRSHHHH!!!$"

VolcanionCave_3F_Text_IntroAwNuts::
	.string "{SPEAKER NAME_PLAYER_AQUA COLOR_AQUA}YOWZA!! That is one strong POKéMON!\p"
	.string "That's it, I'm getting out of-\p$"

VolcanionCave_3F_Text_IntroVolcanionUsedEarthPower::
	.string "{AUTO_SCROLL 1}{SPEAKER NAME_PLAYER_MAGMA COLOR_MAGMA}What the-{PAUSE 20}\p"
	.string "{AUTO_SCROLL 0}{SPEAKER NAME_NONE COLOR_NORMAL}VOLCANION used EARTH POWER!$"

VolcanionCave_3F_Text_IntroBattleAgainOrLookAround::
	.string "{SPEAKER NAME_PLAYER_AQUA COLOR_AQUA}Oof, that was a close one!\n"
	.string "You still alive, {PLAYER_MAGMA}?\p"
	.string "{SPEAKER NAME_PLAYER_MAGMA COLOR_MAGMA}Regrettably, I am.\p"
	.string "On the bright side, its attack\n"
	.string "destroyed the rocks over there.\p"
	.string "{SPEAKER NAME_PLAYER_AQUA COLOR_AQUA}Perfect, let's see if there's anything\n"
	.string "in here we can use to teach that meanie\l"
	.string "VOLCANION not to mess with us!\p"
	.string "{SPEAKER NAME_PLAYER_MAGMA COLOR_MAGMA}You named it already?\n"
	.string "And why did you call it VOLCANION??\p"
	.string "{SPEAKER NAME_PLAYER_AQUA COLOR_AQUA}Well, we found it in VOLCANO CAVERN\n"
	.string "and ion know what its deal is!\p"
	.string "{SPEAKER NAME_PLAYER_MAGMA COLOR_MAGMA}Unbelievable…\p"
	.string "It's too bad that the first person who\n"
	.string "sees a POKéMON has full legal rights to\l"
	.string "decide the name of its species forever.\p"
	.string "{SPEAKER NAME_PLAYER_AQUA COLOR_AQUA}IM GONNA BE FAMOUS!!!!\p"
	.string "{SPEAKER NAME_PLAYER_MAGMA COLOR_MAGMA}If you can get out of here in\n"
	.string "one piece, maybe.\p"
	.string "{SPEAKER NAME_PLAYER_AQUA COLOR_AQUA}What are we waiting here for then?\n"
	.string "Let's go!!!\p$"

VolcanionCave_3F_OnLoad::
	call_if_ne VAR_VOLCANION_CAVE_2F_STRENGTH_BUTTON_1, 100, VolcanionCave_3F_EventScript_SetRockBarrier1
	call_if_eq VAR_TEMP_F, 1, VolcanionCave_3F_EventScript_SetMetatilesBlueButtonPressed
	call_if_ge VAR_VOLCANION_CAVE_3F_STATE, 1, VolcanionCave_3F_EventScript_SetMetatilesRocksBroken
	call_if_eq VAR_GOLEM_ROCK_SLIDE_STATE, 0, VolcanionCave_3F_EventScript_SetMetatilesNoRockSlideBlockade
	call_if_ne VAR_GOLEM_ROCK_SLIDE_STATE, 0, VolcanionCave_3F_EventScript_SetMetatilesRockSlideBlockade
	call VolcanionCave_3F_EventScript_SetHPBar
	end

VolcanionCave_3F_EventScript_SetRockBarrier1::
	@ setmetatile 26, 64, METATILE_Cave_RockBarrier_Left, TRUE
	@ setmetatile 27, 64, METATILE_Cave_RockBarrier_MiddleHorizontal, TRUE
	@ setmetatile 28, 64, METATILE_Cave_RockBarrier_Right, TRUE
	return

VolcanionCave_3F_EventScript_BlueButton::
	lockall
	setvar VAR_TEMP_F, 1
	playse SE_PIN
	call VolcanionCave_3F_EventScript_SetMetatilesBlueButtonPressed
	special DrawWholeMapView
	releaseall
	end

VolcanionCave_3F_EventScript_RedButton::
	lockall
	setvar VAR_TEMP_F, 0
	playse SE_PIN
	call VolcanionCave_3F_EventScript_SetMetatilesRedButtonPressed
	special DrawWholeMapView
	releaseall
	end

VolcanionCave_3F_EventScript_SetMetatilesBlueButtonPressed::
	@ setmetatile 7, 48, METATILE_Cave_CoolButton_Pressed, FALSE
	@ setmetatile 11, 46, METATILE_Cave_CoolButton_Red, FALSE
	@ setmetatile 10, 46, METATILE_Cave_CoolGem_Blue_Ground_Empty, FALSE
	@ setmetatile 8, 50, METATILE_Cave_CoolGem_Red_Ground_Full, TRUE
	return

VolcanionCave_3F_EventScript_SetMetatilesRedButtonPressed::
	@ setmetatile 7, 48, METATILE_Cave_CoolButton_Blue, FALSE
	@ setmetatile 11, 46, METATILE_Cave_CoolButton_Pressed, FALSE
	@ setmetatile 10, 46, METATILE_Cave_CoolGem_Blue_Ground_Full, TRUE
	@ setmetatile 8, 50, METATILE_Cave_CoolGem_Red_Ground_Empty, FALSE
	return

VolcanionCave_3F_EventScript_SetMetatilesRocksBroken::
	setmetatile 10, 24, METATILE_Cave_Floor_Smooth_Top, FALSE
	setmetatile 10, 25, METATILE_Cave_Floor_Smooth, FALSE
	setmetatile 9, 25, METATILE_Cave_Floor_Smooth, FALSE
	setmetatile 9, 26, METATILE_Cave_Floor_Smooth, FALSE
	setmetatile 22, 24, METATILE_Cave_Floor_Smooth_Top, FALSE
	setmetatile 22, 25, METATILE_Cave_Floor_Smooth, FALSE
	setmetatile 23, 25, METATILE_Cave_Floor_Smooth, FALSE
	setmetatile 23, 26, METATILE_Cave_Floor_Smooth, FALSE
	return

VolcanionCave_3F_EventScript_SetHPBar::
	call_if_ne VAR_LOCALID_CURRENT_HP_BAR, 0, VolcanionCave_3F_EventScript_RemoveHPBar
	setvar VAR_LOCALID_CURRENT_HP_BAR, 0
	switch VAR_CURRENT_HP_BAR_COLOR
	case_call 1, VolcanionCave_3F_EventScript_SetHPBarGreen
	case_call 2, VolcanionCave_3F_EventScript_SetHPBarYellow
	case_call 3, VolcanionCave_3F_EventScript_SetHPBarRed
	goto_if_eq VAR_LOCALID_CURRENT_HP_BAR, 0, VolcanionCave_3F_EventScript_AddNoHPBar
	addobject VAR_LOCALID_CURRENT_HP_BAR
	setobjectxyperm VAR_LOCALID_CURRENT_HP_BAR, 16, 19
	setobjectxy VAR_LOCALID_CURRENT_HP_BAR, 16, 19
	return

VolcanionCave_3F_EventScript_RemoveHPBar::
	setobjectxyperm VAR_LOCALID_CURRENT_HP_BAR, 43, 18
	setobjectxy VAR_LOCALID_CURRENT_HP_BAR, 43, 18
	return

VolcanionCave_3F_EventScript_AddNoHPBar::
	return

VolcanionCave_3F_EventScript_SetHPBarGreen::
	setvar VAR_LOCALID_CURRENT_HP_BAR LOCALID_3F_HP_BAR_GREEN
	return

VolcanionCave_3F_EventScript_SetHPBarYellow::
	setvar VAR_LOCALID_CURRENT_HP_BAR LOCALID_3F_HP_BAR_YELLOW
	return

VolcanionCave_3F_EventScript_SetHPBarRed::
	setvar VAR_LOCALID_CURRENT_HP_BAR LOCALID_3F_HP_BAR_RED
	return

VolcanionCave_3F_EventScript_Volcanion::
	call VolcanionCave_3F_EventScript_VolcanionCry
	closemessage
	goto_if_unset FLAG_PLAYER_2_READY_TO_BATTLE_TOGETHER, VolcanionCave_3F_EventScript_AskVolcanionMultiBattle
	clearflag FLAG_PLAYER_2_READY_TO_BATTLE_TOGETHER
	getplayerxy VAR_0x8008, VAR_0x8009
	callnative IsPlayerOne
	call_if_eq VAR_RESULT, TRUE, VolcanionCave_3F_EventScript_PlayerWalkLeftForBattle
	call_if_eq VAR_RESULT, FALSE, VolcanionCave_3F_EventScript_PlayerWalkRightForBattle
	setwildbattle SPECIES_VOLCANION, 40, TRUE
	multi_fixed_players_vs_wild PARTNER_PLAYER_2
	specialvar VAR_RESULT, GetBattleOutcome
	@ TODO: change to goto_if_eq (currently goto_if_ne for testing purposes)
	goto_if_ne VAR_RESULT, B_OUTCOME_WON, VolcanionCave_3F_EventScript_DefeatedVolcanion
	call VolcanionCave_3F_EventScript_VolcanionCry
	closemessage
	release
	end

VolcanionCave_3F_EventScript_AskVolcanionMultiBattle::
	delay 10
	msgbox VolcanionCave_3F_Text_BattleTogether, MSGBOX_YESNO
	switch VAR_RESULT
	case YES, VolcanionCave_3F_EventScript_GetReadyForVolcanionMultiBattle
	closemessage
	release
	end

VolcanionCave_3F_EventScript_GetReadyForVolcanionMultiBattle::
	closemessage
	setflag FLAG_SET_PLAYER_2_FOR_VOLCANION_BATTLE
	setflag FLAG_PLAYER_2_READY_TO_BATTLE_TOGETHER
	callnative SwitchCharacters
	waitstate
	release
	end

VolcanionCave_3F_EventScript_PlayerWalkDownForBattle::
	applymovement LOCALID_PLAYER, VolcanionCave_3F_Movement_PlayerWalkDownForBattle
	waitmovement 0
	return

VolcanionCave_3F_EventScript_PlayerWalkLeftForBattle::
	goto_if_eq VAR_0x8009, 21, VolcanionCave_3F_EventScript_PlayerWalkDownForBattle
	applymovement LOCALID_PLAYER, VolcanionCave_3F_Movement_PlayerWalkLeftForBattle
	waitmovement 0
	return

VolcanionCave_3F_EventScript_PlayerWalkRightForBattle::
	goto_if_eq VAR_0x8009, 21, VolcanionCave_3F_EventScript_PlayerWalkDownForBattle
	applymovement LOCALID_PLAYER, VolcanionCave_3F_Movement_PlayerWalkRightForBattle
	waitmovement 0
	return

VolcanionCave_3F_Movement_PlayerWalkDownForBattle::
	walk_down
	walk_in_place_up
	step_end

VolcanionCave_3F_Movement_PlayerWalkLeftForBattle::
	walk_left
	walk_in_place_up
	step_end

VolcanionCave_3F_Movement_PlayerWalkRightForBattle::
	walk_right
	walk_in_place_up
	step_end

VolcanionCave_3F_EventScript_DefeatedVolcanion::
	setvar VAR_CURRENT_HP_BAR_COLOR, 0
	call VolcanionCave_3F_EventScript_SetHPBar
	playmoncry SPECIES_VOLCANION, CRY_MODE_NORMAL
	message VolcanionCave_3F_Text_VolcanionCryDefeated
	waitmessage
	waitmoncry
	callnative IsPlayerOne
	call_if_eq VAR_RESULT, TRUE, VolcanionCave_3F_EventScript_SetLocalIdsPlayer1
	call_if_eq VAR_RESULT, FALSE, VolcanionCave_3F_EventScript_SetLocalIdsPlayer2
	applymovement LOCALID_PLAYER_MAGMA, Common_Movement_WalkInPlaceFasterLeft
	applymovement LOCALID_PLAYER_AQUA, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	message VolcanionCave_3F_Text_WeDidIt
	waitmessage
	closemessage
	release
	end

VolcanionCave_3F_EventScript_SetLocalIdsPlayer1::
	setvar LOCALID_PLAYER_AQUA, LOCALID_PLAYER
	setvar LOCALID_PLAYER_MAGMA, LOCALID_PLAYER_2
	return

VolcanionCave_3F_EventScript_SetLocalIdsPlayer2::
	setvar LOCALID_PLAYER_AQUA, LOCALID_PLAYER_2
	setvar LOCALID_PLAYER_MAGMA, LOCALID_PLAYER
	return

VolcanionCave_3F_Text_BattleTogether::
	.string "Battle together?$"

VolcanionCave_3F_Text_VolcanionCryDefeated::
	.string "{SPEAKER NAME_VOLCANION COLOR_NORMAL}FWAHHRSHHHH…$"

VolcanionCave_3F_Text_WeDidIt::
	.string "{SPEAKER NAME_PLAYER_AQUA COLOR_AQUA}We did it!\p$"

VolcanionCave_3F_EventScript_ZinniaEnter::
	setvar VAR_ZINNIA_STATE, 1
	addobject LOCALID_3F_ZINNIA
	addobject LOCALID_3F_WHISMUR
	release
	end

VolcanionCave_3F_EventScript_Zinnia::
	release
	end

VolcanionCave_3F_EventScript_Whismur::
	release
	end

VolcanionCave_3F_EventScript_Golem::
	applymovement LOCALID_3F_GOLEM, Common_Movement_FacePlayer
	goto_if_set FLAG_ROCK_SLIDE_HIT_VOLCANION, VolcanionCave_3F_EventScript_GolemSatisfied
	call VolcanionCave_3F_EventScript_SetMetatilesRockSlideBlockade
	special DrawWholeMapView
	playmoncry SPECIES_GOLEM_ALOLA, CRY_MODE_ENCOUNTER
	message VolcanionCave_3F_Text_GolemCry
	waitmoncry
	waitmessage
	closemessage
	delay 10
	goto_if_set FLAG_TALKED_VOLCANION_CAVE_3F_GOLEM, VolcanionCave_3F_EventScript_GolemUsedRockSlide
	setflag FLAG_TALKED_VOLCANION_CAVE_3F_GOLEM
	message VolcanionCave_3F_Text_GolemSeemsAngry
	waitmessage
	closemessage
	delay 20
	playbgm MUS_VS_VOLCANION, FALSE
	call VolcanionCave_3F_EventScript_RockSlideSpawnRocks
	message VolcanionCave_3F_Text_GolemUsedRockSlide
	applymovement LOCALID_PLAYER, VolcanionCave_3F_Movement_PlayerNoticeRockSlide
	waitmovement 0
	waitmessage
	closemessage
	applymovement LOCALID_PLAYER, VolcanionCave_3F_Movement_PlayerDodgeRockUp
	call VolcanionCave_3F_EventScript_RockSlideDropRocks
	callnative IsPlayerOne
	call_if_eq VAR_RESULT, TRUE, VolcanionCave_3F_EventScript_MaybeICanUseThisAqua
	call_if_eq VAR_RESULT, FALSE, VolcanionCave_3F_EventScript_MaybeICanUseThisMagma
	waitmessage
	call VolcanionCave_3F_EventScript_RockSlideSpawnRocks
	applymovement LOCALID_PLAYER, VolcanionCave_3F_Movement_PlayerNoticeRockSlide
	waitmovement 0
	delay 20
	callnative IsPlayerOne
	call_if_eq VAR_RESULT, TRUE, VolcanionCave_3F_EventScript_GottaRunAqua
	call_if_eq VAR_RESULT, FALSE, VolcanionCave_3F_EventScript_GottaRunMagma
	applymovement LOCALID_PLAYER, VolcanionCave_3F_Movement_PlayerDodgeRockDown
	call VolcanionCave_3F_EventScript_RockSlideDropRocks
	closemessage
	setvar VAR_GOLEM_ROCK_SLIDE_STATE, 1
	delay 70
	goto VolcanionCave_3F_EventScript_RockSlide
	end

VolcanionCave_3F_EventScript_GolemUsedRockSlide::
	playbgm MUS_VS_VOLCANION, FALSE
	call VolcanionCave_3F_EventScript_RockSlideSpawnRocks
	message VolcanionCave_3F_Text_GolemUsedRockSlide
	applymovement LOCALID_PLAYER, VolcanionCave_3F_Movement_PlayerNoticeRockSlide
	waitmovement 0
	waitmessage
	delay 20
	callnative IsPlayerOne
	call_if_eq VAR_RESULT, TRUE, VolcanionCave_3F_EventScript_GottaRunAqua
	call_if_eq VAR_RESULT, FALSE, VolcanionCave_3F_EventScript_GottaRunMagma
	applymovement LOCALID_PLAYER, VolcanionCave_3F_Movement_PlayerDodgeRockUp
	call VolcanionCave_3F_EventScript_RockSlideDropRocks
	closemessage
	setvar VAR_GOLEM_ROCK_SLIDE_STATE, 1
	delay 70
	goto VolcanionCave_3F_EventScript_RockSlide
	end

VolcanionCave_3F_EventScript_RockSlide::
	call VolcanionCave_3F_EventScript_RockSlideSpawnRocks
	call VolcanionCave_3F_EventScript_RockSlideDropRocks

	goto_if_eq VAR_GOLEM_ROCK_SLIDE_STATE, 3, VolcanionCave_3F_EventScript_RockSlideHitVolcanion
	goto_if_eq VAR_GOLEM_ROCK_SLIDE_STATE, 2, VolcanionCave_3F_EventScript_RockSlideHitPlayer

	delay 70
	goto VolcanionCave_3F_EventScript_RockSlide

VolcanionCave_3F_EventScript_RockSlideSpawnRocks::
	@ Shake screen
	setvar VAR_0x8004, 0  @ Vertical pan
	setvar VAR_0x8005, 3  @ Horizontal pan
	setvar VAR_0x8006, 10  @ Num shakes
	setvar VAR_0x8007, 4  @ Shake delay
	special ShakeScreen

	@ Spawn rocks
	getplayerxy VAR_0x8008, VAR_0x8009

	subvar VAR_0x8009, 5
	subvar VAR_0x8008, 1
	addobject LOCALID_3F_ROCK_SLIDE_1
	setobjectsubpriority LOCALID_3F_ROCK_SLIDE_1, MAP_VOLCANION_CAVE_3F, 200
	setobjectxyperm LOCALID_3F_ROCK_SLIDE_1, VAR_0x8008, VAR_0x8009
	setobjectxy LOCALID_3F_ROCK_SLIDE_1, VAR_0x8008, VAR_0x8009

	addvar VAR_0x8008, 1
	addobject LOCALID_3F_ROCK_SLIDE_2
	setobjectsubpriority LOCALID_3F_ROCK_SLIDE_2, MAP_VOLCANION_CAVE_3F, 200
	setobjectxyperm LOCALID_3F_ROCK_SLIDE_2, VAR_0x8008, VAR_0x8009
	setobjectxy LOCALID_3F_ROCK_SLIDE_2, VAR_0x8008, VAR_0x8009

	addvar VAR_0x8008, 1
	addobject LOCALID_3F_ROCK_SLIDE_3
	setobjectsubpriority LOCALID_3F_ROCK_SLIDE_3, MAP_VOLCANION_CAVE_3F, 200
	setobjectxyperm LOCALID_3F_ROCK_SLIDE_3, VAR_0x8008, VAR_0x8009
	setobjectxy LOCALID_3F_ROCK_SLIDE_3, VAR_0x8008, VAR_0x8009
	return

VolcanionCave_3F_EventScript_RockSlideDropRocks::
	@ Drop rocks
	applymovement LOCALID_3F_ROCK_SLIDE_1, VolcanionCave_3F_Movement_Rock1FallDown
	applymovement LOCALID_3F_ROCK_SLIDE_3, VolcanionCave_3F_Movement_Rock3FallDown
	applymovement LOCALID_3F_ROCK_SLIDE_2, VolcanionCave_3F_Movement_Rock2FallDown
	delay 30
	playse SE_FALL
	delay 20
	playse SE_M_ROCK_THROW
	delay 8
	playse SE_M_ROCK_THROW
	delay 8
	playse SE_M_ROCK_THROW
	waitmovement 0

	@ Remove rocks
	setobjectxyperm LOCALID_3F_ROCK_SLIDE_1, 39, 34
	removeobject LOCALID_3F_ROCK_SLIDE_1
	setobjectxyperm LOCALID_3F_ROCK_SLIDE_3, 39, 36
	removeobject LOCALID_3F_ROCK_SLIDE_3
	setobjectxyperm LOCALID_3F_ROCK_SLIDE_2, 39, 33
	removeobject LOCALID_3F_ROCK_SLIDE_2
	return

VolcanionCave_3F_EventScript_MaybeICanUseThisAqua::
	message VolcanionCave_3F_Text_MaybeICanUseThisAqua
	return

VolcanionCave_3F_EventScript_MaybeICanUseThisMagma::
	message VolcanionCave_3F_Text_MaybeICanUseThisMagma
	return

VolcanionCave_3F_EventScript_GottaRunAqua::
	message VolcanionCave_3F_Text_GottaRunAqua
	return

VolcanionCave_3F_EventScript_GottaRunMagma::
	message VolcanionCave_3F_Text_GottaRunMagma
	return

VolcanionCave_3F_EventScript_SetMetatilesRockSlideBlockade::
	setmetatile 6, 24, METATILE_Cave_Rock_1, TRUE
	setmetatile 5, 25, METATILE_Cave_Rock_1, TRUE
	setmetatile 6, 26, METATILE_Cave_Rock_2, TRUE
	setmetatile 26, 24, METATILE_Cave_Rock_2, TRUE
	setmetatile 27, 25, METATILE_Cave_Rock_1, TRUE
	setmetatile 28, 26, METATILE_Cave_Rock_2, TRUE
	setmetatile 16, 33, METATILE_Cave_Rock_2, TRUE
	return

VolcanionCave_3F_EventScript_SetMetatilesNoRockSlideBlockade::
	setmetatile 6, 24, METATILE_Cave_Floor_Smooth, FALSE
	setmetatile 5, 25, METATILE_Cave_Floor_Smooth, FALSE
	setmetatile 6, 26, METATILE_Cave_Floor_Smooth, FALSE
	setmetatile 26, 24, METATILE_Cave_Floor_Smooth, FALSE
	setmetatile 27, 25, METATILE_Cave_Floor_Smooth, FALSE
	setmetatile 28, 26, METATILE_Cave_Floor_Smooth, FALSE
	setmetatile 16, 33, METATILE_Cave_Floor_Smooth, FALSE
	return

VolcanionCave_3F_Movement_Rock1FallDown::
	delay_16
	delay_16
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	rock_smash_break
	step_end

VolcanionCave_3F_Movement_Rock3FallDown::
	delay_16
	delay_16
	delay_8
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	rock_smash_break
	step_end

VolcanionCave_3F_Movement_Rock2FallDown::
	delay_16
	delay_16
	delay_8
	delay_8
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	rock_smash_break
	step_end

VolcanionCave_3F_Movement_PlayerNoticeRockSlide::
	face_up
	emote_exclamation_mark
	step_end

VolcanionCave_3F_Movement_PlayerDodgeRockUp::
	walk_in_place_fast_up
	walk_in_place_fast_up
	walk_in_place_fast_up
	delay_16
	delay_8
	jump_up
	face_down
	step_end

VolcanionCave_3F_Movement_PlayerDodgeRockDown::
	walk_in_place_fast_up
	walk_in_place_fast_up
	walk_in_place_fast_up
	delay_16
	delay_8
	jump_up
	step_end

VolcanionCave_3F_Text_GolemCry::
	.string "{SPEAKER NAME_GOLEM COLOR_NORMAL}GOOOOLEM!\p$"

VolcanionCave_3F_Text_GolemSeemsAngry::
	.string "GOLEM seems angry!\p$"

VolcanionCave_3F_Text_GolemSeemsSatisfied::
	.string "GOLEM seems satisfied!\p$"

VolcanionCave_3F_Text_GolemUsedRockSlide::
	.string "GOLEM used ROCK SLIDE!{PAUSE 40}$"

VolcanionCave_3F_Text_MaybeICanUseThisAqua::
	.string "{SPEAKER NAME_PLAYER COLOR_AQUA} Maybe I can use this.{PAUSE 25}.{PAUSE 25}.$"

VolcanionCave_3F_Text_MaybeICanUseThisMagma::
	.string "{SPEAKER NAME_PLAYER COLOR_MAGMA} Maybe I can use this.{PAUSE 25}.{PAUSE 25}.$"

VolcanionCave_3F_Text_GottaRunAqua::
	.string "{SPEAKER NAME_PLAYER COLOR_AQUA} Uh oh!{PAUSE 40} Gotta run!$"

VolcanionCave_3F_Text_GottaRunMagma::
	.string "{SPEAKER NAME_PLAYER COLOR_MAGMA} Uh oh!{PAUSE 40} Gotta run!$"

VolcanionCave_3F_EventScript_RockSlideHitPlayer::
	setvar VAR_GOLEM_ROCK_SLIDE_STATE, 4
	applymovement LOCALID_PLAYER, VolcanionCave_3F_Movement_PlayerFlicker
	waitmovement 0
	fadedefaultbgm
	message VolcanionCave_3F_Text_YouGotHit
	waitmessage
	closemessage
	release
	end

VolcanionCave_3F_Movement_PlayerFlicker::
	set_invisible
	delay_8
	set_visible
	delay_8
	set_invisible
	delay_8
	set_visible
	delay_8
	set_invisible
	delay_8
	set_visible
	step_end

VolcanionCave_3F_Text_YouGotHit::
	.string "Oh nooooo you got hit!\p"
	.string "GOLEM seems to be satisfied\n"
	.string "and stopped using ROCK SLIDE.\p"
	.string "For now…\p$"

VolcanionCave_3F_EventScript_RockSlideHitVolcanion::
	call VolcanionCave_3F_EventScript_SetMetatilesNoRockSlideBlockade
	special DrawWholeMapView
	setflag FLAG_ROCK_SLIDE_HIT_VOLCANION
	setvar VAR_GOLEM_ROCK_SLIDE_STATE, 0
	applymovement LOCALID_3F_VOLCANION, VolcanionCave_3F_Movement_VolcanionFlicker
	applymovement VAR_LOCALID_CURRENT_HP_BAR, VolcanionCave_3F_Movement_VolcanionFlicker
	waitmovement 0
	addvar VAR_CURRENT_HP_BAR_COLOR, 1
	applymovement LOCALID_3F_VOLCANION, VolcanionCave_3F_Movement_VolcanionSetVisible
	call VolcanionCave_3F_EventScript_SetHPBar
	message VolcanionCave_3F_Text_VolcanionGotHit
	waitmessage
	fadedefaultbgm
	closemessage
	release
	end

VolcanionCave_3F_Movement_VolcanionFlicker::
	set_invisible
	delay_8
	set_visible
	delay_8
	set_invisible
	delay_8
	set_visible
	delay_8
	set_invisible
	delay_8
	step_end

VolcanionCave_3F_Movement_VolcanionSetVisible::
	set_visible
	step_end

VolcanionCave_3F_Text_VolcanionGotHit::
	.string "Oh yeaaaah VOLCANION got hit!\p$"


VolcanionCave_3F_EventScript_GolemSatisfied::
	lock
	playmoncry SPECIES_GOLEM_ALOLA, CRY_MODE_ENCOUNTER
	message VolcanionCave_3F_Text_GolemCry
	waitmessage
	closemessage
	delay 10
	message VolcanionCave_3F_Text_GolemSeemsSatisfied
	waitmessage
	closemessage
	release
	end

VolcanionCave_3F_EventScript_Diglett::
	lock
	applymovement LOCALID_3F_DIGLETT, Common_Movement_FacePlayer
	waitmovement 0
	callnative IsPlayerOne
	goto_if_eq VAR_RESULT, FALSE, VolcanionCave_3F_EventScript_DiglettMagma
	goto VolcanionCave_3F_EventScript_DiglettAqua
	end

VolcanionCave_3F_EventScript_DiglettMagma::
	call VolcanionCave_3F_EventScript_DiglettCry
	message VolcanionCave_3F_Text_AskDiggsHelpMagma
	waitmessage
	call VolcanionCave_3F_EventScript_DiglettCry
	closemessage
	delay 10
	playbgm MUS_VS_VOLCANION, FALSE
	message VolcanionCave_3F_Text_DiglettUsedDig
	waitmessage
	call VolcanionCave_3F_EventScript_DiglettUseDig
	call VolcanionCave_3F_EventScript_DiglettCry
	message VolcanionCave_3F_Text_ThanksDiggsMagma
	waitmessage
	call VolcanionCave_1F_EventScript_VolcanionUseSteamEruption
	message VolcanionCave_3F_Text_RipDiggsMagma
	waitmessage
	closemessage
	call VolcanionCave_3F_EventScript_CameraMoveToPlayerAfterSteamEruption
	release
	end

VolcanionCave_3F_EventScript_DiglettAqua::
	call VolcanionCave_3F_EventScript_AgentDiggsCry
	message VolcanionCave_3F_Text_AskDiggsHelpAqua
	waitmessage
	call VolcanionCave_3F_EventScript_AgentDiggsCry
	closemessage
	delay 10
	playbgm MUS_VS_VOLCANION, FALSE
	message VolcanionCave_3F_Text_AgentDiggsUsedDig
	waitmessage
	call VolcanionCave_3F_EventScript_DiglettUseDig
	call VolcanionCave_3F_EventScript_AgentDiggsCry
	message VolcanionCave_3F_Text_ThanksDiggsAqua
	waitmessage
	call VolcanionCave_1F_EventScript_VolcanionUseSteamEruption
	message VolcanionCave_3F_Text_RipDiggsAqua
	waitmessage
	closemessage
	call VolcanionCave_3F_EventScript_CameraMoveToPlayerAfterSteamEruption
	release
	end

VolcanionCave_3F_EventScript_DiglettCry::
	playmoncry SPECIES_DIGLETT, CRY_MODE_NORMAL
	message VolcanionCave_3F_Text_DiglettCry
	waitmessage
	waitmoncry
	return

VolcanionCave_3F_EventScript_AgentDiggsCry::
	playmoncry SPECIES_DIGLETT, CRY_MODE_NORMAL
	message VolcanionCave_3F_Text_AgentDiggsCry
	waitmessage
	waitmoncry
	return

VolcanionCave_3F_EventScript_DiglettUseDig::
	special SpawnCameraObject
	applymovement LOCALID_3F_DIGLETT, VolcanionCave_3F_Movement_DiglettDigDown
	delay 10
	playse SE_M_DIG
	waitmovement 0
	waitse
	applymovement LOCALID_CAMERA, VolcanionCave_3F_Movement_CameraMoveWithDiglettToVolcanion
	applymovement LOCALID_3F_DIGLETT, VolcanionCave_3F_Movement_DiglettDigToVolcanion
	waitmovement 0
	setvar VAR_0x8004, 0  @ Vertical pan
	setvar VAR_0x8005, 3  @ Horizontal pan
	setvar VAR_0x8006, 3  @ Num shakes
	setvar VAR_0x8007, 4  @ Shake delay
	special ShakeScreen
	applymovement LOCALID_3F_VOLCANION, VolcanionCave_3F_Movement_VolcanionLookAround
	delay 40
	setvar VAR_0x8004, 0  @ Vertical pan
	setvar VAR_0x8005, 5  @ Horizontal pan
	setvar VAR_0x8006, 6  @ Num shakes
	setvar VAR_0x8007, 2  @ Shake delay
	special ShakeScreen
	delay 20
	waitmovement 0
	delay 20
	playse SE_M_DIG
	applymovement LOCALID_3F_DIGLETT, VolcanionCave_3F_Movement_DiglettAttackVolcanion
	applymovement LOCALID_3F_VOLCANION, VolcanionCave_3F_Movement_VolcanionGetAttackedByDiglett
	delay 16
	closemessage
	playse SE_SUPER_EFFECTIVE
	delay 16
	playse SE_M_DIG
	waitmovement 0
	applymovement LOCALID_3F_VOLCANION, VolcanionCave_3F_Movement_VolcanionFlicker
	applymovement VAR_LOCALID_CURRENT_HP_BAR, VolcanionCave_3F_Movement_VolcanionFlicker
	waitmovement 0
	addvar VAR_CURRENT_HP_BAR_COLOR, 1
	applymovement LOCALID_3F_VOLCANION, VolcanionCave_3F_Movement_VolcanionSetVisible
	call VolcanionCave_3F_EventScript_SetHPBar
	lock
	fadedefaultbgm
	applymovement LOCALID_CAMERA, VolcanionCave_3F_Movement_CameraMoveDownToDiglett
	applymovement LOCALID_3F_DIGLETT, VolcanionCave_3F_Movement_DiglettDigBackUp
	waitmovement 0
	applymovement LOCALID_3F_DIGLETT, Common_Movement_WalkInPlaceUp
	return

VolcanionCave_1F_EventScript_VolcanionUseSteamEruption::
	playbgm MUS_VS_VOLCANION, FALSE
	call VolcanionCave_3F_EventScript_VolcanionCry
	closemessage
	delay 10
	message VolcanionCave_3F_Text_VolcanionUsedSteamEruption
	waitmessage
	setvar VAR_0x8004, 0  @ Vertical pan
	setvar VAR_0x8005, 3  @ Horizontal pan
	setvar VAR_0x8006, 40  @ Num shakes
	setvar VAR_0x8007, 4  @ Shake delay
	special ShakeScreen
	delay 20
	playse SE_M_HYDRO_PUMP
	setmetatile 16, 22, METATILE_General_SteamEruption_EndFloor, FALSE
	special DrawWholeMapView
	delay 2
	setmetatile 16, 22, METATILE_General_SteamEruption_EndFull, FALSE
	special DrawWholeMapView
	delay 2
	setmetatile 16, 22, METATILE_General_SteamEruption_Connection, FALSE
	setmetatile 16, 23, METATILE_General_SteamEruption_EndStairs, FALSE
	special DrawWholeMapView
	delay 2
	setmetatile 16, 22, METATILE_General_SteamEruption_Main, FALSE
	setmetatile 16, 23, METATILE_General_SteamEruption_EndFull, FALSE
	special DrawWholeMapView
	delay 2
	setmetatile 16, 22, METATILE_General_SteamEruption_Main, FALSE
	setmetatile 16, 23, METATILE_General_SteamEruption_Connection, FALSE
	setmetatile 16, 24, METATILE_General_SteamEruption_EndFloor, FALSE
	special DrawWholeMapView
	applymovement LOCALID_3F_DIGLETT, VolcanionCave_3F_Movement_DiglettGetPushedBack
	applymovement LOCALID_CAMERA, VolcanionCave_3F_Movement_DiglettGetPushedBack
	delay 2
	setmetatile 16, 22, METATILE_General_SteamEruption_Main, FALSE
	setmetatile 16, 23, METATILE_General_SteamEruption_Main, FALSE
	setmetatile 16, 24, METATILE_General_SteamEruption_EndFull, FALSE
	special DrawWholeMapView
	delay 2
	setmetatile 16, 22, METATILE_General_SteamEruption_Main, FALSE
	setmetatile 16, 23, METATILE_General_SteamEruption_Main, FALSE
	setmetatile 16, 24, METATILE_General_SteamEruption_Connection, FALSE
	setmetatile 16, 25, METATILE_General_SteamEruption_EndFloor, FALSE
	special DrawWholeMapView
	delay 100
	setmetatile 16, 22, METATILE_General_SteamEruption_BottomHalf, FALSE
	setmetatile 16, 23, METATILE_General_SteamEruption_Main, FALSE
	setmetatile 16, 24, METATILE_General_SteamEruption_Main, FALSE
	setmetatile 16, 25, METATILE_General_SteamEruption_EndTopHalf, FALSE
	special DrawWholeMapView
	delay 2
	setmetatile 16, 22, METATILE_Cave_Floor_Smooth, FALSE
	setmetatile 16, 23, METATILE_General_SteamEruption_Main, FALSE
	setmetatile 16, 24, METATILE_General_SteamEruption_Main, FALSE
	setmetatile 16, 25, METATILE_General_SteamEruption_TopHalf, FALSE
	special DrawWholeMapView
	delay 2
	setmetatile 16, 23, METATILE_General_SteamEruption_BottomHalfStairs, FALSE
	setmetatile 16, 24, METATILE_General_SteamEruption_Main, FALSE
	setmetatile 16, 25, METATILE_General_SteamEruption_TopHalf, FALSE
	special DrawWholeMapView
	delay 2
	setmetatile 16, 23, METATILE_Cave_Stairs, FALSE
	setmetatile 16, 24, METATILE_General_SteamEruption_Main, FALSE
	setmetatile 16, 25, METATILE_General_SteamEruption_TopHalf, FALSE
	special DrawWholeMapView
	delay 2
	setmetatile 16, 24, METATILE_General_SteamEruption_BottomHalf, FALSE
	setmetatile 16, 25, METATILE_General_SteamEruption_TopHalf, FALSE
	special DrawWholeMapView
	delay 2
	setmetatile 16, 24, METATILE_Cave_Floor_Smooth, FALSE
	setmetatile 16, 25, METATILE_General_SteamEruption_TopHalf, FALSE
	special DrawWholeMapView
	delay 2
	setmetatile 16, 25, METATILE_Cave_Floor_Smooth, FALSE
	special DrawWholeMapView
	closemessage
	playse SE_SUPER_EFFECTIVE
	applymovement LOCALID_3F_DIGLETT, VolcanionCave_3F_Movement_PlayerFlicker
	waitmovement 0
	delay 20
	playmoncry SPECIES_DIGLETT, CRY_MODE_NORMAL
	waitmoncry
	playse SE_FAINT
	removeobject LOCALID_3F_DIGLETT
	fadedefaultbgm
	delay 40
	return

VolcanionCave_3F_EventScript_CameraMoveToPlayerAfterSteamEruption::
	applymovement LOCALID_CAMERA, VolcanionCave_3F_Movement_CameraMoveToPlayerAfterSteamEruption
	waitmovement 0
	special RemoveCameraObject
	return

VolcanionCave_3F_Movement_DiglettDigDown::
	walk_in_place_fast_left
	walk_in_place_fast_left
	walk_in_place_fast_left
	set_invisible
	step_end

VolcanionCave_3F_Movement_DiglettDigToVolcanion::
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_down
	face_up
	step_end

VolcanionCave_3F_Movement_CameraMoveWithDiglettToVolcanion::
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	step_end

VolcanionCave_3F_Movement_VolcanionLookAround::
	emote_question_mark
	walk_in_place_left
	delay_16
	walk_in_place_right
	delay_16
	walk_in_place_down
	step_end

VolcanionCave_3F_Movement_DiglettAttackVolcanion::
	set_visible
	walk_fast_up
	delay_16
	walk_in_place_fast_up
	walk_in_place_fast_up
	walk_in_place_fast_up
	set_invisible

VolcanionCave_3F_Movement_VolcanionGetAttackedByDiglett::
	delay_8
	lock_facing_direction
	walk_up
	delay_16
	walk_fast_down
	unlock_facing_direction
	step_end

VolcanionCave_3F_Movement_CameraMoveDownToDiglett::
	walk_down
	walk_down
	step_end

VolcanionCave_3F_Movement_DiglettDigBackUp::
	walk_down
	walk_down
	walk_down
	face_up
	set_visible
	step_end

VolcanionCave_3F_Movement_DiglettGetPushedBack::
	lock_facing_direction
	walk_down
	unlock_facing_direction
	step_end

VolcanionCave_3F_Movement_CameraMoveToPlayerAfterSteamEruption::
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

VolcanionCave_3F_Text_DiglettCry::
	.string "{SPEAKER NAME_DIGLETT COLOR_AQUA}Pipipi wowow!\p$"

VolcanionCave_3F_Text_AgentDiggsCry::
	.string "{SPEAKER NAME_AGENT_DIGGS COLOR_AQUA}Pipipi wowow!\p$"

VolcanionCave_3F_Text_AskDiggsHelpMagma::
	.string "{SPEAKER NAME_PLAYER COLOR_MAGMA}Hey eeeeeh…\n"
	.string "You're working for TEAM AQUA right?\p"
	.string "Wanna help us out?\p$"

VolcanionCave_3F_Text_AskDiggsHelpAqua::
	.string "{SPEAKER NAME_PLAYER COLOR_AQUA}Hey AGENT DIGGS!\n"
	.string "Wanna help us beat up VOLCANION?\p$"

VolcanionCave_3F_Text_DiglettUsedDig::
	.string "DIGLETT used DIG!$"

VolcanionCave_3F_Text_AgentDiggsUsedDig::
	.string "AGENT DIGGS used DIG!$"

VolcanionCave_3F_Text_ThanksDiggsMagma::
	.string "{SPEAKER NAME_PLAYER COLOR_MAGMA}Thank you, strange DIGLETT!\p"
	.string "Now get out of there before-{PAUSE 10}$"

VolcanionCave_3F_Text_ThanksDiggsAqua::
	.string "{SPEAKER NAME_PLAYER COLOR_AQUA}Thanks, AGENT DIGGS!\p"
	.string "Now get out of there before-{PAUSE 10}$"

VolcanionCave_3F_Text_VolcanionUsedSteamEruption::
	.string "VOLCANION used STEAM ERUPTION!$"

VolcanionCave_3F_Text_RipDiggsMagma::
	.string "{SPEAKER NAME_PLAYER COLOR_MAGMA}Nooooooo, strange DIGLETT!!\p$"

VolcanionCave_3F_Text_RipDiggsAqua::
	.string "{SPEAKER NAME_PLAYER COLOR_AQUA}Nooooooo, AGENT DIGGS!\p$"

VolcanionCave_3F_EventScript_Cramorant::
	release
	end

VolcanionCave_3F_EventScript_Pikachu::
	message VolcanionCave_3F_Text_RocketMottoStart
	waitmessage
	playse SE_FALL
	addobject LOCALID_3F_JESSIE
	setobjectxy LOCALID_3F_JESSIE, 28, 2
	applymovement LOCALID_3F_JESSIE, VolcanionCave_3F_Movement_TeamRocketFallDown
	waitmovement 0
	playse SE_M_STRENGTH
	message VolcanionCave_3F_Text_RocketMottoJessieEnter
	waitmessage
	playse SE_FALL
	addobject LOCALID_3F_JAMES
	setobjectxy LOCALID_3F_JAMES, 29, 2
	applymovement LOCALID_3F_JAMES, VolcanionCave_3F_Movement_TeamRocketFallDown
	waitmovement 0
	playse SE_M_STRENGTH
	message VolcanionCave_3F_Text_RocketMottoJamesEnter
	waitmessage
	playse SE_FALL
	addobject LOCALID_3F_MEOWTH
	setobjectxy LOCALID_3F_MEOWTH, 30, 2
	applymovement LOCALID_3F_MEOWTH, VolcanionCave_3F_Movement_TeamRocketFallDown
	waitmovement 0
	playse SE_M_STRENGTH
	message VolcanionCave_3F_Text_RocketMottoMeowthEnter
	waitmessage
	message VolcanionCave_3F_Text_RocketMottoRest
	waitmessage
	trainerbattle_no_intro TRAINER_TEAM_ROCKET_DUO_VC_3F, VolcanionCave_2F_Text_AquaGruntDefeat
	release
	end

VolcanionCave_3F_Movement_TeamRocketFallDown::
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	step_end

VolcanionCave_3F_Text_RocketMottoStart::
	.string "{SPEAKER NAME_QUESTION_MARKS COLOR_JESSIE}{FONT_TYPE 1}Prepare for trouble!\p"
	.string "{SPEAKER NAME_QUESTION_MARKS COLOR_JAMES}…we're in HOENN.\p"
	.string "{SPEAKER NAME_QUESTION_MARKS COLOR_JESSIE}…oh. {FONT_TYPE 0}Ahem…\p"
	.string "Prepare for trouble from the skies!\p"
	.string "{SPEAKER NAME_QUESTION_MARKS COLOR_JAMES}From beyond the stars, a nasty surprise!\p$"

VolcanionCave_3F_Text_RocketMottoJessieEnter::
	.string "{SPEAKER NAME_ROCKET COLOR_JESSIE}An evil as old as the galaxy…\p$"

VolcanionCave_3F_Text_RocketMottoJamesEnter::
	.string "{SPEAKER NAME_ROCKET COLOR_JAMES}…sent here to fulfill our destiny!\p$"

VolcanionCave_3F_Text_RocketMottoMeowthEnter::
	.string "{SPEAKER NAME_ROCKET_3 COLOR_NORMAL}Plus, there's me!\p$"

VolcanionCave_3F_Text_RocketMottoRest::
	.string "{SPEAKER NAME_ROCKET COLOR_JESSIE}To denounce the evils\n"
	.string "of truth and love!\p"
	.string "{SPEAKER NAME_ROCKET COLOR_JAMES}To extend our reach\n"
	.string "to the stars above!\p"
	.string "{SPEAKER NAME_JESSIE COLOR_JESSIE}Jessie!\p"
	.string "{SPEAKER NAME_JAMES COLOR_JAMES}And James!\p"
	.string "{SPEAKER NAME_MEOWTH COLOR_NORMAL}And Meowth are the names!\p"
	.string "{SPEAKER NAME_JESSIE COLOR_JESSIE}Anywhere there's peace in the universe…\p"
	.string "{SPEAKER NAME_JAMES COLOR_JAMES}…Team Rocket…\p"
	.string "{SPEAKER NAME_MEOWTH COLOR_NORMAL}…will be there…\p"
	.string "{SPEAKER NAME_ALL COLOR_NORMAL}…to make everything worse!\p$"
