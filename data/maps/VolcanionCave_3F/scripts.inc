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
	hideobjectat LOCALID_PLAYER_2, MAP_VOLCANION_CAVE_1F
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

VolcanionCave_3F_EventScript_DefeatedVolcanion::
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
	waitmessage
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
	.string "{SPEAKER NAME_VOLCANION COLOR_NORMAL}FWAHHRSHHHH!!!\p$"

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
	switch VAR_CURRENT_HP_BAR_COLOR
	case_call 1, VolcanionCave_3F_EventScript_SetHPBarGreen
	case_call 2, VolcanionCave_3F_EventScript_SetHPBarYellow
	case_call 3, VolcanionCave_3F_EventScript_SetHPBarRed
	goto_if_eq VAR_LOCALID_CURRENT_HP_BAR, 0, VolcanionCave_3F_EventScript_AddNoHPBar
	addobject VAR_LOCALID_CURRENT_HP_BAR
	setobjectxyperm VAR_LOCALID_CURRENT_HP_BAR, 16, 19
	setobjectxy VAR_LOCALID_CURRENT_HP_BAR, 16, 19
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
