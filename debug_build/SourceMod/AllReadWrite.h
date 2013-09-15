//±£¡Ù∫Õæ…∞Ê±æºÊ»›

<%FileComment%>
#ClassRep#
<%ClassComment%>
struct  <%ClassName%>
{
  #MemberRep#
  <%MemberReadDataType%> <%MemberReadDataName%>; <%MemberComment%>
  #MemberRepEnd#
  #DynamicClass#
  String data;
  #DynamicClassElse#
  #DynamicClassEnd#
  <%ClassName%>() {
    Clear();
    <%SetHeadStr%>
  }
  int ReadData(char *_lpData, int _Len = 0, int Key=0) {
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
    if(_Len != 0 && pos != _Len)
      GetLog()->Warn(FormatStr("Error in <%ClassName%> : %s ", BinToStr(_lpData, _Len)));
    return pos;
  }
  void Clear() {
    #DynamicClass#
    #MemberRep#
    <%MemberClearFunc%>
    #MemberRepEnd#
    #DynamicClassElse#
    memset(this, 0, sizeof(*this));
    #DynamicClassEnd#
  }
  int GetLength() {
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
  String GetBuffer(int Key=0) {
    String data;
    data.SetLength(GetLength());
    ZeroMemory(data.c_str(), data.Length());
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