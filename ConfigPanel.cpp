/***************************************************************
 * Name:      ClasSQL
 * Purpose:   Code::Blocks plugin
 * Author:    RTOSkit (rtoskit@gmail.com)
 * Created:   2013-03-03
 * Copyright: Maurizio Spoto
 * License:   BSD 2c
 **************************************************************/
#include "ConfigPanel.h"

//(*InternalHeaders(ConfigPanel)
#include <wx/intl.h>
#include <wx/string.h>
//*)

#include <wx/dirdlg.h>



/**
 * @note PROFILE's DEFINE
 */
#define CLASSQL_NAME                       _T("ClasSQL")

/**
 * @note DEFINE USED IN CODE
 */
#define CC_NULL                             _T("")


//(*IdInit(ConfigPanel)
const long ConfigPanel::ID_STATICBOX1 = wxNewId();
const long ConfigPanel::ID_STATICTEXT1 = wxNewId();
const long ConfigPanel::ID_TEXTCTRL1 = wxNewId();
const long ConfigPanel::ID_BUTTON1 = wxNewId();
const long ConfigPanel::ID_PANEL1 = wxNewId();
const long ConfigPanel::ID_STATICBOX2 = wxNewId();
const long ConfigPanel::ID_BUTTON2 = wxNewId();
const long ConfigPanel::ID_PANEL2 = wxNewId();
//*)


/**
 * @note I18N's STUFF
 */
const wxString ConfigPanel::TITLE_DDLG_DBPATH                    (_("Choose a SQLite3DB directory"));
const wxString ConfigPanel::MSG_MDLG_WANT_CLEAR_CONFIG_DATA      (_("Do you want to clear all stored project configuration data?"));
const wxString ConfigPanel::TITLE_MDLG_CLAER_CONFIG_DATA         (_("Clear stored configuration?"));
const wxString ConfigPanel::MSG_MDLG_CLEAR_CONFIG_SUCCESSFUL     (_("Clear stored configuration successful!"));
const wxString ConfigPanel::TITLE_MDLG_INFORMATION               (_("Information"));




BEGIN_EVENT_TABLE(ConfigPanel,wxPanel)
	//(*EventTable(ConfigPanel)
	//*)
END_EVENT_TABLE()



ConfigPanel::ConfigPanel(wxWindow* parent)
{
	//(*Initialize(ConfigPanel)
	wxBoxSizer* BoxSizer1;

	Create(parent, wxID_ANY, wxDefaultPosition, wxSize(30,131), wxTAB_TRAVERSAL, _T("wxID_ANY"));
	BoxSizer1 = new wxBoxSizer(wxVERTICAL);
	Panel1 = new wxPanel(this, ID_PANEL1, wxDefaultPosition, wxSize(482,144), wxTAB_TRAVERSAL, _T("ID_PANEL1"));
	StaticBox1 = new wxStaticBox(Panel1, ID_STATICBOX1, _("Default Configuration"), wxPoint(0,0), wxSize(482,160), 0, _T("ID_STATICBOX1"));
	StaticText1 = new wxStaticText(Panel1, ID_STATICTEXT1, _("SQLite DB path:"), wxPoint(8,30), wxSize(104,15), 0, _T("ID_STATICTEXT1"));
	txtDBpath = new wxTextCtrl(Panel1, ID_TEXTCTRL1, wxEmptyString, wxPoint(107,24), wxSize(332,25), 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	btnDBpath = new wxButton(Panel1, ID_BUTTON1, _("..."), wxPoint(442,24), wxSize(32,24), 0, wxDefaultValidator, _T("ID_BUTTON1"));
	BoxSizer1->Add(Panel1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Panel2 = new wxPanel(this, ID_PANEL2, wxDefaultPosition, wxSize(480,173), wxTAB_TRAVERSAL, _T("ID_PANEL2"));
	StaticBox2 = new wxStaticBox(Panel2, ID_STATICBOX2, _("Environment Options"), wxPoint(0,0), wxSize(482,160), 0, _T("ID_STATICBOX2"));
	btnClearSC = new wxButton(Panel2, ID_BUTTON2, _("Clear stored configuration"), wxPoint(16,32), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
	BoxSizer1->Add(Panel2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(BoxSizer1);
	FileDialog1 = new wxFileDialog(this, _("Select file"), wxEmptyString, wxEmptyString, wxFileSelectorDefaultWildcardStr, wxFD_DEFAULT_STYLE, wxDefaultPosition, wxDefaultSize, _T("wxFileDialog"));
	BoxSizer1->SetSizeHints(this);

	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ConfigPanel::OnbtnDBpathClick);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ConfigPanel::OnbtnClearSCClick);
	//*)


    m_s3dbPath = CC_NULL;
    ConfigManager *  cfg = Manager::Get()->GetConfigManager(CLASSQL_NAME);
    cfg->Read(_T("s3dbpath"),&m_s3dbPath);
    txtDBpath->SetValue(m_s3dbPath);



}

ConfigPanel::~ConfigPanel()
{
	//(*Destroy(ConfigPanel)
	//*)
}


void ConfigPanel::OnApply()
{
   ConfigManager *  cfg = Manager::Get()->GetConfigManager(CLASSQL_NAME);
   m_s3dbPath = txtDBpath->GetValue();
   cfg->Write(_T("s3dbpath"), m_s3dbPath);
}


void ConfigPanel::OnbtnDBpathClick(wxCommandEvent& event)
{
    if(m_s3dbPath.IsEmpty()){
       m_s3dbPath = ::wxGetCwd();
    }
    wxDirDialog dlg (this,TITLE_DDLG_DBPATH, m_s3dbPath);
    if (dlg.ShowModal()==wxID_OK)
    {
        m_s3dbPath = dlg.GetPath();
        txtDBpath->SetValue(m_s3dbPath);
    }

}

void ConfigPanel::OnbtnClearSCClick(wxCommandEvent& event)
{

    if(cbMessageBox(MSG_MDLG_WANT_CLEAR_CONFIG_DATA,
                    TITLE_MDLG_CLAER_CONFIG_DATA,
                    wxYES_NO | wxYES_DEFAULT | wxICON_QUESTION,
                    Manager::Get()->GetAppWindow()) == wxID_YES)
    {

      ConfigManager *  cfg = Manager::Get()->GetConfigManager(CLASSQL_NAME);
      cfg->Write(_T("prjcfg"), (wxString) _T(""));
      cbMessageBox(MSG_MDLG_CLEAR_CONFIG_SUCCESSFUL,
                TITLE_MDLG_INFORMATION,
                wxOK | wxICON_INFORMATION,
                Manager::Get()->GetAppWindow());
    }
}
