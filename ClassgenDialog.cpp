/***************************************************************
 * Name:      ClasSQL
 * Purpose:   Code::Blocks plugin
 * Author:    RTOSkit (rtoskit@gmail.com)
 * Created:   2013-03-03
 * Copyright: Maurizio Spoto
 * License:   BSD 2c
 **************************************************************/

#include "ClassgenDialog.h"

//(*InternalHeaders(ClassgenDialog)
#include <wx/settings.h>
#include <wx/font.h>
#include <wx/intl.h>
#include <wx/string.h>
//*)

#include <climits>
#include <cstring>
#include <cstdlib>
#include <memory>


/**
 * @note DEFINE USED IN CUSTOM CSV CONFIGURATION
 */
#define C_SPLIT_RECORD                      _T('|')
#define C_SPLIT_RVALUE                      _T('·')
#define C_SPLIT_FIELD                       _T('¡')
#define C_SPLIT_FVALUE                      _T('¿')



/**
 * @note DEFINE USED IN PARSING/COMPOSER
 */
#define CC_DOTH                             _T(".h")
#define CC_DOTCPP                           _T(".cpp")
#define CC_TDMVECTOR                        _T("vector")
#define CC_TDMLIST                          _T("list")

/**
 * @note DEFINE USED IN CODE
 */
#define CC_NULL                             _T("")

/**
 * @note DEFINE USED IN AFFINITY TYPE TO TYPE
 */
//IN TYPE
#define CC_DOUBLE                           _T("DOUBLE")
#define CC_INTEGER                          _T("INTEGER")
#define CC_BOOLEAN                          _T("BOOLEAN")
#define CC_TEXT                             _T("TEXT")
#define CC_BIGINT                           _T("BIGINT")
//OUT TYPE
#define TCC_INTEGER                         _T("INTEGER")
#define TCC_DOUBLE                          _T("DOUBLE")
#define TCC_BOOLEAN                         _T("BOOLEAN")
#define TCC_TEXT                            _T("TEXT")
#define TCC_INT64                           _T("INT64")


/**
 * @note DEFINE USED IN UNZIP CONTROLLER
 */
#define ZIP_SECTOR                         10241
                                           //10kb+\0
#ifndef __WXMSW__
#define ZIP_PACKAGE                        _T("/ClasSQL.zip")
#define FOLDER_SQL_LAYERING                _T("sqlbridges/")
#define PKG_API_CLASS                      _T("runlibs/sqlite3/api/sqlite3.c")
#define PKG_API_HEADER                     _T("runlibs/sqlite3/api/sqlite3.h")
#define PKG_WRAPPER_CLASS                  _T("runlibs/sqlite3/wxsqlite3.cpp")
#define PKG_WRAPPER_HEADER1                _T("runlibs/sqlite3/include/wx/wxsqlite3.h")
#define PKG_WRAPPER_HEADER2                _T("runlibs/sqlite3/include/wx/wxsqlite3def.h")
#define PKG_WRAPPER_HEADER3                _T("runlibs/sqlite3/include/wx/wxsqlite3opt.h")
#define PKG_WRAPPER_HEADER4                _T("runlibs/sqlite3/include/wx/wxsqlite3dyn.h")
#else
#define ZIP_PACKAGE                        _T("\\ClasSQL.zip")
#define FOLDER_SQL_LAYERING                _T("sqlbridges\\")
#define PKG_API_CLASS                      _T("runlibs\\sqlite3\\api\\sqlite3.c")
#define PKG_API_HEADER                     _T("runlibs\\sqlite3\\api\\sqlite3.h")
#define PKG_WRAPPER_CLASS                  _T("runlibs\\sqlite3\\wxsqlite3.cpp")
#define PKG_WRAPPER_HEADER1                _T("runlibs\\sqlite3\\include\\wx\\wxsqlite3.h")
#define PKG_WRAPPER_HEADER2                _T("runlibs\\sqlite3\\include\\wx\\wxsqlite3def.h")
#define PKG_WRAPPER_HEADER3                _T("runlibs\\sqlite3\\include\\wx\\wxsqlite3opt.h")
#define PKG_WRAPPER_HEADER4                _T("runlibs\\sqlite3\\include\\wx\\wxsqlite3dyn.h")
#endif

#define OUT_API_CLASS(x)                   x->GetCommonTopLevelPath()+PKG_API_CLASS
#define OUT_API_HEADER(x)                  x->GetCommonTopLevelPath()+PKG_API_HEADER
#define OUT_WRAPPER_CLASS(x)               x->GetCommonTopLevelPath()+PKG_WRAPPER_CLASS
#define OUT_WRAPPER_HEADER(x,y)            x->GetCommonTopLevelPath()+PKG_WRAPPER_HEADER##y


/**
 * @note PROFILE's DEFINE
 */
#define CLASSQL_NAME                       _T("ClasSQL")
#define CLASSQL_PACKAGE                    _T("ClasSQL.zip")
#define CLASSQL_VERSION                    _T("v.0.1");
#define PREFIX_CLASS                       _T("Bridge")
#define EXTENSION_DB_SUPPORT               _T("DB files (*.s3db)|*.s3db")



//(*IdInit(ClassgenDialog)
const long ClassgenDialog::ID_STATICBOX1 = wxNewId();
const long ClassgenDialog::ID_STATICBOX2 = wxNewId();
const long ClassgenDialog::ID_BUTTON1 = wxNewId();
const long ClassgenDialog::ID_BUTTON2 = wxNewId();
const long ClassgenDialog::ID_STATICTEXT2 = wxNewId();
const long ClassgenDialog::ID_TEXTCTRL2 = wxNewId();
const long ClassgenDialog::ID_BUTTON3 = wxNewId();
const long ClassgenDialog::ID_BUTTON4 = wxNewId();
const long ClassgenDialog::ID_PANEL1 = wxNewId();
const long ClassgenDialog::ID_NOTEBOOK1 = wxNewId();
const long ClassgenDialog::ID_STATICBOX3 = wxNewId();
const long ClassgenDialog::ID_CHECKLISTBOX1 = wxNewId();
const long ClassgenDialog::ID_STATICBOX4 = wxNewId();
const long ClassgenDialog::ID_GRID1 = wxNewId();
const long ClassgenDialog::ID_STATICTEXT1 = wxNewId();
const long ClassgenDialog::ID_STATICTEXT3 = wxNewId();
const long ClassgenDialog::ID_STATICTEXT4 = wxNewId();
const long ClassgenDialog::ID_TEXTCTRL1 = wxNewId();
const long ClassgenDialog::ID_TEXTCTRL3 = wxNewId();
const long ClassgenDialog::ID_TEXTCTRL4 = wxNewId();
const long ClassgenDialog::ID_STATICBOX5 = wxNewId();
const long ClassgenDialog::ID_STATICTEXT5 = wxNewId();
const long ClassgenDialog::ID_RADIOBOX1 = wxNewId();
//*)



/**
 * @note I18N's STUFF
 */
const wxString ClassgenDialog::TITLE_FDLG_DBPATH                    (_("Open SQLite3 .s3db file"));
const wxString ClassgenDialog::MSG_MDLG_FILE                        (_("File :"));
const wxString ClassgenDialog::TITLE_MDLG_OPEN_FILE_ERROR           (_("Open file error"));
const wxString ClassgenDialog::MSG_MDLG_TABLE_STRUCT_NOT_AVAILABLE  (_("Table struct not available"));
const wxString ClassgenDialog::TITLE_MDLG_IMPORT_TABLE_STRUCT       (_("Import Table struct"));
const wxString ClassgenDialog::MSG_MDLG_YOU_NEED_A_PROJECT          (_("You need to open a project/workspace before using this plugin!"));
const wxString ClassgenDialog::MSG_MDLG_DO_YOU_WANT_CLASSES         (_("Do you want generate/add the abstraction classes \nfor all selected tables?"));
const wxString ClassgenDialog::TITLE_MDLG_GENERATE_CLASSES          (_("Generate Classes?"));
const wxString ClassgenDialog::MSG_MDLG_ENVIRONMENT_IS_LOOK         (_("Your environment is in read only mode, is not possible generate new files!"));
const wxString ClassgenDialog::MSG_MDLG_ANY_TABLE_SELECTED          (_("You not have selected any table"));
const wxString ClassgenDialog::TITLE_MDLG_NOT_TABLE                 (_("Tables not Selected!"));
const wxString ClassgenDialog::MSG_MDLG_GENERATION_IS_STOPPED       (_("ClasSQL can't continue with generation of classes."));
const wxString ClassgenDialog::TITLE_MDLG_EDITOR_ACCESS_ERROR       (_("Editor access Error"));
const wxString ClassgenDialog::MSG_MDLG_NOT_WRITE_FILEH             (_("Could not save .h file %s.\nAborting..."));
const wxString ClassgenDialog::MSG_MDLG_NOT_WRITE_FILECPP           (_("Could not save .cpp file %s.\nAborting..."));
const wxString ClassgenDialog::TITLE_MDLG_WRITE_FILE_ERROR          (_("Error write to disk"));
const wxString ClassgenDialog::MSG_MDLG_DBPATH_NOTVALID             (_("Invalid DB path: \n"));


BEGIN_EVENT_TABLE(ClassgenDialog,wxDialog)
	//(*EventTable(ClassgenDialog)
	//*)
END_EVENT_TABLE()





/**
 * @note CLASS STUFF
 */
