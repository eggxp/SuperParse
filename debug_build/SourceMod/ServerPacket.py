#!/usr/bin/python
# -*- coding: GBK -*-

import ParseFile
import WorkSpaceManager
import LogUI
import Formater

def WriteMemRecvFunc(index):
    ParseFile.WriteStr("");
    ParseFile.WriteStr("//%s" % WorkSpaceManager.GetPackDetail(index)["HeadDescribe"]);
    ParseFile.WriteStr("void    PacketParse::OnRecv_%s(char *lpData, int len)" % WorkSpaceManager.GetPackDetail(index)["HeadName"])
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
            callBackFuncName = WorkSpaceManager.GetPackWorkSpaceDetail(index, i)["CallBackFuncName"]
            ParseFile.WriteStr("if(fp%s)" % callBackFuncName)
            ParseFile.WriteStr("{")            
            ParseFile.WriteStr("//%s" % WorkSpaceManager.GetPackWorkSpaceDetail(index, i)["Comment"])
            ParseFile.WriteStr("%s %s;" % (WorkSpaceManager.GetPackWorkSpaceDetail(index, i)["StructTypeName"],
                                          callBackFuncName))
            ParseFile.WriteStr("%s.ReadData(lpData);" % callBackFuncName)
            
            ParseFile.WriteStr("fp%s(m_PlayerIndex, &%s);" % (callBackFuncName,callBackFuncName))
            ParseFile.WriteStr("}");
            ParseFile.WriteStr("else if(fpDefault)");
            ParseFile.WriteStr("{")
            ParseFile.WriteStr("fpDefault(m_PlayerIndex, lpData, len);");
            ParseFile.WriteStr("}");
            ParseFile.WriteStr("}");
            ParseFile.WriteStr("catch(Exception &e)")
            ParseFile.WriteStr("{")
            ParseFile.WriteStr('GetLog()->Fatal("Fatal Error In %s, Message : %%s, data : %%s", e.Message, BinToStr(lpData, len));' % callBackFuncName)
            ParseFile.WriteStr("}")
            ParseFile.WriteStr("break;")
            ParseFile.WriteStr("}");
        else :
            ParseFile.WriteStr("break;")

    ParseFile.WriteStr("}")
        
    ParseFile.WriteStr("}")
 
