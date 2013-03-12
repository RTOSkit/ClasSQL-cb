/***************************************************************
 * Name:      ClasSQL
 * Purpose:   Code::Blocks plugin
 * Author:    RTOSkit (rtoskit@gmail.com)
 * Created:   2013-03-03
 * Copyright: Maurizio Spoto
 * License:   BSD 2c
 **************************************************************/

#ifndef PROJECTSCFG_H
#define PROJECTSCFG_H

#include <wx/string.h>
#include <wx/tokenzr.h>

class ProjectCfg
{
    public:
        ProjectCfg();
        ~ProjectCfg();
        typedef enum {
            E_s3dbPath = 0,
            E_s3dbFile,
        }eValType;
        wxString GetValue(eValType evt);
        void SetValue(eValType evt, wxString val);
        void RecordToFields(wxString tokenStr,wxChar sField,wxChar sValue);
        wxString FieldsToRecord(wxChar sField,wxChar sValue);

    private:
        wxString            m_s3dbPath;
        wxString            m_s3dbFile;

};

#endif // PROJECTSCFG_H