ClassgenDialog::ClassgenDialog(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{


    m_forceClose=false;
	//(*Initialize(ClassgenDialog)
	Create(parent, wxID_ANY, _("ClasSQL Plugin - Generator of Abstraction for SQL layering class"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE|wxDIALOG_NO_PARENT, _T("wxID_ANY"));
	SetClientSize(wxSize(631,577));
	sbxClassdefinition = new wxStaticBox(this, ID_STATICBOX1, _("SQL Inspector"), wxPoint(8,128), wxSize(616,232), 0, _T("ID_STATICBOX1"));
	sbxLibraryrules = new wxStaticBox(this, ID_STATICBOX2, _("Stuff\'s identifications "), wxPoint(8,360), wxSize(320,128), 0, _T("ID_STATICBOX2"));
	btnCancel = new wxButton(this, ID_BUTTON1, _("Cancel"), wxPoint(336,496), wxSize(141,72), 0, wxDefaultValidator, _T("ID_BUTTON1"));
	btnOK = new wxButton(this, ID_BUTTON2, _("Generate Class"), wxPoint(488,496), wxSize(136,72), 0, wxDefaultValidator, _T("ID_BUTTON2"));
	Notebook1 = new wxNotebook(this, ID_NOTEBOOK1, wxPoint(8,8), wxSize(616,112), 0, _T("ID_NOTEBOOK1"));
	Panel1 = new wxPanel(Notebook1, ID_PANEL1, wxDefaultPosition, wxSize(608,65), wxTAB_TRAVERSAL, _T("ID_PANEL1"));
	labDBpath = new wxStaticText(Panel1, ID_STATICTEXT2, _("DB path:"), wxPoint(8,22), wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	txtDBpath = new wxTextCtrl(Panel1, ID_TEXTCTRL2, wxEmptyString, wxPoint(66,16), wxSize(416,25), 0, wxDefaultValidator, _T("ID_TEXTCTRL2"));
	btnBrowseDB = new wxButton(Panel1, ID_BUTTON3, _("..."), wxPoint(485,16), wxSize(32,24), 0, wxDefaultValidator, _T("ID_BUTTON3"));
	btnDBprocess = new wxButton(Panel1, ID_BUTTON4, _("process"), wxPoint(520,16), wxSize(85,24), 0, wxDefaultValidator, _T("ID_BUTTON4"));
	Notebook1->AddPage(Panel1, _("SQLite"), false);
	StaticBox1 = new wxStaticBox(this, ID_STATICBOX3, _("Tables"), wxPoint(16,152), wxSize(152,200), 0, _T("ID_STATICBOX3"));
	StaticBox1->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_INACTIVECAPTIONTEXT));
	clbxTables = new wxCheckListBox(this, ID_CHECKLISTBOX1, wxPoint(24,168), wxSize(136,176), 0, 0, wxSIMPLE_BORDER|wxALWAYS_SHOW_SB|wxCLIP_CHILDREN, wxDefaultValidator, _T("ID_CHECKLISTBOX1"));
	clbxTables->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNTEXT));
	clbxTables->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_MENUBAR));
	wxFont clbxTablesFont(11,wxSWISS,wxFONTSTYLE_ITALIC,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	clbxTables->SetFont(clbxTablesFont);
	StaticBox2 = new wxStaticBox(this, ID_STATICBOX4, _("Fields"), wxPoint(168,152), wxSize(448,200), 0, _T("ID_STATICBOX4"));
	gridFields = new wxGrid(this, ID_GRID1, wxPoint(176,168), wxSize(432,176), wxNO_BORDER, _T("ID_GRID1"));
	gridFields->CreateGrid(100,3);
	gridFields->EnableEditing(true);
	gridFields->EnableGridLines(true);
	gridFields->SetColLabelSize(14);
	gridFields->SetRowLabelSize(4);
	gridFields->SetDefaultColSize(135, true);
	gridFields->SetLabelTextColour(wxSystemSettings::GetColour(wxSYS_COLOUR_SCROLLBAR));
	gridFields->SetColLabelValue(0, _("ORDER"));
	gridFields->SetColLabelValue(1, _("NAME"));
	gridFields->SetColLabelValue(2, _("TYPE"));
	gridFields->SetDefaultCellFont( gridFields->GetFont() );
	gridFields->SetDefaultCellTextColour( gridFields->GetForegroundColour() );
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Author:"), wxPoint(49,392), wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	StaticText2 = new wxStaticText(this, ID_STATICTEXT3, _("Copyright:"), wxPoint(32,424), wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	StaticText3 = new wxStaticText(this, ID_STATICTEXT4, _("License:"), wxPoint(44,456), wxDefaultSize, 0, _T("ID_STATICTEXT4"));
	txtAuthor = new wxTextCtrl(this, ID_TEXTCTRL1, wxEmptyString, wxPoint(112,384), wxSize(208,25), 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	txtCopyright = new wxTextCtrl(this, ID_TEXTCTRL3, _("2013 ..."), wxPoint(112,416), wxSize(208,25), 0, wxDefaultValidator, _T("ID_TEXTCTRL3"));
	txtLicense = new wxTextCtrl(this, ID_TEXTCTRL4, _("GPL"), wxPoint(112,448), wxSize(208,25), 0, wxDefaultValidator, _T("ID_TEXTCTRL4"));
	StaticBox3 = new wxStaticBox(this, ID_STATICBOX5, _("Search directories in compiler Targets"), wxPoint(336,360), wxSize(288,128), 0, _T("ID_STATICBOX5"));
	StaticText4 = new wxStaticText(this, ID_STATICTEXT5, _("runlibs/sqlite3/include\nrunlibs/sqlite3/api\nsqlbridges"), wxPoint(352,392), wxSize(228,54), 0, _T("ID_STATICTEXT5"));
	wxFont StaticText4Font(16,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Arial"),wxFONTENCODING_DEFAULT);
	StaticText4->SetFont(StaticText4Font);
	wxString __wxRadioBoxChoices_1[2] =
	{
		_("use std::vector"),
		_("use std::list")
	};
	rbxTDM = new wxRadioBox(this, ID_RADIOBOX1, _("Transport Data Mode"), wxPoint(8,488), wxSize(320,80), 2, __wxRadioBoxChoices_1, 2, 0, wxDefaultValidator, _T("ID_RADIOBOX1"));
	FileDialog1 = new wxFileDialog(this, _("Select file"), wxEmptyString, wxEmptyString, wxFileSelectorDefaultWildcardStr, 0, wxDefaultPosition, wxDefaultSize, _T("wxFileDialog"));
	Center();

	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ClassgenDialog::OnbtnCancelClick);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ClassgenDialog::OnbtnOKClick);
	Connect(ID_TEXTCTRL2,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&ClassgenDialog::OntxtDBpathText);
	Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ClassgenDialog::OnbtnBrowseDBClick);
	Connect(ID_BUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ClassgenDialog::OnbtnDBprocessClick);
	Connect(ID_CHECKLISTBOX1,wxEVT_COMMAND_LISTBOX_SELECTED,(wxObjectEventFunction)&ClassgenDialog::OnclbxTablesToggled);
	//*)

    InitProjectCfg();

}

ClassgenDialog::~ClassgenDialog()
{
	//(*Destroy(ClassgenDialog)
	//*)
}


/**
 * @note EVENTS
 */
void ClassgenDialog::OnbtnOKClick(wxCommandEvent& event)
{
    SaveProjectCfg();
    EndModal(wxID_OK);
}

void ClassgenDialog::OnbtnCancelClick(wxCommandEvent& event)
{
    EndModal(wxID_CANCEL);
}

/* -----------------------------------------------------------------------------------------------------
*  Select a s3db File
*/
void ClassgenDialog::OnbtnBrowseDBClick(wxCommandEvent& event)
{

    wxFileDialog *fdlg = new wxFileDialog(this, TITLE_FDLG_DBPATH, m_s3dbPathGlobal,CC_NULL,
                       EXTENSION_DB_SUPPORT, wxFD_OPEN|wxFD_FILE_MUST_EXIST);

    if (fdlg->ShowModal() == wxID_CANCEL)
        return;

    wxFileInputStream input_stream(fdlg->GetPath());
    if (!input_stream.IsOk())
    {
        wxString objStr = MSG_MDLG_FILE + fdlg->GetPath();
        cbMessageBox(objStr,TITLE_MDLG_OPEN_FILE_ERROR, wxICON_ERROR | wxOK);
        return;
    }else{
        m_s3dbPathGlobal = fdlg->GetPath();
        m_prjCfg->SetValue(ProjectCfg::E_s3dbFile,fdlg->GetFilename());
        m_prjCfg->SetValue(ProjectCfg::E_s3dbPath,m_s3dbPathGlobal);
        txtDBpath->SetValue(m_s3dbPathGlobal);
    }
}

/* -----------------------------------------------------------------------------------------------------
*  Launch Process s3db File
*/
void ClassgenDialog::OnbtnDBprocessClick(wxCommandEvent& event)
{
    if(!txtDBpath->GetValue().IsEmpty()){
      EditMode(ProcessDBfile(txtDBpath->GetValue()));
    }
}


/* -----------------------------------------------------------------------------------------------------
*  Invoke when list table change selection
*/
void ClassgenDialog::OnclbxTablesToggled(wxCommandEvent& event)
{
    int idx = clbxTables->GetSelection();
    if(idx != wxNOT_FOUND){
         PopulateFieldsGrid(txtDBpath->GetValue(),clbxTables->GetString(idx));
    }else{
      cbMessageBox(MSG_MDLG_TABLE_STRUCT_NOT_AVAILABLE,
                   TITLE_MDLG_IMPORT_TABLE_STRUCT, wxICON_ERROR | wxOK);
    }
    btnOK->Enable(ControlSelectedTables());
}


void ClassgenDialog::OntxtDBpathText(wxCommandEvent& event)
{
   if(txtDBpath->GetValue().IsEmpty()){
       EditMode(false);
   }else{
       btnDBprocess->Enable(true);
   }
}





  /**
  * @note DIALOG ABSTRACTION METHODS
  */
void ClassgenDialog::GenerateGrid(int rows)
{
    gridFields->ClearGrid();
    gridFields->DeleteRows(0,100,false);
    gridFields->InsertRows(0,rows);
    gridFields->EnableEditing(false);
    gridFields->EnableGridLines(true);
}

void ClassgenDialog::SetFieldsGrid(const wxString& col1, const wxString& col2, const wxString& col3, int row)
{
    gridFields->SetCellValue( row, 0, col1 );
    gridFields->SetCellValue( row, 1, col2 );
    gridFields->SetCellValue( row, 2, col3 );
}

void ClassgenDialog::AppendListItem(const wxString& item)
{
    clbxTables->Append(item);
}

void ClassgenDialog::ClearListItem(void)
{
    clbxTables->Clear();
}

std::list<wxString> ClassgenDialog::ReadSelectedTables(void)
{
   std::list<wxString> out;
   int ci = clbxTables->GetCount();
   for(int i=0;i<ci;i++){
      if(clbxTables->IsChecked(i)){
         out.push_back((wxString)clbxTables->GetString(i));
      }
   }
   return out;
}


bool ClassgenDialog::ControlSelectedTables(void)
{
   bool out=false;
   int ci = clbxTables->GetCount();
   for(int i=0;i<ci;i++){
      if(clbxTables->IsChecked(i)){
         out=true;
         break;
      }
   }
   return out;
}


