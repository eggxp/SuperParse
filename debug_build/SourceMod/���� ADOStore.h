<%FileComment%>
#ClassRep#
struct  <%ClassName%>;
typedef     void        (__closure  *   <%ClassName%>ADOQueryOK)(<%ClassName%> * curData);
<%ClassComment%>
struct	<%ClassName%>
{
    #MemberRep#
    <%MemberReadDataType%>		<%MemberReadDataName%>;		<%MemberComment%>
    #MemberRepEnd#
    DWORD    ADOResult;
    bool				ADOStoreCreate(TADOStoredProc *StoredProc, bool bNeedOutput)
    {
        try
        {
            StoredProc->Parameters->Clear();
        #MemberRep#
            <%ADOStoreCreateFunc%>
        #MemberRepEnd#
            if(bNeedOutput)
                StoredProc->Parameters->CreateParameter("@ADOResult", ftInteger, pdOutput, sizeof(int), 0);
            else
            	StoredProc->Parameters->CreateParameter("@ADOResult", ftInteger, pdInput, sizeof(int), 0);
            return true;
        }
        catch(Exception &e)
        {
            GetLog()->Error("ADOStoreCreate Error : %s", e.Message);
            return false;
        }
    }
    bool                            ADOStoreRead(TADOStoredProc *StoredProc)
    {
        try
        {
            String  buffer;
        #MemberRep#
            <%ADOStoreReadFunc%>
        #MemberRepEnd#
            ADOResult = (DWORD)StoredProc->Parameters->ParamByName("@ADOResult")->Value;
            return true;
        }
        catch(Exception &e)
        {
            GetLog()->Error("ADOStoreRead Error : %s", e.Message);
            return false;
        }
    }
    bool				RunStoreProc(TADOStoredProc *StoredProc, String  procedureName, bool bNeedOutput)
    {
        try
        {
            StoredProc->ProcedureName = procedureName;
            if(ADOStoreCreate(StoredProc, bNeedOutput) == false)
                return false;
            StoredProc->Prepared=true;
            StoredProc->ExecProc();
            
            if(bNeedOutput)
            {
                if(ADOStoreRead(StoredProc) == false)
                    return false;
            }
            return  true;
        }
        catch(Exception & e)
        {
            GetLog()->Error("%s ´æ´¢¹ý³Ì´íÎó : %s", procedureName, e.Message);
            return false;
        }
    }
    bool				ADOLoad(TADOStoredProc *StoredProc)
    {
        return	RunStoreProc(StoredProc, "<%StoreProcName%>_Load", true);
    }
    bool				ADOInsert(TADOStoredProc *StoredProc)
    {
        return	RunStoreProc(StoredProc, "<%StoreProcName%>_Insert", false);
    }
    bool				ADOUpdate(TADOStoredProc *StoredProc)
    {
        return	RunStoreProc(StoredProc, "<%StoreProcName%>_Save", false);
    }
    void				ADOQueryAll(TADOStoredProc * ADOQuery, <%ClassName%>ADOQueryOK  adoQueryOKFunc)
    {
        try
        {
            String buffer;
            ADOQuery->Close();
            ADOQuery->ProcedureName = WideString("<%StoreProcName%>_QueryAll");
            ADOQuery->Open();
            
            while(!ADOQuery->Eof)
            {
                #MemberRep#
                <%ADOQueryReadFunc%>
                #MemberRepEnd#
                if(adoQueryOKFunc)
                    adoQueryOKFunc(this);
                ADOQuery->Next();
            }
            ADOQuery->Close();
        }
        catch(Exception &e)
        {
            GetLog()->Error("<%ClassName%>, QueryAll exception : %s", e.Message);
            return;
        }
    }
    int				ReadData(char *_lpData, int _Len = 0, int Key=0)
    {
        int pos = 0;
    #DynamicClass#
    #MemberRep#
        <%MemberReadDataFunc%>
    #MemberRepEnd#
    #DynamicClassElse#
        memcpy(this, _lpData, sizeof(*this));
        pos += sizeof(*this);
    #DynamicClassEnd#
	
        if(_Len != 0 && pos != _Len)
            GetLog()->Warn(FormatStr("Error in <%ClassName%> : %s ", BinToStr(_lpData, _Len)));
        return pos;
    }
    void                            Clear()
    {
    #DynamicClass#
    #MemberRep#
        <%MemberClearFunc%>
    #MemberRepEnd#
    #DynamicClassElse#
        memset(this, 0, sizeof(*this));
    #DynamicClassEnd#
    }
    int				GetLength()
    {
    #DynamicClass#
        int length = 0;
    #MemberRep#
        <%MemberGetLengthFunc%>
    #MemberRepEnd#
        return	length;
    #DynamicClassElse#
        return sizeof(<%ClassName%>);
    #DynamicClassEnd#
    }
    String				GetBuffer(int Key=0)
    {
        String data;
        data.SetLength(GetLength());
        int pos = 0;
    #DynamicClass#
    #MemberRep#
        <%MemberWriteBufferFunc%>
    #MemberRepEnd#
    #DynamicClassElse#
        WriteBuf(data.c_str(), pos, this, GetLength());
    #DynamicClassEnd#
        return data;
    }
};
#ClassRepEnd#