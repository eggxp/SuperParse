#ClassRep#

if OBJECT_ID ('<%StoreProcName%>_Load', 'p') IS NOT NULL 
DROP PROCEDURE <%StoreProcName%>_Load
GO

CREATE   PROCEDURE <%StoreProcName%>_Load
    #MemberRep#
    <%MemberADOProcName%>
    #MemberRepEnd#
    @ADOResult int OUTPUT
AS
BEGIN

SET NOCOUNT ON 
    set @ADOResult = 0
    <%ADOStoreSqlSelectName%>

SET NOCOUNT OFF
END

GO
#ClassRepEnd#