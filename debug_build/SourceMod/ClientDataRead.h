<%FileComment%>
#ClassRep#
<%ClassComment%>
struct  <%ClassName%>
{
    #MemberRep#
    <%MemberReadDataType%>      <%MemberReadDataName%>;     <%MemberComment%>
    #MemberRepEnd#
    #DynamicClass#
    String                      data;
    #DynamicClassElse#
    #DynamicClassEnd#
    <%ClassName%>()
    {
        Clear();
        <%SetHeadStr%>
    }
    int             ReadData(char *_lpData, int _Len = 0, int Key=0)
    {
        Clear();
        #DynamicClass#
        #DynamicClassElse#
        if(_Len != 0 && _Len != GetLength())
            return 0;
        #DynamicClassEnd#
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
        {
            GetLog()->Warn(FormatStr("Error in <%ClassName%> : %s ", BinToStr(_lpData, _Len)));
            return 0;
        }
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
    int             GetLength()
    {
    #DynamicClass#
        int length = 0;
    #MemberRep#
        <%MemberGetLengthFunc%>
    #MemberRepEnd#
        return  length;
    #DynamicClassElse#
        return sizeof(<%ClassName%>);
    #DynamicClassEnd#
    }
    char *              GetBuffer(int Key=0)
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
    String  OutputString()
    {
        String DumpString;
        DumpString = FormatStr(
                            #MemberRep#
                            "<%MemberRealName%>:<%MemberFormatStringName%><%,%>"
                            #MemberRepEnd#
                            ,
                            #MemberRep#
                            <%MemberRealName%><%,%>
                            #MemberRepEnd#
                            );
                            
        return  DumpString;
    }
    String  GetKey();
};




void        LoadFromTable(const string  &FileName)
{
    fs::XTabFile  FileTable;
    FileTable.Load(FileName.c_str());
    <%ClassName%>    *<%SmallClassName%> = NULL;
    String  ValueString;
    String  KeyType;
    for (int i = 1; i < FileTable.GetHeight(); i++)
    {
        <%SmallClassName%> = new <%ClassName%>;
        #MemberRep#
        <%ClientReadDataFunc%>
        #MemberRepEnd#
        m_ItemList->Add(<%SmallClassName%>->GetKey(),<%SmallClassName%>);
    }
}
#ClassRepEnd#