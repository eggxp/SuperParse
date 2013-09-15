#ClassRep#
if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[<%ClassName%>]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[<%ClassName%>]
GO

CREATE TABLE [dbo].[<%ClassName%>] (
	#MemberRep#
	<%MemberDataSetCreateName%>
	#MemberRepEnd#
) ON [PRIMARY]
GO

ALTER TABLE [dbo].[<%ClassName%>] WITH NOCHECK ADD 
	#MemberRep#NoIDT#
	CONSTRAINT [DF_<%ClassName%>_<%MemberRealName%>] DEFAULT (0) FOR [<%MemberRealName%>],
	#MemberRepEnd#
	CONSTRAINT [PK_<%ClassName%>] PRIMARY KEY  CLUSTERED 
	(
		<%MemberKeyName%>
	)  ON [PRIMARY] 
GO

<%MemberCreateIndex%>
#ClassRepEnd#