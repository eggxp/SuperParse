// Borland C++ Builder
// Copyright (c) 1995, 2005 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Fs_iexpression.pas' rev: 10.00

#ifndef Fs_iexpressionHPP
#define Fs_iexpressionHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member functions
#pragma pack(push,8)
#include <System.hpp>	// Pascal unit
#include <Sysinit.hpp>	// Pascal unit
#include <Sysutils.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <Fs_iinterpreter.hpp>	// Pascal unit
#include <Variants.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Fs_iexpression
{
//-- type declarations -------------------------------------------------------
#pragma option push -b-
enum TfsOperatorType { opNone, opGreat, opLess, opLessEq, opGreatEq, opNonEq, opEq, opPlus, opMinus, opOr, opXor, opMul, opDivFloat, opDivInt, opMod, opAnd, opShl, opShr, opLeftBracket, opRightBracket, opNot, opUnMinus, opIn, opIs };
#pragma option pop

class DELPHICLASS TfsExpressionNode;
class PASCALIMPLEMENTATION TfsExpressionNode : public Fs_iinterpreter::TfsCustomVariable 
{
	typedef Fs_iinterpreter::TfsCustomVariable inherited;
	
private:
	TfsExpressionNode* FLeft;
	TfsExpressionNode* FRight;
	TfsExpressionNode* FParent;
	void __fastcall AddNode(TfsExpressionNode* Node);
	void __fastcall RemoveNode(TfsExpressionNode* Node);
	
public:
	__fastcall virtual ~TfsExpressionNode(void);
	virtual int __fastcall Priority(void) = 0 ;
public:
	#pragma option push -w-inl
	/* TfsCustomVariable.Create */ inline __fastcall TfsExpressionNode(const AnsiString AName, Fs_iinterpreter::TfsVarType ATyp, const AnsiString ATypeName) : Fs_iinterpreter::TfsCustomVariable(AName, ATyp, ATypeName) { }
	#pragma option pop
	
};


class DELPHICLASS TfsOperandNode;
class PASCALIMPLEMENTATION TfsOperandNode : public TfsExpressionNode 
{
	typedef TfsExpressionNode inherited;
	
public:
	__fastcall TfsOperandNode(const Variant &AValue);
	virtual int __fastcall Priority(void);
public:
	#pragma option push -w-inl
	/* TfsExpressionNode.Destroy */ inline __fastcall virtual ~TfsOperandNode(void) { }
	#pragma option pop
	
};


class DELPHICLASS TfsOperatorNode;
class PASCALIMPLEMENTATION TfsOperatorNode : public TfsExpressionNode 
{
	typedef TfsExpressionNode inherited;
	
private:
	TfsOperatorType FOp;
	bool FOptimizeInt;
	bool FOptimizeBool;
	
public:
	__fastcall TfsOperatorNode(TfsOperatorType Op);
	virtual int __fastcall Priority(void);
public:
	#pragma option push -w-inl
	/* TfsExpressionNode.Destroy */ inline __fastcall virtual ~TfsOperatorNode(void) { }
	#pragma option pop
	
};


class DELPHICLASS TfsDesignatorNode;
class PASCALIMPLEMENTATION TfsDesignatorNode : public TfsOperandNode 
{
	typedef TfsOperandNode inherited;
	
private:
	Fs_iinterpreter::TfsDesignator* FDesignator;
	Fs_iinterpreter::TfsCustomVariable* FVar;
	
protected:
	virtual Variant __fastcall GetValue();
	
public:
	__fastcall TfsDesignatorNode(Fs_iinterpreter::TfsDesignator* ADesignator);
	__fastcall virtual ~TfsDesignatorNode(void);
};


class DELPHICLASS TfsSetNode;
class PASCALIMPLEMENTATION TfsSetNode : public TfsOperandNode 
{
	typedef TfsOperandNode inherited;
	
private:
	Fs_iinterpreter::TfsSetExpression* FSetExpression;
	
protected:
	virtual Variant __fastcall GetValue();
	
public:
	__fastcall TfsSetNode(Fs_iinterpreter::TfsSetExpression* ASet);
	__fastcall virtual ~TfsSetNode(void);
};


class DELPHICLASS TfsExpression;
class PASCALIMPLEMENTATION TfsExpression : public Fs_iinterpreter::TfsCustomExpression 
{
	typedef Fs_iinterpreter::TfsCustomExpression inherited;
	
private:
	TfsExpressionNode* FCurNode;
	TfsExpressionNode* FNode;
	void __fastcall AddOperand(TfsExpressionNode* Node);
	
protected:
	virtual Variant __fastcall GetValue();
	virtual void __fastcall SetValue(const Variant &Value);
	
public:
	__fastcall TfsExpression(void);
	__fastcall virtual ~TfsExpression(void);
	void __fastcall AddConst(const Variant &AValue);
	void __fastcall AddDesignator(Fs_iinterpreter::TfsDesignator* ADesignator);
	void __fastcall AddOperator(const AnsiString Op);
	void __fastcall AddSet(Fs_iinterpreter::TfsSetExpression* ASet);
	AnsiString __fastcall Finalize();
	AnsiString __fastcall Optimize(Fs_iinterpreter::TfsDesignator* Designator);
	Fs_iinterpreter::TfsCustomVariable* __fastcall SingleItem(void);
};


//-- var, const, procedure ---------------------------------------------------

}	/* namespace Fs_iexpression */
using namespace Fs_iexpression;
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Fs_iexpression
