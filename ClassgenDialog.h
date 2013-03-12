/***************************************************************
 * Name:      ClasSQL
 * Purpose:   Code::Blocks plugin
 * Author:    RTOSkit (rtoskit@gmail.com)
 * Created:   2013-03-03
 * Copyright: Maurizio Spoto
 * License:   BSD 2c
 **************************************************************/

#ifndef CLASSGENDIALOG_H
#define CLASSGENDIALOG_H

//(*Headers(ClassgenDialog)
#include <wx/notebook.h>
#include <wx/stattext.h>
#include <wx/radiobox.h>
#include <wx/textctrl.h>
#include <wx/checklst.h>
#include <wx/statbox.h>
#include <wx/panel.h>
#include <wx/grid.h>
#include <wx/filedlg.h>
#include <wx/button.h>
#include <wx/dialog.h>
//*)



#ifndef CB_PRECOMP
    #include <wx/fs_zip.h>
    #include <wx/intl.h>
    #include <wx/menu.h>
    #include <wx/string.h>
    #include <wx/utils.h>
    #include <wx/xrc/xmlres.h>
    #include <wx/msgdlg.h>
    #include <wx/wfstream.h>
    #include <wx/zipstrm.h>
    #include <wx/archive.h>


    #include "configmanager.h"
    #include "editormanager.h"
    #include "macrosmanager.h"
    #include "compilerfactory.h"
    #include "cbstyledtextctrl.h"
    #include "cbeditor.h"
    #include "cbproject.h"
    #include "configmanager.h"
    #include "globals.h"
    #include "logmanager.h"
    #include "manager.h"
    #include "projectmanager.h"
    #include "editorbase.h"
    #include "settings.h"
    #include "printing_types.h"
#endif

#include <vector>
#include <list>

#include "ProjectCfg.h"
#include "wx/wxsqlite3.h"



/**
 *  UNCLASSED RAM
 */
extern wxString wxsCPP_FILE;
extern wxString wxsCPP_CHUNK_1;
extern wxString wxsCPP_DELETE_METHOD;
extern wxString wxsCPP_SELECT_METHOD;
extern wxString wxsCPP_UPDATE_METHOD;
extern wxString wxsCPP_INSERT_METHOD_1;
extern wxString wxsCPP_INSERT_METHOD_2;
extern wxString wxsH_FILE;
extern wxString wxsH_CHUNK_1;
extern wxString wxsH_INSERT_STATEMENTS_CHUNK_1;
extern wxString wxsH_SELECT_STATEMENTS_CHUNK_1;
extern wxString wxsH_SELECT_STATEMENTS_MACRO_1;
extern wxString wxsH_SELECT_STATEMENTS_MACRO_2;
extern wxString wxsH_SELECT_STATEMENTS_MACRO_3;
extern wxString wxsH_SELECT_STATEMENTS_MACRO_4;
extern wxString wxsH_SELECT_STATEMENTS_CHUNK_2;
extern wxString wxsH_UPDATE_STATEMENTS_CHUNK_1;
extern wxString wxsH_UPDATE_STATEMENTS_MACRO_1;
extern wxString wxsH_UPDATE_STATEMENTS_MACRO_2;
extern wxString wxsH_UPDATE_STATEMENTS_CHUNK_2;
extern wxString wxsH_DELETE_STATEMENTS_CHUNK_1;
extern wxString wxsH_DELETE_STATEMENTS_MACRO_1;
extern wxString wxsH_DELETE_STATEMENTS_MACRO_2;
extern wxString wxsH_DELETE_STATEMENTS_CHUNK_2;
extern wxString wxsH_TYPEDEF_STRUCT;
extern wxString wxsH_CLASS_DEFINE;


typedef struct{
    wxString Type;
    wxString Name;
}Prefields;

typedef struct{
    wxString Author;
    wxString Copyright;
    wxString License;
    wxString ClasSQL_version;
    wxString Tablename;
    wxString DBpath;
    bool isVector;
}DataTransport;


