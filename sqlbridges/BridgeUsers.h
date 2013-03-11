/***************************************************************
 * Name:      BridgeUsers.h
 * Purpose:   Layering Abstraction for SQL Statements
 *            on 'users' table.
 * Author:    <author>
 * Created:   2013-03-11
 * Copyright: 2013 YO
 * License:   not free
 **************************************************************
 ** Generated with ClasSQL (v.0.1)
 **************************************************************/

#ifndef BRIDGEUSERS_H
#define BRIDGEUSERS_H



#include <climits>
#include <cstring>
#include <cstdlib>
#include <cstddef>
#include <memory>
#include <iostream>
#include <list>
#include <vector>


#include <wx/app.h>

#include "wx/wxsqlite3.h"

//DEFINE PARAMETERS
#define DEFAULT_QUERY_LIMIT                                (1000)

//MACRO TYPE
#define UsersList                                        std::list<UsersRecord>
#define UsersIterator                                    std::list<UsersRecord>::iterator


/**
 * INSERT STATEMENTS
 */

//INSERT ONE RECORD
#define InsertRecord(x)                                    InsertRecordQuery(x)
//INSERT LIST OF RECORDS
#define InsertRecords(x)                                   InsertRecordsQuery(x)

/**
 * SELECT STATEMENTS
 */

//FREE QUERY WITHOUT LIMIT
#define GetListFreeStatement(x)                            GetListFromQuery(_T(x),_T(""),_T(""))
//FREE QUERY WITH LIMIT
#define GetListFrameFreeStatement(x,y)                     GetListFromQuery(_T(x),_T(""),_T(""),y)

//FREE CONDITION WITHOUT LIMIT
#define GetListWhere(x)                                    GetListFromQuery(_T("SELECT * FROM users WHERE "),_T(x),_T(""))
//FREE CONDITION WITH LIMIT
#define GetListFrameWhere(x,y)                             GetListFromQuery(_T("SELECT * FROM users WHERE "),_T(x),_T(""), y)

//SEARCH BY ID
#define GetListWhereID(x)                                  GetListFromQuery(_T("SELECT * FROM users WHERE ID = "),_T(x),_T(" "))



#define GetListWhereLoginExactly(x)                       GetListFromQuery(_T("SELECT * FROM users WHERE login = '"),_T(x),_T("' "))
#define GetListWherePassExactly(x)                       GetListFromQuery(_T("SELECT * FROM users WHERE pass = '"),_T(x),_T("' "))
#define GetListWhereTypeExactly(x)                       GetListFromQuery(_T("SELECT * FROM users WHERE type = '"),_T(x),_T("' "))
#define GetListWhereInstalerIDExactly(x)                       GetListFromQuery(_T("SELECT * FROM users WHERE instalerID = '"),_T(x),_T("' "))
#define GetListWhereNameExactly(x)                       GetListFromQuery(_T("SELECT * FROM users WHERE name = '"),_T(x),_T("' "))
#define GetListWhereTelcExactly(x)                       GetListFromQuery(_T("SELECT * FROM users WHERE telc = '"),_T(x),_T("' "))

#define GetListWhereLoginLike(x)                          GetListFromQuery(_T("SELECT * FROM users WHERE login LIKE '"),_T(x), _T("' "))
#define GetListWherePassLike(x)                          GetListFromQuery(_T("SELECT * FROM users WHERE pass LIKE '"),_T(x), _T("' "))
#define GetListWhereTypeLike(x)                          GetListFromQuery(_T("SELECT * FROM users WHERE type LIKE '"),_T(x), _T("' "))
#define GetListWhereInstalerIDLike(x)                          GetListFromQuery(_T("SELECT * FROM users WHERE instalerID LIKE '"),_T(x), _T("' "))
#define GetListWhereNameLike(x)                          GetListFromQuery(_T("SELECT * FROM users WHERE name LIKE '"),_T(x), _T("' "))
#define GetListWhereTelcLike(x)                          GetListFromQuery(_T("SELECT * FROM users WHERE telc LIKE '"),_T(x), _T("' "))

