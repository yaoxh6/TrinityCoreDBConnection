/*
 * This file is part of the TrinityCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "TestDatabase.h"
#include "../MySQLPreparedStatement.h"

void TestDatabaseConnection::DoPrepareStatements()
{
    if (!m_reconnecting)
        m_stmts.resize(MAX_TESTDATABASE_STATEMENTS);
    PrepareStatement(SAKILA_SEL_ACTOR_INFO, "select id,name,phone from employee where id=?", CONNECTION_SYNCH);
    PrepareStatement(SAKILA_SEL_ACTOR_INFO_ASYNC, "select id,name,phone from employee where id=?", CONNECTION_ASYNC);
}

TestDatabaseConnection::TestDatabaseConnection(MySQLConnectionInfo& connInfo) : MySQLConnection(connInfo)
{
}

TestDatabaseConnection::TestDatabaseConnection(ProducerConsumerQueue<SQLOperation*>* q, MySQLConnectionInfo& connInfo) : MySQLConnection(q, connInfo)
{
}

TestDatabaseConnection::~TestDatabaseConnection()
{
}
