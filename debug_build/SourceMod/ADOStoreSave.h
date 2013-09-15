#ClassRep#
if OBJECT_ID ('<%StoreProcName%>_Save', 'p') IS NOT NULL 
DROP PROCEDURE <%StoreProcName%>_Save
GO

CREATE   PROCEDURE <%StoreProcName%>_Save
    #MemberRep#
    <%MemberADOProcNoOutput%>
    #MemberRepEnd#
    @ADOResult int OUTPUT
AS
BEGIN

SET NOCOUNT ON 
    set @ADOResult = 0
    
    UPDATE <%ClassName%>
    set
        #MemberRep#NoIDT#
        <%MemberRealName%>=@<%MemberRealName%>,
        #MemberRepEnd#
        @ADOResult=1
    WHERE <%ADOStoreSqlWhereName%>

SET NOCOUNT OFF
END

GO
#ClassRepEnd#