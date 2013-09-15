<%FileComment%>
#ClassRep#
<%ClassComment%>
struct	<%ClassName%>
{
    #MemberRep#
    <%MemberReadDataType%>		<%MemberReadDataName%>;		<%MemberComment%>
    #MemberRepEnd#
    DWORD    ADOResult;
    <%ClassName%>()
    {
        Clear();
    }
    ~<%ClassName%>()
    {
    }
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
            GetLog()->Error("<%ClassName%>, %s, ADOStoreCreate Error : %s", SOURCE_INFO, e.Message);
            return false;
        }
    }
    bool                            ADOStoreRead(TADOStoredProc *StoredProc)
    {
        try
        {
            String  buffer;
            ADOResult = (DWORD)StoredProc->Parameters->ParamByName("@ADOResult")->Value;
            if(ADOResult == 0)
            {
                //¶ÁÈ¡Ê§°Ü
                return false;
            }
        #MemberRep#
            <%ADOStoreReadFunc%>
        #MemberRepEnd#
        
            <%StaticCharFix%>
            return true;
        }
        catch(Exception &e)
        {
            GetLog()->Error("<%ClassName%>, %s, ADOStoreRead Error : %s", SOURCE_INFO, e.Message);
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
            GetLog()->Error("<%ClassName%>, %s, %s ´æ´¢¹ý³Ì´íÎó : %s", SOURCE_INFO, procedureName, e.Message);
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
    bool				ADOCheckUpdate(TADOStoredProc *StoredProc)
    {
        return	RunStoreProc(StoredProc, "<%StoreProcName%>_CheckUpdate", false);
    }
    String              GetADORecords(TADOStoredProc * ADOQuery)
    {
        String buffer;
        String result;
        DWORD    DataCount = ADOQuery->RecordCount;
        result.SetLength(sizeof(DataCount) + GetLength() * DataCount);
        int pos = 0;
        WriteDWORD(result.c_str(), pos, DataCount);
        while(!ADOQuery->Eof)
        {
            Clear();
            #MemberRep#
            <%ADOQueryReadFunc%>
            #MemberRepEnd#
            <%StaticCharFix%>
            buffer = String(GetBuffer(), GetLength());
            WriteBuf(result.c_str(), pos, buffer.c_str(), buffer.Length());
            ADOQuery->Next();
        }
        return	result;
    }
    String				ADOQueryAll(TADOStoredProc * ADOQuery)
    {
        try
        {
            ADOQuery->Close();
            ADOQuery->ProcedureName = WideString("<%StoreProcName%>_QueryAll");
            ADOQuery->Open();
            
            String result = GetADORecords(ADOQuery);
            ADOQuery->Close();
            return	result;
        }
        catch(Exception &e)
        {
            GetLog()->Error("<%ClassName%>, %s, QueryAll exception : %s", SOURCE_INFO, e.Message);
            return "";
        }
    }
    String				ADOQueryIndex(TADOStoredProc * StoredProc)
    {
        try
        {
            StoredProc->Close();
            StoredProc->ProcedureName = WideString("<%StoreProcName%>_QueryIndex");
            StoredProc->Parameters->Clear();
            <%ADOStoreCreateIndexFunc%>
            StoredProc->Open();
            
            String result = GetADORecords(StoredProc);
            StoredProc->Close();
            return	result;
        }
        catch(Exception &e)
        {
            GetLog()->Error("<%ClassName%>, %s, QueryAll exception : %s", SOURCE_INFO, e.Message);
            return "";
        }
    }
    int				ReadData(char *_lpData, int _Len = 0, int Key=0)
    {
        Clear();
        int pos = 0;
    #DynamicClass#
    #MemberRep#
        <%MemberReadDataFunc%>
    #MemberRepEnd#
    #DynamicClassElse#
        memcpy(this, _lpData, sizeof(*this));
        pos += sizeof(*this);
    #DynamicClassEnd#
         <%StaticCharFix%>
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
    char *				GetBuffer(int Key=0)
    {
        #DynamicClass#
        data.SetLength(GetLength());
        ZeroMemory(data.c_str(), data.Length());
        int pos = 0;
    #MemberRep#
        <%MemberWriteBufferFunc%>
    #MemberRepEnd#
        return data.c_str();
        #DynamicClassElse#
        return    (char *)this;
        #DynamicClassEnd#
    }
};
#ClassRepEnd#