void ClassgenDialog::EditMode(bool isEdit)
{
  if(isEdit){
     clbxTables->Enable(true);
     gridFields->Enable(true);
     if(!txtDBpath->GetValue().IsEmpty()){
        btnDBprocess->Enable(true);
     }else{
        btnDBprocess->Enable(false);
     }
     btnOK->Enable(ControlSelectedTables());
  }else{
     clbxTables->Enable(false);
     gridFields->Enable(false);
     if(!txtDBpath->GetValue().IsEmpty()){
        btnDBprocess->Enable(true);
     }else{
        btnDBprocess->Enable(false);
     }
     btnOK->Enable(false);
  }
}









 /**
  * @note TRANSPORT METHODS
  */

/* -----------------------------------------------------------------------------------------------------
*  Init Project default environment for ClasSQL from Custom CSV Configuration fields
*/
void ClassgenDialog::InitProjectCfg(void)
{

    GenerateGrid(100);

    ProjectManager* prjMan = Manager::Get()->GetProjectManager();
    m_prj = prjMan->GetActiveProject();

    if (m_prj)
    {
        m_s3dbPathGlobal = _T("");
        m_prjName = m_prj->GetTitle();

        ConfigManager *  cfg = Manager::Get()->GetConfigManager(CLASSQL_NAME);
        cfg->Read(_T("m_s3dbPath"),&m_s3dbPathGlobal);
        cfg->Read(_T("m_Author"),&m_Author);
        cfg->Read(_T("m_Copyright"),&m_Copyright);
        cfg->Read(_T("m_License"),&m_License);


        txtAuthor->SetValue(m_Author);
        txtCopyright->SetValue(m_Copyright);
        txtLicense->SetValue(m_License);

        m_prjCfg =  new ProjectCfg();
        wxString str_prjcfg = _T("");
        cfg->Read(_T("prjcfg"),&str_prjcfg);


        if(m_s3dbPathGlobal.IsEmpty())
           m_s3dbPathGlobal = m_prj->GetCommonTopLevelPath();

        if(!str_prjcfg.IsEmpty())
        {
            wxStringTokenizer tProjects(str_prjcfg,C_SPLIT_RECORD);
            while ( tProjects.HasMoreTokens() )
            {

                wxString temp1 = tProjects.GetNextToken();

                wxStringTokenizer tProject(temp1,C_SPLIT_RVALUE);
                if(tProject.HasMoreTokens()){

                    wxString baneCtrl = tProject.GetNextToken();

                    if(m_prjName.CompareTo(baneCtrl)==0){
                        wxString temp2 = tProject.GetNextToken();
                        m_prjCfg->RecordToFields(temp2,C_SPLIT_FIELD,C_SPLIT_FVALUE);
                    }
                }
            }

            if(!m_prjCfg->GetValue(ProjectCfg::E_s3dbPath).IsEmpty())
            {
               m_s3dbPathGlobal = m_prjCfg->GetValue(ProjectCfg::E_s3dbPath);
               txtDBpath->SetValue(m_s3dbPathGlobal);
            }
        }


    }
    else
    {
        m_forceClose=true;
        cbMessageBox(MSG_MDLG_YOU_NEED_A_PROJECT,
                     CLASSQL_NAME, wxICON_ERROR | wxOK);
    }
    EditMode(!txtDBpath->GetValue().IsEmpty());

}

/* -----------------------------------------------------------------------------------------------------
*  Save Project default environment for ClasSQL to a Custom CSV Configuration fields
*/
void ClassgenDialog::SaveProjectCfg(void)
{
    ConfigManager *  cfg = Manager::Get()->GetConfigManager(CLASSQL_NAME);
    wxString str_prjcfg  = CC_NULL;
    wxString str_record  = CC_NULL;
    wxString str_records = CC_NULL;
    cfg->Read(_T("prjcfg"),&str_prjcfg);
    bool isFound=false;

    if( cbMessageBox( MSG_MDLG_DO_YOU_WANT_CLASSES,
                      TITLE_MDLG_GENERATE_CLASSES,
                      wxYES_NO | wxYES_DEFAULT | wxICON_QUESTION,
                      Manager::Get()->GetAppWindow()) == wxID_YES)
    {

        if(TransferRunlibsToEvironment())
        {

            DoFiles();
            //FORCE BUSY IO
            TransferRunlibsToEvironment();

            str_record = m_prjCfg->FieldsToRecord(C_SPLIT_FIELD,C_SPLIT_FVALUE);

            if(!str_record.IsEmpty())
            {
                str_record = m_prjName + C_SPLIT_RVALUE + str_record;
                if(str_prjcfg.IsEmpty())
                {
                    str_records = str_record + C_SPLIT_RECORD;
                }
                else
                {
                    wxStringTokenizer tProjects(str_prjcfg,C_SPLIT_RECORD);
                    while ( tProjects.HasMoreTokens() )
                    {
                        wxString ptProject = tProjects.GetNextToken();
                        wxStringTokenizer tProject(ptProject,C_SPLIT_RVALUE);
                        if(tProject.HasMoreTokens()){
                            wxString nameCtrl = tProject.GetNextToken();
                            if(m_prjName.CompareTo(nameCtrl)==0){
                               str_records += str_record;
                               isFound = true;
                            }
                            else
                            {
                               str_records += ptProject;
                            }
                            str_records += C_SPLIT_RECORD;
                        }
                    }
                    if(!isFound){
                        str_records += str_record + C_SPLIT_RECORD;
                    }
                    if(!m_prjCfg->GetValue(ProjectCfg::E_s3dbPath).IsEmpty())
                    {
                       m_s3dbPathGlobal = m_prjCfg->GetValue(ProjectCfg::E_s3dbPath);
                    }
                 }
            }

            m_Author = txtAuthor->GetValue();
            m_Copyright = txtCopyright->GetValue();
            m_License = txtLicense->GetValue();

            cfg->Write(_T("prjcfg"), str_records);
            cfg->Write(_T("m_Author"), m_Author);
            cfg->Write(_T("m_Copyright"), m_Copyright);
            cfg->Write(_T("m_License"), m_License);
        }
        else
        {
            cbMessageBox(MSG_MDLG_ENVIRONMENT_IS_LOOK,
                         CLASSQL_NAME, wxICON_ERROR | wxOK);
            m_forceClose=true;
        }
    }else{
        EndModal(wxID_CANCEL);
    }

}










  /**
  * @note SET ENVIRONMENT METHODS
  */
/* -----------------------------------------------------------------------------------------------------
*  Transfer runlibs dir struct from plugin zip to project path
*/
bool ClassgenDialog::TransferRunlibsToEvironment(void)
{

    bool out = true;

    ProjectManager* prjMan = Manager::Get()->GetProjectManager();
    m_prj = prjMan->GetActiveProject();

    ConfigManager *  cfg = Manager::Get()->GetConfigManager(CLASSQL_NAME);

    std::auto_ptr<wxZipEntry> entry;
    wxFFileInputStream in(cfg->GetDataFolder()+ZIP_PACKAGE);
    wxZipInputStream zip(in);


    while (entry.reset(zip.GetNextEntry()), entry.get() != NULL)
    {

        wxString readName = entry->GetName();
        wxString outName = _T("");
        bool isError=false;
        if(readName.CompareTo(PKG_API_CLASS)==0){
           isError = !ZisToFile(outName=OUT_API_CLASS(m_prj),&zip);
        }
        else if(readName.CompareTo(PKG_API_HEADER)==0){
           isError = !ZisToFile(OUT_API_HEADER(m_prj),&zip);
        }
        else if(readName.CompareTo(PKG_WRAPPER_CLASS)==0){
           isError = !ZisToFile(outName=OUT_WRAPPER_CLASS(m_prj),&zip);
        }
        else if(readName.CompareTo(PKG_WRAPPER_HEADER1)==0){
           isError = !ZisToFile(OUT_WRAPPER_HEADER(m_prj,1),&zip);
        }
        else if(readName.CompareTo(PKG_WRAPPER_HEADER2)==0){
           isError = !ZisToFile(OUT_WRAPPER_HEADER(m_prj,2),&zip);
        }
        else if(readName.CompareTo(PKG_WRAPPER_HEADER3)==0){
           isError = !ZisToFile(OUT_WRAPPER_HEADER(m_prj,3),&zip);
        }
        else if(readName.CompareTo(PKG_WRAPPER_HEADER4)==0){
           isError = !ZisToFile(OUT_WRAPPER_HEADER(m_prj,4),&zip);
        }

        if(isError){
            out=false;
            break;
        }

        if(!outName.IsEmpty())
        {
           prjMan->AddFileToProject(outName, m_prj, m_Targets);
        }
    }

    if(out){
        prjMan->RebuildTree();
    }
    return out;
}


/* -----------------------------------------------------------------------------------------------------
*  //TODO Configure Build Options
*/
bool ClassgenDialog::SetCompilerOptions(void)
{
   return false;
}








 /**
  * @note SQLCLASS GENERATION METHODS
  */

bool ClassgenDialog::DoFiles(void)
{

      std::list<wxString> tableList = ReadSelectedTables();
      int sizeList = tableList.size();

      if(sizeList>0)
      {
          ProjectManager* prjMan = Manager::Get()->GetProjectManager();
          m_prj = prjMan->GetActiveProject();

          DataTransport dataTransport;

          m_Author = txtAuthor->GetValue();
          m_Copyright = txtCopyright->GetValue();
          m_License = txtLicense->GetValue();


          dataTransport.isVector = !rbxTDM->GetSelection();
          dataTransport.Author = m_Author;
          dataTransport.Copyright = m_Copyright;
          dataTransport.License = m_License;
          dataTransport.ClasSQL_version = CLASSQL_VERSION;

          wxString path = txtDBpath->GetValue();
          dataTransport.DBpath = path;

          std::list<wxString>::iterator ittl;
          for(ittl=tableList.begin();ittl!=tableList.end();++ittl)
          {

              wxString tablename = *ittl;
              std::list<Prefields> listPrefields = ImportFieldsType(path,tablename);
              if(listPrefields.size()>0)
              {
                  dataTransport.Tablename = tablename;
                  MakeFormatBuffers(dataTransport,listPrefields);
                  wxString hPath;
                  wxString cppPath;
                  DoFileH(tablename,m_prj->GetCommonTopLevelPath() + FOLDER_SQL_LAYERING ,hPath);
                  prjMan->AddFileToProject(hPath, m_prj, m_Targets);
                  DoFileCPP(tablename,m_prj->GetCommonTopLevelPath() + FOLDER_SQL_LAYERING ,cppPath);
                  prjMan->AddFileToProject(cppPath, m_prj, m_Targets);
              }
          }
          prjMan->RebuildTree();
          return true;
      }
      else
      {
        cbMessageBox(MSG_MDLG_ANY_TABLE_SELECTED,
                     TITLE_MDLG_NOT_TABLE, wxICON_ERROR | wxOK);
      }

}


