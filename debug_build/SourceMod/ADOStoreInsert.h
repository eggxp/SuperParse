#ClassRep#

if OBJECT_ID ('<%StoreProcName%>_Insert', 'p') IS NOT NULL 
DROP PROCEDURE <%StoreProcName%>_Insert
GO

CREATE   PROCEDURE <%StoreProcName%>_Insert
    #MemberRep#
    <%MemberADOProcNoOutput%>
    #MemberRepEnd#
    @ADOResult int
AS
BEGIN

SET NOCOUNT ON 

    INSERT <%ClassName%>   (
        #MemberRep#NoIDT#
        <%MemberRealName%><%,%>
        #MemberRepEnd#
    )
    VALUES
    (
    	#MemberRep#NoIDT#
        @<%MemberRealName%><%,%>
        #MemberRepEnd#
    )

SET NOCOUNT OFF
END

GO
#ClassRepEnd#