EventScript_Player2_Singleplayer::
	lock
	goto_if_set FLAG_PLAYER_2_READY_TO_BATTLE_TOGETHER, EventScript_Player2_ReadyToBattle
	faceplayer
	message Player2_Text_HiPlayer
	waitmessage
	multichoicedefault 21, 6, MULTI_PLAYER_2, 0, FALSE
	switch VAR_RESULT
	case 0, Player2_Singleplayer_Trade
	case 1, Player2_Singleplayer_Talk
	case 2, Player2_Singleplayer_Cancel
	case MULTI_B_PRESSED, Player2_Singleplayer_Cancel
	release
	end

Player2_Singleplayer_Trade::
	@ choose player mon
	msgbox Player2_Text_GiveWhatPokemon, MSGBOX_NPC
	special ChoosePartyMon
	copyvar VAR_0x800A, VAR_0x8004
	goto_if_ge VAR_0x800A, PARTY_SIZE, Player2_Singleplayer_Cancel
	specialvar VAR_0x8008, GetTradeSpecies

	@ choose partner mon
	callnative SwitchParties
	msgbox Player2_Text_ReceiveWhatPokemon, MSGBOX_NPC
	special ChoosePartyMon
	copyvar VAR_0x800B, VAR_0x8004
	specialvar VAR_0x8009, GetTradeSpecies
	callnative SwitchParties
	goto_if_ge VAR_0x800B, PARTY_SIZE, Player2_Singleplayer_Cancel

	@ confirm trade
	callnative BufferSinglePlayerTradeNicknames
	msgbox Player2_Text_GivePokemonForPokemon, MSGBOX_YESNO
	switch VAR_RESULT
	case NO, Player2_Singleplayer_Cancel
	case YES, Player2_Singleplayer_DoTrade
	case MULTI_B_PRESSED, Player2_Singleplayer_Cancel
	release
	end

Player2_Singleplayer_DoTrade::
	special DoSinglePlayerTradeScene
	callnative BufferSinglePlayerTradeNicknames
	msgbox Player2_Text_TakeGoodCareOfPokemon, MSGBOX_NPC
	release
	end

Player2_Singleplayer_Talk::
	msgbox Player2_Text_Talk, MSGBOX_NPC
	release
	end

Player2_Singleplayer_Cancel::
	msgbox Player2_Text_WeGotThis, MSGBOX_NPC
	release
	end

Player2_Text_HiPlayer::
	.string "{RIVAL}: Hi {PLAYER}!\nWhat do you want to do?$"

Player2_Text_GiveWhatPokemon::
	.string "{RIVAL}: What POKéMON do you\nwant to give?$"

Player2_Text_ReceiveWhatPokemon::
	.string "{RIVAL}: What POKéMON do you\nwant to receive?$"

Player2_Text_GivePokemonForPokemon::
	.string "{RIVAL}: Trade {STR_VAR_1}\nfor {STR_VAR_2}?$"

Player2_Text_TakeGoodCareOfPokemon::
	.string "{RIVAL}: I'll take good care\nof {STR_VAR_2}!$"

Player2_Text_Talk::
	.string "{RIVAL}: Wow, we're talking!$"

Player2_Text_WeGotThis::
	.string "{RIVAL}: We got this!$"

Player2_Connect::
	message gText_PleaseWaitForLink
	waitmessage
	special TryTradeLinkup
	goto_if_eq VAR_RESULT, LINKUP_SUCCESS, Player2_LinkSuccess
	goto_if_eq VAR_RESULT, LINKUP_SOMEONE_NOT_READY, Player2_AbortLinkTryAgain
	goto_if_eq VAR_RESULT, LINKUP_DIFF_SELECTIONS, Player2_AbortLinkTryAgain
	goto_if_eq VAR_RESULT, LINKUP_WRONG_NUM_PLAYERS, Player2_AbortLinkTryAgain
	goto_if_eq VAR_RESULT, LINKUP_FAILED, Player2_AbortLinkTryAgain
	goto_if_eq VAR_RESULT, LINKUP_CONNECTION_ERROR, Player2_AbortLinkTryAgain
	goto_if_eq VAR_RESULT, LINKUP_PLAYER_NOT_READY, Player2_AbortLinkTryAgain
	goto_if_eq VAR_RESULT, LINKUP_PARTNER_NOT_READY, Player2_AbortLinkTryAgain
	end

Player2_AbortLinkTryAgain::
	special CloseLink
	msgbox CableClub_Text_PleaseVisitAgain, MSGBOX_DEFAULT
	release
	end

Player2_LinkSuccess::
	callnative StoreLinkPlayerName
	setvar VAR_0x8004, USING_TRADE_CENTER
	copyvar VAR_CABLE_CLUB_STATE, VAR_0x8004
	getplayerxy VAR_TEMP_0, VAR_TEMP_1
	setwarp MAP_OLDALE_TOWN, VAR_TEMP_0, VAR_TEMP_1
	special DoCableClubWarp
	end

EventScript_Player2_Multiplayer::
	lock
	faceplayer
	message Player2_Text_HiPlayer
	waitmessage
	multichoicedefault 21, 6, MULTI_PLAYER_2, 0, FALSE
	switch VAR_RESULT
	case 0, Player2_Multiplayer_Trade
	case 1, Player2_Multiplayer_Talk
	case 2, Player2_Multiplayer_Cancel
	case MULTI_B_PRESSED, Player2_Multiplayer_Cancel
	release
	end

Player2_Multiplayer_Trade::
	setvar VAR_0x8005, 0
	special PlayerEnteredTradeSeat
	end

Player2_Multiplayer_Talk::
	msgbox Player2_Text_Talk, MSGBOX_NPC
	release
	end

Player2_Multiplayer_Cancel::
	msgbox Player2_Text_WeGotThis, MSGBOX_NPC
	release
	end

EventScript_Player2_ReadyToBattle::
	lock
	msgbox Player2_Text_ReadyToBattle, MSGBOX_DEFAULT
	release
	end

Player2_Text_ReadyToBattle::
	.string "{RIVAL} is ready to battle!$"