/* -----------------------------------------------------------------------------------------------------
*  Make .h file
*
*/
bool ClassgenDialog::DoFileH(const wxString& fileName,const wxString& filePath, wxString&  filePathOut)
{
    wxString out = CC_NULL;
    wxString tmpH = PREFIX_CLASS + fileName + CC_DOTH;
    tmpH[6] = wxToupper(tmpH[6]);

    wxFileName hFname(UnixFilename(tmpH));
    hFname.MakeAbsolute(filePath);
    DoForceDirectory(hFname);

    cbEditor* new_ed = Manager::Get()->GetEditorManager()->New(hFname.GetFullPath());
    if (!new_ed)
    {
        cbMessageBox(MSG_MDLG_GENERATION_IS_STOPPED,
                     TITLE_MDLG_EDITOR_ACCESS_ERROR, wxICON_ERROR, this);
        return false;
    }


    wxString buffer = new_ed->GetControl()->GetText();
    Manager::Get()->GetMacrosManager()->ReplaceMacros(buffer);

    buffer << m_tHeader;
    m_tHeader = CC_NULL;

    new_ed->GetControl()->SetText(buffer);
    if (!new_ed->Save())
    {
        wxString msg;
        msg.Printf(MSG_MDLG_NOT_WRITE_FILEH, hFname.GetFullPath().c_str());
        cbMessageBox(msg, TITLE_MDLG_WRITE_FILE_ERROR, wxICON_ERROR, this);
        return false;
    }

    filePathOut = hFname.GetFullPath();

    return true;
}

/* -----------------------------------------------------------------------------------------------------
*  Make .cpp file
*
*/
bool ClassgenDialog::DoFileCPP(const wxString& fileName,const wxString& filePath, wxString&  filePathOut)
{
    wxString out = CC_NULL;
    wxString tmpH = PREFIX_CLASS + fileName + CC_DOTCPP;
    tmpH[6] = wxToupper(tmpH[6]);


    wxFileName cppFname(UnixFilename(tmpH));
    cppFname.MakeAbsolute(filePath);
    DoForceDirectory(cppFname);


    cbEditor* new_ed = Manager::Get()->GetEditorManager()->New(cppFname.GetFullPath());
    if (!new_ed)
    {
        cbMessageBox(MSG_MDLG_GENERATION_IS_STOPPED,
                     TITLE_MDLG_EDITOR_ACCESS_ERROR, wxICON_ERROR, this);
        return false;
    }


    wxString buffer = new_ed->GetControl()->GetText();
    Manager::Get()->GetMacrosManager()->ReplaceMacros(buffer);

    buffer << m_tCpp;
    m_tCpp = CC_NULL;

    new_ed->GetControl()->SetText(buffer);
    if (!new_ed->Save())
    {
        wxString msg;
        msg.Printf(MSG_MDLG_NOT_WRITE_FILECPP, cppFname.GetFullPath().c_str());
        cbMessageBox(msg, TITLE_MDLG_WRITE_FILE_ERROR, wxICON_ERROR, this);
        return false;
    }

    filePathOut = cppFname.GetFullPath();

    return true;
}





