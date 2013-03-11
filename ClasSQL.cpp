#include <sdk.h> // Code::Blocks SDK
#ifndef CB_PRECOMP
    #include <wx/fs_zip.h>
    #include <wx/intl.h>
    #include <wx/menu.h>
    #include <wx/string.h>
    #include <wx/utils.h>
    #include <wx/xrc/xmlres.h>
    #include "cbproject.h"
    #include "configmanager.h"
    #include "globals.h"
    #include "logmanager.h"
    #include "manager.h"
    #include "projectmanager.h"
#endif
#include <configurationpanel.h>
#include "ConfigPanel.h"
#include "ClassgenDialog.h"
#include "ClasSQL.h"

// Register the plugin with Code::Blocks.
// We are using an anonymous namespace so we don't litter the global one.
namespace
{
    PluginRegistrant<ClasSQL> reg(_T("ClasSQL"));
    int idLaunch = wxNewId();
}


// events handling
BEGIN_EVENT_TABLE(ClasSQL, cbPlugin)
    EVT_MENU(idLaunch, ClasSQL::OnLaunch)
END_EVENT_TABLE()

// constructor
ClasSQL::ClasSQL()
{
     // Make sure our resources are available.
    // In the generated boilerplate code we have no resources but when
    // we add some, it will be nice that this code is in place already ;)
    if(!Manager::LoadResource(_T("ClasSQL.zip")))
    {
        NotifyMissingFile(_T("ClasSQL.zip"));
    }
}

// destructor
ClasSQL::~ClasSQL()
{
}

void ClasSQL::OnAttach()
{
	m_FileNewMenu = 0;
	cbPlugin::OnAttach();
    // do whatever initialization you need for your plugin
    // NOTE: after this function, the inherited member variable
    // m_IsAttached will be TRUE...
    // You should check for it in other functions, because if it
    // is FALSE, it means that the application did *not* "load"
    // (see: does not need) this plugin...
}

void ClasSQL::OnRelease(bool appShutDown)
{

	if (m_FileNewMenu)
	{
		m_FileNewMenu->Delete(idLaunch);
		m_FileNewMenu = 0;
	}
	cbPlugin::OnRelease(appShutDown);
    // do de-initialization for your plugin
    // if appShutDown is true, the plugin is unloaded because Code::Blocks is being shut down,
    // which means you must not use any of the SDK Managers
    // NOTE: after this function, the inherited member variable
    // m_IsAttached will be FALSE...
}

int ClasSQL::Configure()
{
    cbConfigurationDialog dlg(Manager::Get()->GetAppWindow(), wxID_ANY, _("ClasSQL Config"));
    cbConfigurationPanel* panel = GetConfigurationPanel(&dlg);
    if (panel)
    {
        dlg.AttachConfigurationPanel(panel);
        PlaceWindow(&dlg);
        return dlg.ShowModal() == wxID_OK ? 0 : -1;
    }
    return -1;
}

void ClasSQL::BuildMenu(wxMenuBar* menuBar)
{

	if (m_FileNewMenu)
	{
		m_FileNewMenu->Delete(idLaunch);
		m_FileNewMenu = 0;
	}

    const int pos = menuBar->FindMenu(_("&File"));
    if (pos != wxNOT_FOUND)
    {
        wxMenu* fm = menuBar->GetMenu(pos);
        int id = fm->FindItem(_("New"));
        wxMenuItem* mn = fm->FindItem(id);
        m_FileNewMenu = mn ? mn->GetSubMenu() : 0;
        if (m_FileNewMenu)
        {
			m_FileNewMenu->Insert(3, idLaunch, _("SQL layering Class..."));
        }
		else
			Manager::Get()->GetLogManager()->DebugLog(_T("Could not find File->New menu!"));
    }
    else
        Manager::Get()->GetLogManager()->DebugLog(_T("Could not find File menu!"));



    //NotImplemented(_T("ClasSQL::BuildMenu()"));
}















void ClasSQL::BuildModuleMenu(const ModuleType type, wxMenu* menu, const FileTreeData* data)
{
    //Some library module is ready to display a pop-up menu.
    //Check the parameter \"type\" and see which module it is
    //and append any items you need in the menu...
    //TIP: for consistency, add a separator as the first item...
    NotImplemented(_T("ClasSQL::BuildModuleMenu()"));
}




bool ClasSQL::BuildToolBar(wxToolBar* toolBar)
{
    //The application is offering its toolbar for your plugin,
    //to add any toolbar items you want...
    //Append any items you need on the toolbar...
    NotImplemented(_T("ClasSQL::BuildToolBar()"));

    // return true if you add toolbar items
    return false;
}



void ClasSQL::OnLaunch(wxCommandEvent& event)
{
    ProjectManager* prjMan = Manager::Get()->GetProjectManager();
    cbProject* prj = prjMan->GetActiveProject();
    bool isPrj=false;
    ClassgenDialog dlg(Manager::Get()->GetAppWindow());

    if(!dlg.isForceClose()){
        PlaceWindow(&dlg);
        if (dlg.ShowModal() == wxID_OK)
        {
            if (prj)
            {
                cbMessageBox(   _("The new classes has been created.\nRemember to add the following paths\nto your compiler targets:\n\
                                  ___________________________\n\
                                  runlibs/sqlite3/include\n\
                                  runlibs/sqlite3/api\n\
                                  sqlbridges"),
                                _("Information"),
                                wxOK | wxICON_INFORMATION,
                                Manager::Get()->GetAppWindow());
            }

        }
    }

}

cbConfigurationPanel* ClasSQL::GetConfigurationPanel(wxWindow* parent)
{
   return new ConfigPanel(parent);
}
