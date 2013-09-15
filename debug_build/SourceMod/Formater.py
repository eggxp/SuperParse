#!/usr/bin/python
# -*- coding: GBK -*-

import ParseFile
import WorkSpaceManager
import LogUI

def  SourceFormat():
    insertStr = ""
    blockStr = "    "
    needMoveRight = 0
    needMoveLeft = 0
    for i in range (0, ParseFile.GetStrLineCount()):
        CurStr = ParseFile.GetStr(i)

        Place = CurStr.find("}")
        if Place >= 0:
            insertStr = insertStr.replace(blockStr, "", 1)

        if needMoveLeft == 1:
            insertStr = insertStr.replace(blockStr, "", 1)
            needMoveLeft = 0

        Place = CurStr.find("{")
        if needMoveRight == 1 :
            if Place < 0:
                insertStr += blockStr
                needMoveLeft = 1;
            needMoveRight = 0

        if ((CurStr.find("protected:") < 0) and
                (CurStr.find("public:") < 0) and
                (CurStr.find("private:") < 0)):
            CurStr = insertStr + CurStr
        
        Place = CurStr.find("{")
        if Place >= 0:
            insertStr += blockStr

        Place = CurStr.find(" case")
        if Place >= 0:
            needMoveRight = 1;
        Place = CurStr.find(" if")
        if Place >= 0:
            needMoveRight = 1;

        ParseFile.SetStr(i, CurStr)