bool ClassgenDialog::MakeFormatBuffers(DataTransport dataTransport, std::list<Prefields> listPrefields)
{

      wxString author = dataTransport.Author;
      wxString copyright = dataTransport.Copyright;
      wxString license = dataTransport.License;
      wxString classql_version = dataTransport.ClasSQL_version;
      wxString default_dbpath = dataTransport.DBpath;
      wxString tdm = (dataTransport.isVector)?CC_TDMVECTOR:CC_TDMLIST;
      wxString date;
      wxDateTime dt = wxDateTime::Today();
      date.sprintf(_("%s"),dt.FormatISODate().c_str());
      wxString tablename = dataTransport.Tablename;
      wxString tablename_capital = tablename;
      tablename_capital[0] = wxToupper(tablename_capital[0]);
      wxString tablename_upper = tablename;
      tablename_upper.MakeUpper();


      wxString fieldslist_selectmethod = CC_NULL;
      wxString fieldslist_updatemethod_p1  = CC_NULL;
      wxString fieldslist_updatemethod_p2  = CC_NULL;

      wxString fieldslist_insertmethod_p1 = CC_NULL;
      wxString fieldslist_insertmethod_p2 = CC_NULL;
      wxString fieldslist_insertmethod_p3 = CC_NULL;

      wxString macroslist_ssm1 = CC_NULL;
      wxString macroslist_ssm2 = CC_NULL;
      wxString macroslist_ssm3 = CC_NULL;
      wxString macroslist_ssm4 = CC_NULL;

      wxString macroslist_usm1 = CC_NULL;
      wxString macroslist_usm2 = CC_NULL;

      wxString macroslist_dsm1 = CC_NULL;
      wxString macroslist_dsm2 = CC_NULL;

      wxString fieldslist_intypedef = CC_NULL;


       wxString _wxsCPP_FILE = wxsCPP_FILE;
       wxString _wxsCPP_CHUNK_1 = wxsCPP_CHUNK_1;
       wxString _wxsCPP_DELETE_METHOD = wxsCPP_DELETE_METHOD;
       wxString _wxsCPP_SELECT_METHOD = wxsCPP_SELECT_METHOD;
       wxString _wxsCPP_UPDATE_METHOD = wxsCPP_UPDATE_METHOD;
       wxString _wxsCPP_INSERT_METHOD_1 = wxsCPP_INSERT_METHOD_1;
       wxString _wxsCPP_INSERT_METHOD_2 = wxsCPP_INSERT_METHOD_2;
       wxString _wxsH_FILE = wxsH_FILE;
       wxString _wxsH_CHUNK_1 = wxsH_CHUNK_1;
       wxString _wxsH_INSERT_STATEMENTS_CHUNK_1 = wxsH_INSERT_STATEMENTS_CHUNK_1;
       wxString _wxsH_SELECT_STATEMENTS_CHUNK_1 = wxsH_SELECT_STATEMENTS_CHUNK_1;
       wxString _wxsH_SELECT_STATEMENTS_MACRO_1 = wxsH_SELECT_STATEMENTS_MACRO_1;
       wxString _wxsH_SELECT_STATEMENTS_MACRO_2 = wxsH_SELECT_STATEMENTS_MACRO_2;
       wxString _wxsH_SELECT_STATEMENTS_MACRO_3 = wxsH_SELECT_STATEMENTS_MACRO_3;
       wxString _wxsH_SELECT_STATEMENTS_MACRO_4 = wxsH_SELECT_STATEMENTS_MACRO_4;
       wxString _wxsH_SELECT_STATEMENTS_CHUNK_2 = wxsH_SELECT_STATEMENTS_CHUNK_2;
       wxString _wxsH_UPDATE_STATEMENTS_CHUNK_1 = wxsH_UPDATE_STATEMENTS_CHUNK_1;
       wxString _wxsH_UPDATE_STATEMENTS_MACRO_1 = wxsH_UPDATE_STATEMENTS_MACRO_1;
       wxString _wxsH_UPDATE_STATEMENTS_MACRO_2 = wxsH_UPDATE_STATEMENTS_MACRO_2;
       wxString _wxsH_UPDATE_STATEMENTS_CHUNK_2 = wxsH_UPDATE_STATEMENTS_CHUNK_2;
       wxString _wxsH_DELETE_STATEMENTS_CHUNK_1 = wxsH_DELETE_STATEMENTS_CHUNK_1;
       wxString _wxsH_DELETE_STATEMENTS_MACRO_1 = wxsH_DELETE_STATEMENTS_MACRO_1;
       wxString _wxsH_DELETE_STATEMENTS_MACRO_2 = wxsH_DELETE_STATEMENTS_MACRO_2;
       wxString _wxsH_DELETE_STATEMENTS_CHUNK_2 = wxsH_DELETE_STATEMENTS_CHUNK_2;
       wxString _wxsH_TYPEDEF_STRUCT = wxsH_TYPEDEF_STRUCT;
       wxString _wxsH_CLASS_DEFINE = wxsH_CLASS_DEFINE;


      std::list<Prefields>::iterator it;
      it = listPrefields.begin();

      wxRegEx rule_tn( _T("(<tablename>)"), wxRE_ADVANCED );
      wxRegEx rule_tnc(_T("(<tablename_capital>)"), wxRE_ADVANCED  );
      wxRegEx rule_tnu(_T("(<tablename_upper>)"), wxRE_ADVANCED  );

      int i=1;
      for(it = listPrefields.begin();it!=listPrefields.end();++it,i++){
         Prefields pf = *it;
         wxString sm1;
         wxString um1;
         wxString um2;
         wxString im1;
         wxString itd;
         if(pf.Type.CompareTo(TCC_INTEGER)==0){
            sm1.sprintf(_T("GetInt(%d);\n"),i);
            um1 = _T(" %u");
            um2 = _T(",\n");
            im1 = CC_NULL;
            itd = _T("int ");
         }else if(pf.Type.CompareTo(TCC_INT64)==0){
            sm1.sprintf(_T("GetInt64(%d);\n"),i);
            um1 = _T(" %ul");
            um2 = _T(",\n");
            im1 = CC_NULL;
            itd = _T("long long ");
         }else if(pf.Type.CompareTo(TCC_DOUBLE)==0){
            sm1.sprintf(_T("GetDouble(%d);\n"),i);
            um1 = _T(" %lf");
            um2 = _T(",\n");
            im1 = CC_NULL;
            itd = _T("double ");
         }else if(pf.Type.CompareTo(TCC_BOOLEAN)==0){
            sm1.sprintf(_T("GetBool(%d);\n"),i);
            um1 = _T(" %d");
            um2 = _T(",\n");
            im1 = CC_NULL;
            itd = _T("bool ");
         }else{
            sm1.sprintf(_T("GetString(%d);\n"),i);
            um1 = _T("'%s'");
            um2 = _T(".c_str(),\n");
            im1 = _T(".c_str()");
            itd = _T("wxString ");
         }
         fieldslist_selectmethod << (wxString)((i>1)?(wxString)_T("\t\t   ar."):(wxString)_T("\t   ar.")) << pf.Name << _T(" = q.");
         fieldslist_selectmethod << sm1;
         fieldslist_updatemethod_p1 << (wxString)((i>1)?_T(",<backslash> \n\t\t\t "):_T("<backslash>\n\t\t\t ")) << pf.Name << _T(" = ");
         fieldslist_updatemethod_p1 << um1;
         fieldslist_updatemethod_p2 << (wxString)((i>1)?_T("\t\t\t\t\t\t record."):_T("record.")) << pf.Name;
         fieldslist_updatemethod_p2 << um2;
         fieldslist_insertmethod_p1 << (wxString)((i>1)?_T(" ,<backslash>\n\t\t\t "):_T(" <backslash>\n\t\t\t ")) << pf.Name;
         fieldslist_insertmethod_p2 << (wxString)((i>1)?_T(" ,<backslash>\n\t\t\t "):_T("\n\t\t\t ")) << um1;
         fieldslist_insertmethod_p3 << (wxString)((i>1)?_T("\t\t\t ,record."):_T("record.")) << pf.Name;
         fieldslist_insertmethod_p3 << im1 << (wxString)((i>1)?_T("\n"):_T("\n"));
         fieldslist_intypedef << (wxString)((i>1)?_T("  "):CC_NULL) << itd << pf.Name << _T(";\n");

         wxRegEx rule_fn( _T("(<fieldname>)"));
         wxRegEx rule_fnc(_T("(<fieldname_capital>)"));

         wxString fieldname_capital = pf.Name;
         fieldname_capital[0] = wxToupper(fieldname_capital[0]);

         wxString t_ssm1 = _wxsH_SELECT_STATEMENTS_MACRO_1;
         wxString t_ssm2 = _wxsH_SELECT_STATEMENTS_MACRO_2;
         wxString t_ssm3 = _wxsH_SELECT_STATEMENTS_MACRO_3;
         wxString t_ssm4 = _wxsH_SELECT_STATEMENTS_MACRO_4;

         wxString t_usm1 = _wxsH_UPDATE_STATEMENTS_MACRO_1;
         wxString t_usm2 = _wxsH_UPDATE_STATEMENTS_MACRO_2;

         wxString t_dsm1 = _wxsH_DELETE_STATEMENTS_MACRO_1;
         wxString t_dsm2 = _wxsH_DELETE_STATEMENTS_MACRO_2;

         rule_fn.ReplaceAll(&t_ssm1,pf.Name);
         rule_fnc.ReplaceAll(&t_ssm1,fieldname_capital);
         rule_tn.ReplaceAll(&t_ssm1,tablename);

         rule_fn.ReplaceAll(&t_ssm2,pf.Name);
         rule_fnc.ReplaceAll(&t_ssm2,fieldname_capital);
         rule_tn.ReplaceAll(&t_ssm2,tablename);

         rule_fn.ReplaceAll(&t_ssm3,pf.Name);
         rule_fnc.ReplaceAll(&t_ssm3,fieldname_capital);
         rule_tn.ReplaceAll(&t_ssm3,tablename);

         rule_fn.ReplaceAll(&t_ssm4,pf.Name);
         rule_fnc.ReplaceAll(&t_ssm4,fieldname_capital);
         rule_tn.ReplaceAll(&t_ssm4,tablename);


         rule_fn.ReplaceAll(&t_usm1,pf.Name);
         rule_fnc.ReplaceAll(&t_usm1,fieldname_capital);

         rule_fn.ReplaceAll(&t_usm2,pf.Name);
         rule_fnc.ReplaceAll(&t_usm2,fieldname_capital);


         rule_fn.ReplaceAll(&t_dsm1,pf.Name);
         rule_fnc.ReplaceAll(&t_dsm1,fieldname_capital);


         rule_fn.ReplaceAll(&t_dsm2,pf.Name);
         rule_fnc.ReplaceAll(&t_dsm2,fieldname_capital);


         macroslist_ssm1 << t_ssm1 << CC_NULL;
         macroslist_ssm2 << t_ssm2 << CC_NULL;
         macroslist_ssm3 << t_ssm3 << CC_NULL;
         macroslist_ssm4 << t_ssm4 << CC_NULL;

         macroslist_usm1 << t_usm1 << CC_NULL;
         macroslist_usm2 << t_usm2 << CC_NULL;
         macroslist_dsm1 << t_dsm1 << CC_NULL;
         macroslist_dsm2 << t_dsm2 << CC_NULL;

      }



      if(1){//H_FILE

          if(1){//wxsH_CHUNK_1
             wxRegEx rule_author( _T("(<author>)"));
             wxRegEx rule_date( _T("(<date>)"));
             wxRegEx rule_copyright( _T("(<copyright>)"));
             wxRegEx rule_license( _T("(<license>)"));
             wxRegEx rule_classql_version( _T("(<classql_version>)"));
             wxRegEx rule_tdm( _T("(<tdm>)"));

             rule_author.ReplaceAll(&wxsH_CHUNK_1,author);
             rule_date.ReplaceAll(&_wxsH_CHUNK_1,date);
             rule_copyright.ReplaceAll(&_wxsH_CHUNK_1,copyright);
             rule_license.ReplaceAll(&_wxsH_CHUNK_1,license);
             rule_classql_version.ReplaceAll(&_wxsH_CHUNK_1,classql_version);
             rule_tdm.ReplaceAll(&_wxsH_CHUNK_1,tdm);

             rule_tnu.ReplaceAll(&_wxsH_CHUNK_1,tablename_upper);
             rule_tnc.ReplaceAll(&_wxsH_CHUNK_1,tablename_capital);

          }

          if(1){//wxsH_INSERT_STATEMENTS_CHUNK_1
          }

          if(1){//wxsH_SELECT_STATEMENTS_CHUNK_1
              rule_tn.ReplaceAll(&wxsH_SELECT_STATEMENTS_CHUNK_1,tablename);
          }

          if(1){//wxsH_SELECT_STATEMENTS_CHUNK_2
             wxRegEx rule_ssm1( _T("(<wxsH_SELECT_STATEMENTS_MACRO_1>)"));
             wxRegEx rule_ssm2( _T("(<wxsH_SELECT_STATEMENTS_MACRO_2>)"));
             wxRegEx rule_ssm3( _T("(<wxsH_SELECT_STATEMENTS_MACRO_3>)"));
             wxRegEx rule_ssm4( _T("(<wxsH_SELECT_STATEMENTS_MACRO_4>)"));


             rule_ssm1.ReplaceAll(&_wxsH_SELECT_STATEMENTS_CHUNK_2,macroslist_ssm1);
             rule_ssm2.ReplaceAll(&_wxsH_SELECT_STATEMENTS_CHUNK_2,macroslist_ssm2);
             rule_ssm3.ReplaceAll(&_wxsH_SELECT_STATEMENTS_CHUNK_2,macroslist_ssm3);
             rule_ssm4.ReplaceAll(&_wxsH_SELECT_STATEMENTS_CHUNK_2,macroslist_ssm4);
             rule_tn.ReplaceAll(&_wxsH_SELECT_STATEMENTS_CHUNK_2,tablename);
          }

          if(1){//wxsH_UPDATE_STATEMENTS_CHUNK_1
          }

          if(1){//wxsH_UPDATE_STATEMENTS_CHUNK_2
             wxRegEx rule_usm1( _T("(<wxsH_UPDATE_STATEMENTS_MACRO_1>)"));
             wxRegEx rule_usm2( _T("(<wxsH_UPDATE_STATEMENTS_MACRO_2>)"));

             rule_usm1.ReplaceAll(&_wxsH_UPDATE_STATEMENTS_CHUNK_2,macroslist_usm1);
             rule_usm2.ReplaceAll(&_wxsH_UPDATE_STATEMENTS_CHUNK_2,macroslist_usm2);
          }

          if(1){//wxsH_DELETE_STATEMENTS_CHUNK_1
          }

          if(1){//wxsH_DELETE_STATEMENTS_CHUNK_2
             wxRegEx rule_dsm1( _T("(<wxsH_DELETE_STATEMENTS_MACRO_1>)"));
             wxRegEx rule_dsm2( _T("(<wxsH_DELETE_STATEMENTS_MACRO_2>)"));

             rule_dsm1.ReplaceAll(&_wxsH_DELETE_STATEMENTS_CHUNK_2,macroslist_dsm1);
             rule_dsm2.ReplaceAll(&_wxsH_DELETE_STATEMENTS_CHUNK_2,macroslist_dsm2);
          }

          if(1){//wxsH_TYPEDEF_STRUCT
             wxRegEx rule_td( _T("(<fieldslist_intypedef>)"));

             rule_td.ReplaceAll(&_wxsH_TYPEDEF_STRUCT,fieldslist_intypedef);
             rule_tnc.ReplaceAll(&_wxsH_TYPEDEF_STRUCT,tablename_capital);

          }


          if(1){//wxsH_CLASS_DEFINE
             wxRegEx rule_ddbp( _T("(<default_dbpath>)"));

             rule_ddbp.ReplaceAll(&_wxsH_CLASS_DEFINE,default_dbpath);
             rule_tnu.ReplaceAll(&_wxsH_CLASS_DEFINE,tablename_upper);
             rule_tnc.ReplaceAll(&_wxsH_CLASS_DEFINE,tablename_capital);
          }


          if(1){//wxsH_FILE
             wxRegEx rule_c1( _T("(<wxsH_CHUNK_1>)"));
             wxRegEx rule_c2( _T("(<wxsH_INSERT_STATEMENTS_CHUNK_1>)"));
             wxRegEx rule_c3( _T("(<wxsH_SELECT_STATEMENTS_CHUNK_1>)"));
             wxRegEx rule_c4( _T("(<wxsH_SELECT_STATEMENTS_CHUNK_2>)"));
             wxRegEx rule_c5( _T("(<wxsH_UPDATE_STATEMENTS_CHUNK_1>)"));
             wxRegEx rule_c6( _T("(<wxsH_UPDATE_STATEMENTS_CHUNK_2>)"));
             wxRegEx rule_c7( _T("(<wxsH_DELETE_STATEMENTS_CHUNK_1>)"));
             wxRegEx rule_c8( _T("(<wxsH_DELETE_STATEMENTS_CHUNK_2>)"));
             wxRegEx rule_c9( _T("(<wxsH_TYPEDEF_STRUCT>)"));
             wxRegEx rule_c10( _T("(<wxsH_CLASS_DEFINE>)"));

             rule_c1.ReplaceAll(&_wxsH_FILE,_wxsH_CHUNK_1);
             rule_c2.ReplaceAll(&_wxsH_FILE,_wxsH_INSERT_STATEMENTS_CHUNK_1);
             rule_c3.ReplaceAll(&_wxsH_FILE,_wxsH_SELECT_STATEMENTS_CHUNK_1);
             rule_c4.ReplaceAll(&_wxsH_FILE,_wxsH_SELECT_STATEMENTS_CHUNK_2);
             rule_c5.ReplaceAll(&_wxsH_FILE,_wxsH_UPDATE_STATEMENTS_CHUNK_1);
             rule_c6.ReplaceAll(&_wxsH_FILE,_wxsH_UPDATE_STATEMENTS_CHUNK_2);
             rule_c7.ReplaceAll(&_wxsH_FILE,_wxsH_DELETE_STATEMENTS_CHUNK_1);
             rule_c8.ReplaceAll(&_wxsH_FILE,_wxsH_DELETE_STATEMENTS_CHUNK_2);
             rule_c9.ReplaceAll(&_wxsH_FILE,_wxsH_TYPEDEF_STRUCT);
             rule_c10.ReplaceAll(&_wxsH_FILE,_wxsH_CLASS_DEFINE);

             rule_tn.ReplaceAll(&_wxsH_FILE,tablename);
             rule_tnc.ReplaceAll(&_wxsH_FILE,tablename_capital);

          }

      }

      if(1){//CPP_FILE

          if(1){//wxsCPP_CHUNK_1
             wxRegEx rule_author( _T("(<author>)"));
             wxRegEx rule_date( _T("(<date>)"));
             wxRegEx rule_copyright( _T("(<copyright>)"));
             wxRegEx rule_license( _T("(<license>)"));
             wxRegEx rule_classql_version( _T("(<classql_version>)"));

             rule_author.ReplaceAll(&_wxsCPP_CHUNK_1,author);
             rule_date.ReplaceAll(&_wxsCPP_CHUNK_1,date);
             rule_copyright.ReplaceAll(&_wxsCPP_CHUNK_1,copyright);
             rule_license.ReplaceAll(&_wxsCPP_CHUNK_1,license);
             rule_classql_version.ReplaceAll(&_wxsCPP_CHUNK_1,classql_version);

             rule_tnc.ReplaceAll(&_wxsCPP_CHUNK_1,tablename_capital);

          }

          if(1){//wxsCPP_DELETE_METHOD
             rule_tn.ReplaceAll(&_wxsCPP_DELETE_METHOD,tablename);
             rule_tnc.ReplaceAll(&_wxsCPP_DELETE_METHOD,tablename_capital);
          }

          if(1){//wxsCPP_SELECT_METHOD
             wxRegEx rule_sm1( _T("(<fieldslist_selectmethod>)"));

             rule_sm1.ReplaceAll(&_wxsCPP_SELECT_METHOD,fieldslist_selectmethod);
             rule_tnc.ReplaceAll(&_wxsCPP_SELECT_METHOD,tablename_capital);
          }

          if(1){//wxsCPP_UPDATE_METHOD
             wxRegEx rule_um1( _T("(<fieldslist_updatemethod_p1>)"));
             wxRegEx rule_um2( _T("(<fieldslist_updatemethod_p2>)"));

             rule_um1.ReplaceAll(&_wxsCPP_UPDATE_METHOD,fieldslist_updatemethod_p1);
             rule_um2.ReplaceAll(&_wxsCPP_UPDATE_METHOD,fieldslist_updatemethod_p2);
             rule_tn.ReplaceAll(&_wxsCPP_UPDATE_METHOD,tablename);
             rule_tnc.ReplaceAll(&_wxsCPP_UPDATE_METHOD,tablename_capital);
          }

          if(1){//wxsCPP_INSERT_METHOD_1
             wxRegEx rule_im1( _T("(<fieldslist_insertmethod_p1>)"));
             wxRegEx rule_im2( _T("(<fieldslist_insertmethod_p2>)"));
             wxRegEx rule_im3( _T("(<fieldslist_insertmethod_p3>)"));

             rule_im1.ReplaceAll(&_wxsCPP_INSERT_METHOD_1,fieldslist_insertmethod_p1);
             rule_im2.ReplaceAll(&_wxsCPP_INSERT_METHOD_1,fieldslist_insertmethod_p2);
             rule_im3.ReplaceAll(&_wxsCPP_INSERT_METHOD_1,fieldslist_insertmethod_p3);
             rule_tn.ReplaceAll(&_wxsCPP_INSERT_METHOD_1,tablename);
             rule_tnc.ReplaceAll(&_wxsCPP_INSERT_METHOD_1,tablename_capital);
          }

          if(1){//wxsCPP_INSERT_METHOD_2
             wxRegEx rule_im1( _T("(<fieldslist_insertmethod_p1>)"));
             wxRegEx rule_im2( _T("(<fieldslist_insertmethod_p2>)"));
             wxRegEx rule_im3( _T("(<fieldslist_insertmethod_p3>)"));

             rule_im1.ReplaceAll(&_wxsCPP_INSERT_METHOD_2,fieldslist_insertmethod_p1);
             rule_im2.ReplaceAll(&_wxsCPP_INSERT_METHOD_2,fieldslist_insertmethod_p2);
             rule_im3.ReplaceAll(&_wxsCPP_INSERT_METHOD_2,fieldslist_insertmethod_p3);
             rule_tn.ReplaceAll(&_wxsCPP_INSERT_METHOD_2,tablename);
             rule_tnc.ReplaceAll(&_wxsCPP_INSERT_METHOD_2,tablename_capital);
          }

          if(1){//wxsCPP_FILE
             wxRegEx rule_c1( _T("(<wxsCPP_CHUNK_1>)"));
             wxRegEx rule_c2( _T("(<wxsCPP_DELETE_METHOD>)"));
             wxRegEx rule_c3( _T("(<wxsCPP_SELECT_METHOD>)"));
             wxRegEx rule_c4( _T("(<wxsCPP_UPDATE_METHOD>)"));
             wxRegEx rule_c5( _T("(<wxsCPP_INSERT_METHOD_1>)"));
             wxRegEx rule_c6( _T("(<wxsCPP_INSERT_METHOD_2>)"));
             wxRegEx rule_bs(_T("(<backslash>)"), wxRE_ADVANCED  );

             rule_c1.ReplaceAll(&_wxsCPP_FILE,_wxsCPP_CHUNK_1);
             rule_c2.ReplaceAll(&_wxsCPP_FILE,_wxsCPP_DELETE_METHOD);
             rule_c3.ReplaceAll(&_wxsCPP_FILE,_wxsCPP_SELECT_METHOD);
             rule_c4.ReplaceAll(&_wxsCPP_FILE,_wxsCPP_UPDATE_METHOD);
             rule_c5.ReplaceAll(&_wxsCPP_FILE,_wxsCPP_INSERT_METHOD_1);
             rule_c6.ReplaceAll(&_wxsCPP_FILE,_wxsCPP_INSERT_METHOD_2);

             rule_tn.ReplaceAll(&_wxsCPP_FILE,tablename);
             rule_tnc.ReplaceAll(&_wxsCPP_FILE,tablename_capital);
             rule_bs.ReplaceAll(&_wxsCPP_FILE,_T(" \\\\"));
          }
      }


      m_tHeader = _wxsH_FILE;
      m_tCpp = _wxsCPP_FILE;

      return true;

}




  /**
  * @note SQL METHODS
  */
