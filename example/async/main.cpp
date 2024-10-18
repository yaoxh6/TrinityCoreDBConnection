
#include "AsyncCallbackProcessor.h"
#include "DatabaseEnv.h"
#include "DatabaseLoader.h"
#include "DatabaseWorkerPool.h"
#include "DatabaseEnvFwd.h"
#include "Log.h"
#include "MySQLThreading.h"

bool isStop = false;
QueryCallbackProcessor _queryProcessor;
void onGetRes(PreparedQueryResult result)
{
    if (result)
    {
        TC_LOG_INFO("", "onGetRes, actor_id=%u,first_name=%s,last_name=%d", (*result)[0].GetUInt8(),(*result)[1].GetString(),(*result)[2].GetUInt32());
    }
    return;
}

void onGetChainRes1(PreparedQueryResult result)
{
    if (result)
    {
        TC_LOG_INFO("", "onGetChainRes1, actor_id=%u,first_name=%s,last_name=%d", (*result)[0].GetUInt8(),(*result)[1].GetString(),(*result)[2].GetUInt32());
    }
    return;
}


void onGetChainRes2(PreparedQueryResult result)
{
    if (result)
    {
        TC_LOG_INFO("", "onGetChainRes2, actor_id=%u,first_name=%s,last_name=%d", (*result)[0].GetUInt8(),(*result)[1].GetString(),(*result)[2].GetUInt32());
    }
    isStop = true;
    return;
}

void WorldUpdateLoop() {
    while (!isStop)
    {
        _queryProcessor.ProcessReadyCallbacks();
    }   
}

int main() 
{
    MySQL::Library_Init();
    DatabaseLoader loader;
    loader.AddDatabase(TestDatabase, "192.168.56.101;3306;yaoxh6;yaoxh6;test_connect", 1, 1);
    if (!loader.Load()) {
        TC_LOG_ERROR("", "sakila connect error");
        return 1;
    }
    {
        auto stmt = TestDatabase.GetPreparedStatement(SAKILA_SEL_ACTOR_INFO_ASYNC);
        stmt->setUInt8(0, 1);
        _queryProcessor.AddCallback(TestDatabase.AsyncQuery(stmt).WithPreparedCallback([](PreparedQueryResult result)
        {
            onGetRes(std::move(result));
        }));
    }
    {
        auto stmt = TestDatabase.GetPreparedStatement(SAKILA_SEL_ACTOR_INFO_ASYNC);
        stmt->setUInt8(0, 1);
        _queryProcessor.AddCallback(TestDatabase.AsyncQuery(stmt)
        .WithChainingPreparedCallback([stmt](QueryCallback& queryCallback, PreparedQueryResult result)
        {
            onGetChainRes1(std::move(result));
            auto stmt = TestDatabase.GetPreparedStatement(SAKILA_SEL_ACTOR_INFO_ASYNC);
            stmt->setUInt8(0, 1);
            queryCallback.SetNextQuery(TestDatabase.AsyncQuery(stmt));
        }).WithPreparedCallback([](PreparedQueryResult result){
            onGetChainRes2(std::move(result));
        }));
    }
    WorldUpdateLoop();
    TestDatabase.Close();
    MySQL::Library_End();
    return 0;
}