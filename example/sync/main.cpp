

#include "DatabaseEnv.h"
#include "DatabaseLoader.h"
#include "DatabaseWorkerPool.h"
#include "DatabaseEnvFwd.h"
#include "Log.h"
#include "MySQLThreading.h"

int main() 
{
    MySQL::Library_Init();
    DatabaseLoader loader;
    loader.AddDatabase(TestDatabase, "192.168.56.101;3306;yaoxh6;yaoxh6;test_connect", 8, 2);
    if (!loader.Load()) {
        TC_LOG_ERROR("", "sakila connect error");
        return 1;
    }

    {
        auto result = TestDatabase.Query("select id,name,phone from employee where id=1");

        TC_LOG_INFO("", "id=%u,name=%s,phone=%d", (*result)[0].GetUInt8(),(*result)[1].GetString(),(*result)[2].GetUInt32());
    }
    {
        auto stmt = TestDatabase.GetPreparedStatement(SAKILA_SEL_ACTOR_INFO);
        stmt->setUInt8(0, 1);
        auto result = TestDatabase.Query(stmt);
        TC_LOG_INFO("", "actor_id=%u,first_name=%s,last_name=%d", (*result)[0].GetUInt8(),(*result)[1].GetString(),(*result)[2].GetUInt32());
    }
    

    TestDatabase.Close();
    MySQL::Library_End();
    return 0;
}