/* -----------------------------------------------------------------------------------------------------
*  Open DB File from user select path
*/
bool ClassgenDialog::ProcessDBfile(const wxString& strDBpath)
{
    bool out=true;
    wxSQLite3Database* db = NULL;
    if (wxFileExists(strDBpath))
    {
        db = new wxSQLite3Database();
        db->Open(strDBpath);
        wxSQLite3ResultSet q1 = db->ExecuteQuery("SELECT * FROM sqlite_master WHERE type='table';");
        ClearListItem();
        while (q1.NextRow())
        {
           AppendListItem(q1.GetString(1));
        }
        db->Close();

    }else{
        cbMessageBox((wxString)MSG_MDLG_DBPATH_NOTVALID << strDBpath,
                 TITLE_MDLG_OPEN_FILE_ERROR, wxICON_ERROR | wxOK);
        out=false;
    }

    return out;
}
/* -----------------------------------------------------------------------------------------------------
*  Populate grid with reference on table list
*/
bool ClassgenDialog::PopulateFieldsGrid(const wxString& strDBpath, const wxString& strTableName)
{
    bool out=true;
    wxString tableName = strTableName;
    wxSQLite3Database* db = NULL;
    if (wxFileExists(strDBpath))
    {
        db = new wxSQLite3Database();
        db->Open(strDBpath);

        wxSQLite3Table t = db->GetTable(_T("pragma table_info(")+tableName+_T(");"));
        int rows = t.GetRowCount();
        GenerateGrid(rows);
        for (int i = 0; i < rows; i++)
        {
           t.SetRow(i);
           SetFieldsGrid(t.GetString(0),
                         t.GetString(1),
                         t.GetString(2),i);

        }
        db->Close();
    }else{
        cbMessageBox((wxString)MSG_MDLG_DBPATH_NOTVALID << strDBpath,
                TITLE_MDLG_OPEN_FILE_ERROR, wxICON_ERROR | wxOK);
    }
    return out;
}


/* -----------------------------------------------------------------------------------------------------
*  Import Tables fields from table list
*/
std::list<Prefields> ClassgenDialog::ImportFieldsType(const wxString& strDBpath, const wxString& strTableName)
{
    std::list<Prefields> out;
    wxString tableName = strTableName;
    wxSQLite3Database* db = NULL;

    if (wxFileExists(strDBpath))
    {
        db = new wxSQLite3Database();
        db->Open(strDBpath);

        wxSQLite3Table t = db->GetTable(_T("pragma table_info(")+tableName+_T(");"));
        int rows = t.GetRowCount();
        Prefields tpf;
        for (int i = 0; i < rows; i++)
        {
           t.SetRow(i);
           wxString type = t.GetString(2);
           type.MakeUpper();
           wxString name = t.GetString(1);
           name.MakeUpper();
           if(name.CompareTo(_T("ID"))!=0)
           {
               if(type.Contains(CC_INTEGER)!=0){
                  type = TCC_INTEGER;
               }else if(type.Contains(CC_DOUBLE)!=0){
                  type = TCC_DOUBLE;
               }else if(type.Contains(CC_BOOLEAN)!=0){
                  type = TCC_BOOLEAN;
               }else{
                  type = TCC_TEXT;
               }
               tpf.Type = type;
               tpf.Name = t.GetString(1);
               out.push_back(tpf);
           }
        }
        db->Close();
    }else{
        cbMessageBox((wxString)MSG_MDLG_DBPATH_NOTVALID << strDBpath,
                 TITLE_MDLG_OPEN_FILE_ERROR, wxICON_ERROR | wxOK);
    }
    return out;
}





  /**
  * @note I/O METHODS
  */

