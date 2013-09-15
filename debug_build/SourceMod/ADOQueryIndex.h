#ClassRep#

if OBJECT_ID ('<%StoreProcName%>_QueryIndex', 'p') IS NOT NULL 
DROP PROCEDURE <%StoreProcName%>_QueryIndex
GO

CREATE   PROCEDURE <%StoreProcName%>_QueryIndex
    <%MemberIndexProc%>
AS
BEGIN

SET NOCOUNT ON 
    <%ADOStoreSqlQueryIndexName%>

SET NOCOUNT OFF
END

GO
#ClassRepEnd#