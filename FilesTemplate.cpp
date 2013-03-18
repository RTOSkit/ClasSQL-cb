/***************************************************************
 * Name:      ClasSQL
 * Purpose:   Code::Blocks plugin
 * Author:    RTOSkit (rtoskit@gmail.com)
 * Created:   2013-03-13
 * Copyright: Maurizio Spoto
 * License:   BSD 2c
 **************************************************************/

 #include <wx/string.h>

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
        if((m_db!=NULL)\\&\\&(m_db->IsOpen()))\n\
        {\n\
           m_db->Begin();\n\
           wxString _query;\n\
           _query.sprintf(_T(\"DELETE FROM <tablename> WHERE %s%s%s ;\"),\n\
                         prequery.c_str(),\n\
                         query.c_str(),\n\
                         postquery.c_str());\n\
           int result = m_db->ExecuteUpdate(_query);\n\
           m_db->Commit();\n\
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
     if((m_db!=NULL)\\&\\&(m_db->IsOpen()))\n\
     {\n\
       wxString _query;\n\
       _query.sprintf(_T(\"%s%s%s LIMIT %d ;\"),\n\
                      prequery.c_str(),\n\
                      query.c_str(),\n\
                      postquery.c_str(), limit);\n\
       wxSQLite3ResultSet q = m_db->ExecuteQuery(_query);\n\
       while (q.NextRow())\n\
       {\n\
           <tablename_capital>Record ar;\n\
           ar.ID = q.GetInt(0);\n\
     <fieldslist_selectmethod>\
           ar.query = _query;\n\
           out.push_back(ar);\n\
       }\n\
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
        if((m_db!=NULL)\\&\\&(m_db->IsOpen()))\n\
        {\n\
           m_db->Begin();\n\
           wxString _query;\n\
           _query.sprintf(_T(\"UPDATE <tablename> SET <fieldslist_updatemethod_p1> WHERE %s%s%s ;\"),\n\
                         <fieldslist_updatemethod_p2>\
                         prequery.c_str(),\n\
                         query.c_str(),\n\
                         postquery.c_str());\n\
           int result = m_db->ExecuteUpdate(_query);\n\
           m_db->Commit();\n\
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
        if((m_db!=NULL)\\&\\&(m_db->IsOpen()))\n\
        {\n\
           m_db->Begin();\n\
           <tablename_capital>Iterator it;\n\
           int result = 0 ,i=0;\n\
           for (it = records.begin(); it!=records.end(); ++it,i++){\n\
               <tablename_capital>Record record = *it;\n\
               wxString _query;\n\
               _query.sprintf(_T(\"INSERT INTO <tablename> (<fieldslist_insertmethod_p1>) VALUES ( <backslash><fieldslist_insertmethod_p2>) ;\"),\n\
              <fieldslist_insertmethod_p3>\
                             );\n\
               result += m_db->ExecuteUpdate(_query);\n\
           }\n\
           m_db->Commit();\n\
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
        if((m_db!=NULL)\\&\\&(m_db->IsOpen()))\n\
        {\n\
           m_db->Begin();\n\
           wxString _query;\n\
           _query.sprintf(_T(\"INSERT INTO <tablename> (<fieldslist_insertmethod_p1>) VALUES ( <backslash><fieldslist_insertmethod_p2>) ;\"),\n\
              <fieldslist_insertmethod_p3>\
                         );\n\
           int result = m_db->ExecuteUpdate(_query);\n\
           m_db->Commit();\n\
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
#include <climits>\n\
#include <cstring>\n\
#include <cstdlib>\n\
#include <cstddef>\n\
#include <memory>\n\
#include <iostream>\n\
#include <list>\n\
#include <vector>\n\
\n\
#include <wx/app.h>\n\
#include \"wx/wxsqlite3.h\"\n\
\n\
//DEFINE PARAMETERS\n\
#define DEFAULT_QUERY_LIMIT<whitespaces>(1000)\n\
//MACRO TYPE\n\
#define <tablename_capital>List        <whitespaces>std::<tdm><<tablename_capital>Record>\n\
#define <tablename_capital>Iterator    <whitespaces>std::<tdm><<tablename_capital>Record>::iterator");


wxString wxsH_INSERT_STATEMENTS_CHUNK_1 =
_T("\n\
/**\n\
 * INSERT STATEMENTS\n\
 */\n\
//INSERT ONE RECORD\n\
#define <tablename_capital>InsertRecord(x) <whitespaces><tablename_capital>InsertRecordQuery(x)\n\
//INSERT LIST OF RECORDS\n\
#define <tablename_capital>InsertRecords(x)<whitespaces><tablename_capital>InsertRecordsQuery(x)");


wxString wxsH_SELECT_STATEMENTS_CHUNK_1 =
_T("\n\
/**\n\
 * SELECT STATEMENTS\n\
 */\n\
//FREE QUERY WITHOUT LIMIT\n\
#define <tablename_capital>GetListFreeStatement(x)       <whitespaces><tablename_capital>GetListFromQuery(_T(x),_T(\"\"),_T(\"\"))\n\
//FREE QUERY WITH LIMIT\n\
#define <tablename_capital>GetListFrameFreeStatement(x,y)<whitespaces><tablename_capital>GetListFromQuery(_T(x),_T(\"\"),_T(\"\"),y)\n\
//FREE CONDITION WITHOUT LIMIT\n\
#define <tablename_capital>GetListWhere(x)               <whitespaces><tablename_capital>GetListFromQuery(_T(\"SELECT * FROM <tablename> WHERE \"),_T(x),_T(\"\"))\n\
//FREE CONDITION WITH LIMIT\n\
#define <tablename_capital>GetListFrameWhere(x,y)        <whitespaces><tablename_capital>GetListFromQuery(_T(\"SELECT * FROM <tablename> WHERE \"),_T(x),_T(\"\"), y)\n\
//SEARCH BY ID\n\
#define <tablename_capital>GetListWhereID(x)             <whitespaces><tablename_capital>GetListFromQuery(_T(\"SELECT * FROM <tablename> WHERE ID = \"),_T(x),_T(\" \"))\n\
//SEARCH BY SINGLE FIELD");


wxString wxsH_SELECT_STATEMENTS_MACRO_1 =
_T("#define <tablename_capital>GetListWhere<fieldname_capital>Exactly(x)<whitespaces><tablename_capital>GetListFromQuery(_T(\"SELECT * FROM <tablename> WHERE <fieldname> = '\"),_T(x),_T(\"' \"))\n");


wxString wxsH_SELECT_STATEMENTS_MACRO_2 =
_T("\n\
#define <tablename_capital>GetListWhere<fieldname_capital>Like(x)<whitespaces><tablename_capital>GetListFromQuery(_T(\"SELECT * FROM <tablename> WHERE <fieldname> LIKE '\"),_T(x), _T(\"' \"))");


wxString wxsH_SELECT_STATEMENTS_MACRO_3 =
_T("\n\
#define <tablename_capital>GetListFrameWhere<fieldname_capital>Exactly(x,y)<whitespaces><tablename_capital>GetListFromQuery(_T(\"SELECT * FROM <tablename> WHERE <fieldname> = '\"),_T(x),_T(\"' \"),y)");


wxString wxsH_SELECT_STATEMENTS_MACRO_4 =
_T("\n\
#define <tablename_capital>GetListFrameWhere<fieldname_capital>Like(x,y)<whitespaces><tablename_capital>GetListFromQuery(_T(\"SELECT * FROM <tablename> WHERE <fieldname> LIKE '\"),_T(x), _T(\"' \"),y)");



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
//FREE WHERE\n\
#define <tablename_capital>UpdateRecordsWhere(x,y) <whitespaces><tablename_capital>UpdateRecordsQueryWhere(_T(x),_T(\"\"),_T(\"\"),y)\n\
//UPDATE BY ID\n\
#define <tablename_capital>UpdateRecordWhereID(x,y)<whitespaces><tablename_capital>UpdateRecordsQueryWhere(_T(\" ID = \"),_T(x),_T(\" \"),y)\n\
//UPDATE BY SINGLE FIELD");




wxString wxsH_UPDATE_STATEMENTS_MACRO_1 =
_T("#define <tablename_capital>UpdateRecordsWhere<fieldname_capital>Exactly(x,y)<whitespaces><tablename_capital>UpdateRecordsQueryWhere(_T(\" <fieldname> = '\"),_T(x),_T(\"' \"),y)\n");

wxString wxsH_UPDATE_STATEMENTS_MACRO_2 =
_T("\n\
#define <tablename_capital>UpdateRecordsWhere<fieldname_capital>Like(x,y)<whitespaces><tablename_capital>UpdateRecordsQueryWhere(_T(\" <fieldname> LIKE '\"),_T(x),_T(\"' \"),y)");


wxString wxsH_UPDATE_STATEMENTS_CHUNK_2 =
_T("\n\
<wxsH_UPDATE_STATEMENTS_MACRO_1>\n\
<wxsH_UPDATE_STATEMENTS_MACRO_2>\n");


wxString wxsH_DELETE_STATEMENTS_CHUNK_1 =
_T("\n\
/**\n\
 * DELETE STATEMENTS\n\
 */\n\
//FREE WHERE\n\
#define <tablename_capital>DeleteRecordsWhere(x) <whitespaces><tablename_capital>DeleteRecordsQueryWhere(_T(x),_T(\"\"),_T(\"\"))\n\
//DELETE BY ID\n\
#define <tablename_capital>DeleteRecordWhereID(x)<whitespaces><tablename_capital>DeleteRecordsQueryWhere(_T(\" ID = \"),_T(x),_T(\" \"))\n\
//DELETE BY SINGLE FIELD");



wxString wxsH_DELETE_STATEMENTS_MACRO_1 =
_T("#define <tablename_capital>DeleteRecordsWhere<fieldname_capital>Exactly(x)<whitespaces><tablename_capital>DeleteRecordsQueryWhere(_T(\" <fieldname> = '\"),_T(x),_T(\"' \"))\n");

wxString wxsH_DELETE_STATEMENTS_MACRO_2 =
_T("\n\
#define <tablename_capital>DeleteRecordsWhere<fieldname_capital>Like(x)<whitespaces><tablename_capital>DeleteRecordsQueryWhere(_T(\" <fieldname> LIKE '\"),_T(x),_T(\"' \"))");


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
        Bridge<tablename_capital>(const wxString dbPath= _T(\"<default_dbpath>\"),wxSQLite3Database* db=NULL)\n\
        {m_dbPath = dbPath; m_db = (db!=NULL)?db:OpenDB();}\n\
        ~Bridge<tablename_capital>()\n\
        {if((m_db!=NULL)\\&\\&(m_db->IsOpen())){m_db->Close();}}\n\
\n\
        //TRANSPORT METHODS\n\
        wxString GetDBpath(void){ return m_dbPath; };\n\
        void SetDBpath(wxString value){m_dbPath = value; }\n\
        wxSQLite3Database* GetDB(void) {return m_db;}\n\
        void SetDB(wxSQLite3Database* value){ m_db = value; }\n\
\n\
        //SQL GENERATE METHODS\n\
        wxSQLite3Database* OpenDB(void);\n\
        void ReopenDB(void)\n\
        {if((m_db!=NULL)\\&\\&(m_db->IsOpen())){m_db->Close();} m_db = OpenDB();}\n\
        void CloseDB(void)\n\
        {if((m_db!=NULL)\\&\\&(m_db->IsOpen())){m_db->Close();}}\n\
        bool IsOpenDB(void)\n\
        { return ((m_db!=NULL)?m_db->IsOpen():false);}\n\
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
        wxSQLite3Database* m_db;\n\
};\n\
\n\
\n\
#endif // BRIDGE<tablename_upper>_H\n");


