/***************************************************************
 * Name:      ClasSQL
 * Purpose:   Code::Blocks plugin
 * Author:    RTOSkit (rtoskit@gmail.com)
 * Created:   2013-03-03
 * Copyright: Maurizio Spoto
 * License:   BSD 2c
 **************************************************************/

#ifndef CONFIGPANEL_H
#define CONFIGPANEL_H

//(*Headers(ConfigPanel)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/statbox.h>
#include <wx/panel.h>
#include <wx/filedlg.h>
#include <wx/button.h>
//*)


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

class wxWindow;

class ConfigPanel: public cbConfigurationPanel
{
	public:

		ConfigPanel(wxWindow* parent);
		virtual ~ConfigPanel();

		//(*Declarations(ConfigPanel)
		wxTextCtrl* txtDBpath;
		wxButton* btnClearSC;
		wxPanel* Panel1;
		wxStaticText* StaticText1;
		wxFileDialog* FileDialog1;
		wxStaticBox* StaticBox1;
		wxStaticBox* StaticBox2;
		wxPanel* Panel2;
		wxButton* btnDBpath;
		//*)

	protected:

		//(*Identifiers(ConfigPanel)
		static const long ID_STATICBOX1;
		static const long ID_STATICTEXT1;
		static const long ID_TEXTCTRL1;
		static const long ID_BUTTON1;
		static const long ID_PANEL1;
		static const long ID_STATICBOX2;
		static const long ID_BUTTON2;
		static const long ID_PANEL2;
		//*)

		static const wxString TITLE_DDLG_DBPATH;
		static const wxString MSG_MDLG_WANT_CLEAR_CONFIG_DATA;
		static const wxString TITLE_MDLG_CLAER_CONFIG_DATA;
		static const wxString MSG_MDLG_CLEAR_CONFIG_SUCCESSFUL;
		static const wxString TITLE_MDLG_INFORMATION;

	private:
        virtual wxString GetTitle() const
        { return _("ClasSQL configuration"); }
        virtual wxString GetBitmapBaseName() const
        { return _T("ClasSQL"); }
        virtual void OnApply();
        virtual void OnCancel()
        { ; }

		//(*Handlers(ConfigPanel)
		void OnbtnDBpathClick(wxCommandEvent& event);
		void OnbtnClearSCClick(wxCommandEvent& event);
		//*)


		wxString            m_s3dbPath;

		DECLARE_EVENT_TABLE()
};

#endif