/* -----------------------------------------------------------------------------------------------------
*  ZipInputStream To Disk File
*/
bool ClassgenDialog::ZisToFile(const wxString& strName,wxZipInputStream * zip)
{
   bool out = false;
   wxTempFile tfile(UnixFilename(strName));
   char buffer[ZIP_SECTOR];

   DoForceDirectory(strName);

   do{
       zip->Read(buffer, sizeof(buffer));
       tfile.Write(buffer, zip->LastRead());
   }while(!zip->Eof());

   if(out=(tfile.Length())){
        tfile.Commit();
   }
   return out;
}
/* -----------------------------------------------------------------------------------------------------
*  Make recursive dir from FileName
*  Method inherit from Code::Blocks Classwizard Core Plugin by Yiannis An. Mandravellos
*/
void ClassgenDialog::DoForceDirectory(const wxFileName & filename)
{
    wxFileName parentname(filename);
    parentname.RemoveLastDir();

    if ((filename != parentname) && (parentname.GetDirCount() >= 1) )
        DoForceDirectory(parentname);

    if (!wxDirExists(filename.GetPath()))
        wxMkdir(filename.GetPath());
}















































/**
 *  UNCLASSED RAM
 */



/**
 * IMPLMENTATION CHUNKS
 */

wxString wxsCPP_FILE =
_T("<wxsCPP_CHUNK_1>\n\
<wxsCPP_DELETE_METHOD>\n\
<wxsCPP_SELECT_METHOD>\n\
<wxsCPP_UPDATE_METHOD>\n\
<wxsCPP_INSERT_METHOD_1>\n\
<wxsCPP_INSERT_METHOD_2>");

wxString wxsCPP_CHUNK_1 =
_T("\
/***************************************************************\n\
 * Name:      Bridge<tablename_capital>.cpp\n\
 * Purpose:   Layering Abstraction for SQL Statements\n\
 *            on '<tablename>' table.\n\
 * Author:    <author>\n\
 * Created:   <date>\n\
 * Copyright: <copyright>\n\
 * License:   <license>\n\
 **************************************************************\n\
 ** Generated with ClasSQL (<classql_version>)\n\
 **************************************************************/\n\
\n\
#include \"Bridge<tablename_capital>.h\"\n\
\n\
\n\
wxSQLite3Database* Bridge<tablename_capital>::OpenDB(void)\
{\n\
    wxString tDBName = m_dbPath;\n\
    wxSQLite3Database* db = NULL;\n\
    if (wxFileExists(tDBName))\n\
    {\n\
        db = new wxSQLite3Database();\n\
        db->Open(tDBName);\n\
    }\n\
    return db;\n\
}\n");



wxString wxsCPP_DELETE_METHOD =
_T("\n\
/**\n\
 * DELETE STATEMENT\n\
 */\n\
wxString Bridge<tablename_capital>::<tablename_capital>DeleteRecordsQueryWhere(const wxString\\& prequery,\n\
                                                 const wxString\\& query,\n\
                                                 const wxString\\& postquery)\n\
{\n\
    try{\n\
        if(wxSQLite3Database* db = OpenDB())\n\
        {\n\
           db->Begin();\n\
           wxString _query;\n\
           _query.sprintf(_T(\"DELETE FROM <tablename> WHERE %s%s%s ;\"),\n\
                         prequery.c_str(),\n\
                         query.c_str(),\n\
                         postquery.c_str());\n\
           int result = db->ExecuteUpdate(_query);\n\
           db->Commit();\n\
           db->Close();\n\
           if(result){\n\
             wxString out;\n\
             out.sprintf(_T(\" %s \\n delete records: %d\"), _query.c_str(), result);\n\
             return out;\n\
           }else{\n\
             return (wxString)_T(\"NULL\");\n\
           }\n\
        }else{\n\
           return (wxString)_T(\"NULL\");\n\
        }\n\
    }catch (wxSQLite3Exception\\& e){\n\
       return (wxString)_T(\"NULL\");\n\
    }\n\
}\n");


wxString wxsCPP_SELECT_METHOD =
_T("\n\
/**\n\
 * SELECT STATEMENT\n\
 */\n\
\n\
<tablename_capital>List Bridge<tablename_capital>::<tablename_capital>GetListFromQuery(const wxString\\& prequery,\n\
                                                      const wxString\\& query,\n\
                                                      const wxString\\& postquery,\n\
                                                      int limit)\n\
{\n\
  <tablename_capital>List out;\n\
  try{\n\
     if(wxSQLite3Database* db = OpenDB())\n\
     {\n\
       wxString _query;\n\
       _query.sprintf(_T(\"%s%s%s LIMIT %d ;\"),\n\
                      prequery.c_str(),\n\
                      query.c_str(),\n\
                      postquery.c_str(), limit);\n\
       wxSQLite3ResultSet q = db->ExecuteQuery(_query);\n\
       while (q.NextRow())\n\
       {\n\
           <tablename_capital>Record ar;\n\
           ar.ID = q.GetInt(0);\n\
     <fieldslist_selectmethod>\
           ar.query = _query;\n\
           out.push_back(ar);\n\
       }\n\
       db->Close();\n\
     }\n\
     return out;\n\
  }catch (wxSQLite3Exception\\& e){\n\
     return out;\n\
  }\n\
}\n");



wxString wxsCPP_UPDATE_METHOD =
_T("\n\
/**\n\
 * UPDATE STATEMENT\n\
 */\n\
wxString Bridge<tablename_capital>::<tablename_capital>UpdateRecordsQueryWhere(const wxString\\& prequery,\n\
                                                const wxString\\& query,\n\
                                                const wxString\\& postquery,\n\
                                                <tablename_capital>Record record)\n\
{\n\
    try{\n\
        if(wxSQLite3Database* db = OpenDB())\n\
        {\n\
           db->Begin();\n\
           wxString _query;\n\
           _query.sprintf(_T(\"UPDATE <tablename> SET <fieldslist_updatemethod_p1> WHERE %s%s%s ;\"),\n\
                         <fieldslist_updatemethod_p2>\
                         prequery.c_str(),\n\
                         query.c_str(),\n\
                         postquery.c_str());\n\
           int result = db->ExecuteUpdate(_query);\n\
           db->Commit();\n\
           db->Close();\n\
           if(result){\n\
             wxString out;\n\
             out.sprintf(_T(\" %s \\n changed records: %d\"), _query.c_str(), result);\n\
             return out;\n\
           }else{\n\
             return (wxString)_T(\"NULL\");\n\
           }\n\
        }else{\n\
           return (wxString)_T(\"NULL\");\n\
        }\n\
    }catch (wxSQLite3Exception\\& e){\n\
       return (wxString)_T(\"NULL\");\n\
    }\n\
}\n");






wxString wxsCPP_INSERT_METHOD_1 =
_T("\n\
/**\n\
 * INSERT STATEMENT MULTI RECORDS\n\
 */\n\
\n\
wxString Bridge<tablename_capital>::<tablename_capital>InsertRecordsQuery(<tablename_capital>List records)\n\
{\n\
    try{\n\
        if(wxSQLite3Database* db = OpenDB())\n\
        {\n\
           db->Begin();\n\
           <tablename_capital>Iterator it;\n\
           int result = 0 ,i=0;\n\
           for (it = records.begin(); it!=records.end(); ++it,i++){\n\
               <tablename_capital>Record record = *it;\n\
               wxString _query;\n\
               _query.sprintf(_T(\"INSERT INTO <tablename> (<fieldslist_insertmethod_p1>) VALUES ( <backslash><fieldslist_insertmethod_p2>) ;\"),\n\
              <fieldslist_insertmethod_p3>\
                             );\n\
               result += db->ExecuteUpdate(_query);\n\
           }\n\
           db->Commit();\n\
           db->Close();\n\
           if(result){\n\
             wxString out;\n\
             out.sprintf(_T(\" insert records: %d/%d \"),result, i);\n\
             return out;\n\
           }else{\n\
             return (wxString)_T(\"NULL\");\n\
           }\n\
        }else{\n\
          return (wxString)_T(\"NULL\");\n\
        }\n\
    }catch (wxSQLite3Exception\\& e){\n\
        return (wxString)_T(\"NULL\");\n\
    }\n\
}\n");


wxString wxsCPP_INSERT_METHOD_2 =
_T("\n\
/**\n\
 * INSERT STATEMENT BY ONE\n\
 */\n\
\n\
wxString Bridge<tablename_capital>::<tablename_capital>InsertRecordQuery(<tablename_capital>Record record)\n\
{\n\
    try{\n\
        if(wxSQLite3Database* db = OpenDB())\n\
        {\n\
           db->Begin();\n\
           wxString _query;\n\
           _query.sprintf(_T(\"INSERT INTO <tablename> (<fieldslist_insertmethod_p1>) VALUES ( <backslash><fieldslist_insertmethod_p2>) ;\"),\n\
              <fieldslist_insertmethod_p3>\
                         );\n\
           int result = db->ExecuteUpdate(_query);\n\
           db->Commit();\n\
           db->Close();\n\
           if(result){\n\
             wxString out;\n\
             out.sprintf(_T(\" %s \\n insert record: %d\"), _query.c_str(), result);\n\
             return out;\n\
           }else{\n\
             return (wxString)_T(\"NULL\");\n\
           }\n\
        }else{\n\
           return (wxString)_T(\"NULL\");\n\
        }\n\
    }catch (wxSQLite3Exception\\& e){\n\
        return (wxString)_T(\"NULL\");\n\
    }\n\
}\n");



 /**
 * HEADER CHUNKS
 */

wxString wxsH_FILE =
_T("<wxsH_CHUNK_1>\n\
<wxsH_INSERT_STATEMENTS_CHUNK_1>\n\
<wxsH_SELECT_STATEMENTS_CHUNK_1>\n\
<wxsH_SELECT_STATEMENTS_CHUNK_2>\n\
<wxsH_UPDATE_STATEMENTS_CHUNK_1>\n\
<wxsH_UPDATE_STATEMENTS_CHUNK_2>\n\
<wxsH_DELETE_STATEMENTS_CHUNK_1>\n\
<wxsH_DELETE_STATEMENTS_CHUNK_2>\n\
<wxsH_TYPEDEF_STRUCT>\n\
<wxsH_CLASS_DEFINE>");


