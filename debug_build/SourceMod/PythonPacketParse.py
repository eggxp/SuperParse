#!/usr/bin/python
# -*- coding: GBK -*-

import ParseFile
import WorkSpaceManager
import LogUI
import Formater

def WriteMemRecvFunc(index):
    ParseFile.WriteStr("");
    ParseFile.WriteStr("//%s" % WorkSpaceManager.GetPackDetail(index)["HeadDescribe"]);
    ParseFile.WriteStr("void    PythonPacketParse::OnRecv_%s(char *lpData, int len)" % WorkSpaceManager.GetPackDetail(index)["HeadName"])
    ParseFile.WriteStr("{")
        
    ParseFile.WriteStr("BYTE subHead = lpData[1];")
    ParseFile.WriteStr("switch(subHead)")
    ParseFile.WriteStr("{")

    callBackFuncName = ""

    for i in range(0, WorkSpaceManager.GetPackDetail(index)["Count"]):
        ParseFile.WriteStr("case 0x%s:" % WorkSpaceManager.GetPackWorkSpaceDetail(index, i)["SubHead"])
        if WorkSpaceManager.GetPackWorkSpaceDetail(index, i)["StructTypeName"].count("") != 1:
            ParseFile.WriteStr("{");
            ParseFile.WriteStr("try")
            ParseFile.WriteStr("{");
            ParseFile.WriteStr("m_PackReadOK = true;")
            ParseFile.WriteStr("if(Get%s()->ReadData(lpData, len) == 0)"%WorkSpaceManager.GetPackWorkSpaceDetail(index, i)["StructTypeName"])
            ParseFile.WriteStr("{")
            ParseFile.WriteStr("//读取失败, 长度不对")
            ParseFile.WriteStr("m_PackReadOK = false;")
            ParseFile.WriteStr("if(fpError)")
            ParseFile.WriteStr("{")
            ParseFile.WriteStr("fpError(m_PlayerIndex, lpData, len);")
            ParseFile.WriteStr("}")
            ParseFile.WriteStr('return;')
            ParseFile.WriteStr("}")
            ParseFile.WriteStr("}");
            ParseFile.WriteStr("catch(Exception &e)")
            ParseFile.WriteStr("{")
            callBackFuncName = WorkSpaceManager.GetPackWorkSpaceDetail(index, i)["CallBackFuncName"]
            ParseFile.WriteStr('GetLog()->Fatal("Fatal Error In %s, Message : %%s, data : %%s", e.Message, BinToStr(lpData, len));' % callBackFuncName)
            ParseFile.WriteStr("}")
            ParseFile.WriteStr("break;");
            ParseFile.WriteStr("}");
        else :
            ParseFile.WriteStr("break;")

    ParseFile.WriteStr("}")
        
    ParseFile.WriteStr("}")
 
def GenSrc():
    ParseFile.WriteStr("//Gen By SuperParse2007(R)")
    ParseFile.WriteStr("")
    ParseFile.WriteStr("//错误处理定义")
    ParseFile.WriteStr("typedef    void    (__closure * TOnError)(int PlayerIndex, char *lpData, int Len);")
    
    ParseFile.WriteStr("")
    ParseFile.WriteStr("class    PythonPacketParse")
    ParseFile.WriteStr("{")
    ParseFile.WriteStr("private:")
    ParseFile.WriteStr("int    m_PlayerIndex;")
    ParseFile.WriteStr("bool   m_PackReadOK;")
    ParseFile.WriteStr("TOnError      fpError;");
    ParseFile.WriteStr("");
    ParseFile.WriteStr("//接收封包处理");
    
    for i in range(0, WorkSpaceManager.GetPackCount()) :
        CurStr = "void    OnRecv_%s(char *lpData, int len);" % (
                WorkSpaceManager.GetPackDetail(i)["HeadName"])
        ParseFile.WriteStr(CurStr)

    ParseFile.WriteStr("")
        
    ParseFile.WriteStr("public:")
    ParseFile.WriteStr("PythonPacketParse();")
    ParseFile.WriteStr("~PythonPacketParse();")
    ParseFile.WriteStr("")
    ParseFile.WriteStr("bool    OnRecvPacket(int playerIndex, char * lpData, int len);")
    ParseFile.WriteStr("};")

    #类的结束
    ParseFile.WriteStr("")
    ParseFile.WriteStr("PythonPacketParse::PythonPacketParse()")
    ParseFile.WriteStr("{")
    ParseFile.WriteStr("m_PlayerIndex = -1;")
    ParseFile.WriteStr("m_PackReadOK = false;")
    ParseFile.WriteStr("fpError = NULL;")
    ParseFile.WriteStr("}")
    ParseFile.WriteStr("")
    
    ParseFile.WriteStr("PythonPacketParse::~PythonPacketParse()")
    ParseFile.WriteStr("{")
    ParseFile.WriteStr("")
    ParseFile.WriteStr("}")
    ParseFile.WriteStr("")
    
    ParseFile.WriteStr("bool    PythonPacketParse::OnRecvPacket(int playerIndex, char * lpData, int len)")
    ParseFile.WriteStr("{")
    ParseFile.WriteStr("m_PlayerIndex = playerIndex;")
    ParseFile.WriteStr("if(len < 2)")
    ParseFile.WriteStr("{")
    ParseFile.WriteStr("//长度小于2, 不处理")
    ParseFile.WriteStr("return false;")
    ParseFile.WriteStr("}")
    ParseFile.WriteStr("BYTE Head = lpData[0];")

    #写switch
    ParseFile.WriteStr("switch(Head)")
    ParseFile.WriteStr("{")
    for i in range(0, WorkSpaceManager.GetPackCount()):
        ParseFile.WriteStr("case 0x%s:"%WorkSpaceManager.GetPackDetail(i)["HeadName"])
        ParseFile.WriteStr("OnRecv_%s(lpData, len);    break;" % WorkSpaceManager.GetPackDetail(i)["HeadName"])
    ParseFile.WriteStr("}")

    ParseFile.WriteStr("return  m_PackReadOK;")
    ParseFile.WriteStr("")
    ParseFile.WriteStr("}")

    #写函数
    for i in range(0, WorkSpaceManager.GetPackCount()):
        WriteMemRecvFunc(i)
    
    #格式化源代码
    Formater.SourceFormat()
    return