#define GetListFrameWhereLoginExactly(x,y)                GetListFromQuery(_T("SELECT * FROM users WHERE login = '"),_T(x),_T("' "),y)
#define GetListFrameWherePassExactly(x,y)                GetListFromQuery(_T("SELECT * FROM users WHERE pass = '"),_T(x),_T("' "),y)
#define GetListFrameWhereTypeExactly(x,y)                GetListFromQuery(_T("SELECT * FROM users WHERE type = '"),_T(x),_T("' "),y)
#define GetListFrameWhereInstalerIDExactly(x,y)                GetListFromQuery(_T("SELECT * FROM users WHERE instalerID = '"),_T(x),_T("' "),y)
#define GetListFrameWhereNameExactly(x,y)                GetListFromQuery(_T("SELECT * FROM users WHERE name = '"),_T(x),_T("' "),y)
#define GetListFrameWhereTelcExactly(x,y)                GetListFromQuery(_T("SELECT * FROM users WHERE telc = '"),_T(x),_T("' "),y)

#define GetListFrameWhereLoginLike(x,y)                   GetListFromQuery(_T("SELECT * FROM users WHERE login LIKE '"),_T(x), _T("' "),y)
#define GetListFrameWherePassLike(x,y)                   GetListFromQuery(_T("SELECT * FROM users WHERE pass LIKE '"),_T(x), _T("' "),y)
#define GetListFrameWhereTypeLike(x,y)                   GetListFromQuery(_T("SELECT * FROM users WHERE type LIKE '"),_T(x), _T("' "),y)
#define GetListFrameWhereInstalerIDLike(x,y)                   GetListFromQuery(_T("SELECT * FROM users WHERE instalerID LIKE '"),_T(x), _T("' "),y)
#define GetListFrameWhereNameLike(x,y)                   GetListFromQuery(_T("SELECT * FROM users WHERE name LIKE '"),_T(x), _T("' "),y)
#define GetListFrameWhereTelcLike(x,y)                   GetListFromQuery(_T("SELECT * FROM users WHERE telc LIKE '"),_T(x), _T("' "),y)


/**
 * UPDATE STATEMENTS
 */

//FREE WHERE
#define UpdateRecordsWhere(x,y)                             UpdateRecordsQueryWhere(_T(x),_T(""),_T(""),y)

//UPDATE BY ID
#define UpdateRecordWhereID(x,y)                            UpdateRecordsQueryWhere(_T(" ID = "),_T(x),_T(" "),y)



#define UpdateRecordsWhereLoginExactly(x,y)                UpdateRecordsQueryWhere(_T(" login = '"),_T(x),_T("' "),y)
#define UpdateRecordsWherePassExactly(x,y)                UpdateRecordsQueryWhere(_T(" pass = '"),_T(x),_T("' "),y)
#define UpdateRecordsWhereTypeExactly(x,y)                UpdateRecordsQueryWhere(_T(" type = '"),_T(x),_T("' "),y)
#define UpdateRecordsWhereInstalerIDExactly(x,y)                UpdateRecordsQueryWhere(_T(" instalerID = '"),_T(x),_T("' "),y)
#define UpdateRecordsWhereNameExactly(x,y)                UpdateRecordsQueryWhere(_T(" name = '"),_T(x),_T("' "),y)
#define UpdateRecordsWhereTelcExactly(x,y)                UpdateRecordsQueryWhere(_T(" telc = '"),_T(x),_T("' "),y)

#define UpdateRecordsWhereLoginLike(x,y)                   UpdateRecordsQueryWhere(_T(" login LIKE '"),_T(x),_T("' "),y)
#define UpdateRecordsWherePassLike(x,y)                   UpdateRecordsQueryWhere(_T(" pass LIKE '"),_T(x),_T("' "),y)
#define UpdateRecordsWhereTypeLike(x,y)                   UpdateRecordsQueryWhere(_T(" type LIKE '"),_T(x),_T("' "),y)
#define UpdateRecordsWhereInstalerIDLike(x,y)                   UpdateRecordsQueryWhere(_T(" instalerID LIKE '"),_T(x),_T("' "),y)
#define UpdateRecordsWhereNameLike(x,y)                   UpdateRecordsQueryWhere(_T(" name LIKE '"),_T(x),_T("' "),y)
#define UpdateRecordsWhereTelcLike(x,y)                   UpdateRecordsQueryWhere(_T(" telc LIKE '"),_T(x),_T("' "),y)