class ClassgenDialog: public wxDialog
{
	public:
		ClassgenDialog(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~ClassgenDialog();
        bool isForceClose(){ return m_forceClose; }
        typedef struct {
          wxString field1;
          wxString field2;
          wxString field3;
        }records;

		//(*Declarations(ClassgenDialog)
		wxTextCtrl* txtDBpath;
		wxTextCtrl* txtLicense;
		wxNotebook* Notebook1;
		wxStaticText* StaticText2;
		wxButton* btnCancel;
		wxCheckListBox* clbxTables;
		wxButton* btnDBprocess;
		wxTextCtrl* txtCopyright;
		wxPanel* Panel1;
		wxStaticText* StaticText1;
		wxFileDialog* FileDialog1;
		wxStaticText* StaticText3;
		wxStaticBox* StaticBox1;
		wxButton* btnOK;
		wxStaticBox* StaticBox2;
		wxGrid* gridFields;
		wxRadioBox* rbxTDM;
		wxStaticText* labDBpath;
		wxStaticBox* sbxLibraryrules;
		wxStaticBox* StaticBox3;
		wxStaticBox* sbxClassdefinition;
		wxTextCtrl* txtAuthor;
		wxStaticText* StaticText4;
		wxButton* btnBrowseDB;
		//*)

	protected:

		//(*Identifiers(ClassgenDialog)
		static const long ID_STATICBOX1;
		static const long ID_STATICBOX2;
		static const long ID_BUTTON1;
		static const long ID_BUTTON2;
		static const long ID_STATICTEXT2;
		static const long ID_TEXTCTRL2;
		static const long ID_BUTTON3;
		static const long ID_BUTTON4;
		static const long ID_PANEL1;
		static const long ID_NOTEBOOK1;
		static const long ID_STATICBOX3;
		static const long ID_CHECKLISTBOX1;
		static const long ID_STATICBOX4;
		static const long ID_GRID1;
		static const long ID_STATICTEXT1;
		static const long ID_STATICTEXT3;
		static const long ID_STATICTEXT4;
		static const long ID_TEXTCTRL1;
		static const long ID_TEXTCTRL3;
		static const long ID_TEXTCTRL4;
		static const long ID_STATICBOX5;
		static const long ID_STATICTEXT5;
		static const long ID_RADIOBOX1;
		//*)

		static const wxString TITLE_FDLG_DBPATH;
		static const wxString TITLE_MDLG_OPEN_FILE_ERROR;
		static const wxString TITLE_MDLG_IMPORT_TABLE_STRUCT;
		static const wxString TITLE_MDLG_GENERATE_CLASSES;
		static const wxString TITLE_MDLG_NOT_TABLE;
		static const wxString TITLE_MDLG_EDITOR_ACCESS_ERROR;
		static const wxString TITLE_MDLG_WRITE_FILE_ERROR;

		static const wxString MSG_MDLG_FILE;
		static const wxString MSG_MDLG_TABLE_STRUCT_NOT_AVAILABLE;
		static const wxString MSG_MDLG_YOU_NEED_A_PROJECT;
		static const wxString MSG_MDLG_DO_YOU_WANT_CLASSES;
		static const wxString MSG_MDLG_ENVIRONMENT_IS_LOOK;
		static const wxString MSG_MDLG_ANY_TABLE_SELECTED;
		static const wxString MSG_MDLG_GENERATION_IS_STOPPED;
		static const wxString MSG_MDLG_NOT_WRITE_FILEH;
		static const wxString MSG_MDLG_NOT_WRITE_FILECPP;
		static const wxString MSG_MDLG_DBPATH_NOTVALID;

	private:

		//(*Handlers(ClassgenDialog)
		void OnbtnOKClick(wxCommandEvent& event);
		void OnbtnCancelClick(wxCommandEvent& event);
		void OnbtnBrowseDBClick(wxCommandEvent& event);
		void OnbtnDBprocessClick(wxCommandEvent& event);
		void OnclbxTablesToggled(wxCommandEvent& event);
		void OnPaint(wxPaintEvent& event);
		void OnInit(wxInitDialogEvent& event);
		void OnButton1Click(wxCommandEvent& event);
		void OntxtDBpathText(wxCommandEvent& event);
		void OnCheckBox1Click(wxCommandEvent& event);
		void OnCheckBox2Click(wxCommandEvent& event);
		void OnTextCtrl3Text(wxCommandEvent& event);
		void OnrbxTDMSelect(wxCommandEvent& event);
		//*)
		//DIALOG
		void GenerateGrid(int rows);
		void SetFieldsGrid(const wxString& col1, const wxString& col2, const wxString& col3, int row);
		void AppendListItem(const wxString& item);
		void ClearListItem(void);
		std::list<wxString> ReadSelectedTables(void);
		void EditMode(bool isEdit);
		bool ControlSelectedTables(void);
		//TRANSPORT
		void InitProjectCfg(void);
		void SaveProjectCfg(void);
		//ENVIRONMENT
		bool TransferRunlibsToEvironment(void);
		bool SetCompilerOptions(void);
		//CLASS GENERATION
		bool DoFiles(void);
        bool DoFileH(const wxString& fileName,const wxString& filePath, wxString& filePathOut);
        bool DoFileCPP(const wxString& fileName,const wxString& filePath, wxString&  filePathOut);
        bool MakeFormatBuffers(DataTransport dataTransport, std::list<Prefields> listPrefields);
		//SQL
		bool ProcessDBfile(const wxString& strDBpath);
		bool PopulateFieldsGrid(const wxString& strDBpath, const wxString& strTableName);
		std::list<Prefields> ImportFieldsType(const wxString& strDBpath, const wxString& strTableName);
		//I/O
		bool ZisToFile(const wxString& strName,wxZipInputStream * zip);
		void DoForceDirectory(const wxFileName & filename);


		cbProject*          m_prj;
		ProjectCfg*         m_prjCfg;
		wxString            m_prjName;
		wxString            m_s3dbPathGlobal;
        wxString            m_Author;
        wxString            m_Copyright;
        wxString            m_License;
        wxString            m_tHeader;
        wxString            m_tCpp;
        bool                m_forceClose;
        wxArrayInt          m_Targets;



		DECLARE_EVENT_TABLE()
};



#endif

