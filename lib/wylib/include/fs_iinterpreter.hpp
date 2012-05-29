// Borland C++ Builder
// Copyright (c) 1995, 2005 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Fs_iinterpreter.pas' rev: 10.00

#ifndef Fs_iinterpreterHPP
#define Fs_iinterpreterHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member functions
#pragma pack(push,8)
#include <System.hpp>	// Pascal unit
#include <Sysinit.hpp>	// Pascal unit
#include <Sysutils.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <Fs_xml.hpp>	// Pascal unit
#include <Variants.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Fs_iinterpreter
{
//-- type declarations -------------------------------------------------------
#pragma option push -b-
enum TfsVarType { fvtInt, fvtBool, fvtFloat, fvtChar, fvtstring, fvtClass, fvtArray, fvtVariant, fvtEnum, fvtConstructor };
#pragma option pop

struct TfsTypeRec
{
	
public:
	TfsVarType Typ;
	SmallString<32>  TypeName;
} ;

typedef Variant __fastcall (__closure *TfsGetValueEvent)(System::TObject* Instance, TMetaClass* ClassType, const AnsiString PropName);

typedef void __fastcall (__closure *TfsSetValueEvent)(System::TObject* Instance, TMetaClass* ClassType, const AnsiString PropName, const Variant &Value);

typedef Variant __fastcall (__closure *TfsCallMethodEvent)(System::TObject* Instance, TMetaClass* ClassType, const AnsiString MethodName, Variant &Params);

class DELPHICLASS TfsScript;
typedef void __fastcall (__closure *TfsRunLineEvent)(TfsScript* Sender, const AnsiString UnitName, const AnsiString SourcePos);

typedef void __fastcall (__closure *TfsGetUnitEvent)(TfsScript* Sender, const AnsiString UnitName, AnsiString &UnitText);

class DELPHICLASS TfsItemList;
class PASCALIMPLEMENTATION TfsItemList : public System::TObject 
{
	typedef System::TObject inherited;
	
protected:
	Classes::TList* FItems;
	
public:
	__fastcall TfsItemList(void);
	__fastcall virtual ~TfsItemList(void);
	virtual void __fastcall Clear(void);
	int __fastcall Count(void);
	void __fastcall Add(System::TObject* Item);
	void __fastcall Remove(System::TObject* Item);
};


class DELPHICLASS TfsStatement;
class PASCALIMPLEMENTATION TfsStatement : public TfsItemList 
{
	typedef TfsItemList inherited;
	
private:
	TfsScript* FProgram;
	AnsiString FSourcePos;
	AnsiString FUnitName;
	TfsStatement* __fastcall GetItem(int Index);
	void __fastcall RunLine(void);
	
public:
	__fastcall virtual TfsStatement(TfsScript* AProgram, const AnsiString UnitName, const AnsiString SourcePos);
	virtual void __fastcall Execute(void);
	__property TfsStatement* Items[int Index] = {read=GetItem};
public:
	#pragma option push -w-inl
	/* TfsItemList.Destroy */ inline __fastcall virtual ~TfsStatement(void) { }
	#pragma option pop
	
};


class DELPHICLASS TfsCustomVariable;
class DELPHICLASS TfsClassVariable;
class PASCALIMPLEMENTATION TfsScript : public Classes::TComponent 
{
	typedef Classes::TComponent inherited;
	
private:
	System::TObject* FAddedBy;
	bool FBreakCalled;
	bool FContinueCalled;
	bool FExitCalled;
	AnsiString FErrorMsg;
	AnsiString FErrorPos;
	Classes::TList* FItems;
	bool FIsRunning;
	Classes::TStrings* FLines;
	TfsGetUnitEvent FOnGetUnit;
	TfsRunLineEvent FOnRunLine;
	TfsScript* FParent;
	TfsScript* FProgRunning;
	TfsStatement* FStatement;
	AnsiString FSyntaxType;
	AnsiString FErrorUnit;
	Classes::TStringList* FUnitLines;
	TfsCustomVariable* __fastcall GetItem(int Index);
	void __fastcall RunLine(const AnsiString UnitName, const AnsiString Index);
	Variant __fastcall GetVariables(AnsiString Index);
	void __fastcall SetVariables(AnsiString Index, const Variant &Value);
	void __fastcall SetLines(const Classes::TStrings* Value);
	
public:
	__fastcall virtual TfsScript(Classes::TComponent* AOwner);
	__fastcall virtual ~TfsScript(void);
	void __fastcall Add(System::TObject* Item);
	void __fastcall AddCodeLine(const AnsiString UnitName, const AnsiString APos);
	HIDESBASE void __fastcall Remove(System::TObject* Item);
	void __fastcall RemoveItems(System::TObject* Owner);
	void __fastcall ClearAll(void);
	void __fastcall Clear(void);
	void __fastcall Stop(void);
	int __fastcall Count(void);
	TfsClassVariable* __fastcall AddClass(TMetaClass* AClass, const AnsiString Ancestor);
	void __fastcall AddConst(const AnsiString Name, const AnsiString Typ, const Variant &Value);
	void __fastcall AddEnum(const AnsiString Typ, const AnsiString Names);
	void __fastcall AddEnumSet(const AnsiString Typ, const AnsiString Names);
	void __fastcall AddComponent(Classes::TComponent* Form);
	void __fastcall AddForm(Classes::TComponent* Form);
	void __fastcall AddMethod(const AnsiString Syntax, TfsCallMethodEvent CallEvent, const AnsiString Category = "", const AnsiString Description = "");
	void __fastcall AddObject(const AnsiString Name, System::TObject* Obj);
	void __fastcall AddVariable(const AnsiString Name, const AnsiString Typ, const Variant &Value);
	void __fastcall AddType(const AnsiString TypeName, TfsVarType ParentType);
	Variant __fastcall CallFunction(const AnsiString Name, const Variant &Params);
	Variant __fastcall CallFunction1(const AnsiString Name, Variant &Params);
	bool __fastcall Compile(void);
	void __fastcall Execute(void);
	bool __fastcall Run(void);
	void __fastcall Terminate(void);
	Variant __fastcall Evaluate(const AnsiString Expression);
	bool __fastcall IsExecutableLine(int LineN, const AnsiString UnitName = "");
	bool __fastcall GetILCode(Classes::TStream* Stream);
	bool __fastcall SetILCode(Classes::TStream* Stream);
	TfsCustomVariable* __fastcall Find(const AnsiString Name);
	TfsClassVariable* __fastcall FindClass(const AnsiString Name);
	TfsCustomVariable* __fastcall FindLocal(const AnsiString Name);
	__property System::TObject* AddedBy = {read=FAddedBy, write=FAddedBy};
	__property AnsiString ErrorMsg = {read=FErrorMsg, write=FErrorMsg};
	__property AnsiString ErrorPos = {read=FErrorPos, write=FErrorPos};
	__property AnsiString ErrorUnit = {read=FErrorUnit, write=FErrorUnit};
	__property TfsCustomVariable* Items[int Index] = {read=GetItem};
	__property bool IsRunning = {read=FIsRunning, nodefault};
	__property TfsScript* Parent = {read=FParent, write=FParent};
	__property TfsStatement* Statement = {read=FStatement};
	__property Variant Variables[AnsiString Index] = {read=GetVariables, write=SetVariables};
	
__published:
	__property Classes::TStrings* Lines = {read=FLines, write=SetLines};
	__property AnsiString SyntaxType = {read=FSyntaxType, write=FSyntaxType};
	__property TfsGetUnitEvent OnGetUnit = {read=FOnGetUnit, write=FOnGetUnit};
	__property TfsRunLineEvent OnRunLine = {read=FOnRunLine, write=FOnRunLine};
};


class DELPHICLASS TfsAssignmentStmt;
class DELPHICLASS TfsDesignator;
class DELPHICLASS TfsParamItem;
class PASCALIMPLEMENTATION TfsCustomVariable : public TfsItemList 
{
	typedef TfsItemList inherited;
	
public:
	TfsParamItem* operator[](int Index) { return Params[Index]; }
	
private:
	System::TObject* FAddedBy;
	bool FIsReadOnly;
	AnsiString FName;
	bool FNeedResult;
	TfsCustomVariable* FRefItem;
	AnsiString FSourcePos;
	TfsVarType FTyp;
	AnsiString FTypeName;
	Variant FValue;
	TfsParamItem* __fastcall GetParam(int Index);
	System::PVariant __fastcall GetPValue(void);
	
protected:
	virtual void __fastcall SetValue(const Variant &Value);
	virtual Variant __fastcall GetValue();
	
public:
	__fastcall TfsCustomVariable(const AnsiString AName, TfsVarType ATyp, const AnsiString ATypeName);
	AnsiString __fastcall GetFullTypeName();
	int __fastcall GetNumberOfRequiredParams(void);
	__property System::TObject* AddedBy = {read=FAddedBy};
	__property bool IsReadOnly = {read=FIsReadOnly, write=FIsReadOnly, nodefault};
	__property AnsiString Name = {read=FName};
	__property bool NeedResult = {read=FNeedResult, write=FNeedResult, nodefault};
	__property TfsParamItem* Params[int Index] = {read=GetParam/*, default*/};
	__property System::PVariant PValue = {read=GetPValue};
	__property TfsCustomVariable* RefItem = {read=FRefItem, write=FRefItem};
	__property AnsiString SourcePos = {read=FSourcePos, write=FSourcePos};
	__property TfsVarType Typ = {read=FTyp, write=FTyp, nodefault};
	__property AnsiString TypeName = {read=FTypeName, write=FTypeName};
	__property Variant Value = {read=GetValue, write=SetValue};
public:
	#pragma option push -w-inl
	/* TfsItemList.Destroy */ inline __fastcall virtual ~TfsCustomVariable(void) { }
	#pragma option pop
	
};


#pragma option push -b-
enum TfsDesignatorKind { dkOther, dkVariable, dkStringArray, dkArray };
#pragma option pop

class DELPHICLASS TfsDesignatorItem;
class DELPHICLASS TfsCustomExpression;
class PASCALIMPLEMENTATION TfsDesignatorItem : public TfsItemList 
{
	typedef TfsItemList inherited;
	
public:
	TfsCustomExpression* operator[](int Index) { return Items[Index]; }
	
private:
	bool FFlag;
	TfsCustomVariable* FRef;
	AnsiString FSourcePos;
	TfsCustomExpression* __fastcall GetItem(int Index);
	
public:
	__property TfsCustomExpression* Items[int Index] = {read=GetItem/*, default*/};
	__property bool Flag = {read=FFlag, write=FFlag, nodefault};
	__property TfsCustomVariable* Ref = {read=FRef, write=FRef};
	__property AnsiString SourcePos = {read=FSourcePos, write=FSourcePos};
public:
	#pragma option push -w-inl
	/* TfsItemList.Create */ inline __fastcall TfsDesignatorItem(void) : TfsItemList() { }
	#pragma option pop
	#pragma option push -w-inl
	/* TfsItemList.Destroy */ inline __fastcall virtual ~TfsDesignatorItem(void) { }
	#pragma option pop
	
};


class PASCALIMPLEMENTATION TfsDesignator : public TfsCustomVariable 
{
	typedef TfsCustomVariable inherited;
	
public:
	TfsDesignatorItem* operator[](int Index) { return Items[Index]; }
	
private:
	TfsDesignatorKind FKind;
	TfsScript* FProgram;
	TfsCustomVariable* FRef1;
	TfsDesignatorItem* FRef2;
	Fs_xml::TfsXMLItem* FLateBindingXmlSource;
	void __fastcall CheckLateBinding(void);
	Variant __fastcall DoCalc(const Variant &AValue, bool Flag);
	TfsDesignatorItem* __fastcall GetItem(int Index);
	
protected:
	virtual Variant __fastcall GetValue();
	virtual void __fastcall SetValue(const Variant &Value);
	
public:
	__fastcall TfsDesignator(TfsScript* AProgram);
	void __fastcall Borrow(TfsDesignator* ADesignator);
	void __fastcall Finalize(void);
	__property TfsDesignatorItem* Items[int Index] = {read=GetItem/*, default*/};
	__property TfsDesignatorKind Kind = {read=FKind, nodefault};
	__property Fs_xml::TfsXMLItem* LateBindingXmlSource = {read=FLateBindingXmlSource, write=FLateBindingXmlSource};
public:
	#pragma option push -w-inl
	/* TfsItemList.Destroy */ inline __fastcall virtual ~TfsDesignator(void) { }
	#pragma option pop
	
};


class PASCALIMPLEMENTATION TfsAssignmentStmt : public TfsStatement 
{
	typedef TfsStatement inherited;
	
private:
	TfsDesignator* FDesignator;
	TfsCustomExpression* FExpression;
	TfsCustomVariable* FVar;
	TfsCustomVariable* FExpr;
	
public:
	__fastcall virtual ~TfsAssignmentStmt(void);
	virtual void __fastcall Execute(void);
	void __fastcall Optimize(void);
	__property TfsDesignator* Designator = {read=FDesignator, write=FDesignator};
	__property TfsCustomExpression* Expression = {read=FExpression, write=FExpression};
public:
	#pragma option push -w-inl
	/* TfsStatement.Create */ inline __fastcall virtual TfsAssignmentStmt(TfsScript* AProgram, const AnsiString UnitName, const AnsiString SourcePos) : TfsStatement(AProgram, UnitName, SourcePos) { }
	#pragma option pop
	
};


class DELPHICLASS TfsAssignPlusStmt;
class PASCALIMPLEMENTATION TfsAssignPlusStmt : public TfsAssignmentStmt 
{
	typedef TfsAssignmentStmt inherited;
	
public:
	virtual void __fastcall Execute(void);
public:
	#pragma option push -w-inl
	/* TfsAssignmentStmt.Destroy */ inline __fastcall virtual ~TfsAssignPlusStmt(void) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TfsStatement.Create */ inline __fastcall virtual TfsAssignPlusStmt(TfsScript* AProgram, const AnsiString UnitName, const AnsiString SourcePos) : TfsAssignmentStmt(AProgram, UnitName, SourcePos) { }
	#pragma option pop
	
};


class DELPHICLASS TfsAssignMinusStmt;
class PASCALIMPLEMENTATION TfsAssignMinusStmt : public TfsAssignmentStmt 
{
	typedef TfsAssignmentStmt inherited;
	
public:
	virtual void __fastcall Execute(void);
public:
	#pragma option push -w-inl
	/* TfsAssignmentStmt.Destroy */ inline __fastcall virtual ~TfsAssignMinusStmt(void) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TfsStatement.Create */ inline __fastcall virtual TfsAssignMinusStmt(TfsScript* AProgram, const AnsiString UnitName, const AnsiString SourcePos) : TfsAssignmentStmt(AProgram, UnitName, SourcePos) { }
	#pragma option pop
	
};


class DELPHICLASS TfsAssignMulStmt;
class PASCALIMPLEMENTATION TfsAssignMulStmt : public TfsAssignmentStmt 
{
	typedef TfsAssignmentStmt inherited;
	
public:
	virtual void __fastcall Execute(void);
public:
	#pragma option push -w-inl
	/* TfsAssignmentStmt.Destroy */ inline __fastcall virtual ~TfsAssignMulStmt(void) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TfsStatement.Create */ inline __fastcall virtual TfsAssignMulStmt(TfsScript* AProgram, const AnsiString UnitName, const AnsiString SourcePos) : TfsAssignmentStmt(AProgram, UnitName, SourcePos) { }
	#pragma option pop
	
};


class DELPHICLASS TfsAssignDivStmt;
class PASCALIMPLEMENTATION TfsAssignDivStmt : public TfsAssignmentStmt 
{
	typedef TfsAssignmentStmt inherited;
	
public:
	virtual void __fastcall Execute(void);
public:
	#pragma option push -w-inl
	/* TfsAssignmentStmt.Destroy */ inline __fastcall virtual ~TfsAssignDivStmt(void) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TfsStatement.Create */ inline __fastcall virtual TfsAssignDivStmt(TfsScript* AProgram, const AnsiString UnitName, const AnsiString SourcePos) : TfsAssignmentStmt(AProgram, UnitName, SourcePos) { }
	#pragma option pop
	
};


class DELPHICLASS TfsCallStmt;
class PASCALIMPLEMENTATION TfsCallStmt : public TfsStatement 
{
	typedef TfsStatement inherited;
	
private:
	TfsDesignator* FDesignator;
	AnsiString FModificator;
	
public:
	__fastcall virtual ~TfsCallStmt(void);
	virtual void __fastcall Execute(void);
	__property TfsDesignator* Designator = {read=FDesignator, write=FDesignator};
	__property AnsiString Modificator = {read=FModificator, write=FModificator};
public:
	#pragma option push -w-inl
	/* TfsStatement.Create */ inline __fastcall virtual TfsCallStmt(TfsScript* AProgram, const AnsiString UnitName, const AnsiString SourcePos) : TfsStatement(AProgram, UnitName, SourcePos) { }
	#pragma option pop
	
};


class DELPHICLASS TfsIfStmt;
class PASCALIMPLEMENTATION TfsIfStmt : public TfsStatement 
{
	typedef TfsStatement inherited;
	
private:
	TfsCustomExpression* FCondition;
	TfsStatement* FElseStmt;
	
public:
	__fastcall virtual TfsIfStmt(TfsScript* AProgram, const AnsiString UnitName, const AnsiString SourcePos);
	__fastcall virtual ~TfsIfStmt(void);
	virtual void __fastcall Execute(void);
	__property TfsCustomExpression* Condition = {read=FCondition, write=FCondition};
	__property TfsStatement* ElseStmt = {read=FElseStmt, write=FElseStmt};
};


class DELPHICLASS TfsCaseSelector;
class DELPHICLASS TfsSetExpression;
class PASCALIMPLEMENTATION TfsSetExpression : public TfsCustomVariable 
{
	typedef TfsCustomVariable inherited;
	
private:
	TfsCustomExpression* __fastcall GetItem(int Index);
	
protected:
	virtual Variant __fastcall GetValue();
	
public:
	bool __fastcall Check(const Variant &Value);
	__property TfsCustomExpression* Items[int Index] = {read=GetItem};
public:
	#pragma option push -w-inl
	/* TfsCustomVariable.Create */ inline __fastcall TfsSetExpression(const AnsiString AName, TfsVarType ATyp, const AnsiString ATypeName) : TfsCustomVariable(AName, ATyp, ATypeName) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TfsItemList.Destroy */ inline __fastcall virtual ~TfsSetExpression(void) { }
	#pragma option pop
	
};


class PASCALIMPLEMENTATION TfsCaseSelector : public TfsStatement 
{
	typedef TfsStatement inherited;
	
private:
	TfsSetExpression* FSetExpression;
	
public:
	__fastcall virtual ~TfsCaseSelector(void);
	bool __fastcall Check(const Variant &Value);
	__property TfsSetExpression* SetExpression = {read=FSetExpression, write=FSetExpression};
public:
	#pragma option push -w-inl
	/* TfsStatement.Create */ inline __fastcall virtual TfsCaseSelector(TfsScript* AProgram, const AnsiString UnitName, const AnsiString SourcePos) : TfsStatement(AProgram, UnitName, SourcePos) { }
	#pragma option pop
	
};


class DELPHICLASS TfsCaseStmt;
class PASCALIMPLEMENTATION TfsCaseStmt : public TfsStatement 
{
	typedef TfsStatement inherited;
	
private:
	TfsCustomExpression* FCondition;
	TfsStatement* FElseStmt;
	
public:
	__fastcall virtual TfsCaseStmt(TfsScript* AProgram, const AnsiString UnitName, const AnsiString SourcePos);
	__fastcall virtual ~TfsCaseStmt(void);
	virtual void __fastcall Execute(void);
	__property TfsCustomExpression* Condition = {read=FCondition, write=FCondition};
	__property TfsStatement* ElseStmt = {read=FElseStmt, write=FElseStmt};
};


class DELPHICLASS TfsRepeatStmt;
class PASCALIMPLEMENTATION TfsRepeatStmt : public TfsStatement 
{
	typedef TfsStatement inherited;
	
private:
	TfsCustomExpression* FCondition;
	bool FInverseCondition;
	
public:
	__fastcall virtual ~TfsRepeatStmt(void);
	virtual void __fastcall Execute(void);
	__property TfsCustomExpression* Condition = {read=FCondition, write=FCondition};
	__property bool InverseCondition = {read=FInverseCondition, write=FInverseCondition, nodefault};
public:
	#pragma option push -w-inl
	/* TfsStatement.Create */ inline __fastcall virtual TfsRepeatStmt(TfsScript* AProgram, const AnsiString UnitName, const AnsiString SourcePos) : TfsStatement(AProgram, UnitName, SourcePos) { }
	#pragma option pop
	
};


class DELPHICLASS TfsWhileStmt;
class PASCALIMPLEMENTATION TfsWhileStmt : public TfsStatement 
{
	typedef TfsStatement inherited;
	
private:
	TfsCustomExpression* FCondition;
	
public:
	__fastcall virtual ~TfsWhileStmt(void);
	virtual void __fastcall Execute(void);
	__property TfsCustomExpression* Condition = {read=FCondition, write=FCondition};
public:
	#pragma option push -w-inl
	/* TfsStatement.Create */ inline __fastcall virtual TfsWhileStmt(TfsScript* AProgram, const AnsiString UnitName, const AnsiString SourcePos) : TfsStatement(AProgram, UnitName, SourcePos) { }
	#pragma option pop
	
};


class DELPHICLASS TfsForStmt;
class PASCALIMPLEMENTATION TfsForStmt : public TfsStatement 
{
	typedef TfsStatement inherited;
	
private:
	TfsCustomExpression* FBeginValue;
	bool FDown;
	TfsCustomExpression* FEndValue;
	TfsCustomVariable* FVariable;
	
public:
	__fastcall virtual ~TfsForStmt(void);
	virtual void __fastcall Execute(void);
	__property TfsCustomExpression* BeginValue = {read=FBeginValue, write=FBeginValue};
	__property bool Down = {read=FDown, write=FDown, nodefault};
	__property TfsCustomExpression* EndValue = {read=FEndValue, write=FEndValue};
	__property TfsCustomVariable* Variable = {read=FVariable, write=FVariable};
public:
	#pragma option push -w-inl
	/* TfsStatement.Create */ inline __fastcall virtual TfsForStmt(TfsScript* AProgram, const AnsiString UnitName, const AnsiString SourcePos) : TfsStatement(AProgram, UnitName, SourcePos) { }
	#pragma option pop
	
};


class DELPHICLASS TfsVbForStmt;
class PASCALIMPLEMENTATION TfsVbForStmt : public TfsStatement 
{
	typedef TfsStatement inherited;
	
private:
	TfsCustomExpression* FBeginValue;
	TfsCustomExpression* FEndValue;
	TfsCustomExpression* FStep;
	TfsCustomVariable* FVariable;
	
public:
	__fastcall virtual ~TfsVbForStmt(void);
	virtual void __fastcall Execute(void);
	__property TfsCustomExpression* BeginValue = {read=FBeginValue, write=FBeginValue};
	__property TfsCustomExpression* EndValue = {read=FEndValue, write=FEndValue};
	__property TfsCustomExpression* Step = {read=FStep, write=FStep};
	__property TfsCustomVariable* Variable = {read=FVariable, write=FVariable};
public:
	#pragma option push -w-inl
	/* TfsStatement.Create */ inline __fastcall virtual TfsVbForStmt(TfsScript* AProgram, const AnsiString UnitName, const AnsiString SourcePos) : TfsStatement(AProgram, UnitName, SourcePos) { }
	#pragma option pop
	
};


class DELPHICLASS TfsCppForStmt;
class PASCALIMPLEMENTATION TfsCppForStmt : public TfsStatement 
{
	typedef TfsStatement inherited;
	
private:
	TfsStatement* FFirstStmt;
	TfsCustomExpression* FExpression;
	TfsStatement* FSecondStmt;
	
public:
	__fastcall virtual TfsCppForStmt(TfsScript* AProgram, const AnsiString UnitName, const AnsiString SourcePos);
	__fastcall virtual ~TfsCppForStmt(void);
	virtual void __fastcall Execute(void);
	__property TfsStatement* FirstStmt = {read=FFirstStmt, write=FFirstStmt};
	__property TfsCustomExpression* Expression = {read=FExpression, write=FExpression};
	__property TfsStatement* SecondStmt = {read=FSecondStmt, write=FSecondStmt};
};


class DELPHICLASS TfsTryStmt;
class PASCALIMPLEMENTATION TfsTryStmt : public TfsStatement 
{
	typedef TfsStatement inherited;
	
private:
	bool FIsExcept;
	TfsStatement* FExceptStmt;
	
public:
	__fastcall virtual TfsTryStmt(TfsScript* AProgram, const AnsiString UnitName, const AnsiString SourcePos);
	__fastcall virtual ~TfsTryStmt(void);
	virtual void __fastcall Execute(void);
	__property bool IsExcept = {read=FIsExcept, write=FIsExcept, nodefault};
	__property TfsStatement* ExceptStmt = {read=FExceptStmt, write=FExceptStmt};
};


class DELPHICLASS TfsBreakStmt;
class PASCALIMPLEMENTATION TfsBreakStmt : public TfsStatement 
{
	typedef TfsStatement inherited;
	
public:
	virtual void __fastcall Execute(void);
public:
	#pragma option push -w-inl
	/* TfsStatement.Create */ inline __fastcall virtual TfsBreakStmt(TfsScript* AProgram, const AnsiString UnitName, const AnsiString SourcePos) : TfsStatement(AProgram, UnitName, SourcePos) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TfsItemList.Destroy */ inline __fastcall virtual ~TfsBreakStmt(void) { }
	#pragma option pop
	
};


class DELPHICLASS TfsContinueStmt;
class PASCALIMPLEMENTATION TfsContinueStmt : public TfsStatement 
{
	typedef TfsStatement inherited;
	
public:
	virtual void __fastcall Execute(void);
public:
	#pragma option push -w-inl
	/* TfsStatement.Create */ inline __fastcall virtual TfsContinueStmt(TfsScript* AProgram, const AnsiString UnitName, const AnsiString SourcePos) : TfsStatement(AProgram, UnitName, SourcePos) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TfsItemList.Destroy */ inline __fastcall virtual ~TfsContinueStmt(void) { }
	#pragma option pop
	
};


class DELPHICLASS TfsExitStmt;
class PASCALIMPLEMENTATION TfsExitStmt : public TfsStatement 
{
	typedef TfsStatement inherited;
	
public:
	virtual void __fastcall Execute(void);
public:
	#pragma option push -w-inl
	/* TfsStatement.Create */ inline __fastcall virtual TfsExitStmt(TfsScript* AProgram, const AnsiString UnitName, const AnsiString SourcePos) : TfsStatement(AProgram, UnitName, SourcePos) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TfsItemList.Destroy */ inline __fastcall virtual ~TfsExitStmt(void) { }
	#pragma option pop
	
};


class DELPHICLASS TfsWithStmt;
class PASCALIMPLEMENTATION TfsWithStmt : public TfsStatement 
{
	typedef TfsStatement inherited;
	
private:
	TfsDesignator* FDesignator;
	TfsCustomVariable* FVariable;
	
public:
	__fastcall virtual ~TfsWithStmt(void);
	virtual void __fastcall Execute(void);
	__property TfsDesignator* Designator = {read=FDesignator, write=FDesignator};
	__property TfsCustomVariable* Variable = {read=FVariable, write=FVariable};
public:
	#pragma option push -w-inl
	/* TfsStatement.Create */ inline __fastcall virtual TfsWithStmt(TfsScript* AProgram, const AnsiString UnitName, const AnsiString SourcePos) : TfsStatement(AProgram, UnitName, SourcePos) { }
	#pragma option pop
	
};


class DELPHICLASS TfsVariable;
class PASCALIMPLEMENTATION TfsVariable : public TfsCustomVariable 
{
	typedef TfsCustomVariable inherited;
	
public:
	#pragma option push -w-inl
	/* TfsCustomVariable.Create */ inline __fastcall TfsVariable(const AnsiString AName, TfsVarType ATyp, const AnsiString ATypeName) : TfsCustomVariable(AName, ATyp, ATypeName) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TfsItemList.Destroy */ inline __fastcall virtual ~TfsVariable(void) { }
	#pragma option pop
	
};


class DELPHICLASS TfsTypeVariable;
class PASCALIMPLEMENTATION TfsTypeVariable : public TfsCustomVariable 
{
	typedef TfsCustomVariable inherited;
	
public:
	#pragma option push -w-inl
	/* TfsCustomVariable.Create */ inline __fastcall TfsTypeVariable(const AnsiString AName, TfsVarType ATyp, const AnsiString ATypeName) : TfsCustomVariable(AName, ATyp, ATypeName) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TfsItemList.Destroy */ inline __fastcall virtual ~TfsTypeVariable(void) { }
	#pragma option pop
	
};


class DELPHICLASS TfsstringVariable;
class PASCALIMPLEMENTATION TfsstringVariable : public TfsVariable 
{
	typedef TfsVariable inherited;
	
private:
	AnsiString FStr;
	
protected:
	virtual void __fastcall SetValue(const Variant &Value);
	virtual Variant __fastcall GetValue();
public:
	#pragma option push -w-inl
	/* TfsCustomVariable.Create */ inline __fastcall TfsstringVariable(const AnsiString AName, TfsVarType ATyp, const AnsiString ATypeName) : TfsVariable(AName, ATyp, ATypeName) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TfsItemList.Destroy */ inline __fastcall virtual ~TfsstringVariable(void) { }
	#pragma option pop
	
};


class PASCALIMPLEMENTATION TfsParamItem : public TfsCustomVariable 
{
	typedef TfsCustomVariable inherited;
	
private:
	Variant FDefValue;
	bool FIsOptional;
	bool FIsVarParam;
	
public:
	__fastcall TfsParamItem(const AnsiString AName, TfsVarType ATyp, const AnsiString ATypeName, bool AIsOptional, bool AIsVarParam);
	__property Variant DefValue = {read=FDefValue, write=FDefValue};
	__property bool IsOptional = {read=FIsOptional, nodefault};
	__property bool IsVarParam = {read=FIsVarParam, nodefault};
public:
	#pragma option push -w-inl
	/* TfsItemList.Destroy */ inline __fastcall virtual ~TfsParamItem(void) { }
	#pragma option pop
	
};


class DELPHICLASS TfsProcVariable;
class PASCALIMPLEMENTATION TfsProcVariable : public TfsCustomVariable 
{
	typedef TfsCustomVariable inherited;
	
private:
	bool FExecuting;
	bool FIsFunc;
	TfsScript* FProgram;
	
protected:
	virtual Variant __fastcall GetValue();
	
public:
	__fastcall TfsProcVariable(const AnsiString AName, TfsVarType ATyp, const AnsiString ATypeName, TfsScript* AParent, bool AIsFunc);
	__fastcall virtual ~TfsProcVariable(void);
	__property bool Executing = {read=FExecuting, nodefault};
	__property bool IsFunc = {read=FIsFunc, nodefault};
	__property TfsScript* Prog = {read=FProgram};
};


class PASCALIMPLEMENTATION TfsCustomExpression : public TfsCustomVariable 
{
	typedef TfsCustomVariable inherited;
	
public:
	#pragma option push -w-inl
	/* TfsCustomVariable.Create */ inline __fastcall TfsCustomExpression(const AnsiString AName, TfsVarType ATyp, const AnsiString ATypeName) : TfsCustomVariable(AName, ATyp, ATypeName) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TfsItemList.Destroy */ inline __fastcall virtual ~TfsCustomExpression(void) { }
	#pragma option pop
	
};


class DELPHICLASS TfsCustomHelper;
class PASCALIMPLEMENTATION TfsCustomHelper : public TfsCustomVariable 
{
	typedef TfsCustomVariable inherited;
	
private:
	TfsCustomVariable* FParentRef;
	Variant FParentValue;
	TfsScript* FProgram;
	
public:
	__property TfsCustomVariable* ParentRef = {read=FParentRef, write=FParentRef};
	__property Variant ParentValue = {read=FParentValue, write=FParentValue};
	__property TfsScript* Prog = {read=FProgram, write=FProgram};
public:
	#pragma option push -w-inl
	/* TfsCustomVariable.Create */ inline __fastcall TfsCustomHelper(const AnsiString AName, TfsVarType ATyp, const AnsiString ATypeName) : TfsCustomVariable(AName, ATyp, ATypeName) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TfsItemList.Destroy */ inline __fastcall virtual ~TfsCustomHelper(void) { }
	#pragma option pop
	
};


class DELPHICLASS TfsArrayHelper;
class PASCALIMPLEMENTATION TfsArrayHelper : public TfsCustomHelper 
{
	typedef TfsCustomHelper inherited;
	
protected:
	virtual void __fastcall SetValue(const Variant &Value);
	virtual Variant __fastcall GetValue();
	
public:
	__fastcall TfsArrayHelper(const AnsiString AName, int DimCount, TfsVarType Typ, const AnsiString TypeName);
public:
	#pragma option push -w-inl
	/* TfsItemList.Destroy */ inline __fastcall virtual ~TfsArrayHelper(void) { }
	#pragma option pop
	
};


class DELPHICLASS TfsstringHelper;
class PASCALIMPLEMENTATION TfsstringHelper : public TfsCustomHelper 
{
	typedef TfsCustomHelper inherited;
	
protected:
	virtual void __fastcall SetValue(const Variant &Value);
	virtual Variant __fastcall GetValue();
	
public:
	__fastcall TfsstringHelper(void);
public:
	#pragma option push -w-inl
	/* TfsItemList.Destroy */ inline __fastcall virtual ~TfsstringHelper(void) { }
	#pragma option pop
	
};


class DELPHICLASS TfsPropertyHelper;
class PASCALIMPLEMENTATION TfsPropertyHelper : public TfsCustomHelper 
{
	typedef TfsCustomHelper inherited;
	
private:
	TMetaClass* FClassRef;
	bool FIsPublished;
	TfsGetValueEvent FOnGetValue;
	TfsSetValueEvent FOnSetValue;
	
protected:
	virtual void __fastcall SetValue(const Variant &Value);
	virtual Variant __fastcall GetValue();
	
public:
	__property bool IsPublished = {read=FIsPublished, nodefault};
	__property TfsGetValueEvent OnGetValue = {read=FOnGetValue, write=FOnGetValue};
	__property TfsSetValueEvent OnSetValue = {read=FOnSetValue, write=FOnSetValue};
public:
	#pragma option push -w-inl
	/* TfsCustomVariable.Create */ inline __fastcall TfsPropertyHelper(const AnsiString AName, TfsVarType ATyp, const AnsiString ATypeName) : TfsCustomHelper(AName, ATyp, ATypeName) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TfsItemList.Destroy */ inline __fastcall virtual ~TfsPropertyHelper(void) { }
	#pragma option pop
	
};


class DELPHICLASS TfsMethodHelper;
class PASCALIMPLEMENTATION TfsMethodHelper : public TfsCustomHelper 
{
	typedef TfsCustomHelper inherited;
	
private:
	AnsiString FCategory;
	TMetaClass* FClassRef;
	AnsiString FDescription;
	bool FIndexMethod;
	TfsCallMethodEvent FOnCall;
	AnsiString FSyntax;
	
protected:
	virtual void __fastcall SetValue(const Variant &Value);
	virtual Variant __fastcall GetValue();
	
public:
	__fastcall TfsMethodHelper(const AnsiString Syntax, TfsCallMethodEvent CallEvent);
	__property AnsiString Category = {read=FCategory, write=FCategory};
	__property AnsiString Description = {read=FDescription, write=FDescription};
	__property bool IndexMethod = {read=FIndexMethod, nodefault};
	__property AnsiString Syntax = {read=FSyntax};
	__property TfsCallMethodEvent OnCall = {read=FOnCall, write=FOnCall};
public:
	#pragma option push -w-inl
	/* TfsItemList.Destroy */ inline __fastcall virtual ~TfsMethodHelper(void) { }
	#pragma option pop
	
};


class DELPHICLASS TfsComponentHelper;
class PASCALIMPLEMENTATION TfsComponentHelper : public TfsCustomHelper 
{
	typedef TfsCustomHelper inherited;
	
private:
	Classes::TComponent* FComponent;
	
protected:
	virtual Variant __fastcall GetValue();
	
public:
	__fastcall TfsComponentHelper(Classes::TComponent* Component);
public:
	#pragma option push -w-inl
	/* TfsItemList.Destroy */ inline __fastcall virtual ~TfsComponentHelper(void) { }
	#pragma option pop
	
};


class DELPHICLASS TfsCustomEvent;
class PASCALIMPLEMENTATION TfsCustomEvent : public System::TObject 
{
	typedef System::TObject inherited;
	
private:
	TfsProcVariable* FHandler;
	System::TObject* FInstance;
	
protected:
	void __fastcall CallHandler(System::TVarRec * Params, const int Params_Size);
	
public:
	__fastcall virtual TfsCustomEvent(System::TObject* AObject, TfsProcVariable* AHandler);
	virtual void * __fastcall GetMethod(void) = 0 ;
	__property TfsProcVariable* Handler = {read=FHandler};
	__property System::TObject* Instance = {read=FInstance};
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~TfsCustomEvent(void) { }
	#pragma option pop
	
};


typedef TMetaClass* TfsEventClass;

class DELPHICLASS TfsEventHelper;
class PASCALIMPLEMENTATION TfsEventHelper : public TfsCustomHelper 
{
	typedef TfsCustomHelper inherited;
	
private:
	TMetaClass* FClassRef;
	TMetaClass* FEvent;
	
protected:
	virtual void __fastcall SetValue(const Variant &Value);
	virtual Variant __fastcall GetValue();
	
public:
	__fastcall TfsEventHelper(const AnsiString Name, TMetaClass* AEvent);
public:
	#pragma option push -w-inl
	/* TfsItemList.Destroy */ inline __fastcall virtual ~TfsEventHelper(void) { }
	#pragma option pop
	
};


class PASCALIMPLEMENTATION TfsClassVariable : public TfsCustomVariable 
{
	typedef TfsCustomVariable inherited;
	
private:
	AnsiString FAncestor;
	TMetaClass* FClassRef;
	TfsCustomHelper* FDefProperty;
	TfsItemList* FMembers;
	void __fastcall AddComponent(Classes::TComponent* c);
	void __fastcall AddPublishedProperties(TMetaClass* AClass);
	TfsCustomHelper* __fastcall GetMembers(int Index);
	int __fastcall GetMembersCount(void);
	
protected:
	virtual Variant __fastcall GetValue();
	
public:
	__fastcall TfsClassVariable(TMetaClass* AClass, const AnsiString Ancestor);
	__fastcall virtual ~TfsClassVariable(void);
	void __fastcall AddConstructor(AnsiString Syntax, TfsCallMethodEvent CallEvent);
	void __fastcall AddProperty(const AnsiString Name, const AnsiString Typ, TfsGetValueEvent GetEvent, TfsSetValueEvent SetEvent = 0x0);
	void __fastcall AddDefaultProperty(const AnsiString Name, const AnsiString Params, const AnsiString Typ, TfsCallMethodEvent CallEvent, bool AReadOnly = false);
	void __fastcall AddIndexProperty(const AnsiString Name, const AnsiString Params, const AnsiString Typ, TfsCallMethodEvent CallEvent, bool AReadOnly = false);
	void __fastcall AddMethod(const AnsiString Syntax, TfsCallMethodEvent CallEvent);
	void __fastcall AddEvent(const AnsiString Name, TMetaClass* AEvent);
	TfsCustomHelper* __fastcall Find(const AnsiString Name);
	__property AnsiString Ancestor = {read=FAncestor};
	__property TMetaClass* ClassRef = {read=FClassRef};
	__property TfsCustomHelper* DefProperty = {read=FDefProperty};
	__property TfsCustomHelper* Members[int Index] = {read=GetMembers};
	__property int MembersCount = {read=GetMembersCount, nodefault};
};


class DELPHICLASS TfsVariableDesignator;
class PASCALIMPLEMENTATION TfsVariableDesignator : public TfsDesignator 
{
	typedef TfsDesignator inherited;
	
protected:
	virtual Variant __fastcall GetValue();
	virtual void __fastcall SetValue(const Variant &Value);
public:
	#pragma option push -w-inl
	/* TfsDesignator.Create */ inline __fastcall TfsVariableDesignator(TfsScript* AProgram) : TfsDesignator(AProgram) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TfsItemList.Destroy */ inline __fastcall virtual ~TfsVariableDesignator(void) { }
	#pragma option pop
	
};


class DELPHICLASS TfsStringDesignator;
class PASCALIMPLEMENTATION TfsStringDesignator : public TfsDesignator 
{
	typedef TfsDesignator inherited;
	
protected:
	virtual Variant __fastcall GetValue();
	virtual void __fastcall SetValue(const Variant &Value);
public:
	#pragma option push -w-inl
	/* TfsDesignator.Create */ inline __fastcall TfsStringDesignator(TfsScript* AProgram) : TfsDesignator(AProgram) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TfsItemList.Destroy */ inline __fastcall virtual ~TfsStringDesignator(void) { }
	#pragma option pop
	
};


class DELPHICLASS TfsArrayDesignator;
class PASCALIMPLEMENTATION TfsArrayDesignator : public TfsDesignator 
{
	typedef TfsDesignator inherited;
	
protected:
	virtual Variant __fastcall GetValue();
	virtual void __fastcall SetValue(const Variant &Value);
public:
	#pragma option push -w-inl
	/* TfsDesignator.Create */ inline __fastcall TfsArrayDesignator(TfsScript* AProgram) : TfsDesignator(AProgram) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TfsItemList.Destroy */ inline __fastcall virtual ~TfsArrayDesignator(void) { }
	#pragma option pop
	
};


class DELPHICLASS TfsEventList;
class PASCALIMPLEMENTATION TfsEventList : public TfsItemList 
{
	typedef TfsItemList inherited;
	
public:
	void __fastcall FreeObjectEvents(System::TObject* Instance);
public:
	#pragma option push -w-inl
	/* TfsItemList.Create */ inline __fastcall TfsEventList(void) : TfsItemList() { }
	#pragma option pop
	#pragma option push -w-inl
	/* TfsItemList.Destroy */ inline __fastcall virtual ~TfsEventList(void) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------
extern PACKAGE TfsScript* __fastcall fsGlobalUnit(void);
extern PACKAGE TfsEventList* __fastcall fsEventList(void);

}	/* namespace Fs_iinterpreter */
using namespace Fs_iinterpreter;
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Fs_iinterpreter