/**
 * DELETE STATEMENTS
 */

//FREE WHERE
#define DeleteRecordsWhere(x)                              DeleteRecordsQueryWhere(_T(x),_T(""),_T(""))

//DELETE BY ID
#define DeleteRecordWhereID(x)                             DeleteRecordsQueryWhere(_T(" ID = "),_T(x),_T(" "))


#define DeleteRecordsWhereLoginExactly(x)                 DeleteRecordsQueryWhere(_T(" login = '"),_T(x),_T("' "))
#define DeleteRecordsWherePassExactly(x)                 DeleteRecordsQueryWhere(_T(" pass = '"),_T(x),_T("' "))
#define DeleteRecordsWhereTypeExactly(x)                 DeleteRecordsQueryWhere(_T(" type = '"),_T(x),_T("' "))
#define DeleteRecordsWhereInstalerIDExactly(x)                 DeleteRecordsQueryWhere(_T(" instalerID = '"),_T(x),_T("' "))
#define DeleteRecordsWhereNameExactly(x)                 DeleteRecordsQueryWhere(_T(" name = '"),_T(x),_T("' "))
#define DeleteRecordsWhereTelcExactly(x)                 DeleteRecordsQueryWhere(_T(" telc = '"),_T(x),_T("' "))

#define DeleteRecordsWhereLoginLike(x)                    DeleteRecordsQueryWhere(_T(" login LIKE '"),_T(x),_T("' "))
#define DeleteRecordsWherePassLike(x)                    DeleteRecordsQueryWhere(_T(" pass LIKE '"),_T(x),_T("' "))
#define DeleteRecordsWhereTypeLike(x)                    DeleteRecordsQueryWhere(_T(" type LIKE '"),_T(x),_T("' "))
#define DeleteRecordsWhereInstalerIDLike(x)                    DeleteRecordsQueryWhere(_T(" instalerID LIKE '"),_T(x),_T("' "))
#define DeleteRecordsWhereNameLike(x)                    DeleteRecordsQueryWhere(_T(" name LIKE '"),_T(x),_T("' "))
#define DeleteRecordsWhereTelcLike(x)                    DeleteRecordsQueryWhere(_T(" telc LIKE '"),_T(x),_T("' "))


typedef struct {

  //FIX MEMBERS
  int ID;
  wxString query;

  //FIELDS IN TABLE
  wxString login;
  wxString pass;
  int type;
  wxString instalerID;
  wxString name;
  wxString telc;


}UsersRecord;


class BridgeUsers
{
    public:
        BridgeUsers(const wxString dbPath= _T("C:UsersbitehackCBProjectsClasSQLbinwxlogdb.1.s3db"))
        {m_dbPath = dbPath; }
        ~BridgeUsers();

        //TRANSPORT METHODS
        wxString GetDBpath(void){ return m_dbPath; };
        void SetDBpath(wxString value){m_dbPath = value; }

        //SQL GENERATE METHODS
        wxSQLite3Database* OpenDB(void);
        wxString InsertRecordQuery(UsersRecord record);
        wxString InsertRecordsQuery(UsersList records);
        UsersList GetListFromQuery(const wxString& prequery,
                                     const wxString& query,
                                     const wxString& postquery,
                                     int limit=DEFAULT_QUERY_LIMIT);
        wxString UpdateRecordsQueryWhere(const wxString& prequery,
                                     const wxString& query,
                                     const wxString& postquery,
                                     UsersRecord record);
        wxString DeleteRecordsQueryWhere(const wxString& prequery,
                                     const wxString& query,
                                     const wxString& postquery);



    private:
        wxString m_dbPath;
};


#endif // BRIDGEUSERS_H
