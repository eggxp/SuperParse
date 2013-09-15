#ClassRep#

if OBJECT_ID ('<%StoreProcName%>_CheckUpdate', 'p') IS NOT NULL 
DROP PROCEDURE <%StoreProcName%>_CheckUpdate
GO

CREATE   PROCEDURE <%StoreProcName%>_CheckUpdate
    #MemberRep#
    <%MemberADOProcNoOutput%>
    #MemberRepEnd#
    @ADOResult int
AS
BEGIN

SET NOCOUNT ON 
    DECLARE	@RecordCount int
    SET		@RecordCount = 0
    
    SELECT @RecordCount = count(*)  FROM  <%ClassName%>  WHERE   <%MemberKeyName%> = @<%MemberKeyName%>
    
    IF @RecordCount = 0
    BEGIN
        --调用Insert
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
    END
    ELSE
    BEGIN
        --调用Update
        UPDATE <%ClassName%>
        set
            #MemberRep#NoIDT#
            <%MemberRealName%>=@<%MemberRealName%>,
            #MemberRepEnd#
            @ADOResult=1
        WHERE <%ADOStoreSqlWhereName%>
    END
        

SET NOCOUNT OFF
END

GO
#ClassRepEnd#