def GenSrc():
    ParseFile.WriteStr("//Gen By SuperParse2007(R)")
    ParseFile.WriteStr("#include \"FrmDebug.h\"")
    ParseFile.WriteStr("")
    ParseFile.WriteStr("//回调函数类型定义")

    for i in range(0, WorkSpaceManager.GetWorkSpaceCount()):
        if WorkSpaceManager.GetWorkSpaceDetail(i)["StructTypeName"].count("") == 1 :
            continue
        CurStr = "typedef    bool    (__closure * T%s)(int PlayerIndex, %s * recv%s);" % (
                            WorkSpaceManager.GetWorkSpaceDetail(i)["CallBackFuncName"],
                            WorkSpaceManager.GetWorkSpaceDetail(i)["StructTypeName"],
                            WorkSpaceManager.GetWorkSpaceDetail(i)["CallBackFuncName"],)
        ParseFile.WriteStr(CurStr)

    ParseFile.WriteStr("typedef    void    (__closure * TOnDefault)(int PlayerIndex, char *lpData, int Len);")
    
    ParseFile.WriteStr("")
    ParseFile.WriteStr("class    PacketParse")
    ParseFile.WriteStr("{")
    ParseFile.WriteStr("private:")
    ParseFile.WriteStr("int    m_PlayerIndex;")
    ParseFile.WriteStr("public:")

    ParseFile.WriteStr("//回调函数定义");
    for i in range(0, WorkSpaceManager.GetWorkSpaceCount()):
        if WorkSpaceManager.GetWorkSpaceDetail(i)["StructTypeName"].count("") == 1 :
            continue
        CurStr = "T%s    fp%s;" % (WorkSpaceManager.GetWorkSpaceDetail(i)["CallBackFuncName"],
                                  WorkSpaceManager.GetWorkSpaceDetail(i)["CallBackFuncName"])
        ParseFile.WriteStr(CurStr)

    ParseFile.WriteStr("TOnDefault    fpDefault;");

    ParseFile.WriteStr("")
    ParseFile.WriteStr("private:")
    ParseFile.WriteStr("//接收封包处理");
    
    for i in range(0, WorkSpaceManager.GetPackCount()) :
        CurStr = "void    OnRecv_%s(char *lpData, int len);" % (
                WorkSpaceManager.GetPackDetail(i)["HeadName"])
        ParseFile.WriteStr(CurStr)

    ParseFile.WriteStr("")
        
    ParseFile.WriteStr("public:")
    ParseFile.WriteStr("PacketParse();")
    ParseFile.WriteStr("~PacketParse();")
    ParseFile.WriteStr("")
    ParseFile.WriteStr("void    OnRecvPacket(int playerIndex, char * lpData, int len);")
    ParseFile.WriteStr("};")

    #类的结束
    ParseFile.WriteStr("")
    ParseFile.WriteStr("PacketParse::PacketParse()")
    ParseFile.WriteStr("{")
    ParseFile.WriteStr("m_PlayerIndex = 0;")
    for i in range(0, WorkSpaceManager.GetWorkSpaceCount()):
        if WorkSpaceManager.GetWorkSpaceDetail(i)["StructTypeName"].count("") == 1 :
            continue
        ParseFile.WriteStr("fp%s = NULL;" % WorkSpaceManager.GetWorkSpaceDetail(i)["CallBackFuncName"])
    ParseFile.WriteStr("fpDefault = NULL;");

    ParseFile.WriteStr("}")
    ParseFile.WriteStr("")
    
    ParseFile.WriteStr("PacketParse::~PacketParse()")
    ParseFile.WriteStr("{")
    ParseFile.WriteStr("")
    ParseFile.WriteStr("}")
    ParseFile.WriteStr("")
    
    ParseFile.WriteStr("void    PacketParse::OnRecvPacket(int playerIndex, char * lpData, int len)")
    ParseFile.WriteStr("{")
    ParseFile.WriteStr("m_PlayerIndex = playerIndex;")
    ParseFile.WriteStr("if(len < 2)")
    ParseFile.WriteStr("{")
    ParseFile.WriteStr("//长度小于2, 不处理")
    ParseFile.WriteStr("return;")
    ParseFile.WriteStr("}")
    ParseFile.WriteStr("BYTE Head = lpData[0];")

    #写switch
    ParseFile.WriteStr("switch(Head)")
    ParseFile.WriteStr("{")
    for i in range(0, WorkSpaceManager.GetPackCount()):
        ParseFile.WriteStr("case 0x%s:"%WorkSpaceManager.GetPackDetail(i)["HeadName"])
        ParseFile.WriteStr("OnRecv_%s(lpData, len);    break;" % WorkSpaceManager.GetPackDetail(i)["HeadName"])
    ParseFile.WriteStr("}")

    ParseFile.WriteStr("")
    ParseFile.WriteStr("}")

    #写函数
    for i in range(0, WorkSpaceManager.GetPackCount()):
        WriteMemRecvFunc(i)
    
    
    
    
    ParseFile.WriteStr("//Gen By SuperParse2007(R)")
    ParseFile.WriteStr("")
    ParseFile.WriteStr("//错误处理定义")
    
    ParseFile.WriteStr("")
    ParseFile.WriteStr("class    InfoPacketParse")
    ParseFile.WriteStr("{")
    ParseFile.WriteStr("private:")
    ParseFile.WriteStr("int    m_PlayerIndex;")
    ParseFile.WriteStr("bool   m_PackReadOK;")
    ParseFile.WriteStr("TDebugFrm   *   m_OutputFrm;")
    ParseFile.WriteStr("");
    ParseFile.WriteStr("//接收封包处理");
    
    for i in range(0, WorkSpaceManager.GetPackCount()) :
        CurStr = "void    OnRecv_%s(char *lpData, int len);" % (
                WorkSpaceManager.GetPackDetail(i)["HeadName"])
        ParseFile.WriteStr(CurStr)

    ParseFile.WriteStr("")
        
    ParseFile.WriteStr("public:")
    ParseFile.WriteStr("InfoPacketParse(TDebugFrm * outPut);")
    ParseFile.WriteStr("~InfoPacketParse();")
    ParseFile.WriteStr("")
    ParseFile.WriteStr("bool    OnRecvPacket(int playerIndex, char * lpData, int len);")
    ParseFile.WriteStr("};")

    #类的结束
    ParseFile.WriteStr("")
    ParseFile.WriteStr("InfoPacketParse::InfoPacketParse(TDebugFrm * outPut)")
    ParseFile.WriteStr("{")
    ParseFile.WriteStr("m_PlayerIndex = -1;")
    ParseFile.WriteStr("m_PackReadOK = false;")
    ParseFile.WriteStr("m_OutputFrm = outPut;")
    ParseFile.WriteStr("}")
    ParseFile.WriteStr("")
    
    ParseFile.WriteStr("InfoPacketParse::~InfoPacketParse()")
    ParseFile.WriteStr("{")
    ParseFile.WriteStr("")
    ParseFile.WriteStr("}")
    ParseFile.WriteStr("")
    
    ParseFile.WriteStr("bool    InfoPacketParse::OnRecvPacket(int playerIndex, char * lpData, int len)")
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
        WriteMemRecvFuncGenInfo(i)
    
    
    #格式化源代码
    Formater.SourceFormat()
    return



def WriteMemRecvFuncGenInfo(index):
    ParseFile.WriteStr("");
    ParseFile.WriteStr("//%s" % WorkSpaceManager.GetPackDetail(index)["HeadDescribe"]);
    ParseFile.WriteStr("void    InfoPacketParse::OnRecv_%s(char *lpData, int len)" % WorkSpaceManager.GetPackDetail(index)["HeadName"])
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
            callBackFuncName = WorkSpaceManager.GetPackWorkSpaceDetail(index, i)["CallBackFuncName"]
            ParseFile.WriteStr("//%s" % WorkSpaceManager.GetPackWorkSpaceDetail(index, i)["Comment"])
            ParseFile.WriteStr("%s %s;" % (WorkSpaceManager.GetPackWorkSpaceDetail(index, i)["StructTypeName"],
                                          callBackFuncName))
            ParseFile.WriteStr("%s.ReadData(lpData);" % callBackFuncName)
            ParseFile.WriteStr("m_OutputFrm->AddRecvInfo(%s.OutputString());"%callBackFuncName)
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
 