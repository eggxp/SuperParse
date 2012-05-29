//---------------------------------------------------------------------------


#pragma hdrstop

#include "AllSourceGen.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

AllSourceGen::AllSourceGen()
{
	m_WorkSpaceManager = NULL;
	m_PluginManager = NULL;
	m_AllClassList = new TStringList;
}

AllSourceGen::~AllSourceGen()
{
	delete	m_AllClassList;
}

void		AllSourceGen::SaveSource(WorkSpaceManager	*	workSpaceManager,
										PluginManager	*	pluginManager,
										String		fileName,
										String		sourceMod)
{
	m_WorkSpaceManager = workSpaceManager;
	m_PluginManager = pluginManager;

	m_AllClassList->Clear();
	String	fileRealName = ExtractFileName(fileName);
	if(fileRealName.AnsiPos("."))
		fileRealName = LeftString(fileRealName, ".");
	auto_ptr<TStringList>	saveStr(new	TStringList);
	saveStr->Add("//---------------------------------------------------------------------------");
	String	defName = FormatStr("%sH", fileRealName);
	saveStr->Add(FormatStr("#ifndef %s", defName));
	saveStr->Add(FormatStr("#define %s", defName));
	saveStr->Add("//---------------------------------------------------------------------------");
	saveStr->Add("");
	saveStr->Add("#include	<vcl.h>");
	saveStr->Add("#include	\"CommFunc.h\"");
	saveStr->Add("#include	\"AList.h\"");
	saveStr->Add("");
	saveStr->Add("#pragma pack(push, 1)");

	//加入插件的头定义
	saveStr->Add("//插件头");
	auto_ptr<TStringList>	curStr(new TStringList);
	for(int i=0; i<m_PluginManager->GetPluginCount(); i++)
	{
		curStr->LoadFromFile(m_PluginManager->GetPlugin(i)->Name + ".h");
		saveStr->AddStrings(curStr.get());
	}

	//加入
	saveStr->Add("//============================================================");
	saveStr->Add("//文件定义");
	curStr->Clear();
	String curClassName;
	for(int i=0; i<m_WorkSpaceManager->GetWorkSpaceCount(); i++)
	{
		saveStr->Add(FormatStr("//%s", m_WorkSpaceManager->GetWorkSpace(i)->GetFullName()));
		m_WorkSpaceManager->GetWorkSpace(i)->OpenClassOnly();


		for(int j=0; j<m_WorkSpaceManager->GetWorkSpace(i)->GetClassManager()->GetClassCount(); j++)
		{
			curClassName = m_WorkSpaceManager->GetWorkSpace(i)->GetClassManager()->GetClassByIndex(j)->GetName();
			if(m_AllClassList->IndexOf(curClassName) == -1)
			{
				m_AllClassList->Add(curClassName);
			}
			else
			{
				//已经有这个类, 删除
				m_WorkSpaceManager->GetWorkSpace(i)->GetClassManager()->DeleteClass(j);
				j--;
			}
		}

		m_SourceGen.GenSource(workSpaceManager->GetWorkSpace(i),
                    sourceMod,
					m_WorkSpaceManager->GetWorkSpace(i)->GetClassManager(),
					curStr.get());
		m_WorkSpaceManager->GetWorkSpace(i)->Close();
		curStr->Add("");
		saveStr->AddStrings(curStr.get());
		saveStr->Add("//------------------------------------------------------");
	}

	saveStr->Add("#pragma pack(pop)");
	saveStr->Add("#endif");
	saveStr->SaveToFile(fileName);

}
