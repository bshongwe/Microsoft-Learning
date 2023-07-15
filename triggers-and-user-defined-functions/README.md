# Create triggers and user-defined functions

Azure Cosmos DB supports pretriggers and post-triggers. Pretriggers are executed before modifying a database item and post-triggers are executed after modifying a database item. Triggers aren't automatically executed, they must be specified for each database operation where you want them to execute. After you define a trigger, you should register it by using the Azure Cosmos DB SDKs.

For examples of how to register and call a trigger, see pretriggers and post-triggers.

# Pretriggers
The following example shows how a pretrigger is used to validate the properties of an Azure Cosmos item that is being created, it adds a timestamp property to a newly added item if it doesn't contain one.

Pretriggers can't have any input parameters. The request object in the trigger is used to manipulate the request message associated with the operation. In the previous example, the pretrigger is run when creating an Azure Cosmos item, and the request message body contains the item to be created in JSON format.

When triggers are registered, you can specify the operations that it can run with. This trigger should be created with a TriggerOperation value of TriggerOperation.Create, which means using the trigger in a replace operation isn't permitted.

# Post-triggers
The following example shows a post-trigger. This trigger queries for the metadata item and updates it with details about the newly created item.

One thing that is important to note is the transactional execution of triggers in Azure Cosmos DB. The post-trigger runs as part of the same transaction for the underlying item itself. An exception during the post-trigger execution fails the whole transaction. Anything committed is rolled back and an exception returned.

# User-defined functions
The following sample creates a UDF to calculate income tax for various income brackets. This user-defined function would then be used inside a query. For the purposes of this example assume there's a container called "Incomes" with properties as follows:
<code>{
   "name": "User One",
   "country": "USA",
   "income": 70000
}</code>


