/***************************************************************
 * Name:      BridgeUsers.cpp
 * Purpose:   Layering Abstraction for SQL Statements
 *            on 'users' table.
 * Author:    Test Author
 * Created:   2013-03-11
 * Copyright: 2013 YO
 * License:   not free
 **************************************************************
 ** Generated with ClasSQL (v.0.1)
 **************************************************************/

#include "BridgeUsers.h"


wxSQLite3Database* BridgeUsers::OpenDB(void){
    wxString tDBName = m_dbPath;
    wxSQLite3Database* db = NULL;
    if (wxFileExists(tDBName))
    {
        db = new wxSQLite3Database();
        db->Open(tDBName);
    }
    return db;
}


/**
 * DELETE STATEMENT
 */
wxString BridgeUsers::DeleteRecordsQueryWhere(const wxString& prequery,
                                                 const wxString& query,
                                                 const wxString& postquery)
{
    try{
        if(wxSQLite3Database* db = OpenDB())
        {
           db->Begin();
           wxString _query;
           _query.sprintf(_T("DELETE FROM users WHERE %s%s%s ;"),
                         prequery.c_str(),
                         query.c_str(),
                         postquery.c_str());
           int result = db->ExecuteUpdate(_query);
           db->Commit();
           db->Close();
           if(result){
             wxString out;
             out.sprintf(_T(" %s n delete records: %d"), _query.c_str(), result);
             return out;
           }else{
             return (wxString)_T("NULL");
           }
        }else{
           return (wxString)_T("NULL");
        }
    }catch (wxSQLite3Exception& e){
       return (wxString)_T("NULL");
    }
}


/**
 * SELECT STATEMENT
 */

UsersList BridgeUsers::GetListFromQuery(const wxString& prequery,
                                                      const wxString& query,
                                                      const wxString& postquery,
                                                      int limit)
{
  UsersList out;
  try{
     if(wxSQLite3Database* db = OpenDB())
     {
       wxString _query;
       _query.sprintf(_T("%s%s%s LIMIT %d ;"),
                      prequery.c_str(),
                      query.c_str(),
                      postquery.c_str(), limit);
       wxSQLite3ResultSet q = db->ExecuteQuery(_query);
       while (q.NextRow())
       {
           UsersRecord ar;
           ar.ID = q.GetInt(0);
     	   ar.login = q.GetString(1);
		   ar.pass = q.GetString(2);
		   ar.type = q.GetInt(3);
		   ar.instalerID = q.GetString(4);
		   ar.name = q.GetString(5);
		   ar.telc = q.GetString(6);
           ar.query = _query;
           out.push_back(ar);
       }
       db->Close();
     }
     return out;
  }catch (wxSQLite3Exception& e){
     return out;
  }
}


/**
 * UPDATE STATEMENT
 */
wxString BridgeUsers::UpdateRecordsQueryWhere(const wxString& prequery,
                                                const wxString& query,
                                                const wxString& postquery,
                                                UsersRecord record)
{
    try{
        if(wxSQLite3Database* db = OpenDB())
        {
           db->Begin();
           wxString _query;
           _query.sprintf(_T("UPDATE users SET  \
			 login = '%s', \
			 pass = '%s', \
			 type =  %u, \
			 instalerID = '%s', \
			 name = '%s', \
			 telc = '%s' WHERE %s%s%s ;"),
                         record.login.c_str(),
						 record.pass.c_str(),
						 record.type,
						 record.instalerID.c_str(),
						 record.name.c_str(),
						 record.telc.c_str(),
                         prequery.c_str(),
                         query.c_str(),
                         postquery.c_str());
           int result = db->ExecuteUpdate(_query);
           db->Commit();
           db->Close();
           if(result){
             wxString out;
             out.sprintf(_T(" %s n changed records: %d"), _query.c_str(), result);
             return out;
           }else{
             return (wxString)_T("NULL");
           }
        }else{
           return (wxString)_T("NULL");
        }
    }catch (wxSQLite3Exception& e){
       return (wxString)_T("NULL");
    }
}


/**
 * INSERT STATEMENT MULTI RECORDS
 */

wxString BridgeUsers::InsertRecordsQuery(UsersList records)
{
    try{
        if(wxSQLite3Database* db = OpenDB())
        {
           db->Begin();
           UsersIterator it;
           int result = 0 ,i=0;
           for (it = records.begin(); it!=records.end(); ++it,i++){
               UsersRecord record = *it;
               wxString _query;
               _query.sprintf(_T("INSERT INTO users (  \
			 login , \
			 pass , \
			 type , \
			 instalerID , \
			 name , \
			 telc) VALUES (  \
			 '%s' , \
			 '%s' , \
			  %u , \
			 '%s' , \
			 '%s' , \
			 '%s') ;"),
              record.login.c_str()
			 ,record.pass.c_str()
			 ,record.type
			 ,record.instalerID.c_str()
			 ,record.name.c_str()
			 ,record.telc.c_str()
                             );
               result += db->ExecuteUpdate(_query);
           }
           db->Commit();
           db->Close();
           if(result){
             wxString out;
             out.sprintf(_T(" insert records: %d/%d "),result, i);
             return out;
           }else{
             return (wxString)_T("NULL");
           }
        }else{
          return (wxString)_T("NULL");
        }
    }catch (wxSQLite3Exception& e){
        return (wxString)_T("NULL");
    }
}


/**
 * INSERT STATEMENT BY ONE
 */

wxString BridgeUsers::InsertRecordQuery(UsersRecord record)
{
    try{
        if(wxSQLite3Database* db = OpenDB())
        {
           db->Begin();
           wxString _query;
           _query.sprintf(_T("INSERT INTO users (  \
			 login , \
			 pass , \
			 type , \
			 instalerID , \
			 name , \
			 telc) VALUES (  \
			 '%s' , \
			 '%s' , \
			  %u , \
			 '%s' , \
			 '%s' , \
			 '%s') ;"),
              record.login.c_str()
			 ,record.pass.c_str()
			 ,record.type
			 ,record.instalerID.c_str()
			 ,record.name.c_str()
			 ,record.telc.c_str()
                         );
           int result = db->ExecuteUpdate(_query);
           db->Commit();
           db->Close();
           if(result){
             wxString out;
             out.sprintf(_T(" %s n insert record: %d"), _query.c_str(), result);
             return out;
           }else{
             return (wxString)_T("NULL");
           }
        }else{
           return (wxString)_T("NULL");
        }
    }catch (wxSQLite3Exception& e){
        return (wxString)_T("NULL");
    }
}
