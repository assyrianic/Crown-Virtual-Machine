#include "tagha.hpp"


void Tagha_::Delete()
{
	Tagha_Free((struct Tagha *)this);
}

void Tagha_::PrintPtrs()
{
	Tagha_PrintPtrs((struct Tagha *)this);
}

void Tagha_::PrintStack()
{
	Tagha_PrintStack((struct Tagha *)this);
}

void Tagha_::PrintData()
{
	Tagha_PrintData((struct Tagha *)this);
}

void Tagha_::PrintInstrs()
{
	Tagha_PrintInstrs((struct Tagha *)this);
}

void Tagha_::PrintRegData()
{
	Tagha_PrintRegData((struct Tagha *)this);
}

void Tagha_::Reset()
{
	Tagha_Reset((struct Tagha *)this);
}

void *Tagha_::GetGlobalByName(const char *strGlobalName)
{
	return Tagha_GetGlobalByName((struct Tagha *)this, strGlobalName);
}

bool Tagha_::BindGlobalPtr(const char *strGlobalName, void *pVar)
{
	return Tagha_BindGlobalPtr((struct Tagha *)this, strGlobalName, pVar);
}

void Tagha_::PushValue(const CValue value)
{
	Tagha_PushValue((struct Tagha *)this, value);
}

CValue Tagha_::PopValue()
{
	return Tagha_PopValue((struct Tagha *)this);
}

void Tagha_::SetCmdArgs(char *argv[])
{
	Tagha_SetCmdArgs((struct Tagha *)this, argv);
}

uint32_t Tagha_::GetMemSize()
{
	return Tagha_GetMemSize((struct Tagha *)this);
}

uint32_t Tagha_::GetInstrSize()
{
	return Tagha_GetInstrSize((struct Tagha *)this);
}

uint32_t Tagha_::GetMaxInstrs()
{
	return Tagha_GetMaxInstrs((struct Tagha *)this);
}

uint32_t Tagha_::GetNativeCount()
{
	return Tagha_GetNativeCount((struct Tagha *)this);
}

uint32_t Tagha_::GetFuncCount()
{
	return Tagha_GetFuncCount((struct Tagha *)this);
}

uint32_t Tagha_::GetGlobalsCount()
{
	return Tagha_GetGlobalsCount((struct Tagha *)this);
}

bool Tagha_::IsSafemodeActive()
{
	return Tagha_IsSafemodeActive((struct Tagha *)this);
}

bool Tagha_::IsDebugActive()
{
	return Tagha_IsDebugActive((struct Tagha *)this);
}


Tagha_::Tagha_()
{
	Tagha_Init((struct Tagha *)this);
}

void Tagha_::LoadScriptByName(char *filename)
{
	Tagha_LoadScriptByName((struct Tagha *)this, filename);
}

bool Tagha_::RegisterNatives(NativeInfo_ arrNatives[])
{
	return Tagha_RegisterNatives((struct Tagha *)this, (struct NativeInfo *)arrNatives);
}

int32_t Tagha_::RunScript()
{
	return Tagha_RunScript((struct Tagha *)this);
}

int32_t Tagha_::CallFunc(const char *strFunc)
{
	return Tagha_CallFunc((struct Tagha *)this, strFunc);
}

void Tagha_::LoadLibCNatives()
{
	Tagha_LoadLibCNatives((struct Tagha *)this);
}

void Tagha_::LoadSelfNatives()
{
	Tagha_LoadSelfNatives((struct Tagha *)this);
}


void Tagha_::BuildFromFile(const char *filename)
{
	Tagha_BuildFromFile((struct Tagha *)this, filename);
}


