EventScript_Player2::
	lock
	faceplayer
	message gText_HiPlayer
	waitmessage
	multichoicedefault 21, 6, MULTI_PLAYER_2, 0, FALSE
	switch VAR_RESULT
	case 0, Player2_Trade
	case 1, Player2_Talk
	case 2, Player2_Cancel
	case MULTI_B_PRESSED, Player2_Cancel
	release
	end

Player2_Trade::
	@ choose player mon
	msgbox gText_GiveWhatPokemon, MSGBOX_NPC
	special ChoosePartyMon
	copyvar VAR_0x800A, VAR_0x8004
	goto_if_ge VAR_0x800A, PARTY_SIZE, Player2_Cancel
	specialvar VAR_0x8008, GetTradeSpecies

	@ choose partner mon
	callnative SwitchParties
	msgbox gText_ReceiveWhatPokemon, MSGBOX_NPC
	special ChoosePartyMon
	copyvar VAR_0x800B, VAR_0x8004
	specialvar VAR_0x8009, GetTradeSpecies
	callnative SwitchParties
	goto_if_ge VAR_0x800B, PARTY_SIZE, Player2_Cancel

	@ confirm trade
	callnative BufferSinglePlayerTradeNicknames
	msgbox gText_GivePokemonForPokemon, MSGBOX_YESNO
	switch VAR_RESULT
	case NO, Player2_Cancel
	case YES, Player2_DoTrade
	case MULTI_B_PRESSED, Player2_Cancel
	release
	end

Player2_DoTrade::
	special DoSinglePlayerTradeScene
	callnative BufferSinglePlayerTradeNicknames
	msgbox gText_TakeGoodCareOfPokemon, MSGBOX_NPC
	release
	end

Player2_Talk::
	msgbox gText_Talk, MSGBOX_NPC
	release
	end

Player2_Cancel::
	msgbox gText_WeGotThis, MSGBOX_NPC
	release
	end

gText_HiPlayer::
	.string "{RIVAL}: Hi {PLAYER}!\nWhat do you want to do?$"

gText_GiveWhatPokemon::
	.string "{RIVAL}: What POKéMON do you\nwant to give?$"

gText_ReceiveWhatPokemon::
	.string "{RIVAL}: What POKéMON do you\nwant to receive?$"

gText_GivePokemonForPokemon::
	.string "{RIVAL}: Trade {STR_VAR_1}\nfor {STR_VAR_2}?$"

gText_TakeGoodCareOfPokemon::
	.string "{RIVAL}: I'll take good care\nof {STR_VAR_2}!$"

gText_Talk::
	.string "{RIVAL}: Wow, we're talking!$"

gText_WeGotThis::
	.string "{RIVAL}: We got this!$"
