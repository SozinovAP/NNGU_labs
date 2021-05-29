#include "Visual/Visual.h"
#include "Tables/ArraySortTable.h"
#include "Tables/HashTableList.h"
#include "Tables/TableArray.h"
#include "Tables/TableHash.h"
#include "Tables/TableList.h"
#include "Tables/TableTreeAVL.h"
#include<iostream>
#include "Parser/Parser.h"

using namespace std;


int main()
{
	TableManager tableManager;
	ArraySortTable tas;
	HashTableList thl;
	TableArray ta;
	TableHash th;
	TableList tl;
	TableTreeAVL tta;
	tableManager.AddTable(&tas);
	tableManager.AddTable(&thl);
	tableManager.AddTable(&ta);
	tableManager.AddTable(&th);
	tableManager.AddTable(&tl);
	tableManager.AddTable(&tta);
	Visual visual(tableManager);
}