wxString wxsH_CHUNK_1 =
_T("\
/***************************************************************\n\
 * Name:      Bridge<tablename_capital>.h\n\
 * Purpose:   Layering Abstraction for SQL Statements\n\
 *            on '<tablename>' table.\n\
 * Author:    <author>\n\
 * Created:   <date>\n\
 * Copyright: <copyright>\n\
 * License:   <license>\n\
 **************************************************************\n\
 ** Generated with ClasSQL (<classql_version>)\n\
 **************************************************************/\n\
\n\
#ifndef BRIDGE<tablename_upper>_H\n\
#define BRIDGE<tablename_upper>_H\n\
 \n\
 \n\
 \n\
#include <climits>\n\
#include <cstring>\n\
#include <cstdlib>\n\
#include <cstddef>\n\
#include <memory>\n\
#include <iostream>\n\
#include <list>\n\
#include <vector>\n\
\n\
\n\
#include <wx/app.h>\n\
\n\
#include \"wx/wxsqlite3.h\"\n\
\n\
//DEFINE PARAMETERS\n\
#define DEFAULT_QUERY_LIMIT                                (1000)\n\
\n\
//MACRO TYPE\n\
#define <tablename_capital>List                                        std::<tdm><<tablename_capital>Record>\n\
#define <tablename_capital>Iterator                                    std::<tdm><<tablename_capital>Record>::iterator   \n");


wxString wxsH_INSERT_STATEMENTS_CHUNK_1 =
_T("\n\
/**\n\
 * INSERT STATEMENTS\n\
 */\n\
\n\
//INSERT ONE RECORD\n\
#define <tablename_capital>InsertRecord(x)                                    <tablename_capital>InsertRecordQuery(x)\n\
//INSERT LIST OF RECORDS\n\
#define <tablename_capital>InsertRecords(x)                                   <tablename_capital>InsertRecordsQuery(x)");


wxString wxsH_SELECT_STATEMENTS_CHUNK_1 =
_T("\n\
/**\n\
 * SELECT STATEMENTS\n\
 */\n\
\n\
//FREE QUERY WITHOUT LIMIT\n\
#define <tablename_capital>GetListFreeStatement(x)                            <tablename_capital>GetListFromQuery(_T(x),_T(\"\"),_T(\"\"))\n\
//FREE QUERY WITH LIMIT\n\
#define <tablename_capital>GetListFrameFreeStatement(x,y)                     <tablename_capital>GetListFromQuery(_T(x),_T(\"\"),_T(\"\"),y)\n\
\n\
//FREE CONDITION WITHOUT LIMIT\n\
#define <tablename_capital>GetListWhere(x)                                    <tablename_capital>GetListFromQuery(_T(\"SELECT * FROM <tablename> WHERE \"),_T(x),_T(\"\"))\n\
//FREE CONDITION WITH LIMIT\n\
#define <tablename_capital>GetListFrameWhere(x,y)                             <tablename_capital>GetListFromQuery(_T(\"SELECT * FROM <tablename> WHERE \"),_T(x),_T(\"\"), y)\n\
\n\
//SEARCH BY ID\n\
#define <tablename_capital>GetListWhereID(x)                                  <tablename_capital>GetListFromQuery(_T(\"SELECT * FROM <tablename> WHERE ID = \"),_T(x),_T(\" \"))\n");





wxString wxsH_SELECT_STATEMENTS_MACRO_1 =
_T("\n\
#define <tablename_capital>GetListWhere<fieldname_capital>Exactly(x)                       <tablename_capital>GetListFromQuery(_T(\"SELECT * FROM <tablename> WHERE <fieldname> = '\"),_T(x),_T(\"' \"))");


wxString wxsH_SELECT_STATEMENTS_MACRO_2 =
_T("\n\
#define <tablename_capital>GetListWhere<fieldname_capital>Like(x)                          <tablename_capital>GetListFromQuery(_T(\"SELECT * FROM <tablename> WHERE <fieldname> LIKE '\"),_T(x), _T(\"' \"))");


wxString wxsH_SELECT_STATEMENTS_MACRO_3 =
_T("\n\
#define <tablename_capital>GetListFrameWhere<fieldname_capital>Exactly(x,y)                <tablename_capital>GetListFromQuery(_T(\"SELECT * FROM <tablename> WHERE <fieldname> = '\"),_T(x),_T(\"' \"),y)");


wxString wxsH_SELECT_STATEMENTS_MACRO_4 =
_T("\n\
#define <tablename_capital>GetListFrameWhere<fieldname_capital>Like(x,y)                   <tablename_capital>GetListFromQuery(_T(\"SELECT * FROM <tablename> WHERE <fieldname> LIKE '\"),_T(x), _T(\"' \"),y)");



wxString wxsH_SELECT_STATEMENTS_CHUNK_2 =
_T("\n\
<wxsH_SELECT_STATEMENTS_MACRO_1>\n\
<wxsH_SELECT_STATEMENTS_MACRO_2>\n\
<wxsH_SELECT_STATEMENTS_MACRO_3>\n\
<wxsH_SELECT_STATEMENTS_MACRO_4>\n");



wxString wxsH_UPDATE_STATEMENTS_CHUNK_1 =
_T("\n\
/**\n\
 * UPDATE STATEMENTS\n\
 */\n\
\n\
//FREE WHERE\n\
#define <tablename_capital>UpdateRecordsWhere(x,y)                             <tablename_capital>UpdateRecordsQueryWhere(_T(x),_T(\"\"),_T(\"\"),y)\n\
\n\
//UPDATE BY ID\n\
#define <tablename_capital>UpdateRecordWhereID(x,y)                            <tablename_capital>UpdateRecordsQueryWhere(_T(\" ID = \"),_T(x),_T(\" \"),y)\n");




wxString wxsH_UPDATE_STATEMENTS_MACRO_1 =
_T("\n\
#define <tablename_capital>UpdateRecordsWhere<fieldname_capital>Exactly(x,y)                <tablename_capital>UpdateRecordsQueryWhere(_T(\" <fieldname> = '\"),_T(x),_T(\"' \"),y)");

wxString wxsH_UPDATE_STATEMENTS_MACRO_2 =
_T("\n\
#define <tablename_capital>UpdateRecordsWhere<fieldname_capital>Like(x,y)                   <tablename_capital>UpdateRecordsQueryWhere(_T(\" <fieldname> LIKE '\"),_T(x),_T(\"' \"),y)");


wxString wxsH_UPDATE_STATEMENTS_CHUNK_2 =
_T("\n\
<wxsH_UPDATE_STATEMENTS_MACRO_1>\n\
<wxsH_UPDATE_STATEMENTS_MACRO_2>\n");


wxString wxsH_DELETE_STATEMENTS_CHUNK_1 =
_T("\n\
/**\n\
 * DELETE STATEMENTS\n\
 */\n\
\n\
//FREE WHERE\n\
#define <tablename_capital>DeleteRecordsWhere(x)                              <tablename_capital>DeleteRecordsQueryWhere(_T(x),_T(\"\"),_T(\"\"))\n\
\n\
//DELETE BY ID\n\
#define <tablename_capital>DeleteRecordWhereID(x)                             <tablename_capital>DeleteRecordsQueryWhere(_T(\" ID = \"),_T(x),_T(\" \"))");



wxString wxsH_DELETE_STATEMENTS_MACRO_1 =
_T("\n\
#define <tablename_capital>DeleteRecordsWhere<fieldname_capital>Exactly(x)                 <tablename_capital>DeleteRecordsQueryWhere(_T(\" <fieldname> = '\"),_T(x),_T(\"' \"))");

wxString wxsH_DELETE_STATEMENTS_MACRO_2 =
_T("\n\
#define <tablename_capital>DeleteRecordsWhere<fieldname_capital>Like(x)                    <tablename_capital>DeleteRecordsQueryWhere(_T(\" <fieldname> LIKE '\"),_T(x),_T(\"' \"))");


wxString wxsH_DELETE_STATEMENTS_CHUNK_2 =
_T("\n\
<wxsH_DELETE_STATEMENTS_MACRO_1>\n\
<wxsH_DELETE_STATEMENTS_MACRO_2>\n");



wxString wxsH_TYPEDEF_STRUCT =
_T("\n\
typedef struct {\n\
\n\
  //FIX MEMBERS\n\
  int ID;\n\
  wxString query;\n\
\n\
  //FIELDS IN TABLE\n\
  <fieldslist_intypedef>\n\
\n\
}<tablename_capital>Record;\n");



wxString wxsH_CLASS_DEFINE =
_T("\n\
class Bridge<tablename_capital>\n\
{\n\
    public:\n\
        Bridge<tablename_capital>(const wxString dbPath= _T(\"<default_dbpath>\"))\n\
        {m_dbPath = dbPath; }\n\
        ~Bridge<tablename_capital>();\n\
\n\
        //TRANSPORT METHODS\n\
        wxString GetDBpath(void){ return m_dbPath; };\n\
        void SetDBpath(wxString value){m_dbPath = value; }\n\
\n\
        //SQL GENERATE METHODS\n\
        wxSQLite3Database* OpenDB(void);\n\
        wxString <tablename_capital>InsertRecordQuery(<tablename_capital>Record record);\n\
        wxString <tablename_capital>InsertRecordsQuery(<tablename_capital>List records);\n\
        <tablename_capital>List <tablename_capital>GetListFromQuery(const wxString\\& prequery,\n\
                                     const wxString\\& query,\n\
                                     const wxString\\& postquery,\n\
                                     int limit=DEFAULT_QUERY_LIMIT);\n\
        wxString <tablename_capital>UpdateRecordsQueryWhere(const wxString\\& prequery,\n\
                                     const wxString\\& query,\n\
                                     const wxString\\& postquery,\n\
                                     <tablename_capital>Record record);\n\
        wxString <tablename_capital>DeleteRecordsQueryWhere(const wxString\\& prequery,\n\
                                     const wxString\\& query,\n\
                                     const wxString\\& postquery);\n\
\n\
\n\
\n\
    private:\n\
        wxString m_dbPath;\n\
};\n\
\n\
\n\
#endif // BRIDGE<tablename_upper>_H\n");


