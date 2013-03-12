/***************************************************************
 * Name:      ClasSQL
 * Purpose:   Code::Blocks plugin
 * Author:    RTOSkit (rtoskit@gmail.com)
 * Created:   2013-03-03
 * Copyright: Maurizio Spoto
 * License:   BSD 2c
 **************************************************************/

#include "ProjectCfg.h"

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
#include <wx/msgdlg.h>


/**
 * @note DEFINE USED IN CODE
 */
#define CC_NULL                             _T("")

ProjectCfg::ProjectCfg()
{
      m_s3dbPath = CC_NULL;
      m_s3dbFile = CC_NULL;
}

ProjectCfg::~ProjectCfg()
{

}

wxString ProjectCfg::GetValue(eValType evt){
    switch(evt)
    {
       case E_s3dbPath:
           return m_s3dbPath;
       case E_s3dbFile:
           return m_s3dbFile;
    }
}
void ProjectCfg::SetValue(eValType evt, wxString val){
    switch(evt)
    {
       case E_s3dbPath:
            m_s3dbPath = val;
       break;
       case E_s3dbFile:
            m_s3dbFile = val;
       break;
    }
}
void ProjectCfg::RecordToFields(wxString tokenStr,wxChar sField,wxChar sValue){

    wxStringTokenizer tFields(tokenStr,sField);
    while ( tFields.HasMoreTokens() )
    {
        wxStringTokenizer tValue(tFields.GetNextToken(),sValue);
        eValType evt = (eValType) wxAtoi(tValue.GetNextToken());
        wxString val = tValue.GetNextToken();
        SetValue(evt,val);
    }
}
wxString ProjectCfg::FieldsToRecord(wxChar sField,wxChar sValue){
    wxString out = ((wxString)_T("0")) << sValue << m_s3dbPath << sField << \
                              _T("1")  << sValue << m_s3dbFile ;
    return out;

}
