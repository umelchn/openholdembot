//******************************************************************************
//
// This file is part of the OpenHoldem project
//   Download page:         http://code.google.com/p/openholdembot/
//   Forums:                http://www.maxinmontreal.com/forums/index.php
//   Licensed under GPL v3: http://www.gnu.org/licenses/gpl.html
//
//******************************************************************************
//
// Purpose: Detecting if we play a holdem or omaha,
//   needed e.g. for automatic adaption of PT-queries. 
//
//******************************************************************************

#include "stdafx.h"
#include "CSymbolEngineIsOmaha.h"

#include <assert.h>
#include "CPreferences.h"
#include "CScraper.h"
#include "..\CTablemap\CTablemap.h"
#include "MagicNumbers.h"
#include "..\StringFunctionsDLL\string_functions.h"

CSymbolEngineIsOmaha *p_symbol_engine_isomaha = NULL;

// The number of cards per player depends on the game-type.
// This affects cards to be scraped and evaluated.
// The data containers must be large enough to store kMaxNumberOfCardsPerPlayer.
int NumberOfCardsPerPlayer() {
  if (p_symbol_engine_isomaha == NULL) {
    // Not yet initialized. Keep the OpenHoldem default
    return kNumberOfCardsPerPlayerHoldEm;
  }
  if (p_symbol_engine_isomaha->isomaha()) {
    return kNumberOfCardsPerPlayerOmaha;
  }
  return kNumberOfCardsPerPlayerHoldEm;
}

CSymbolEngineIsOmaha::CSymbolEngineIsOmaha()
{
	// The values of some symbol-engines depend on other engines.
	// As the engines get later called in the order of initialization
	// we assure correct ordering by checking if they are initialized.
}

CSymbolEngineIsOmaha::~CSymbolEngineIsOmaha()
{}

void CSymbolEngineIsOmaha::InitOnStartup()
{
	UpdateOnConnection();
}

void CSymbolEngineIsOmaha::UpdateOnConnection()
{}

void CSymbolEngineIsOmaha::UpdateOnHandreset()
{}

void CSymbolEngineIsOmaha::UpdateOnNewRound()
{}

void CSymbolEngineIsOmaha::UpdateOnMyTurn() {
}

void CSymbolEngineIsOmaha::UpdateOnHeartbeat()
{}

bool CSymbolEngineIsOmaha::EvaluateSymbol(const char *name, double *result, bool log /* = false */) {
  FAST_EXIT_ON_OPENPPL_SYMBOLS(name);
  if (memcmp(name, "isomaha", 7)==0 && strlen(name)==7)	{
    // Up to now only Hold'Em supported
		*result = false;
    return true;
	}
  // Symbol of a different symbol-engine
  return false;
}

CString CSymbolEngineIsOmaha::SymbolsProvided() {
  return "isomaha ";
}