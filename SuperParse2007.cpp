//---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------
USEFORM("UI\FrmSourceEdit.cpp", SourceEditFrm);
USEFORM("UI\FrmPlugin.cpp", PluginFrm);
USEFORM("UI\FrmSourceGenDesign.cpp", SourceGenDesignFrm);
USEFORM("UI\FrmSetup.cpp", SetupFrm);
USEFORM("UI\FrmSearchFiles.cpp", SearchFilesFrm);
USEFORM("UI\FrmSearch.cpp", SearchFrm);
USEFORM("UI\FrmListParse.cpp", ListParseFrm);
USEFORM("UI\FrmSelect.cpp", SelectFrm);
USEFORM("UI\FrmTranslation.cpp", TranslationFrm);
USEFORM("UI\FrmLog.cpp", LogFrm);
USEFORM("UI\FrmDesign.cpp", DesignFrm);
USEFORM("CHILDWIN.cpp", MDIChild);
USEFORM("about.cpp", AboutBox);
USEFORM("MAIN.CPP", MainForm);
USEFORM("UI\FrmDebug.cpp", DebugFrm);
USEFORM("UI\FrmConfig.cpp", ConfigFrm);
USEFORM("UI\FrmGoTo.cpp", GoToFrm);
USEFORM("UI\FrmEditFileDescribe.cpp", EditFileDescribeFrm);
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	Application->Initialize();
	Application->CreateForm(__classid(TMainForm), &MainForm);
		Application->CreateForm(__classid(TAboutBox), &AboutBox);
		Application->CreateForm(__classid(TMainForm), &MainForm);
		Application->CreateForm(__classid(TGoToFrm), &GoToFrm);
		Application->CreateForm(__classid(TSelectFrm), &SelectFrm);
		Application->CreateForm(__classid(TTranslationFrm), &TranslationFrm);
		Application->CreateForm(__classid(TLogFrm), &LogFrm);
		Application->CreateForm(__classid(TSourceEditFrm), &SourceEditFrm);
		Application->CreateForm(__classid(TEditFileDescribeFrm), &EditFileDescribeFrm);
		Application->CreateForm(__classid(TPluginFrm), &PluginFrm);
		Application->CreateForm(__classid(TListParseFrm), &ListParseFrm);
		Application->CreateForm(__classid(TSearchFilesFrm), &SearchFilesFrm);
		Application->CreateForm(__classid(TSearchFrm), &SearchFrm);
		Application->CreateForm(__classid(TDesignFrm), &DesignFrm);
		Application->CreateForm(__classid(TSourceGenDesignFrm), &SourceGenDesignFrm);
		Application->CreateForm(__classid(TDebugFrm), &DebugFrm);
		Application->CreateForm(__classid(TConfigFrm), &ConfigFrm);
		Application->CreateForm(__classid(TSetupFrm), &SetupFrm);
		Application->CreateForm(__classid(TConfigFrm), &ConfigFrm);
		Application->CreateForm(__classid(TDebugFrm), &DebugFrm);
		Application->CreateForm(__classid(TDesignFrm), &DesignFrm);
		Application->CreateForm(__classid(TEditFileDescribeFrm), &EditFileDescribeFrm);
		Application->CreateForm(__classid(TGoToFrm), &GoToFrm);
		Application->CreateForm(__classid(TListParseFrm), &ListParseFrm);
		Application->CreateForm(__classid(TLogFrm), &LogFrm);
		Application->CreateForm(__classid(TPluginFrm), &PluginFrm);
		Application->CreateForm(__classid(TSearchFrm), &SearchFrm);
		Application->CreateForm(__classid(TSearchFilesFrm), &SearchFilesFrm);
		Application->CreateForm(__classid(TSelectFrm), &SelectFrm);
		Application->CreateForm(__classid(TSetupFrm), &SetupFrm);
		Application->CreateForm(__classid(TSourceEditFrm), &SourceEditFrm);
		Application->CreateForm(__classid(TSourceGenDesignFrm), &SourceGenDesignFrm);
		Application->CreateForm(__classid(TTranslationFrm), &TranslationFrm);
		Application->Run();

	return 0;
}
//---------------------------------------------------------------------
